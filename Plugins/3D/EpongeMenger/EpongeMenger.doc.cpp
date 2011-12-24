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

/** \namespace Plugins
 *	\brief Espace de nom pour tous les plugins.
 */

/** \namespace Plugins::_3D
 *	\brief Espace de nom pour les plugins 3D.
 *
 *  \c Note : le "_" au début du nom est obligatoire pour avoir un espace de nom commençant par un chiffre.
 */

/**	\class Plugins::_3D::EpongeMenger
 *	\brief Le plugin 3D pour la "Éponge de Menger".
 *
 *	Nous partons d'un cube extrudé découpé en 27 blocs. \n
 *  A chaque itération, chaque bloc est remplacé par par cube le même cube extrudé de départ, en adaptant la taille.
 *
 *  \todo buildOptions : gérer des options.
 */



/** \fn Plugins::_3D::EpongeMenger::EpongeMenger ()
 *
 *	Crée le plugin (inutilisable). Doit être suivit par une appel à \ref Plugins::_3D::EpongeMenger::init "init".
 */


/** \fn bool Plugins::_3D::EpongeMenger::paintCube (const QMatrix4x4 & calcul)
 *	Dessine un cube.
 *
 *	\param[in]	calcul			Matrice pour le placement du cube.
 *
 *	\return Vrai si le dessin à été annulé, sinon Faux.
 */
/** \fn bool Plugins::_3D::EpongeMenger::paintIteration (QMatrix4x4 & calcul,
 *														 const quint8 level)
 *	Dessine une itération de la fractale. \n
 *	Régler \c level à 0 dessine un cube (Cf. \ref Plugins::_3D::EpongeMenger::paintCube "paintCube").
 *
 *	\param[in]	calcul			Matrice pour le placement du 1er sube de l'itération
 *	\param[in]	level			Niveau de l'itération.
 *
 *	\return Vrai si le dessin à été annulé, sinon Faux.
 *
 *	\sa paintCube.
 */
/** \fn bool Plugins::_3D::EpongeMenger::paintIterationLayer (QMatrix4x4 & calcul,
 *															  const quint8 level)
 *	Dessine une "tranche" d'une itération.
 *
 *	\param[in]	calcul			Matrice pour le placement des cubes.
 *	\param[in]	level			Niveau de l'itération.
 *
 *	\return Vrai si le dessin à été annulé, sinon Faux.
 *
 *  \sa paintIteration.
 */


/** \property int Plugins::_3D::EpongeMenger::m_currentProgress
 *	Compteur pour la progression.
 *
 *	\warning 0 <= \a _valeur_ <= maximum()
 *
 *  \getter \ref Plugins::_3D::EpongeMenger::progression "progression".
 *
 *	\sa maximum, progression.
 */
