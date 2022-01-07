// SPDX-FileCopyrightText: 2020-2022 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "lirimodalv1_p.h"
#include "utils_p.h"

namespace Aurora {

namespace Client {

/*
 * LiriModalPrivate
 */

LiriModalV1Private::LiriModalV1Private(LiriModalV1 *self)
    : PrivateClient::zliri_modal_manager_v1()
    , q_ptr(self)
{
}

LiriModalV1Private::~LiriModalV1Private()
{
    qDeleteAll(grabs);
}

void LiriModalV1Private::removeGrab(LiriModalGrabV1 *grab)
{
    Q_Q(LiriModalV1);

    if (grabs.removeOne(grab)) {
        Q_EMIT q->grabbedChanged();
        delete grab;
    }
}

void LiriModalV1Private::removeAllGrabs()
{
    Q_Q(LiriModalV1);

    bool changed = false;

    auto it = grabs.begin();
    while (it != grabs.end()) {
        delete (*it);
        it = grabs.erase(it);
        changed = true;
    }

    if (changed)
        Q_EMIT q->grabbedChanged();
}

/*
 * LiriModalGrab
 */

LiriModalGrabV1::LiriModalGrabV1(LiriModalV1 *modal)
    : manager(modal)
{
}

LiriModalGrabV1::~LiriModalGrabV1()
{
    destroy();
}

void LiriModalGrabV1::zliri_modal_v1_done()
{
    LiriModalV1Private::get(manager)->removeGrab(this);
}

/*
 * LiriModal
 */

LiriModalV1::LiriModalV1()
    : QWaylandClientExtensionTemplate<LiriModalV1>(1)
    , d_ptr(new LiriModalV1Private(this))
{
}

LiriModalV1::~LiriModalV1()
{
}

void LiriModalV1::grab()
{
    Q_D(LiriModalV1);

    auto *modalGrab = new LiriModalGrabV1(this);
    modalGrab->init(d->grab(getWlSeat()));
    d->grabs.append(modalGrab);
}

void LiriModalV1::close()
{
    Q_D(LiriModalV1);
    d->removeAllGrabs();
}

void LiriModalV1::init(struct ::wl_registry *registry, int id, int version)
{
    Q_D(LiriModalV1);
    d->init(registry, id, version);
}

const struct ::wl_interface *LiriModalV1::interface()
{
    return LiriModalV1Private::interface();
}

bool LiriModalV1::isGrabbed() const
{
    Q_D(const LiriModalV1);
    return d->grabs.size() > 0;
}

} // namespace Client

} // namespace Aurora
