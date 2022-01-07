// SPDX-FileCopyrightText: 2021-2022 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef AURORA_CLIENT_LIRILOCKSCREENV1_P_H
#define AURORA_CLIENT_LIRILOCKSCREENV1_P_H

#include <LiriAuroraClient/LiriLockScreenV1>
#include <LiriAuroraClient/private/aurora-client-liri-lockscreen-unstable-v1.h>

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

class LIRIAURORACLIENT_EXPORT LiriLockScreenV1Handle
        : public PrivateClient::zliri_lockscreen_handle_v1
{
public:
    LiriLockScreenV1Handle() = default;
    ~LiriLockScreenV1Handle();

    LiriLockScreenV1 *manager = nullptr;

protected:
    void zliri_lockscreen_handle_v1_locked() override;
};

class LIRIAURORACLIENT_EXPORT LiriLockScreenV1Private
        : public PrivateClient::zliri_lockscreen_v1
{
    Q_DECLARE_PUBLIC(LiriLockScreenV1)
public:
    LiriLockScreenV1Private(LiriLockScreenV1 *self);
    ~LiriLockScreenV1Private();

    LiriLockScreenV1Handle *handle = nullptr;

protected:
    LiriLockScreenV1 *q_ptr = nullptr;
};

} // namespace Client

} // namespace Aurora

#endif // AURORA_CLIENT_LIRILOCKSCREENV1_P_H
