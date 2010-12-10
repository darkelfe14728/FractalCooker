/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	Program
 * Fichier					:	MainWindow.cpp
 *
 * Date de modification		:	lundi 22 mars 2010
 */

/* Copyright (C) 2010 LEVIGNE Florent, GROCCIA Patricia, RICHARD Thomas, ROSSET Julien
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "MainWindow.h"

#include "Plugins.h"

#include "ui_AProposDe.h"

#include <QtCore/QPluginLoader>
#include <QtGui/QAction>

MainWindow::MainWindow (QWidget * parent/* = 0*/,
						Qt::WindowFlags flags/* = 0*/) :
	QMainWindow(parent, flags) {

	m_ui.setupUi(this);

	connect(m_ui.action_Quitter, SIGNAL(triggered()), this, SLOT(close()));
	connect(m_ui.action_AboutPlugins, SIGNAL(triggered()), this, SLOT(aboutPlugins()));

	m_ui.aff3D->hide();

//	m_ui.options2D->hide();
//	m_ui.options3D->hide();

	m_pluginGroup = new QActionGroup(m_ui.menu_Plugins);
	m_pluginGroup->setExclusive(true);

	connect(m_pluginGroup, SIGNAL(triggered(QAction *)), this, SLOT(loadPlugin(QAction *)));

	initPluginDirPath();
	findPlugins();
}



void MainWindow::findPlugins () {

	m_pluginFiles.clear();				// Reset de la liste des plugins

	QStringList pluginsFiles = m_pluginPath.entryList(QDir::Files);

	foreach(QString curr, pluginsFiles) {
		QPluginLoader loader(m_pluginPath.absoluteFilePath(curr));
		QObject * plugin = loader.instance();

		if(plugin) {
			m_pluginFiles += curr;
			addToMenu(plugin, curr);
		}
	}
}

void MainWindow::aboutPlugins () {

	Plugins about(m_pluginPath, m_pluginFiles, this);
	about.exec();
}



void MainWindow::initPluginDirPath () {
	m_pluginPath = qApp->applicationDirPath();

	m_pluginPath.cdUp();				// Pendant la phase de développement
	m_pluginPath.cd("Plugins");
}

void MainWindow::addToMenu (QObject * plugin,
							const QString & path) {

	Fractale2D * fract2D = qobject_cast<Fractale2D *>(plugin);
	if(fract2D) {
		QAction * action = new QAction(fract2D->name(), plugin);
		action->setCheckable(true);
		action->setToolTip(path);

		m_pluginGroup->addAction(action);

		m_ui.menu_Plugins2D->addAction(action);
	}
	else {

		Fractale3D * fract3D = qobject_cast<Fractale3D *>(plugin);
		if(fract3D) {
			QAction * action = new QAction(fract3D->name(), plugin);
			action->setCheckable(true);
			action->setToolTip(path);

			m_pluginGroup->addAction(action);

			m_ui.menu_Plugins3D->addAction(action);
		}
	}
}

void MainWindow::loadPlugin (QAction * action) {

	Fractale2D * fract2D = qobject_cast<Fractale2D *>(action->parent());
	if(fract2D) {
		if(!m_ui.aff2D->isVisible()) {
			m_ui.aff3D->hide();
			m_ui.aff2D->show();
		}

		// TODO : Utile ?
		//m_ui.aff3D->clear();

		if(!m_ui.aff2D->loadFractal(fract2D))
			action->setChecked(false);
	}
	else {
		Fractale3D * fract3D = qobject_cast<Fractale3D *>(action->parent());
		if(fract3D) {
			if(!m_ui.aff3D->isVisible()) {
				m_ui.aff3D->show();
				m_ui.aff2D->hide();
			}

			m_ui.aff3D->loadFractal(fract3D);

			if(m_ui.aff3D->canceled())
				action->setChecked(false);
		}
	}
}


void MainWindow::on_action_About_triggered ()
{
    QDialog dialog;

    Ui::About ui;
    ui.setupUi(&dialog);

    dialog.exec();
}
