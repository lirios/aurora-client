// SPDX-FileCopyrightText: 2020 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef AURORA_CLIENT_QUICKLIRISHORTCUTV1_H
#define AURORA_CLIENT_QUICKLIRISHORTCUTV1_H

#include <QQmlParserStatus>

#include <LiriAuroraClient/LiriShortcutV1>

namespace Aurora {

namespace Client {

class LiriShortcutQml : public LiriShortcutV1, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
public:
    LiriShortcutQml();

protected:
    void classBegin() override {}
    void componentComplete() override;
};

} // namespace Client

} // namespace Aurora

#endif // AURORA_CLIENT_QUICKLIRISHORTCUTV1_H
