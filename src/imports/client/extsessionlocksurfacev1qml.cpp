// SPDX-FileCopyrightText: 2022 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "extsessionlocksurfacev1qml.h"

ExtSessionLockSurfaceV1Qml::ExtSessionLockSurfaceV1Qml(QObject *parent)
    : ExtSessionLockSurfaceV1(parent)
{
}

void ExtSessionLockSurfaceV1Qml::componentComplete()
{
    if (isInitialized())
        return;

    // Find the window from the parent, if not specified
    if (!window()) {
        for (auto *p = parent(); p != nullptr; p = p->parent()) {
            if (auto *w = qobject_cast<QWindow *>(p)) {
                setWindow(w);
                break;
            }
        }
    }

    // Initialize
    initialize();
}
