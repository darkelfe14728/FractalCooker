/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	FractalCooker/FractalCooker
 * Fichier					:	Plugins.cpp
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

#include "Plugins.h"
#include "ui_Plugins.h"

#include <Interfaces/Fractale2D.h>
#include <Interfaces/Fractale3D.h>

#include <QtCore/QPluginLoader>
#include <QtGui/QMenu>
#include <QtGui/QStandardItemModel>

Plugins::Plugins(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Plugins),
	m_model(new QStandardItemModel(0, 2, this))
{
	ui->setupUi(this);
	ui->treeView->setModel(m_model);

	createModel();
}
Plugins::~Plugins()
{
	delete ui;
}


void Plugins::searchPlugins(QActionGroup * group, QMenu * menu_2D, QMenu * menu_3D) {
	QStandardItem * root_2D = new QStandardItem(tr("Fractales 2D"));
	root_2D->setToolTip(tr("Liste des plugins proposant une fractale 2D"));
	m_model->appendRow(root_2D);

	QStandardItem * root_3D = new QStandardItem(tr("Fractales 3D"));
	root_3D->setToolTip(tr("Liste des plugins proposant une fractale 3D"));
	m_model->appendRow(root_3D);

	QStandardItem * root_invalid = new QStandardItem(tr("Plugins invalides"));
	root_invalid->setToolTip(tr("Liste des plugins qui n'ont pas été reconnus par FractalCooker"));
	m_model->appendRow(root_invalid);


	QDir pluginPath = getPluginsDir();
	QStringList pluginFiles = pluginPath.entryList(QDir::Files);

	foreach(QString file, pluginFiles) {
		const QString filename = pluginPath.absoluteFilePath(file);

		QPluginLoader loader(filename);
		QObject * plugin = loader.instance();

		Interfaces::Fractale2D * fract_2D = qobject_cast<Interfaces::Fractale2D *>(plugin);
		if(fract_2D) {
			const QString name = fract_2D->name();

			addPluginToMenu(plugin, name, filename, group, menu_2D);
			addPluginToTree(root_2D, name, filename);
		}
		else {
			Interfaces::Fractale3D * fract_3D = qobject_cast<Interfaces::Fractale3D *>(plugin);
			if(fract_3D) {
				const QString name = fract_3D->name();

				addPluginToMenu(plugin, name, filename, group, menu_3D);
				addPluginToTree(root_3D, name, filename);
			}
			else {
				addPluginToTree(root_invalid, "-", filename);
			}
		}
	}
}



void Plugins::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
	switch (e->type()) {
		case QEvent::LanguageChange:
			ui->retranslateUi(this);
			break;
		default:
			break;
	}
}



void Plugins::createModel() {
	QStandardItem * header_nom = new QStandardItem(tr("Nom"));
	header_nom->setToolTip(tr("Nom du plugin"));
	m_model->setHorizontalHeaderItem(0, header_nom);

	QStandardItem * header_path = new QStandardItem(tr("Chemin"));
	header_path->setToolTip(tr("Chemin sur le disque du plugin"));
	m_model->setHorizontalHeaderItem(1, header_path);
}
const QDir Plugins::getPluginsDir() const {
	QDir path = qApp->applicationDirPath();
	path.cd("Plugins");

	return path;
}
void Plugins::addPluginToMenu(QObject *plugin, const QString &name, const QString &path, QActionGroup *group,
							  QMenu *menu) {
	QAction * action = new QAction(name, plugin);
	action->setCheckable(true);
	action->setToolTip(path);
	action->setStatusTip(path);

	group->addAction(action);
	menu->addAction(action);
}
void Plugins::addPluginToTree(QStandardItem *group, const QString &name, const QString &path) {
	group->appendRow(QList<QStandardItem *>()
					 << new QStandardItem(name)
					 << new QStandardItem(path)
	);
}
