// SPDX-FileCopyrightText: 2020-2022 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef AURORA_CLIENT_LIRICOLORPICKERV1_H
#define AURORA_CLIENT_LIRICOLORPICKERV1_H

#include <QColor>
#include <QWaylandClientExtension>

#include <LiriAuroraClient/liriauroraclientglobal.h>

#include <wayland-client.h>

QT_FORWARD_DECLARE_CLASS(QScreen)

namespace Aurora {

namespace Client {

class LiriColorPickerManagerV1Private;

class LIRIAURORACLIENT_EXPORT LiriColorPickerManagerV1
        : public QWaylandClientExtensionTemplate<LiriColorPickerManagerV1>
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(LiriColorPickerManagerV1)
public:
    LiriColorPickerManagerV1();
    ~LiriColorPickerManagerV1();

    Q_INVOKABLE void pickAtLocation(QScreen *screen, const QPoint &location);
    Q_INVOKABLE void pickInteractively();

    void init(struct ::wl_registry *registry, int id, int version);

    static const struct ::wl_interface *interface();

Q_SIGNALS:
    void colorPicked(const QColor &color);

private:
    QScopedPointer<LiriColorPickerManagerV1Private> const d_ptr;
};

} // namespace Client

} // namespace Aurora

#endif // AURORA_CLIENT_LIRICOLORPICKERV1_H
