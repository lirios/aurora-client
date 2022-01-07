// SPDX-FileCopyrightText: 2020 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "lirishortcutqml.h"

namespace Aurora {

namespace Client {

LiriShortcutQml::LiriShortcutQml()
    : LiriShortcutV1()
{
}

void LiriShortcutQml::componentComplete()
{
    // Find the shell from the parent, if not specified
    if (!shell()) {
        for (auto *p = parent(); p != nullptr; p = p->parent()) {
            if (auto *s = qobject_cast<LiriShellV1 *>(p)) {
                setShell(s);
                break;
            } else if (auto *s = p->findChild<LiriShellV1 *>()) {
                setShell(s);
                break;
            }
        }
    }

    QMetaObject::invokeMethod(this, "bindShortcut", Qt::QueuedConnection);
}

} // namespace Client

} // namespace Aurora
