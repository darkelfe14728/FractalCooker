/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	FractalCooker/FractalCooker
 * Fichier					:	Plugins.h
 *
 * Date de création			:	vendredi 18 mai 2012
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

#ifndef HEADERGUARD_FRACTALCOOKER_PLUGINS_H
#define HEADERGUARD_FRACTALCOOKER_PLUGINS_H

#include <QtCore/QDir>
#include <QtGui/QDialog>

class QActionGroup;
class QMenu;
class QStandardItem;
class QStandardItemModel;

namespace Ui {
	class Plugins;
}

class Plugins : public QDialog
{
		Q_OBJECT

	public:
		explicit Plugins(QWidget *parent = 0);
		~Plugins();

		void searchPlugins (QActionGroup * group, QMenu * menu_2D, QMenu * menu_3D);

	protected:
		void changeEvent(QEvent *e);

	private:
		Ui::Plugins *ui;
		QStandardItemModel *m_model;

		void createModel ();
		const QDir getPluginsDir () const;
		void addPluginToMenu (QObject * plugin, const QString & name, const QString & path, QActionGroup * group,
							  QMenu * menu);
		void addPluginToTree (QStandardItem * group, const QString & name, const QString & path);
};

#endif // HEADERGUARD_FRACTALCOOKER_PLUGINS_H
