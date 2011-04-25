/*
 * Auteur				:	Rosset Julien
 *
 * Projet				:	EpongeMenger
 * Fichier				:	EpongeMenger.h
 *
 * Date de création		:	mercredi 12 mai 2010
 */

/* Copyright (C) 2010-2011 LEVIGNE Florent, GROCCIA Patricia, RICHARD Thomas, ROSSET Julien
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

#ifndef HEADERGUARD_EPONGEMENGER_EPONGEMENGER_H
#define HEADERGUARD_EPONGEMENGER_EPONGEMENGER_H

    #include <Fractale3D.h>

	#include <cmath>

	class QMatrix4x4;

	class EpongeMenger :
		public Fractale3D {

		Q_OBJECT
		Q_INTERFACES(Fractale3D)

		public:
			EpongeMenger ();

			inline void createOptions (QWidget *) {}		// Pas géré pour le moment

			inline QString name () const {
				return QString("Eponge de Menger");
			}

			inline int maximum () const {
				return pow(20, nbIterations());
			}

			const QVector<GLFloat> getVertices () const;

			void paint ();

		private:
			/*!
			 *	Dessine un cube.
			 *
			 *	\param[in]	modelView		Matrice pour le placement du cube.
			 */
			void paintCube (const QMatrix4x4 & modelView);
			/*!
			 *	Dessine une itération de la fractale.
			 *
			 *	Level = 0 dessine un cube.
			 *
			 *	\param[in]	modelView		Matrice pour le placement des cubes.
			 *	\param[in]	level			Niveau de l'itération.
			 */
			void paintIteration (QMatrix4x4 & modelView, const quint8 level);
			/*!
			 *	Dessine une "face" d'un itération.
			 *
			 *	\param[in]	modelView		Matrice pour le placement des cubes.
			 *	\param[in]	level			Niveau de l'itération.
			 */
			void paintIterationLayer (QMatrix4x4 & modelView, const quint8 level);

		private:
			/*!
			 *	Compteur pour la progression.
			 *
			 *	0 <= valeur <= maximum()
			 *
			 *	\sa maximum, progression.
			 */
			int m_currentProgress;
	};

#endif
