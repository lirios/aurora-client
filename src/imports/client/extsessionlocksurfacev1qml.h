// SPDX-FileCopyrightText: 2022 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef EXTSESSIONLOCKSURFACEV1QML_H
#define EXTSESSIONLOCKSURFACEV1QML_H

#include <QQmlParserStatus>

#include <LiriAuroraClient/ExtSessionLockSurfaceV1>

using namespace Aurora::Client;

class ExtSessionLockSurfaceV1Qml
        : public ExtSessionLockSurfaceV1
        , public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
public:
    ExtSessionLockSurfaceV1Qml(QObject *parent = nullptr);

protected:
    void classBegin() override {}
    void componentComplete() override;
};

#endif // EXTSESSIONLOCKSURFACEV1QML_H
