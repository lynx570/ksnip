/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
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

#include "WindowResizer.h"

WindowResizer::WindowResizer(IResizableWindow *resizableWindow, Config *config, QObject *parent) :
	QObject(parent),
	mResizableWindow(resizableWindow),
	mConfig(config),
	mPerformedAutoResize(false),
	mResizeDelayInMs(50)
{
	Q_ASSERT(mResizableWindow != nullptr);
	Q_ASSERT(mConfig != nullptr);
}

void WindowResizer::resize()
{
	if(mResizableWindow->isWindowMaximized()) {
		return;
	}

	auto enforceAutoResize = mConfig->autoResizeToContent() || !mPerformedAutoResize;
	if (enforceAutoResize) {
		QTimer::singleShot(mConfig->resizeToContentDelay(), this, &WindowResizer::resizeWindow);
	}
}

void WindowResizer::resetAndResize()
{
	mPerformedAutoResize = false;
	resize();
}

void WindowResizer::resizeWindow()
{
	mPerformedAutoResize = true;
	mResizableWindow->resizeToContent();
}
