// SPDX-FileCopyrightText: 2019-2021 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef AURORA_CLIENT_UTILS_P_H
#define AURORA_CLIENT_UTILS_P_H

#include <QGuiApplication>
#include <QtGui/qpa/qplatformnativeinterface.h>
#include <QWindow>
#include <QScreen>

#include <wayland-client.h>

static inline struct ::wl_seat *getWlSeat()
{
    void *seat = QGuiApplication::platformNativeInterface()->nativeResourceForIntegration("wl_seat");
    return static_cast<struct ::wl_seat *>(seat);
}

static inline struct ::wl_surface *getWlSurface(QWindow *window)
{
    if (!window)
        return nullptr;
    void *surface = QGuiApplication::platformNativeInterface()->nativeResourceForWindow("surface", window);
    return static_cast<struct ::wl_surface *>(surface);
}

static inline struct ::wl_output *getWlOutput(QScreen *screen)
{
    if (!screen)
        return nullptr;
    void *output = QGuiApplication::platformNativeInterface()->nativeResourceForScreen("output", screen);
    return static_cast<struct ::wl_output *>(output);
}

static inline QScreen *getScreen(struct ::wl_output *output)
{
    const auto screens = QGuiApplication::screens();
    for (auto screen : screens) {
        if (getWlOutput(screen) == output)
            return screen;
    }

    return nullptr;
}

#endif // AURORA_CLIENT_UTILS_P_H
