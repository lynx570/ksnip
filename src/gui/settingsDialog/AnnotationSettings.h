/*
 * Copyright (C) 2019 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KSNIP_ANNOTATIONSETTINGS_H
#define KSNIP_ANNOTATIONSETTINGS_H

#include <QGroupBox>
#include <QCheckBox>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>

#include "src/backend/config/Config.h"
#include "src/backend/WatermarkImageLoader.h"
#include "src/widgets/NumericComboBox.h"
#include "src/widgets/ColorButton.h"
#include "src/common/loader/IconLoader.h"
#include "src/common/provider/ScaledSizeProvider.h"

class AnnotationSettings : public QGroupBox
{
	Q_OBJECT
public:
    explicit AnnotationSettings(Config *config);
    ~AnnotationSettings() override;
    void saveSettings();

private:
    QCheckBox *mSmoothPathCheckbox;
    QCheckBox *mRememberToolSelectionCheckBox;
    QCheckBox *mSwitchToSelectToolAfterDrawingItemCheckBox;
    QCheckBox *mNumberToolSeedChangeUpdatesAllItemsCheckBox;
    QCheckBox *mSelectItemAfterDrawingCheckBox;
    QLabel *mSmoothFactorLabel;
    QLabel *mCanvasColorLabel;
    NumericComboBox *mSmoothFactorCombobox;
    ColorButton *mCanvasColorButton;
    QGridLayout *mLayout;
    Config *mConfig;

    void initGui();
    void loadConfig();

private slots:
    void smoothPathCheckBoxClicked(bool checked);
    void switchToSelectToolAfterDrawingItemCheckBoxClicked(bool checked);
};

#endif //KSNIP_ANNOTATIONSETTINGS_H
