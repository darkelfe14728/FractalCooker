/*
 * Auteur					:	Rosset Julien / Richard Thomas
 *
 * Projet					:	FractalCooker/Plugins/2D
 * Fichier					:	Mandelbrot.doc.cpp
 *
 * Date de modification		:	dimanche 25 décembre 2011
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

/** \namespace Plugins::_2D
 *	\brief Espace de nom pour les plugins 3D.
 *
 *	\c Note : le "_" au début du nom est obligatoire pour avoir un espace de nom commençant par un chiffre.
 */

/** \class Plugins::_2D::Mandelbrot
 *	\brief Le plugin 2D pour la fractale "Mandelbrot".
 */



/** \fn Plugins::_2D::Mandelbrot::Mandelbrot ()
 *	Crée le plugin (inutilisable). Doit être suivit d'un appel à \ref init "Plugins::_2D::Mandelbrot::init".
 */


/** \fn quint32 Plugins::_2D::Mandelbrot::calculerPixel (	const qreal &x,
 *															const qreal &y) const
 *  Fonction qui calcule le nombre d'étapes avant la divergence (ou non) de la suite pour un pixel donné. \n
 *  Elle calcule les termes de la suite de mandelbrot jusqu'à ce qu'elle diverge ou que le nombre maximal d'itérations soit atteint.
 *
 *  \param[in]	x	Coordonnée en X du pixel à traiter.
 *  \param[in]	y	Coordonnée en Y du pixel à traiter.
 *
 *  \return Le nombre d'itérations effectuées (compris entre 0 et le nombre max. d'itérations).
 *
 *  \see generate()
 */
