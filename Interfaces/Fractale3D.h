/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	Program
 * Fichier					:	Fractale3D.h
 *
 * Date de création			:	mercredi 24 février 2010
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

	#include "Fractale.h"

	#include <QtOpenGL/QGLShaderProgram>

    QT_BEGIN_HEADER

	/**
	 *	Interface générique à toutes les fractales 3D. \n
	 *	Chaque plugins de fractales 3D <u>doit</u> hériter de cette interface.
	 *
	 *	\warning Chaque plugin crée avec cette interface doit utiliser OpenGL. Pensez à modifier le projet en conséquence.
	 */
    class Fractale3D :
        public Fractale {

        Q_OBJECT

        public:
            virtual ~Fractale3D () {}

			/**
			 *	Initialise le plugin.
			 *
			 *	\param[in]	nbItération		Le nombre d'itération (la profondeur du calcul).
			 */
            void init (const quint32 nbIteration) {
				setNbIterations(nbIterations);
				resetCancel();
            }

			/*!
			 *	\return la valeur maximale pour la progression (c'est-à-dire la valeur correspondante à 100 %).
			 */
			int maximum () const;

			/**
			 *	Nettoie la fractale.
			 *
			 *	\note A placer dans la classe mère ?
			 */
			virtual void clear () {
				m_forme.clear();
			}

			/*!
			 *	Dessine, avec OpenGL, la fractale via \a program .
			 *
			 *	\param		program		Les shaders pour le dessin OpenGL.
			 *
			 *	\param[in]	camera		Position de la matrice caméra.
			 *	\param[in]	draw		Position de la matrice de dessin.
			 *	\param[in]	color		Position de la couleur de dessin.
			 */
			virtual void paint (QGLShaderProgram & program, const int camera, const int draw, const int color);
    };

    Q_DECLARE_INTERFACE(Fractale3D, "fractalcooker.fractale3D/2.0.0")

    QT_END_HEADER

#endif

