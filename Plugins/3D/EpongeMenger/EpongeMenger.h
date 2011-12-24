/*
 * Auteur				:	Rosset Julien / Levigne Florent
 *
 * Projet				:	FractaleCooker/Plugins/3D
 * Fichier				:	EpongeMenger.h
 *
 * Date de création		:	samedi 24 décembre 2011
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

#ifndef HEADERGUARD_PLUGINS_3D_EPONGEMENGER_H
#define HEADERGUARD_PLUGINS_3D_EPONGEMENGER_H

    #include <Fractale3D.h>
	#include <cmath>

	class QMatrix4x4;

	namespace Plugins {
		namespace _3D {
			class EpongeMenger :
				public Interfaces::Fractale3D {

				Q_OBJECT
				Q_INTERFACES(Interfaces::Fractale3D)

				public:
					EpongeMenger ();

					// Interface
					virtual bool buildOptions (QWidget *);			// Pas géré pour le moment
					virtual const QString name () const;
					int maximum () const;
					const QVector<GLfloat> getVertices () const;

					bool paint (const QMatrix4x4 & modelView);

				private:
					bool paintCube (const QMatrix4x4 & calcul);
					bool paintIteration (QMatrix4x4 & calcul,
										 const quint8 level);
					bool paintIterationLayer (QMatrix4x4 & calcul,
											  const quint8 level);

				private:
					int m_currentProgress;
			};
		}
	}

#endif
