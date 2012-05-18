/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	FractalCooker/FractalCooker
 * Fichier					:	AProposDe.h
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

#ifndef HEADERGUARD_FRACTACOOCKER_APROPOSDE_H
#define HEADERGUARD_FRACTALCOOKER_APROPOSDE_H

#include <QtGui/QDialog>

namespace Ui {
	class AProposDe;
}

class AProposDe : public QDialog
{
		Q_OBJECT

	public:
		explicit AProposDe(QWidget *parent = 0);
		~AProposDe();

	protected:
		void changeEvent(QEvent *e);

	private:
		Ui::AProposDe *ui;
};

#endif // HEADERGUARD_FRACTALCOOKER_APROPOSDE_H
