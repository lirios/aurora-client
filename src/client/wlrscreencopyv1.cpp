// SPDX-FileCopyrightText: 2019-2022 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "utils_p.h"
#include "wlrscreencopyv1_p.h"

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

namespace Aurora {

namespace Client {

Q_LOGGING_CATEGORY(gLcWlrScreencopyV1, "aurora.client.wlrscreencopyv1", QtInfoMsg)

static inline QImage::Format fromWaylandShmFormat(wl_shm_format format)
{
    switch (format) {
    case WL_SHM_FORMAT_XRGB8888: return QImage::Format_RGB32;
    case WL_SHM_FORMAT_ARGB8888: return QImage::Format_ARGB32_Premultiplied;
    case WL_SHM_FORMAT_RGB565: return QImage::Format_RGB16;
    case WL_SHM_FORMAT_XRGB1555: return QImage::Format_RGB555;
    case WL_SHM_FORMAT_RGB888: return QImage::Format_RGB888;
    case WL_SHM_FORMAT_XRGB4444: return QImage::Format_RGB444;
    case WL_SHM_FORMAT_ARGB4444: return QImage::Format_ARGB4444_Premultiplied;
    case WL_SHM_FORMAT_XBGR8888: return QImage::Format_RGBX8888;
    case WL_SHM_FORMAT_ABGR8888: return QImage::Format_RGBA8888_Premultiplied;
    case WL_SHM_FORMAT_XBGR2101010: return QImage::Format_BGR30;
    case WL_SHM_FORMAT_ABGR2101010: return QImage::Format_A2BGR30_Premultiplied;
    case WL_SHM_FORMAT_XRGB2101010: return QImage::Format_RGB30;
    case WL_SHM_FORMAT_ARGB2101010: return QImage::Format_A2RGB30_Premultiplied;
    case WL_SHM_FORMAT_C8: return QImage::Format_Alpha8;
    default: return QImage::Format_Invalid;
    }
}

/*
 * WlrScreencopyManagerV1Private
 */

WlrScreencopyManagerV1Private::WlrScreencopyManagerV1Private()
    : PrivateClient::zwlr_screencopy_manager_v1()
{
    QPlatformNativeInterface *native = QGuiApplication::platformNativeInterface();
    auto *display = static_cast<wl_display *>(native->nativeResourceForIntegration("display"));
    auto *registry = wl_display_get_registry(display);

    static const wl_registry_listener registryListener = {
        global,
        globalRemove
    };
    wl_registry_add_listener(registry, &registryListener, this);
}

WlrScreencopyManagerV1Private::~WlrScreencopyManagerV1Private()
{
    destroy();
}

void WlrScreencopyManagerV1Private::global(void *data, struct ::wl_registry *registry, uint32_t id, const char *interface, uint32_t version)
{
    Q_UNUSED(registry)

    WlrScreencopyManagerV1Private *that = static_cast<WlrScreencopyManagerV1Private *>(data);

    if (strcmp(interface, "wl_shm") == 0)
        that->shm = static_cast<wl_shm *>(wl_registry_bind(registry, id, &wl_shm_interface, qMin<uint32_t>(version, 1)));
}

void WlrScreencopyManagerV1Private::globalRemove(void *data, struct ::wl_registry *registry, uint32_t id)
{
    Q_UNUSED(data)
    Q_UNUSED(registry)
    Q_UNUSED(id)
}

/*
 * WlrScreencopyManagerV1
 */

WlrScreencopyManagerV1::WlrScreencopyManagerV1()
    : QWaylandClientExtensionTemplate<WlrScreencopyManagerV1>(2)
    , d_ptr(new WlrScreencopyManagerV1Private)
{
}

WlrScreencopyManagerV1::~WlrScreencopyManagerV1()
{
}

WlrScreencopyFrameV1 *WlrScreencopyManagerV1::captureScreen(QScreen *screen, bool overlayCursor)
{
    Q_D(WlrScreencopyManagerV1);

    auto *object =
            d->capture_output(overlayCursor ? 1 : 0, getWlOutput(screen));
    auto *frame = new WlrScreencopyFrameV1(this);
    auto *framePriv = WlrScreencopyFrameV1Private::get(frame);
    framePriv->parent = d;
    framePriv->screen = screen;
    framePriv->init(object);
    return frame;
}

WlrScreencopyFrameV1 *WlrScreencopyManagerV1::captureScreenRegion(QScreen *screen, const QRect &region, bool overlayCursor)
{
    Q_D(WlrScreencopyManagerV1);

    auto *object =
            d->capture_output_region(overlayCursor ? 1 : 0, getWlOutput(screen),
                                     region.x(), region.y(), region.width(), region.height());
    auto *frame = new WlrScreencopyFrameV1(this);
    auto *framePriv = WlrScreencopyFrameV1Private::get(frame);
    framePriv->parent = d;
    framePriv->screen = screen;
    framePriv->init(object);
    return frame;
}

void WlrScreencopyManagerV1::init(struct ::wl_registry *registry, int id, int version)
{
    Q_D(WlrScreencopyManagerV1);
    d->init(registry, id, version);
}

const struct ::wl_interface *WlrScreencopyManagerV1::interface()
{
    return WlrScreencopyManagerV1Private::interface();
}

/*
 * WlrScreencopyFrameV1Private
 */

WlrScreencopyFrameV1Private::WlrScreencopyFrameV1Private(WlrScreencopyFrameV1 *self)
    : PrivateClient::zwlr_screencopy_frame_v1()
    , q_ptr(self)
{
}

WlrScreencopyFrameV1Private::~WlrScreencopyFrameV1Private()
{
    if (buffer.data)
        munmap(static_cast<void *>(buffer.data), buffer.stride * buffer.size.height());
    if (buffer.shmBuffer)
        wl_buffer_destroy(buffer.shmBuffer);

    destroy();
}

wl_buffer *WlrScreencopyFrameV1Private::createShmBuffer(quint32 format, const QSize &size, quint32 stride, uchar **out)
{
    int bytesSize = stride * size.height();

    const char name[] = "/aurora-client-screencopy";
    int fd = shm_open(name, O_RDWR | O_CREAT | O_EXCL, 0);
    if (fd < 0) {
        qCWarning(gLcWlrScreencopyV1, "Failed to open shared memory: %s", strerror(errno));
        return nullptr;
    }
    shm_unlink(name);

    int ret;
    while ((ret = ftruncate(fd, bytesSize)) == EINTR) {
        // no-op
    }
    if (ret < 0) {
        close(fd);
        qCWarning(gLcWlrScreencopyV1, "Failed to set shared memory size: %s", strerror(errno));
        return nullptr;
    }

    uchar *data = static_cast<uchar *>(mmap(nullptr, bytesSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
    if (data == (uchar *)MAP_FAILED) {
        close(fd);
        qCWarning(gLcWlrScreencopyV1, "Failed to map shared memory: %s", strerror(errno));
        return nullptr;
    }

    auto *pool = wl_shm_create_pool(parent->shm, fd, bytesSize);
    close(fd);
    auto *shmBuffer = wl_shm_pool_create_buffer(pool, 0, size.width(), size.height(), stride, format);
    wl_shm_pool_destroy(pool);

    *out = data;
    return shmBuffer;
}

void WlrScreencopyFrameV1Private::zwlr_screencopy_frame_v1_buffer(uint32_t format, uint32_t width, uint32_t height, uint32_t stride)
{
    Q_Q(WlrScreencopyFrameV1);

    buffer.format = format;
    buffer.size = QSize(width, height);
    buffer.stride = stride;
    buffer.shmBuffer = createShmBuffer(format, buffer.size, stride, &buffer.data);
    if (!buffer.shmBuffer) {
        qCWarning(gLcWlrScreencopyV1, "Failed to create buffer");
        emit q->failed();
        return;
    }

    copy(buffer.shmBuffer);
}

void WlrScreencopyFrameV1Private::zwlr_screencopy_frame_v1_flags(uint32_t flags)
{
    yInverted = flags & flags_y_invert;
}

void WlrScreencopyFrameV1Private::zwlr_screencopy_frame_v1_ready(uint32_t tv_sec_hi, uint32_t tv_sec_lo, uint32_t tv_nsec)
{
    Q_UNUSED(tv_sec_hi)
    Q_UNUSED(tv_sec_lo)
    Q_UNUSED(tv_nsec)

    Q_Q(WlrScreencopyFrameV1);

    QImage::Format format = fromWaylandShmFormat(static_cast<wl_shm_format>(buffer.format));
    QImage image(buffer.data, buffer.size.width(), buffer.size.height(), buffer.stride, format);
    if (yInverted)
        image = image.mirrored(false, true);

    emit q->copied(image);
}

void WlrScreencopyFrameV1Private::zwlr_screencopy_frame_v1_failed()
{
    Q_Q(WlrScreencopyFrameV1);
    emit q->failed();
}

void WlrScreencopyFrameV1Private::zwlr_screencopy_frame_v1_damage(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    Q_UNUSED(x)
    Q_UNUSED(y)
    Q_UNUSED(width)
    Q_UNUSED(height)
}

/*
 * WlrScreencopyFrameV1
 */

WlrScreencopyFrameV1::WlrScreencopyFrameV1(QObject *parent)
    : QObject(parent)
    , d_ptr(new WlrScreencopyFrameV1Private(this))
{
}

WlrScreencopyFrameV1::~WlrScreencopyFrameV1()
{
}

QScreen *WlrScreencopyFrameV1::screen() const
{
    Q_D(const WlrScreencopyFrameV1);
    return d->screen;
}

} // namespace Client

} // namespace Aurora
