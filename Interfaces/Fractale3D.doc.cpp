/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	FractalCooker/Interfaces
 * Fichier					:	Fractale3D.doc.cpp
 *
 * Date de création			:	dimanche 18 décembre 2011
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

/**	\class Interfaces::Fractale3D
 *	\brief Interfaces des plugins fractale 3D.
 *
 *	Interface générique à toutes les fractales 3D. \n
 *	Chaque plugin de fractales 3D \c DOIT hériter de cette interface.
 *
 *	\warning Chaque plugin créé avec cette interface utilise OpenGL, pensez donc à modifier votre projet en conséquence.
 */



/** \fn Interfaces::Fractale3D::Fractale3D ()
 *
 *  Crée le plugin (inutilisable). Doit être suivit par un appel à \ref Interfaces::Fractale3D::init "init".
 */
/** \fn virtual Interfaces::Fractale3D::~Fractale3D ()
 *
 *	Détruit le plugin.
 */


/** \fn virtual void Interfaces::Fractale3D::init (	QGLShaderProgram * shaders,
 *													const int loc_calcul,
 *													const int loc_color,
 *													const quint32 nbIteration) = 0
 *
 *	Initialise le plugin.
 *
 *	\param[in]	shaders			Pointeur vers le 'programme' de shaders. Sa construction et sa destuction sont à la charge de l'unité appelante.
 *	\param[in]	loc_calcul		Localisation de la matrice de calcul.
 *	\param[in]	loc_color		Localisation de la variable de couleur.
 *	\param[in]	nbIteration		Le nombre d'itération (la profondeur du calcul).
 */

/** \fn virtual const QVector<GLfloat> Interfaces::Fractale3D::getVertices () const = 0
 *
 *	\return Un tableau constitué des différentes vertices (points) de la forme de base à dessiner. Trois coordonnées (x, y et z) par vertices.
 */

/** \fn virtual int Interfaces::Fractale3D::zoom () const
 *
 *	\return Le facteur de zoom.
 */
/** \fn virtual int Interfaces::Fractale3D::nearDistance () const
 *
 *	\return La limite proche de vision.
 */
/** \fn virtual int Interfaces::Fractale3D::farDistance () const
 *
 *	\return La limite lointaine de vision.
 */

/** \fn virtual bool Interfaces::Fractale3D::paint (const QMatrix4x4 & modelView) = 0
 *
 *	Dessine la fractale (avec OpenGL).
 *
 *  \param[in]	modelView		Transformations de base (celles de l'utilisateur).
 *
 *  \return Vrai si le tracé à été annulé, faux sans le cas contraire.
 */

/** \fn int Interfaces::Fractale3D::getCalculLocation () const
 *
 *	\return La localisation (dans les shaders) de la matrice de calcul.
 */
/**	\fn int Interfaces::Fractale3D::getColorLocation () const
 *
 *	\return La localisation (dans les shaders) de la variable de couleur.
 */

/** \fn QGLShaderProgram * Interfaces::Fractale3D::shaders ()
 *
 *  \return Le "programme" d'affichage : gestionnaire de shaders OpenGL.
 */


/** \fn virtual int Interfaces::Fractale3D::maximum () const = 0
 *
 *	\return la valeur maximale pour la progression (c'est-à-dire la valeur correspondante à 100 %).
 */


/** \property QGLShaderProgram * Interfaces::Fractale3D::m_shaders
 *
 *	Le "programme" d'affichage : gestionnaire de shaders OpenGL.
 *
 *	\getter \ref Interfaces::Fractale3D::shaders "shaders".
 */

/** \property int Interfaces::Fractale3D::m_location_calcul
 *
 *	Emplacement de la matrice de calcul dans les shaders.
 *
 *	\getter \ref Interfaces::Fractale3D::getCalculLocation "getCalculLocation".
 */
/** \property int Interfaces::Fractale3D::m_location_color
 *
 *	Emplacement de la variable de couleur dans les shaders.
 *
 *	\getter \ref Interfaces::Fractale3D::getColorLocation "getColorLocation".
 */
