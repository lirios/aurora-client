// SPDX-FileCopyrightText: 2020-2022 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "liricolorpickerv1_p.h"
#include "utils_p.h"

#include <wayland-client.h>

namespace Aurora {

namespace Client {

/*
 * LiriColorPickerManagerPrivate
 */

LiriColorPickerManagerV1Private::~LiriColorPickerManagerV1Private()
{
    qDeleteAll(pickers);
}

/*
 * LiriColorPicker
 */

LiriColorPickerV1::LiriColorPickerV1(struct ::zliri_color_picker_v1 *object, QObject *parent)
    : QObject(parent)
    , PrivateClient::zliri_color_picker_v1(object)
{
}

LiriColorPickerV1::~LiriColorPickerV1()
{
    LiriColorPickerManagerV1Private::get(manager)->pickers.removeOne(this);
    destroy();
}

void LiriColorPickerV1::zliri_color_picker_v1_picked(uint32_t value)
{
    auto rgba = static_cast<QRgb>(value);
    Q_EMIT manager->colorPicked(QColor::fromRgba(rgba));

    deleteLater();
}

/*
 * LiriColorPickerManager
 */

LiriColorPickerManagerV1::LiriColorPickerManagerV1()
    : QWaylandClientExtensionTemplate<LiriColorPickerManagerV1>(1)
    , d_ptr(new LiriColorPickerManagerV1Private)
{
}

LiriColorPickerManagerV1::~LiriColorPickerManagerV1()
{
}

void LiriColorPickerManagerV1::pickAtLocation(QScreen *screen, const QPoint &location)
{
    Q_D(LiriColorPickerManagerV1);

    auto *object = d->pick_at_location(getWlOutput(screen), location.x(), location.y());
    auto *picker = new LiriColorPickerV1(object, this);
    picker->manager = this;
    d->pickers.append(picker);
}

void LiriColorPickerManagerV1::pickInteractively()
{
    Q_D(LiriColorPickerManagerV1);

    auto *object = d->pick_interactively(getWlSeat());
    auto *picker = new LiriColorPickerV1(object, this);
    picker->manager = this;
    d->pickers.append(picker);
}

void LiriColorPickerManagerV1::init(struct ::wl_registry *registry, int id, int version)
{
    Q_D(LiriColorPickerManagerV1);
    d->init(registry, id, version);
}

const struct ::wl_interface *LiriColorPickerManagerV1::interface()
{
    return LiriColorPickerManagerV1Private::interface();
}

} // namespace Client

} // namespace Aurora
