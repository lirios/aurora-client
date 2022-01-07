// SPDX-FileCopyrightText: 2020-2022 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef AURORA_CLIENT_LIRIMODALV1_P_H
#define AURORA_CLIENT_LIRIMODALV1_P_H

#include <LiriAuroraClient/LiriModalV1>
#include <LiriAuroraClient/private/aurora-client-liri-shell-unstable-v1.h>

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

class LIRIAURORACLIENT_EXPORT LiriModalGrabV1
        : public PrivateClient::zliri_modal_v1
{
public:
    LiriModalGrabV1(LiriModalV1 *modal);
    ~LiriModalGrabV1();

    LiriModalV1 *manager = nullptr;

protected:
    void zliri_modal_v1_done() override;
};

class LIRIAURORACLIENT_EXPORT LiriModalV1Private
        : public PrivateClient::zliri_modal_manager_v1
{
    Q_DECLARE_PUBLIC(LiriModalV1)
public:
    LiriModalV1Private(LiriModalV1 *self);
    ~LiriModalV1Private();

    QVector<LiriModalGrabV1 *> grabs;

    void removeGrab(LiriModalGrabV1 *grab);
    void removeAllGrabs();

    static LiriModalV1Private *get(LiriModalV1 *modal) { return modal->d_func(); }

protected:
    LiriModalV1 *q_ptr = nullptr;
};

} // namespace Client

} // namespace Aurora

#endif // AURORA_CLIENT_LIRIMODALV1_P_H
