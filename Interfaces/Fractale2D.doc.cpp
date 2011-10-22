/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	FractalCooker/Interfaces
 * Fichier					:	Fractale2D.doc.cpp
 *
 * Date de création			:	dimanche 18 septembre 2011
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

/**	\class Interfaces::Fractale2D
 *	\brief Interfaces des plugins fractale 2D.
 */



/** \fn virtual Interfaces::Fractale2D::~Fractale2D ()
 *
 *	Détruit le plugin.
 */



/** \fn void Interfaces::Fractale2D::init (	const QRect		& drawZone	= QRect(0, 0, 400, 300),
 *											const QPointF	& centre	= QPointF(-1.0, 0.0),
 *											const qreal		& zoom		= 100.0,
 *											const quint32	& nbIte		= 255)
 *
 *	Initialise le plugin.
 *
 *	\warning Cette fonction \b doit être appelée avant generate.
 *
 *	\param[in]	drawZone		La (taille de la) zone à générer ?
 *	\param[in]	centre			Le point central de la fractale générée (autour de quel point se génère-t-elle ?).
 *	\param[in]	zoom			Le facteur de zoom appliqué.
 *	\param[in]	nbIte			Le nombre d'itération (profondeur du calcul).
 */

