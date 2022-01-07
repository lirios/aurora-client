/****************************************************************************
 * This file is part of Liri.
 *
 * Copyright (C) 2019 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:LGPLv3+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include <QtQml>

#include <LiriAuroraClient/LiriColorPickerManagerV1>
#include <LiriAuroraClient/LiriLockScreenV1>
#include <LiriAuroraClient/LiriModalV1>
#include <LiriAuroraClient/LiriShellV1>
#include <LiriAuroraClient/WlrExportDmabufManagerV1>
#include <LiriAuroraClient/WlrForeignToplevelManagerV1>
#include <LiriAuroraClient/WlrOutputManagerV1>
#include <LiriAuroraClient/WlrScreencopyManagerV1>

#include "lirishortcutqml.h"
#include "wlrlayersurfacev1qml.h"
#include "utils.h"

using namespace Aurora::Client;

class WaylandClientPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")
public:
    void registerTypes(const char *uri)
    {
        // @uri Liri.WaylandClient
        Q_ASSERT(QLatin1String(uri) == QLatin1String("Aurora.Client"));

        const int versionMajor = 1;
        const int versionMinor = 0;

        qmlRegisterType<LiriColorPickerManagerV1>(uri, versionMajor, versionMinor, "LiriColorPickerManagerV1");
        qmlRegisterType<LiriLockScreenV1>(uri, versionMajor, versionMinor, "LiriLockScreenV1");
        qmlRegisterType<LiriModalV1>(uri, versionMajor, versionMinor, "LiriModalV1");
        qmlRegisterType<LiriShellV1>(uri, versionMajor, versionMinor, "LiriShellV1");
        qmlRegisterType<LiriShortcutQml>(uri, versionMajor, versionMinor, "LiriShortcutV1");
        qmlRegisterType<LiriOsdV1>(uri, versionMajor, versionMinor, "LiriOsdV1");

        qmlRegisterType<WlrExportDmabufManagerV1>(uri, versionMajor, versionMinor, "WlrExportDmabufManagerV1");
        qmlRegisterUncreatableType<WlrExportDmabufFrameV1>(uri, versionMajor, versionMinor, "WlrExportDmabufFrameV1",
                                                           QStringLiteral("Cannot create a WlrExportDmabufFrameV1 instance"));

        qmlRegisterType<WlrLayerSurfaceV1Qml>(uri, versionMajor, versionMinor, "WlrLayerSurfaceV1");

        qmlRegisterType<WlrOutputManagerV1>(uri, versionMajor, versionMinor, "WlrOutputManagerV1");
        qmlRegisterUncreatableType<WlrOutputHeadV1>(uri, versionMajor, versionMinor, "WlrOutputHeadV1",
                                                    QStringLiteral("Cannot create a WlrOutputHeadV1 instance"));
        qmlRegisterUncreatableType<WlrOutputModeV1>(uri, versionMajor, versionMinor, "WlrOutputModeV1",
                                                    QStringLiteral("Cannot create a WlrOutputModeV1 instance"));
        qmlRegisterUncreatableType<WlrOutputConfigurationV1>(uri, versionMajor, versionMinor, "WlrOutputConfigurationV1",
                                                             QStringLiteral("Cannot create a WlrOutputConfigurationV1 instance"));
        qmlRegisterUncreatableType<WlrOutputConfigurationHeadV1>(uri, versionMajor, versionMinor, "WlrOutputConfigurationHeadV1",
                                                                 QStringLiteral("Cannot create a WlrOutputConfigurationHeadV1 instance"));

        qmlRegisterType<WlrScreencopyManagerV1>(uri, versionMajor, versionMinor, "WlrScreencopyManagerV1");
        qmlRegisterUncreatableType<WlrScreencopyFrameV1>(uri, versionMajor, versionMinor, "WlrScreencopyFrameV1",
                                                         QStringLiteral("Cannot create a WlrScreencopyFrameV1 instance"));
    }
};

#include "plugin.moc"
