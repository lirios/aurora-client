// SPDX-FileCopyrightText: 2021-2022 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef AURORA_CLIENT_WLRLAYERSURFACEV1_P_H
#define AURORA_CLIENT_WLRLAYERSURFACEV1_P_H

#include <QLoggingCategory>

#include <LiriAuroraClient/WlrLayerSurfaceV1>

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Aurora API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

namespace Aurora {

namespace Client {

Q_DECLARE_LOGGING_CATEGORY(gLcWlrLayerShellV1)

class WlrLayerSurfaceV1Private
{
public:
    WlrLayerSurfaceV1Private() = default;

    bool initialized = false;
    bool setLayerEnabled = false;
    QWindow *window = nullptr;
    WlrLayerSurfaceV1::Layer layer = WlrLayerSurfaceV1::TopLayer;
    QString role = QStringLiteral("unknown");
    WlrLayerSurfaceV1::Anchors anchors;
    qint32 exclusiveZone = 0;
    QMargins margins;
    WlrLayerSurfaceV1::KeyboardInteractivity keyboardInteractivity = WlrLayerSurfaceV1::ExclusiveKeyboardInteractivity;
};

} // namespace Client

} // namespace Aurora

#endif // AURORA_CLIENT_WLRLAYERSURFACEV1_P_H
