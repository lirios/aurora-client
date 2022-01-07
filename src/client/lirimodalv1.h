// SPDX-FileCopyrightText: 2020-2022 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef AURORA_CLIENT_LIRIMODALV1_H
#define AURORA_CLIENT_LIRIMODALV1_H

#include <QWaylandClientExtension>

#include <LiriAuroraClient/liriauroraclientglobal.h>

namespace Aurora {

namespace Client {

class LiriModalV1Private;

class LIRIAURORACLIENT_EXPORT LiriModalV1
        : public QWaylandClientExtensionTemplate<LiriModalV1>
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(LiriModalV1)
    Q_PROPERTY(bool grabbed READ isGrabbed NOTIFY grabbedChanged)
public:
    LiriModalV1();
    ~LiriModalV1();

    bool isGrabbed() const;

    Q_INVOKABLE void grab();
    Q_INVOKABLE void close();

    void init(struct ::wl_registry *registry, int id, int version);

    static const struct ::wl_interface *interface();

Q_SIGNALS:
    void grabbedChanged();

private:
    QScopedPointer<LiriModalV1Private> const d_ptr;
};

} // namespace Client

} // namespace Aurora

#endif // AURORA_CLIENT_LIRIMODALV1_H
