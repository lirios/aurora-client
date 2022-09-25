// SPDX-FileCopyrightText: 2022 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef AURORA_CLIENT_EXTSESSIONLOCKSURFACEV1_P_H
#define AURORA_CLIENT_EXTSESSIONLOCKSURFACEV1_P_H

#include <QLoggingCategory>

#include <LiriAuroraClient/ExtSessionLockSurfaceV1>
namespace Aurora {

namespace Client {

Q_DECLARE_LOGGING_CATEGORY(gLcExtSessionLockSurfaceV1)

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

class ExtSessionLockSurfaceV1Private
{
public:
    ExtSessionLockSurfaceV1Private() = default;

    bool initialized = false;
    QWindow *window = nullptr;
};

} // namespace Client

} // namespace Aurora

#endif // AURORA_CLIENT_EXTSESSIONLOCKSURFACEV1_P_H
