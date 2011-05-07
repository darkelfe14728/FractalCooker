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

	#include <QtCore/QVector>
	#include <QtOpenGL/QGLShaderProgram>

    QT_BEGIN_HEADER

	/*!
	 *	Interface générique à toutes les fractales 3D. \n
	 *	Chaque plugins de fractales 3D <u>doit</u> hériter de cette interface.
	 *
	 *	\warning Chaque plugin crée avec cette interface doit utiliser OpenGL. Pensez à modifier votre projet en conséquence.
	 */
    class Fractale3D :
        public Fractale {

        Q_OBJECT

        public:
			Fractale3D () : m_shaders(0), m_location_calcul(-1), m_location_color(-1) {}
            virtual ~Fractale3D () {}

			/*!
			 *	Initialise le plugin.
			 *
			 *	\param[in]	shaders			Pointeur vers le 'programme' de shaders. Sa construction et sa destuction sont à la charge de l'unité appelante.
			 *	\param[in]	loc_modelView	Localisation de la matrice de calcul.
			 *	\param[in]	loc_color		Localisation de la coloration.
			 *	\param[in]	nbIteration		Le nombre d'itération (la profondeur du calcul).
			 */
            virtual void init (QGLShaderProgram * shaders, const int loc_calcul, const int loc_color, const quint32 nbIteration) {

				m_shaders = shaders;		// Copie d'adresse, et pas de l'objet

				m_location_calcul = loc_calcul;
				m_location_color = loc_color;

				setNbIterations(nbIteration);
				resetCancel();
            }

			/*!
			 *	\return Un tableau constitué des différentes vertices (points) de la forme de base à dessiner. Trois valeur par vertices.
			 */
			virtual const QVector<GLfloat> getVertices () const = 0;

			/*!
			 *	\return Le facteur de zoom (70 par défaut).
			 */
			virtual int zoom () const {
				return 70;
			}
			/*!
			 *	\return La limite proche de vision (1 par défaut).
			 */
			virtual int nearDistance () const {
				return 1;
			}
			/*!
			 *	\return La limite lointaine de vision (1000 par défaut).
			 */
			virtual int farDistance () const {
				return 1000;
			}

			/*!
			 *	Dessine la fractale (avec OpenGL).
			 * 
			 * \param[in]	modelView		Transformations de base (celles de l'utilisateur).
			 * 
			 * \return Vrai si le dessin à été annulé, faux sans le cas contraire.
			 */
			virtual bool paint (const QMatrix4x4 & modelView) = 0;

			/*!
			 *	\return La localisation (dans les shaders) de la matrice de calcul.
			 */
			inline int getCalculLocation () const {
				return m_location_calcul;
			}
			/*!
			 *	\return La localisation (dans les shaders) de la variable de couleur.
			 */
			inline int getColorLocation () const {
				return m_location_color;
			}

			inline QGLShaderProgram * shaders () {
				return m_shaders;
			}

		public:
			/*!
			 *	\return la valeur maximale pour la progression (c'est-à-dire la valeur correspondante à 100 %).
			 *
			 *	\sa progression.
			 */
			virtual int maximum () const = 0;

		private:
			QGLShaderProgram * m_shaders;

			int m_location_calcul;
			int m_location_color;

    };

    Q_DECLARE_INTERFACE(Fractale3D, "fractalcooker.fractale3D/2.0.0")

    QT_END_HEADER

#endif

