/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	Program
 * Fichier					:	MainWindow.h
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

#ifndef HEADERGUARD_PROGRAM_MAINWINDOW_H
#define HEADERGUARD_PROGRAM_MAINWINDOW_H

    #include "Fractale2D.h"
    #include "Fractale3D.h"

    #include "ui_MainWindow.h"

    #include <QtCore/QDir>
    #include <QtCore/QStringList>

    #include <QtGui/QMainWindow>

    QT_BEGIN_HEADER

    class MainWindow :
        public QMainWindow {

        Q_OBJECT

        public:
            MainWindow (QWidget * parent = 0, Qt::WindowFlags flags = 0);

        public slots:
            void findPlugins ();
            void aboutPlugins ();

        private:
            Ui::MainWindow m_ui;
            QActionGroup * m_pluginGroup;

            QDir m_pluginPath;
            QStringList m_pluginFiles;

        private:
            void initPluginDirPath ();
            void addToMenu (QObject * plugin, const QString & path);

        private slots:
            void loadPlugin (QAction * action);

            void on_action_Aide_About_triggered ();
    };

    QT_END_HEADER

#endif
