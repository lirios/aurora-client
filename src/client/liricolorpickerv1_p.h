// SPDX-FileCopyrightText: 2020-2022 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef AURORA_CLIENT_LIRICOLORPICKERV1_P_H
#define AURORA_CLIENT_LIRICOLORPICKERV1_P_H

#include <QVector>

#include <LiriAuroraClient/LiriColorPickerManagerV1>
#include <LiriAuroraClient/private/aurora-client-liri-color-picker-unstable-v1.h>

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

class LIRIAURORACLIENT_EXPORT LiriColorPickerV1
        : public QObject
        , public PrivateClient::zliri_color_picker_v1
{
    Q_OBJECT
public:
    explicit LiriColorPickerV1(struct ::zliri_color_picker_v1 *object,
                               QObject *parent = nullptr);
    ~LiriColorPickerV1();

    LiriColorPickerManagerV1 *manager = nullptr;

protected:
    void zliri_color_picker_v1_picked(uint32_t value) override;
};

class LIRIAURORACLIENT_EXPORT LiriColorPickerManagerV1Private
        : public PrivateClient::zliri_color_picker_manager_v1
{
public:
    LiriColorPickerManagerV1Private() = default;
    ~LiriColorPickerManagerV1Private();

    static LiriColorPickerManagerV1Private *get(LiriColorPickerManagerV1 *self) { return self ? self->d_func() : nullptr; }

    QVector<LiriColorPickerV1 *> pickers;
};

} // namespace Client

} // namespace Aurora

#endif // AURORA_CLIENT_LIRICOLORPICKERV1_P_H
