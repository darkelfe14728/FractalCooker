/*
 * Auteur				:	Rosset Julien
 *
 * Projet				:	DiscoFractale
 * Fichier				:	DiscoFractale.h
 *
 * Date de création		:	mercredi 12 mai 2010
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

#ifndef HEADERGUARD_DISCOFRACTALE_DISCOFRACTALE_H
#define HEADERGUARD_DISCOFRACTALE_DISCOFRACTALE_H

	#include <QtPlugin>
    #include <Fractale3D.h>

	class DiscoFractale :
		public Fractale3D {

		Q_OBJECT
		Q_INTERFACES(Fractale3D)

		public:
			inline QString name () const {
				return QString("Disco Fractale !");
			}

			void generer ();

		private:
			void diviser (const Cube & original, CubeList & final);

		private:
			int current;
	};

#endif
