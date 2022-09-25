// SPDX-FileCopyrightText: 2022 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef AURORA_CLIENT_EXTSESSIONLOCKSURFACEV1_H
#define AURORA_CLIENT_EXTSESSIONLOCKSURFACEV1_H

#include <QWindow>

#include <LiriAuroraClient/liriauroraclientglobal.h>

namespace Aurora {

namespace Client {

class ExtSessionLockSurfaceV1Private;

class LIRIAURORACLIENT_EXPORT ExtSessionLockSurfaceV1 : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(ExtSessionLockSurfaceV1)
    Q_PROPERTY(QWindow *window READ window WRITE setWindow NOTIFY windowChanged)
public:
    ExtSessionLockSurfaceV1(QObject *parent = nullptr);
    ~ExtSessionLockSurfaceV1();

    bool isInitialized() const;

    void initialize();

    QWindow *window() const;
    void setWindow(QWindow *window);

    static ExtSessionLockSurfaceV1 *get(QWindow *window);

Q_SIGNALS:
    void windowChanged(QWindow *window);
    void unlockRequested();

private:
    QScopedPointer<ExtSessionLockSurfaceV1Private> const d_ptr;
};

} // Client

} // Aurora

#endif // AURORA_CLIENT_EXTSESSIONLOCKSURFACEV1_H
