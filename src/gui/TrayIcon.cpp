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

#include "TrayIcon.h"

TrayIcon::TrayIcon(QObject *parent) :
	QSystemTrayIcon(parent),
	mConfig(ConfigProvider::instance()),
	mOpenAction(nullptr),
	mSaveAction(nullptr),
	mPasteAction(nullptr),
	mCopyAction(nullptr),
	mUploadAction(nullptr),
	mShowEditorAction(nullptr),
	mQuitAction(nullptr),
	mActionsMenu(nullptr)
{
	auto icon = IconLoader::loadForTheme(QLatin1String("ksnip"));
	setIcon(icon);

	mShowEditorAction = new QAction(tr("Show Editor"), this);
	mShowEditorAction->setIcon(icon);
	connect(mShowEditorAction, &QAction::triggered, this, &TrayIcon::showEditorTriggered);
	connect(this, &QSystemTrayIcon::activated, this, &TrayIcon::activatedDefaultAction);
	connect(this, &QSystemTrayIcon::messageClicked, this, &TrayIcon::openContentUrl);
}

void TrayIcon::setupMenu()
{
	mMenu.addAction(mShowEditorAction);
	mMenu.addSeparator();
	for(auto captureAction : mCaptureActions) {
		mMenu.addAction(captureAction);
	}
	mMenu.addSeparator();
	mMenu.addMenu(mActionsMenu);
	mMenu.addSeparator();
	mMenu.addAction(mOpenAction);
	mMenu.addAction(mSaveAction);
	mMenu.addAction(mPasteAction);
	mMenu.addAction(mCopyAction);
	mMenu.addAction(mUploadAction);
	mMenu.addSeparator();
	mMenu.addAction(mQuitAction);
	setContextMenu(&mMenu);
}

TrayIcon::~TrayIcon()
{
	delete mShowEditorAction;
}

void TrayIcon::setCaptureActions(const QList<QAction*> &captureActions)
{
	mCaptureActions = captureActions;
}

void TrayIcon::setOpenAction(QAction *action)
{
	mOpenAction = action;
}

void TrayIcon::setSaveAction(QAction *action)
{
	mSaveAction = action;
}

void TrayIcon::setPasteAction(QAction *action)
{
	mPasteAction = action;
}

void TrayIcon::setCopyAction(QAction *action)
{
	mCopyAction = action;
}

void TrayIcon::setUploadAction(QAction *action)
{
	mUploadAction = action;
}

void TrayIcon::setQuitAction(QAction *action)
{
	mQuitAction = action;
}

void TrayIcon::setActionsMenu(QMenu *actionsMenu)
{
	mActionsMenu = actionsMenu;
}

void TrayIcon::setEnabled(bool enabled)
{
	if(enabled) {
		setupMenu();
		show();
	} else {
		hide();
	}
}

void TrayIcon::showInfoToast(const QString &title, const QString &message, const QString &contentUrl)
{
	showMessage(title, message, contentUrl, QSystemTrayIcon::Information);
}

void TrayIcon::showWarningToast(const QString &title, const QString &message, const QString &contentUrl)
{
	showMessage(title, message, contentUrl, QSystemTrayIcon::Warning);
}

void TrayIcon::showCriticalToast(const QString &title, const QString &message, const QString &contentUrl)
{
	showMessage(title, message, contentUrl, QSystemTrayIcon::Critical);
}

void TrayIcon::showMessage(const QString &title, const QString &message, const QString &contentUrl, QSystemTrayIcon::MessageIcon messageIcon)
{
	mToastContentUrl = PathHelper::extractParentDirectory(contentUrl);
	QSystemTrayIcon::showMessage(title, message, messageIcon);
}

void TrayIcon::activatedDefaultAction(ActivationReason reason) const
{
	if(reason != ActivationReason::Context) {
		if (mConfig->defaultTrayIconActionMode() == TrayIconDefaultActionMode::ShowEditor) {
			mShowEditorAction->trigger();
		} else {
			triggerDefaultCaptureMode();
		}
	}
}

void TrayIcon::triggerDefaultCaptureMode() const
{
	auto captureMode = mConfig->defaultTrayIconCaptureMode();
	for(auto action : mCaptureActions) {
		if (action->data().value<CaptureModes>() == captureMode) {
			action->trigger();
			return;
		}
	}
}

void TrayIcon::openContentUrl()
{
	if(!mToastContentUrl.isEmpty() && !mToastContentUrl.isNull()) {
		QDesktopServices::openUrl(mToastContentUrl);
	}
}
