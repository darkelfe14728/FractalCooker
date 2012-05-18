/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	FractalCooker/Interfaces
 * Fichier					:	Fractale3D.h
 *
 * Date de création			:	samedi 17 décembre 2011
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

#ifndef HEADERGUARD_INTERFACES_FRACTALE3D_H
#define HEADERGUARD_INTERFACES_FRACTALE3D_H

	#include "GenericFractale.h"

	#include <QtCore/QVector>
	#include <QtOpenGL/QGLShaderProgram>

	namespace Interfaces {
		class Fractale3D :
				public GenericFractale {

			Q_OBJECT

			public:
				Fractale3D ();
				virtual ~Fractale3D ();

				virtual void generate ();

				virtual void init (QGLShaderProgram * shaders,
								   const int loc_calcul,
								   const int loc_color,
								   const quint32 nbIteration);

				virtual const QVector<GLfloat> getVertices () const = 0;

				virtual int zoom () const;
				virtual int nearDistance () const;
				virtual int farDistance () const;

				virtual bool paint (const QMatrix4x4 & modelView) = 0;

				int getCalculLocation () const;
				int getColorLocation () const;

				QGLShaderProgram * shaders ();

				virtual int maximum () const = 0;

			private:
				QGLShaderProgram * m_shaders;

				int m_location_calcul;
				int m_location_color;
		};
	}

	Q_DECLARE_INTERFACE(Interfaces::Fractale3D, "fractalcooker.interfaces.fractale3d/1.0.0")

#endif

