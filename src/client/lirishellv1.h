// SPDX-FileCopyrightText: 2019-2022 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef AURORA_CLIENT_LIRISHELLV1_H
#define AURORA_CLIENT_LIRISHELLV1_H

#include <QObject>
#include <QWaylandClientExtension>

#include <LiriAuroraClient/liriauroraclientglobal.h>

#include <wayland-client.h>

QT_FORWARD_DECLARE_CLASS(QWindow)

namespace Aurora {

namespace Client {

class LiriShellV1Private;
class LiriShortcutV1Private;
class LiriOsdV1Private;

class LIRIAURORACLIENT_EXPORT LiriShellV1
        : public QWaylandClientExtensionTemplate<LiriShellV1>
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(LiriShellV1)
public:
    LiriShellV1();
    ~LiriShellV1();

    void init(struct ::wl_registry *registry, int id, int version);

    Q_INVOKABLE void sendReady();

    Q_INVOKABLE void terminateCompositor();

    static const struct ::wl_interface *interface();

Q_SIGNALS:
    void logoutRequested();
    void shutdownRequested();
    void quitRequested();

private:
    QScopedPointer<LiriShellV1Private> const d_ptr;
};

class LIRIAURORACLIENT_EXPORT LiriShortcutV1
        : public QWaylandClientExtension
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(LiriShortcutV1)
    Q_PROPERTY(LiriShellV1 *shell READ shell WRITE setShell NOTIFY shellChanged)
    Q_PROPERTY(QString sequence READ sequence WRITE setSequence NOTIFY sequenceChanged)
public:
    LiriShortcutV1();
    ~LiriShortcutV1();

    LiriShellV1 *shell() const;
    void setShell(LiriShellV1 *shell);

    QString sequence() const;
    void setSequence(const QString &sequence);

    const struct wl_interface *extensionInterface() const override { return interface(); }
    void bind(struct ::wl_registry *registry, int id, int ver) override;

    static const struct ::wl_interface *interface();

Q_SIGNALS:
    void shellChanged();
    void sequenceChanged();
    void activated(struct ::wl_seat *seat);

public Q_SLOTS:
    void bindShortcut();

private:
    QScopedPointer<LiriShortcutV1Private> const d_ptr;
};

class LIRIAURORACLIENT_EXPORT LiriOsdV1
        : public QWaylandClientExtensionTemplate<LiriOsdV1>
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(LiriOsdV1)
public:
    LiriOsdV1();
    ~LiriOsdV1();

    void init(struct ::wl_registry *registry, int id, int version);

    static const struct ::wl_interface *interface();

Q_SIGNALS:
    void textRequested(const QString &iconName, const QString &text);
    void progressRequested(const QString &iconName, quint32 value);

private:
    QScopedPointer<LiriOsdV1Private> const d_ptr;
};

} // namespace Client

} // namespace Aurora

#endif // AURORA_CLIENT_LIRISHELLV1_H
