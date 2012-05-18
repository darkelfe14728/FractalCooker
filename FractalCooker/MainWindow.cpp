/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	FractalCooker/FractalCooker
 * Fichier					:	MainWindow.cpp
 *
 * Date de création			:	samedi 21 avril 2012
 */

/* Copyright (C) 2010-2012 LEVIGNE Florent, GROCCIA Patricia, RICHARD Thomas, ROSSET Julien
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
#include "ui_MainWindow.h"

#include "AProposDe.h"
#include "Plugins.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	m_plugins_dialog(new Plugins(this)),
	m_plugins_group(0)
{
	ui->setupUi(this);

	m_plugins_group = new QActionGroup(ui->menu_Plugins);
	m_plugins_group->setExclusive(true);

	//connect(m_plugins_group, SIGNAL(triggered(QAction*)), this, SLOT(loadPlugin(QAction*)));

	m_plugins_dialog->searchPlugins(m_plugins_group, ui->menu_Plugins_2D, ui->menu_Plugins_3D);
	connect(ui->action_Aide_AboutPlugins, SIGNAL(triggered()), m_plugins_dialog, SLOT(exec()));
}
MainWindow::~MainWindow()
{
	delete m_plugins_dialog;
	delete ui;
}



void MainWindow::changeEvent(QEvent *e)
{
	QMainWindow::changeEvent(e);
	switch (e->type()) {
		case QEvent::LanguageChange:
			ui->retranslateUi(this);
			break;
		default:
			break;
	}
}



void MainWindow::on_action_Aide_About_triggered () {
	AProposDe dialog(this);
	dialog.exec ();
}
