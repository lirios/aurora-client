// SPDX-FileCopyrightText: 2021-2022 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef AURORA_CLIENT_LIRILOCKSCREENV1_H
#define AURORA_CLIENT_LIRILOCKSCREENV1_H

#include <QWaylandClientExtension>

#include <LiriAuroraClient/liriauroraclientglobal.h>

namespace Aurora {

namespace Client {

class LiriLockScreenV1Private;

class LIRIAURORACLIENT_EXPORT LiriLockScreenV1
        : public QWaylandClientExtensionTemplate<LiriLockScreenV1>
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(LiriLockScreenV1)
public:
    LiriLockScreenV1();
    ~LiriLockScreenV1();

    Q_INVOKABLE void unlock();

    void init(struct ::wl_registry *registry, int id, int version);

    static const struct ::wl_interface *interface();

Q_SIGNALS:
    void lockRequested();

private:
    QScopedPointer<LiriLockScreenV1Private> const d_ptr;
};

} // namespace Client

} // namespace Aurora

#endif // AURORA_CLIENT_LIRILOCKSCREENV1_H
