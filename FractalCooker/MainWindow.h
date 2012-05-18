/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	FractalCooker/FractalCooker
 * Fichier					:	MainWindow.h
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

#ifndef HEADERGUARD_FRACTALCOOKER_MAINWINDOW_H
#define HEADERGUARD_FRACTALCOOKER_MAINWINDOW_H

#include <QtGui/QMainWindow>

class Plugins;
class QActionGroup;

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	protected:
		void changeEvent(QEvent *e);

	private:
		Ui::MainWindow *ui;
		Plugins *m_plugins_dialog;
		QActionGroup *m_plugins_group;

	private slots:
		void on_action_Aide_About_triggered();
};

#endif // HEADERGUARD_FRACTALCOOKER_MAINWINDOW_H
