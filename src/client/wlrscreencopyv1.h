// SPDX-FileCopyrightText: 2019-2022 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef AURORA_CLIENT_WLRSCREENCOPYV1_H
#define AURORA_CLIENT_WLRSCREENCOPYV1_H

#include <QWaylandClientExtension>

#include <LiriAuroraClient/liriauroraclientglobal.h>

#include <wayland-client.h>

QT_FORWARD_DECLARE_CLASS(QScreen)

namespace Aurora {

namespace Client {

class WlrScreencopyManagerV1Private;
class WlrScreencopyFrameV1;
class WlrScreencopyFrameV1Private;

class LIRIAURORACLIENT_EXPORT WlrScreencopyManagerV1
        : public QWaylandClientExtensionTemplate<WlrScreencopyManagerV1>
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(WlrScreencopyManagerV1)
public:
    explicit WlrScreencopyManagerV1();
    ~WlrScreencopyManagerV1();

    Q_INVOKABLE Aurora::Client::WlrScreencopyFrameV1 *captureScreen(QScreen *screen, bool overlayCursor = false);
    Q_INVOKABLE Aurora::Client::WlrScreencopyFrameV1 *captureScreenRegion(QScreen *screen, const QRect &region,
                                                                          bool overlayCursor = false);

    void init(struct ::wl_registry *registry, int id, int version);

    static const struct ::wl_interface *interface();

private:
    QScopedPointer<WlrScreencopyManagerV1Private> const d_ptr;
};

class LIRIAURORACLIENT_EXPORT WlrScreencopyFrameV1 : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(WlrScreencopyFrameV1)
    Q_PROPERTY(QScreen *screen READ screen CONSTANT)
public:
    ~WlrScreencopyFrameV1();

    QScreen *screen() const;

Q_SIGNALS:
    void copied(const QImage &image);
    void failed();

private:
    QScopedPointer<WlrScreencopyFrameV1Private> const d_ptr;

    explicit WlrScreencopyFrameV1(QObject *parent = nullptr);

    friend class WlrScreencopyManagerV1;
};

} // namespace Client

} // namespace Aurora

#endif // AURORA_CLIENT_WLRSCREENCOPYV1_H
