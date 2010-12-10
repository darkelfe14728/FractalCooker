/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	Program
 * Fichier					:	Plugins.cpp
 *
 * Date de modification		:	dimanche 21 mars 2010
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

#include "Plugins.h"
#include "Fractale2D.h"
#include "Fractale3D.h"

#include <QtCore/QPluginLoader>
#include <QtGui/QTreeWidgetItem>

Plugins::Plugins (const QDir & pluginPath,
				  const QStringList & pluginFiles,
				  QWidget * parent/* = 0*/) :
	QDialog(parent) {

	m_ui.setupUi(this);

	createTree(pluginPath, pluginFiles);
}

void Plugins::createTree (const QDir & pluginPath,
						  const QStringList & pluginFiles) {

	QTreeWidgetItem * root_Fract2D = new QTreeWidgetItem(m_ui.Tree);
		root_Fract2D->setText(0, tr("Fractales 2D"));
		root_Fract2D->setToolTip(0, tr("Liste des plugins de tracé de fractales 2D"));

	QTreeWidgetItem * root_Fract3D = new QTreeWidgetItem(m_ui.Tree);
		root_Fract3D->setText(0, tr("Fractales 3D"));
		root_Fract3D->setToolTip(0, tr("Liste des plugins de tracé de fractales 3D"));

	foreach(QString curr, pluginFiles) {
		QPluginLoader loader(pluginPath.absoluteFilePath(curr));
		QObject * plugin = loader.instance();

		if(plugin) {

			Fractale2D * fract2D = qobject_cast<Fractale2D *>(plugin);
			if(fract2D) {
				QTreeWidgetItem * item_Fract2D = new QTreeWidgetItem(root_Fract2D);

				item_Fract2D->setText(0, fract2D->name());
				item_Fract2D->setText(1, pluginPath.absoluteFilePath(curr));
			}
			else {
				Fractale3D * fract3D = qobject_cast<Fractale3D *>(plugin);
				if(fract3D) {
					QTreeWidgetItem * item_Fract3D = new QTreeWidgetItem(root_Fract3D);

					item_Fract3D->setText(0, fract3D->name());
					item_Fract3D->setText(1, pluginPath.absoluteFilePath(curr));
				}
			}
		}
	}
}
