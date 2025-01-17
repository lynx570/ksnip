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

#ifndef KSNIP_ADDWATERMARKOPERATION_H
#define KSNIP_ADDWATERMARKOPERATION_H

#include <QCoreApplication>

#include <random>

#include "WatermarkImagePreparer.h"
#include "src/gui/messageBoxService/MessageBoxService.h"
#include "src/backend/WatermarkImageLoader.h"
#include "src/backend/config/ConfigProvider.h"
#include "src/gui/imageAnnotator/IImageAnnotator.h"

class AddWatermarkOperation : public QObject
{
	Q_OBJECT
public:
	explicit AddWatermarkOperation(IImageAnnotator *imageAnnotator);
	~AddWatermarkOperation() override;
	void execute();

private:
	IImageAnnotator *mImageAnnotator;
	WatermarkImagePreparer mImagePreparer;
	WatermarkImageLoader mWatermarkImageLoader;
	Config *mConfig;
	IMessageBoxService *mMessageBoxService;

	static QPointF getPositionForWatermark(const QPixmap &image, const QSize &availableSpace) ;
	void NotifyAboutMissingWatermarkImage() const;
};

#endif //KSNIP_ADDWATERMARKOPERATION_H
