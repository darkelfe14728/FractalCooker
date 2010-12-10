/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	Program
 * Fichier					:	Plugins.h
 *
 * Date de modification		:	mercredi 24 février 2010
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

#ifndef HEADERGUARD_PROGRAM_PLUGINS_H
#define HEADERGUARD_PROGRAM_PLUGINS_H

	#include <QtCore/QDir>
	#include <QtCore/QStringList>

	#include <QtGui/QDialog>
	#include "ui_Plugins.h"

	QT_BEGIN_HEADER

	class Plugins :
		public QDialog {

		Q_OBJECT

		public:
			Plugins (const QDir & pluginPath, const QStringList & pluginFiles, QWidget * parent = 0);

		private:
			Ui::Plugins m_ui;

			void createTree (const QDir & pluginPath, const QStringList & pluginFiles);
	};

	QT_END_HEADER

#endif
