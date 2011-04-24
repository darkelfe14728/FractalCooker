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

	#include <cmath>

	#include <QtPlugin>
    #include <Fractale3D.h>

    #include <QtCore/QVector>

	#include <QtGui/QMatrix4x4>

	class EpongeMenger :
		public Fractale3D {

		Q_OBJECT
		Q_INTERFACES(Fractale3D)

		public:
			EpongeMenger ();

			void init (QGLShaderProgram * shaders, int modelView_loc, int color_loc, int nbIteration);

			inline void createOptions (QWidget *) {}		// Pas géré pour le moment

			inline QString name () const {
				return QString("Eponge de Menger");
			}

			inline int maximum () const {
				return pow(20, nbIterations());
			}

			const QVector<GLFloat> getVertices () const;

			const int zoom () const {
				return 70;
			}
			const int near () const {
				return 1;
			}
			const int far () const {
				return 1000;
			}

			void paint ();

			inline int getModelViewLocation () const {
				return m_modelViewLocation;
			}
			inline int getColorLocation () const {
				return m_colorLocation;
			}

		private:
			void paintCube (const QMatrix4x4 & modelView);
			void paintIteration (QMatrix4x4 & modelView, const quint8 level);
			void paintIterationLayer (QMatrix4x4 & modelView, const quint8 level);

		private:
			int m_currentProgress;

			QGLShaderProgram * m_shaders;
			int m_modelViewLocation;
			int m_colorLocation;
	};

#endif
