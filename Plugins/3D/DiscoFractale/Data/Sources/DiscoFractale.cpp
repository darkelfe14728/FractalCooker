/*
 * Auteur				:	Rosset Julien
 *
 * Projet				:	DiscoFractale
 * Fichier				:	DiscoFractale.cpp
 *
 * Date de création		:	mercredi 12 mai 2010
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

#include "DiscoFractale.h"

#include <cmath>				// Pour la fonction pow

#define PARENT_FACE(flag) \
    if(original.hiddenFaces.testFlag(flag)) \
        sousCube.hiddenFaces |= flag;

void DiscoFractale::generer () {

	Cube cubeInitial;
	CubeList sousCubes;

	uncancel();
	m_forme.clear();

	emit maximum(pow(20, m_nbIterations));
	current = 0;

	{	// Initialisation du cube
		const char longueur = pow(3, m_nbIterations);
		
		cubeInitial.avant.haut.gauche.x = -longueur;
		cubeInitial.avant.haut.gauche.y = longueur;
		cubeInitial.avant.haut.gauche.z = longueur;

		cubeInitial.avant.haut.droite.x = longueur;
		cubeInitial.avant.haut.droite.y = longueur;
		cubeInitial.avant.haut.droite.z = longueur;

		cubeInitial.avant.bas.droite.x = longueur;
		cubeInitial.avant.bas.droite.y = -longueur;
		cubeInitial.avant.bas.droite.z = longueur;

		cubeInitial.avant.bas.gauche.x = -longueur;
		cubeInitial.avant.bas.gauche.y = -longueur;
		cubeInitial.avant.bas.gauche.z = longueur;

		cubeInitial.arriere.haut.gauche.x = -longueur;
		cubeInitial.arriere.haut.gauche.y = longueur;
		cubeInitial.arriere.haut.gauche.z = -longueur;

		cubeInitial.arriere.haut.droite.x = longueur;
		cubeInitial.arriere.haut.droite.y = longueur;
		cubeInitial.arriere.haut.droite.z = -longueur;

		cubeInitial.arriere.bas.droite.x = longueur;
		cubeInitial.arriere.bas.droite.y = -longueur;
		cubeInitial.arriere.bas.droite.z = -longueur;

		cubeInitial.arriere.bas.gauche.x = -longueur;
		cubeInitial.arriere.bas.gauche.y = -longueur;
		cubeInitial.arriere.bas.gauche.z = -longueur;
	}

	m_forme.append(cubeInitial);

	for(quint32 i = 0; i < m_nbIterations; i++) {

		foreach(Cube actuel, m_forme) {

			diviser(actuel, sousCubes);
			if(isCancel())
				return;
		}

		m_forme = sousCubes;
		sousCubes.clear();
	}
}


#define NEXT_STEP() \
	emit progression(++current); \
	if(isCancel()) \
		return;

void DiscoFractale::diviser (const Cube & original, CubeList & final) {

	const float longueurSousCube = (original.avant.haut.droite.x - original.avant.haut.gauche.x) / 3;
	Cube sousCube;

	{	// Cube n° 1	:	avant	haut	gauche
			// Calcul des faces cachées
		sousCube.hiddenFaces = static_cast<Cube::Face>(Cube::Arriere | Cube::Droite | Cube::Bas);

		PARENT_FACE(Cube::Haut)
		PARENT_FACE(Cube::Gauche)
		PARENT_FACE(Cube::Avant)

			// Calcul des points
		/* point 0 */
		sousCube.avant.haut.gauche = original.avant.haut.gauche;

		/* point 1 */
		sousCube.avant.haut.droite.x = original.avant.haut.gauche.x + longueurSousCube;
		sousCube.avant.haut.droite.y = original.avant.haut.droite.y;
		sousCube.avant.haut.droite.z = original.avant.haut.droite.z;

		/* point 2 */
		sousCube.avant.bas.droite.x = original.avant.haut.gauche.x + longueurSousCube;
		sousCube.avant.bas.droite.y = original.avant.bas.droite.y + 2 * longueurSousCube;
		sousCube.avant.bas.droite.z = original.avant.bas.droite.z;

		/* point 3 */
		sousCube.avant.bas.gauche.x = original.avant.bas.gauche.x;
		sousCube.avant.bas.gauche.y = original.avant.haut.gauche.y - longueurSousCube;
		sousCube.avant.bas.gauche.z = original.avant.haut.gauche.z;

		/* point 4 */
		sousCube.arriere.haut.gauche.x = original.arriere.haut.gauche.x;
		sousCube.arriere.haut.gauche.y = original.arriere.haut.gauche.y;
		sousCube.arriere.haut.gauche.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 5 */
		sousCube.arriere.haut.droite.x = original.arriere.haut.gauche.x + longueurSousCube;
		sousCube.arriere.haut.droite.y = original.arriere.haut.droite.y;
		sousCube.arriere.haut.droite.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 6 */
		sousCube.arriere.bas.droite.x = original.arriere.haut.gauche.x + longueurSousCube;
		sousCube.arriere.bas.droite.y = original.arriere.haut.gauche.y - longueurSousCube;
		sousCube.arriere.bas.droite.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 7 */
		sousCube.arriere.bas.gauche.x = original.arriere.bas.gauche.x;
		sousCube.arriere.bas.gauche.y = original.avant.haut.gauche.y - longueurSousCube;
		sousCube.arriere.bas.gauche.z = original.avant.haut.gauche.z - longueurSousCube;
	}
	final.append(sousCube);
	NEXT_STEP()

	{	// Cube n° 2	:	avant	haut	milieu
			// Calcul des faces cachées
		sousCube.hiddenFaces = static_cast<Cube::Faces>(Cube::Gauche | Cube::Droite);

		PARENT_FACE(Cube::Haut)
		PARENT_FACE(Cube::Avant)

			// Calcul des points
		/* point 0 */
		sousCube.avant.haut.gauche.x = original.avant.haut.gauche.x + longueurSousCube;
		sousCube.avant.haut.gauche.y = original.avant.haut.gauche.y;
		sousCube.avant.haut.gauche.z = original.avant.haut.gauche.z;

		/* point 1 */
		sousCube.avant.haut.droite.x = original.avant.haut.gauche.x + 2 * longueurSousCube;
		sousCube.avant.haut.droite.y = original.avant.haut.droite.y;
		sousCube.avant.haut.droite.z = original.avant.haut.droite.z;

		/* point 2 */
		sousCube.avant.bas.droite.x = original.avant.haut.gauche.x + 2 * longueurSousCube;
		sousCube.avant.bas.droite.y = original.avant.bas.droite.y + 2*longueurSousCube;
		sousCube.avant.bas.droite.z = original.avant.bas.droite.z;

		/* point 3 */
		sousCube.avant.bas.gauche.x = original.avant.bas.gauche.x + longueurSousCube;
		sousCube.avant.bas.gauche.y = original.avant.haut.gauche.y - longueurSousCube;
		sousCube.avant.bas.gauche.z = original.avant.haut.gauche.z;

		/* point 4 */
		sousCube.arriere.haut.gauche.x = original.arriere.haut.gauche.x + longueurSousCube;
		sousCube.arriere.haut.gauche.y = original.arriere.haut.gauche.y;
		sousCube.arriere.haut.gauche.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 5 */
		sousCube.arriere.haut.droite.x = original.arriere.haut.gauche.x + 2*longueurSousCube;
		sousCube.arriere.haut.droite.y = original.arriere.haut.droite.y;
		sousCube.arriere.haut.droite.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 6 */
		sousCube.arriere.bas.droite.x = original.arriere.haut.gauche.x + 2*longueurSousCube;
		sousCube.arriere.bas.droite.y = original.arriere.haut.gauche.y - longueurSousCube;
		sousCube.arriere.bas.droite.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 7 */
		sousCube.arriere.bas.gauche.x = original.arriere.bas.gauche.x + longueurSousCube;
		sousCube.arriere.bas.gauche.y = original.avant.haut.gauche.y - longueurSousCube;
		sousCube.arriere.bas.gauche.z = original.avant.haut.gauche.z - longueurSousCube;
	}
	final.append(sousCube);
	NEXT_STEP()

    {	// Cube n° 3	:	avant	haut	droite
			// Calcul des faces cachées
		sousCube.hiddenFaces = static_cast<Cube::Faces>(Cube::Bas | Cube::Gauche | Cube::Arriere);

		PARENT_FACE(Cube::Avant)
		PARENT_FACE(Cube::Haut)
		PARENT_FACE(Cube::Droite)

			// Calcul des points
		/* point 0 */
		sousCube.avant.haut.gauche.x = original.avant.haut.gauche.x + 2*longueurSousCube;
		sousCube.avant.haut.gauche.y = original.avant.haut.gauche.y;
		sousCube.avant.haut.gauche.z = original.avant.haut.gauche.z;

		/* point 1 */
		sousCube.avant.haut.droite.x = original.avant.haut.gauche.x + 3*longueurSousCube;
		sousCube.avant.haut.droite.y = original.avant.haut.droite.y;
		sousCube.avant.haut.droite.z = original.avant.haut.droite.z;

		/* point 2 */
		sousCube.avant.bas.droite.x = original.avant.haut.gauche.x + 3*longueurSousCube;
		sousCube.avant.bas.droite.y = original.avant.bas.droite.y + 2*longueurSousCube;
		sousCube.avant.bas.droite.z = original.avant.bas.droite.z;

		/* point 3 */
		sousCube.avant.bas.gauche.x = original.avant.bas.gauche.x + 2*longueurSousCube;
		sousCube.avant.bas.gauche.y = original.avant.haut.gauche.y - longueurSousCube;
		sousCube.avant.bas.gauche.z = original.avant.haut.gauche.z;

		/* point 4 */
		sousCube.arriere.haut.gauche.x = original.arriere.haut.gauche.x + 2*longueurSousCube;
		sousCube.arriere.haut.gauche.y = original.arriere.haut.gauche.y;
		sousCube.arriere.haut.gauche.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 5 */
		sousCube.arriere.haut.droite.x = original.arriere.haut.gauche.x + 3*longueurSousCube;
		sousCube.arriere.haut.droite.y = original.arriere.haut.droite.y;
		sousCube.arriere.haut.droite.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 6 */
		sousCube.arriere.bas.droite.x = original.arriere.haut.gauche.x + 3*longueurSousCube;
		sousCube.arriere.bas.droite.y = original.arriere.haut.gauche.y - longueurSousCube;
		sousCube.arriere.bas.droite.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 7 */
		sousCube.arriere.bas.gauche.x = original.arriere.bas.gauche.x + 2*longueurSousCube;
		sousCube.arriere.bas.gauche.y = original.avant.haut.gauche.y - longueurSousCube;
		sousCube.arriere.bas.gauche.z = original.avant.haut.gauche.z - longueurSousCube;
    }
	final.append(sousCube);
	NEXT_STEP()

    {	// Cube n° 4	:	avant	milieu	droite
			// Calcul des  faces cachées
		sousCube.hiddenFaces = static_cast<Cube::Faces>(Cube::Haut | Cube::Bas);

		PARENT_FACE(Cube::Avant)
		PARENT_FACE(Cube::Droite)

			// Calcul des points
		/* point 0 */
		sousCube.avant.haut.gauche.x = original.avant.haut.gauche.x + 2*longueurSousCube;
		sousCube.avant.haut.gauche.y = original.avant.haut.gauche.y - longueurSousCube;
		sousCube.avant.haut.gauche.z = original.avant.haut.gauche.z;

		/* point 1 */
		sousCube.avant.haut.droite.x = original.avant.haut.gauche.x + 3*longueurSousCube;
		sousCube.avant.haut.droite.y = original.avant.haut.droite.y - longueurSousCube;
		sousCube.avant.haut.droite.z = original.avant.haut.droite.z;

		/* point 2 */
		sousCube.avant.bas.droite.x = original.avant.haut.gauche.x + 3*longueurSousCube;
		sousCube.avant.bas.droite.y = original.avant.bas.droite.y + longueurSousCube;
		sousCube.avant.bas.droite.z = original.avant.bas.droite.z;

		/* point 3 */
		sousCube.avant.bas.gauche.x = original.avant.bas.gauche.x + 2*longueurSousCube;
		sousCube.avant.bas.gauche.y = original.avant.haut.gauche.y - 2*longueurSousCube;
		sousCube.avant.bas.gauche.z = original.avant.haut.gauche.z;

		/* point 4 */
		sousCube.arriere.haut.gauche.x = original.arriere.haut.gauche.x + 2*longueurSousCube;
		sousCube.arriere.haut.gauche.y = original.arriere.haut.gauche.y - longueurSousCube;
		sousCube.arriere.haut.gauche.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 5 */
		sousCube.arriere.haut.droite.x = original.arriere.haut.gauche.x + 3*longueurSousCube;
		sousCube.arriere.haut.droite.y = original.arriere.haut.droite.y - longueurSousCube;
		sousCube.arriere.haut.droite.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 6 */
		sousCube.arriere.bas.droite.x = original.arriere.haut.gauche.x + 3*longueurSousCube;
		sousCube.arriere.bas.droite.y = original.arriere.haut.gauche.y - 2*longueurSousCube;
		sousCube.arriere.bas.droite.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 7 */
		sousCube.arriere.bas.gauche.x = original.arriere.bas.gauche.x + 2*longueurSousCube;
		sousCube.arriere.bas.gauche.y = original.avant.haut.gauche.y - 2*longueurSousCube;
		sousCube.arriere.bas.gauche.z = original.avant.haut.gauche.z - longueurSousCube;
    }
	final.append(sousCube);
	NEXT_STEP()

	{	// Cube n° 5	:	avant	bas		droite
			// Calcul des faces cachées
		sousCube.hiddenFaces = static_cast<Cube::Faces>(Cube::Haut | Cube::Gauche | Cube::Arriere);

		PARENT_FACE(Cube::Avant)
		PARENT_FACE(Cube::Bas)
		PARENT_FACE(Cube::Droite)

			// Calcul de points
		/* point 0 */
		sousCube.avant.haut.gauche.x = original.avant.haut.gauche.x + 2*longueurSousCube;
		sousCube.avant.haut.gauche.y = original.avant.haut.gauche.y - 2*longueurSousCube;
		sousCube.avant.haut.gauche.z = original.avant.haut.gauche.z;

		/* point 1 */
		sousCube.avant.haut.droite.x = original.avant.haut.gauche.x + 3*longueurSousCube;
		sousCube.avant.haut.droite.y = original.avant.haut.droite.y - 2*longueurSousCube;
		sousCube.avant.haut.droite.z = original.avant.haut.droite.z;

		/* point 2 */
		sousCube.avant.bas.droite.x = original.avant.haut.gauche.x + 3*longueurSousCube;
		sousCube.avant.bas.droite.y = original.avant.bas.droite.y ;
		sousCube.avant.bas.droite.z = original.avant.bas.droite.z;

		/* point 3 */
		sousCube.avant.bas.gauche.x = original.avant.bas.gauche.x + 2*longueurSousCube;
		sousCube.avant.bas.gauche.y = original.avant.haut.gauche.y - 3*longueurSousCube;
		sousCube.avant.bas.gauche.z = original.avant.haut.gauche.z;

		/* point 4 */
		sousCube.arriere.haut.gauche.x = original.arriere.haut.gauche.x + 2*longueurSousCube;
		sousCube.arriere.haut.gauche.y = original.arriere.haut.gauche.y - 2*longueurSousCube;
		sousCube.arriere.haut.gauche.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 5 */
		sousCube.arriere.haut.droite.x = original.arriere.haut.gauche.x + 3*longueurSousCube;
		sousCube.arriere.haut.droite.y = original.arriere.haut.droite.y - 2*longueurSousCube;
		sousCube.arriere.haut.droite.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 6 */
		sousCube.arriere.bas.droite.x = original.arriere.haut.gauche.x + 3*longueurSousCube;
		sousCube.arriere.bas.droite.y = original.arriere.haut.gauche.y - 3*longueurSousCube;
		sousCube.arriere.bas.droite.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 7 */
		sousCube.arriere.bas.gauche.x = original.arriere.bas.gauche.x + 2*longueurSousCube;
		sousCube.arriere.bas.gauche.y = original.avant.haut.gauche.y - 3*longueurSousCube;
		sousCube.arriere.bas.gauche.z = original.avant.haut.gauche.z - longueurSousCube;
	}
	final.append(sousCube);
	NEXT_STEP()

	{	// Cube n° 6	:	avant	bas		milieu
			// Calcul des faces cachées
		sousCube.hiddenFaces = static_cast<Cube::Faces>(Cube::Gauche | Cube::Droite);

		PARENT_FACE(Cube::Avant)
		PARENT_FACE(Cube::Bas)

			// Calcul des points
		/* point 0 */
		sousCube.avant.haut.gauche.x = original.avant.haut.gauche.x + longueurSousCube;
		sousCube.avant.haut.gauche.y = original.avant.haut.gauche.y - 2*longueurSousCube;
		sousCube.avant.haut.gauche.z = original.avant.haut.gauche.z;

		/* point 1 */
		sousCube.avant.haut.droite.x = original.avant.haut.gauche.x + 2*longueurSousCube;
		sousCube.avant.haut.droite.y = original.avant.haut.droite.y - 2*longueurSousCube;
		sousCube.avant.haut.droite.z = original.avant.haut.droite.z;

		/* point 2 */
		sousCube.avant.bas.droite.x = original.avant.haut.gauche.x + 2*longueurSousCube;
		sousCube.avant.bas.droite.y = original.avant.bas.droite.y ;
		sousCube.avant.bas.droite.z = original.avant.bas.droite.z;

		/* point 3 */
		sousCube.avant.bas.gauche.x = original.avant.bas.gauche.x + 1*longueurSousCube;
		sousCube.avant.bas.gauche.y = original.avant.haut.gauche.y - 3*longueurSousCube;
		sousCube.avant.bas.gauche.z = original.avant.haut.gauche.z;

		/* point 4 */
		sousCube.arriere.haut.gauche.x = original.arriere.haut.gauche.x + 1*longueurSousCube;
		sousCube.arriere.haut.gauche.y = original.arriere.haut.gauche.y - 2*longueurSousCube;
		sousCube.arriere.haut.gauche.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 5 */
		sousCube.arriere.haut.droite.x = original.arriere.haut.gauche.x + 2*longueurSousCube;
		sousCube.arriere.haut.droite.y = original.arriere.haut.droite.y - 2*longueurSousCube;
		sousCube.arriere.haut.droite.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 6 */
		sousCube.arriere.bas.droite.x = original.arriere.haut.gauche.x + 2*longueurSousCube;
		sousCube.arriere.bas.droite.y = original.arriere.haut.gauche.y - 3*longueurSousCube;
		sousCube.arriere.bas.droite.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 7 */
		sousCube.arriere.bas.gauche.x = original.arriere.bas.gauche.x + longueurSousCube;
		sousCube.arriere.bas.gauche.y = original.avant.haut.gauche.y - 3*longueurSousCube;
		sousCube.arriere.bas.gauche.z = original.avant.haut.gauche.z - longueurSousCube;
	}
	final.append(sousCube);
	NEXT_STEP()

	{	// Cube n° 7	:	avant	bas		gauche
			// Calcul des faces cachées
		sousCube.hiddenFaces = static_cast<Cube::Faces>(Cube::Haut | Cube::Droite | Cube::Arriere);

		PARENT_FACE(Cube::Bas)
		PARENT_FACE(Cube::Avant)
		PARENT_FACE(Cube::Gauche)

			// Calcul des points
		/* point 0 */
		sousCube.avant.haut.gauche.x = original.avant.haut.gauche.x;
		sousCube.avant.haut.gauche.y = original.avant.haut.gauche.y - 2*longueurSousCube;
		sousCube.avant.haut.gauche.z = original.avant.haut.gauche.z;

		/* point 1 */
		sousCube.avant.haut.droite.x = original.avant.haut.gauche.x + longueurSousCube;
		sousCube.avant.haut.droite.y = original.avant.haut.droite.y - 2*longueurSousCube;
		sousCube.avant.haut.droite.z = original.avant.haut.droite.z;

		/* point 2 */
		sousCube.avant.bas.droite.x = original.avant.haut.gauche.x + longueurSousCube;
		sousCube.avant.bas.droite.y = original.avant.bas.droite.y;
		sousCube.avant.bas.droite.z = original.avant.bas.droite.z;

		/* point 3 */
		sousCube.avant.bas.gauche.x = original.avant.bas.gauche.x;
		sousCube.avant.bas.gauche.y = original.avant.haut.gauche.y - 3*longueurSousCube;
		sousCube.avant.bas.gauche.z = original.avant.haut.gauche.z;

		/* point 4 */
		sousCube.arriere.haut.gauche.x = original.arriere.haut.gauche.x;
		sousCube.arriere.haut.gauche.y = original.arriere.haut.gauche.y - 2*longueurSousCube;
		sousCube.arriere.haut.gauche.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 5 */
		sousCube.arriere.haut.droite.x = original.arriere.haut.gauche.x + longueurSousCube;
		sousCube.arriere.haut.droite.y = original.arriere.haut.droite.y - 2*longueurSousCube;
		sousCube.arriere.haut.droite.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 6 */
		sousCube.arriere.bas.droite.x = original.arriere.haut.gauche.x + longueurSousCube;
		sousCube.arriere.bas.droite.y = original.arriere.haut.gauche.y - 3*longueurSousCube;
		sousCube.arriere.bas.droite.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 7 */
		sousCube.arriere.bas.gauche.x = original.arriere.bas.gauche.x;
		sousCube.arriere.bas.gauche.y = original.avant.haut.gauche.y - 3*longueurSousCube;
		sousCube.arriere.bas.gauche.z = original.avant.haut.gauche.z - longueurSousCube;
	}
	final.append(sousCube);
	NEXT_STEP()

    {	// Cube n° 8	:	avant	milieu	gauche
			// Calcul des faces cachées
		sousCube.hiddenFaces = static_cast<Cube::Faces>(Cube::Haut | Cube::Bas);

		PARENT_FACE(Cube::Gauche)
		PARENT_FACE(Cube::Avant)

			// Calcul des points
		/* point 0 */
		sousCube.avant.haut.gauche.x = original.avant.haut.gauche.x;
		sousCube.avant.haut.gauche.y = original.avant.haut.gauche.y - longueurSousCube;
		sousCube.avant.haut.gauche.z = original.avant.haut.gauche.z;

		/* point 1 */
		sousCube.avant.haut.droite.x = original.avant.haut.gauche.x + longueurSousCube;
		sousCube.avant.haut.droite.y = original.avant.haut.droite.y - longueurSousCube;
		sousCube.avant.haut.droite.z = original.avant.haut.droite.z;

		/* point 2 */
		sousCube.avant.bas.droite.x = original.avant.haut.gauche.x + longueurSousCube;
		sousCube.avant.bas.droite.y = original.avant.bas.droite.y + longueurSousCube;
		sousCube.avant.bas.droite.z = original.avant.bas.droite.z;

		/* point 3 */
		sousCube.avant.bas.gauche.x = original.avant.bas.gauche.x;
		sousCube.avant.bas.gauche.y = original.avant.haut.gauche.y - 2*longueurSousCube;
		sousCube.avant.bas.gauche.z = original.avant.haut.gauche.z;

		/* point 4 */
		sousCube.arriere.haut.gauche.x = original.arriere.haut.gauche.x;
		sousCube.arriere.haut.gauche.y = original.arriere.haut.gauche.y - longueurSousCube;
		sousCube.arriere.haut.gauche.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 5 */
		sousCube.arriere.haut.droite.x = original.arriere.haut.gauche.x + longueurSousCube;
		sousCube.arriere.haut.droite.y = original.arriere.haut.droite.y - longueurSousCube;
		sousCube.arriere.haut.droite.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 6 */
		sousCube.arriere.bas.droite.x = original.arriere.haut.gauche.x + longueurSousCube;
		sousCube.arriere.bas.droite.y = original.arriere.haut.gauche.y - 2*longueurSousCube;
		sousCube.arriere.bas.droite.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 7 */
		sousCube.arriere.bas.gauche.x = original.arriere.bas.gauche.x;
		sousCube.arriere.bas.gauche.y = original.avant.haut.gauche.y - 2*longueurSousCube;
		sousCube.arriere.bas.gauche.z = original.avant.haut.gauche.z - longueurSousCube;
    }
	final.append(sousCube);
	NEXT_STEP()

	{	// Cube n° 9	:	arrière	haut	gauche
			// Calcul des faces
		sousCube.hiddenFaces = static_cast<Cube::Faces>(Cube::Bas | Cube::Avant | Cube::Droite);

		PARENT_FACE(Cube::Arriere)
		PARENT_FACE(Cube::Haut)
		PARENT_FACE(Cube::Gauche)

			// Calcul des points
		/* point 0 */
		sousCube.avant.haut.gauche.x = original.avant.haut.gauche.x;
		sousCube.avant.haut.gauche.y = original.avant.haut.gauche.y;
		sousCube.avant.haut.gauche.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 1 */
		sousCube.avant.haut.droite.x = original.avant.haut.gauche.x + longueurSousCube;
		sousCube.avant.haut.droite.y = original.avant.haut.droite.y;
		sousCube.avant.haut.droite.z = original.avant.haut.droite.z - 2*longueurSousCube;

		/* point 2 */
		sousCube.avant.bas.droite.x = original.avant.haut.gauche.x + longueurSousCube;
		sousCube.avant.bas.droite.y = original.avant.bas.droite.y + 2 * longueurSousCube;
		sousCube.avant.bas.droite.z = original.avant.bas.droite.z - 2*longueurSousCube;

		/* point 3 */
		sousCube.avant.bas.gauche.x = original.avant.bas.gauche.x;
		sousCube.avant.bas.gauche.y = original.avant.haut.gauche.y - longueurSousCube;
		sousCube.avant.bas.gauche.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 4 */
		sousCube.arriere.haut.gauche.x = original.arriere.haut.gauche.x;
		sousCube.arriere.haut.gauche.y = original.arriere.haut.gauche.y;
		sousCube.arriere.haut.gauche.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 5 */
		sousCube.arriere.haut.droite.x = original.arriere.haut.gauche.x + longueurSousCube;
		sousCube.arriere.haut.droite.y = original.arriere.haut.droite.y;
		sousCube.arriere.haut.droite.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 6 */
		sousCube.arriere.bas.droite.x = original.arriere.haut.gauche.x + longueurSousCube;
		sousCube.arriere.bas.droite.y = original.arriere.haut.gauche.y - longueurSousCube;
		sousCube.arriere.bas.droite.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 7 */
		sousCube.arriere.bas.gauche.x = original.arriere.bas.gauche.x;
		sousCube.arriere.bas.gauche.y = original.avant.haut.gauche.y - longueurSousCube;
		sousCube.arriere.bas.gauche.z = original.avant.haut.gauche.z - 3*longueurSousCube;
	}
	final.append(sousCube);
	NEXT_STEP()

    {	// Cube n° 10	:	arrière	haut	milieux
			// Calcul des faces cachées
		sousCube.hiddenFaces = static_cast<Cube::Faces>(Cube::Gauche | Cube::Droite);

		PARENT_FACE(Cube::Arriere)
		PARENT_FACE(Cube::Haut)

			// Calcul des points
		/* point 0 */
		sousCube.avant.haut.gauche.x = original.avant.haut.gauche.x + longueurSousCube;
		sousCube.avant.haut.gauche.y = original.avant.haut.gauche.y;
		sousCube.avant.haut.gauche.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 1 */
		sousCube.avant.haut.droite.x = original.avant.haut.gauche.x + 2*longueurSousCube;
		sousCube.avant.haut.droite.y = original.avant.haut.droite.y;
		sousCube.avant.haut.droite.z = original.avant.haut.droite.z - 2*longueurSousCube;

		/* point 2 */
		sousCube.avant.bas.droite.x = original.avant.haut.gauche.x + 2*longueurSousCube;
		sousCube.avant.bas.droite.y = original.avant.bas.droite.y + 2*longueurSousCube;
		sousCube.avant.bas.droite.z = original.avant.bas.droite.z - 2*longueurSousCube;

		/* point 3 */
		sousCube.avant.bas.gauche.x = original.avant.bas.gauche.x + longueurSousCube;
		sousCube.avant.bas.gauche.y = original.avant.haut.gauche.y - longueurSousCube;
		sousCube.avant.bas.gauche.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 4 */
		sousCube.arriere.haut.gauche.x = original.arriere.haut.gauche.x + longueurSousCube;
		sousCube.arriere.haut.gauche.y = original.arriere.haut.gauche.y;
		sousCube.arriere.haut.gauche.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 5 */
		sousCube.arriere.haut.droite.x = original.arriere.haut.gauche.x + 2*longueurSousCube;
		sousCube.arriere.haut.droite.y = original.arriere.haut.droite.y;
		sousCube.arriere.haut.droite.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 6 */
		sousCube.arriere.bas.droite.x = original.arriere.haut.gauche.x + 2*longueurSousCube;
		sousCube.arriere.bas.droite.y = original.arriere.haut.gauche.y - longueurSousCube;
		sousCube.arriere.bas.droite.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 7 */
		sousCube.arriere.bas.gauche.x = original.arriere.bas.gauche.x + longueurSousCube;
		sousCube.arriere.bas.gauche.y = original.avant.haut.gauche.y - longueurSousCube;
		sousCube.arriere.bas.gauche.z = original.avant.haut.gauche.z - 3*longueurSousCube;
    }
	final.append(sousCube);
	NEXT_STEP()

    {	// Cube n° 11	:	arrière haut	droite
			// Calcul des faces cachées
		sousCube.hiddenFaces = static_cast<Cube::Faces>(Cube::Bas | Cube::Gauche | Cube::Avant);

		PARENT_FACE(Cube::Arriere)
		PARENT_FACE(Cube::Haut)
		PARENT_FACE(Cube::Droite)

			// Calculs des points
		/* point 0 */
		sousCube.avant.haut.gauche.x = original.avant.haut.gauche.x + 2*longueurSousCube;
		sousCube.avant.haut.gauche.y = original.avant.haut.gauche.y;
		sousCube.avant.haut.gauche.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 1 */
		sousCube.avant.haut.droite.x = original.avant.haut.gauche.x + 3*longueurSousCube;
		sousCube.avant.haut.droite.y = original.avant.haut.droite.y;
		sousCube.avant.haut.droite.z = original.avant.haut.droite.z - 2*longueurSousCube;

		/* point 2 */
		sousCube.avant.bas.droite.x = original.avant.haut.gauche.x + 3*longueurSousCube;
		sousCube.avant.bas.droite.y = original.avant.bas.droite.y + 2*longueurSousCube;
		sousCube.avant.bas.droite.z = original.avant.bas.droite.z - 2*longueurSousCube;

		/* point 3 */
		sousCube.avant.bas.gauche.x = original.avant.bas.gauche.x + 2*longueurSousCube;
		sousCube.avant.bas.gauche.y = original.avant.haut.gauche.y - longueurSousCube;
		sousCube.avant.bas.gauche.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 4 */
		sousCube.arriere.haut.gauche.x = original.arriere.haut.gauche.x + 2*longueurSousCube;
		sousCube.arriere.haut.gauche.y = original.arriere.haut.gauche.y;
		sousCube.arriere.haut.gauche.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 5 */
		sousCube.arriere.haut.droite.x = original.arriere.haut.gauche.x + 3*longueurSousCube;
		sousCube.arriere.haut.droite.y = original.arriere.haut.droite.y;
		sousCube.arriere.haut.droite.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 6 */
		sousCube.arriere.bas.droite.x = original.arriere.haut.gauche.x + 3*longueurSousCube;
		sousCube.arriere.bas.droite.y = original.arriere.haut.gauche.y - longueurSousCube;
		sousCube.arriere.bas.droite.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 7 */
		sousCube.arriere.bas.gauche.x = original.arriere.bas.gauche.x + 2*longueurSousCube;
		sousCube.arriere.bas.gauche.y = original.avant.haut.gauche.y - longueurSousCube;
		sousCube.arriere.bas.gauche.z = original.avant.haut.gauche.z - 3*longueurSousCube;
    }
	final.append(sousCube);
	NEXT_STEP()

    {	// Cube n° 12	:	arrière	milieu	droite
			// Calcul des faces cachées
		sousCube.hiddenFaces = static_cast<Cube::Faces>(Cube::Haut | Cube::Bas);

		PARENT_FACE(Cube::Arriere)
		PARENT_FACE(Cube::Droite)

			// Calcul des points
		/* point 0 */
		sousCube.avant.haut.gauche.x = original.avant.haut.gauche.x + 2*longueurSousCube;
		sousCube.avant.haut.gauche.y = original.avant.haut.gauche.y - longueurSousCube;
		sousCube.avant.haut.gauche.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 1 */
		sousCube.avant.haut.droite.x = original.avant.haut.gauche.x + 3*longueurSousCube;
		sousCube.avant.haut.droite.y = original.avant.haut.droite.y - longueurSousCube;
		sousCube.avant.haut.droite.z = original.avant.haut.droite.z - 2*longueurSousCube;

		/* point 2 */
		sousCube.avant.bas.droite.x = original.avant.haut.gauche.x + 3*longueurSousCube;
		sousCube.avant.bas.droite.y = original.avant.bas.droite.y + longueurSousCube;
		sousCube.avant.bas.droite.z = original.avant.bas.droite.z - 2*longueurSousCube;

		/* point 3 */
		sousCube.avant.bas.gauche.x = original.avant.bas.gauche.x + 2*longueurSousCube;
		sousCube.avant.bas.gauche.y = original.avant.haut.gauche.y - 2*longueurSousCube;
		sousCube.avant.bas.gauche.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 4 */
		sousCube.arriere.haut.gauche.x = original.arriere.haut.gauche.x + 2*longueurSousCube;
		sousCube.arriere.haut.gauche.y = original.arriere.haut.gauche.y - longueurSousCube;
		sousCube.arriere.haut.gauche.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 5 */
		sousCube.arriere.haut.droite.x = original.arriere.haut.gauche.x + 3*longueurSousCube;
		sousCube.arriere.haut.droite.y = original.arriere.haut.droite.y - longueurSousCube;
		sousCube.arriere.haut.droite.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 6 */
		sousCube.arriere.bas.droite.x = original.arriere.haut.gauche.x + 3*longueurSousCube;
		sousCube.arriere.bas.droite.y = original.arriere.haut.gauche.y - 2*longueurSousCube;
		sousCube.arriere.bas.droite.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 7 */
		sousCube.arriere.bas.gauche.x = original.arriere.bas.gauche.x + 2*longueurSousCube;
		sousCube.arriere.bas.gauche.y = original.avant.haut.gauche.y - 2*longueurSousCube;
		sousCube.arriere.bas.gauche.z = original.avant.haut.gauche.z - 3*longueurSousCube;
    }
	final.append(sousCube);
	NEXT_STEP()

    {	// Cube n° 13	:	arrière	bas		droite
			// Calcul des faces cachées
		sousCube.hiddenFaces = static_cast<Cube::Faces>(Cube::Haut | Cube::Avant | Cube::Gauche);

		PARENT_FACE(Cube::Arriere)
		PARENT_FACE(Cube::Bas)
		PARENT_FACE(Cube::Droite)

			// Calcul des points
		/* point 0 */
		sousCube.avant.haut.gauche.x = original.avant.haut.gauche.x + 2*longueurSousCube;
		sousCube.avant.haut.gauche.y = original.avant.haut.gauche.y - 2*longueurSousCube;
		sousCube.avant.haut.gauche.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 1 */
		sousCube.avant.haut.droite.x = original.avant.haut.gauche.x + 3*longueurSousCube;
		sousCube.avant.haut.droite.y = original.avant.haut.droite.y - 2*longueurSousCube;
		sousCube.avant.haut.droite.z = original.avant.haut.droite.z - 2*longueurSousCube;

		/* point 2 */
		sousCube.avant.bas.droite.x = original.avant.haut.gauche.x + 3*longueurSousCube;
		sousCube.avant.bas.droite.y = original.avant.bas.droite.y ;
		sousCube.avant.bas.droite.z = original.avant.bas.droite.z - 2*longueurSousCube;

		/* point 3 */
		sousCube.avant.bas.gauche.x = original.avant.bas.gauche.x + 2*longueurSousCube;
		sousCube.avant.bas.gauche.y = original.avant.haut.gauche.y - 3*longueurSousCube;
		sousCube.avant.bas.gauche.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 4 */
		sousCube.arriere.haut.gauche.x = original.arriere.haut.gauche.x + 2*longueurSousCube;
		sousCube.arriere.haut.gauche.y = original.arriere.haut.gauche.y - 2*longueurSousCube;
		sousCube.arriere.haut.gauche.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 5 */
		sousCube.arriere.haut.droite.x = original.arriere.haut.gauche.x + 3*longueurSousCube;
		sousCube.arriere.haut.droite.y = original.arriere.haut.droite.y - 2*longueurSousCube;
		sousCube.arriere.haut.droite.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 6 */
		sousCube.arriere.bas.droite.x = original.arriere.haut.gauche.x + 3*longueurSousCube;
		sousCube.arriere.bas.droite.y = original.arriere.haut.gauche.y - 3*longueurSousCube;
		sousCube.arriere.bas.droite.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 7 */
		sousCube.arriere.bas.gauche.x = original.arriere.bas.gauche.x + 2*longueurSousCube;
		sousCube.arriere.bas.gauche.y = original.avant.haut.gauche.y - 3*longueurSousCube;
		sousCube.arriere.bas.gauche.z = original.avant.haut.gauche.z - 3*longueurSousCube;
    }
	final.append(sousCube);
	NEXT_STEP()

    {	// Cube n° 14	:	arrière	bas		milieu
			// Calcul des faces cachées
		sousCube.hiddenFaces = static_cast<Cube::Faces>(Cube::Gauche | Cube::Droite);

		PARENT_FACE(Cube::Arriere)
		PARENT_FACE(Cube::Bas)

			// Calcul des points
		/* point 0 */
		sousCube.avant.haut.gauche.x = original.avant.haut.gauche.x + longueurSousCube;
		sousCube.avant.haut.gauche.y = original.avant.haut.gauche.y - 2*longueurSousCube;
		sousCube.avant.haut.gauche.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 1 */
		sousCube.avant.haut.droite.x = original.avant.haut.gauche.x + 2*longueurSousCube;
		sousCube.avant.haut.droite.y = original.avant.haut.droite.y - 2*longueurSousCube;
		sousCube.avant.haut.droite.z = original.avant.haut.droite.z - 2*longueurSousCube;

		/* point 2 */
		sousCube.avant.bas.droite.x = original.avant.haut.gauche.x + 2*longueurSousCube;
		sousCube.avant.bas.droite.y = original.avant.bas.droite.y ;
		sousCube.avant.bas.droite.z = original.avant.bas.droite.z - 2*longueurSousCube;

		/* point 3 */
		sousCube.avant.bas.gauche.x = original.avant.bas.gauche.x + 1*longueurSousCube;
		sousCube.avant.bas.gauche.y = original.avant.haut.gauche.y - 3*longueurSousCube;
		sousCube.avant.bas.gauche.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 4 */
		sousCube.arriere.haut.gauche.x = original.arriere.haut.gauche.x + 1*longueurSousCube;
		sousCube.arriere.haut.gauche.y = original.arriere.haut.gauche.y - 2*longueurSousCube;
		sousCube.arriere.haut.gauche.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 5 */
		sousCube.arriere.haut.droite.x = original.arriere.haut.gauche.x + 2*longueurSousCube;
		sousCube.arriere.haut.droite.y = original.arriere.haut.droite.y - 2*longueurSousCube;
		sousCube.arriere.haut.droite.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 6 */
		sousCube.arriere.bas.droite.x = original.arriere.haut.gauche.x + 2*longueurSousCube;
		sousCube.arriere.bas.droite.y = original.arriere.haut.gauche.y - 3*longueurSousCube;
		sousCube.arriere.bas.droite.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 7 */
		sousCube.arriere.bas.gauche.x = original.arriere.bas.gauche.x + longueurSousCube;
		sousCube.arriere.bas.gauche.y = original.avant.haut.gauche.y - 3*longueurSousCube;
		sousCube.arriere.bas.gauche.z = original.avant.haut.gauche.z - 3*longueurSousCube;
    }
	final.append(sousCube);
	NEXT_STEP()

    {	// Cube n° 15	:	arrière	bas		gauche
			// Calcul des faces cachées
		sousCube.hiddenFaces = static_cast<Cube::Faces>(Cube::Haut | Cube::Avant | Cube::Droite);

		PARENT_FACE(Cube::Arriere)
		PARENT_FACE(Cube::Bas)
		PARENT_FACE(Cube::Gauche)

			// Calcul des points
		/* point 0 */
		sousCube.avant.haut.gauche.x = original.avant.haut.gauche.x;
		sousCube.avant.haut.gauche.y = original.avant.haut.gauche.y - 2*longueurSousCube;
		sousCube.avant.haut.gauche.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 1 */
		sousCube.avant.haut.droite.x = original.avant.haut.gauche.x + longueurSousCube;
		sousCube.avant.haut.droite.y = original.avant.haut.droite.y - 2*longueurSousCube;
		sousCube.avant.haut.droite.z = original.avant.haut.droite.z - 2*longueurSousCube;

		/* point 2 */
		sousCube.avant.bas.droite.x = original.avant.haut.gauche.x + longueurSousCube;
		sousCube.avant.bas.droite.y = original.avant.bas.droite.y;
		sousCube.avant.bas.droite.z = original.avant.bas.droite.z - 2*longueurSousCube;

		/* point 3 */
		sousCube.avant.bas.gauche.x = original.avant.bas.gauche.x;
		sousCube.avant.bas.gauche.y = original.avant.haut.gauche.y - 3*longueurSousCube;
		sousCube.avant.bas.gauche.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 4 */
		sousCube.arriere.haut.gauche.x = original.arriere.haut.gauche.x;
		sousCube.arriere.haut.gauche.y = original.arriere.haut.gauche.y - 2*longueurSousCube;
		sousCube.arriere.haut.gauche.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 5 */
		sousCube.arriere.haut.droite.x = original.arriere.haut.gauche.x + longueurSousCube;
		sousCube.arriere.haut.droite.y = original.arriere.haut.droite.y - 2*longueurSousCube;
		sousCube.arriere.haut.droite.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 6 */
		sousCube.arriere.bas.droite.x = original.arriere.haut.gauche.x + longueurSousCube;
		sousCube.arriere.bas.droite.y = original.arriere.haut.gauche.y - 3*longueurSousCube;
		sousCube.arriere.bas.droite.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 7 */
		sousCube.arriere.bas.gauche.x = original.arriere.bas.gauche.x;
		sousCube.arriere.bas.gauche.y = original.avant.haut.gauche.y - 3*longueurSousCube;
		sousCube.arriere.bas.gauche.z = original.avant.haut.gauche.z - 3*longueurSousCube;
    }
	final.append(sousCube);
	NEXT_STEP()

    {	// Cube n° 16	:	arrière	milieu	gauche
			// Calcul des faces cachées
		sousCube.hiddenFaces = static_cast<Cube::Faces>(Cube::Haut | Cube::Bas);

		PARENT_FACE(Cube::Arriere)
		PARENT_FACE(Cube::Gauche)

			// Calcul des points
		/* point 0 */
		sousCube.avant.haut.gauche.x = original.avant.haut.gauche.x;
		sousCube.avant.haut.gauche.y = original.avant.haut.gauche.y - longueurSousCube;
		sousCube.avant.haut.gauche.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 1 */
		sousCube.avant.haut.droite.x = original.avant.haut.gauche.x + longueurSousCube;
		sousCube.avant.haut.droite.y = original.avant.haut.droite.y - longueurSousCube;
		sousCube.avant.haut.droite.z = original.avant.haut.droite.z - 2*longueurSousCube;

		/* point 2 */
		sousCube.avant.bas.droite.x = original.avant.haut.gauche.x + longueurSousCube;
		sousCube.avant.bas.droite.y = original.avant.bas.droite.y + longueurSousCube;
		sousCube.avant.bas.droite.z = original.avant.bas.droite.z - 2*longueurSousCube;

		/* point 3 */
		sousCube.avant.bas.gauche.x = original.avant.bas.gauche.x;
		sousCube.avant.bas.gauche.y = original.avant.haut.gauche.y - 2*longueurSousCube;
		sousCube.avant.bas.gauche.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 4 */
		sousCube.arriere.haut.gauche.x = original.arriere.haut.gauche.x;
		sousCube.arriere.haut.gauche.y = original.arriere.haut.gauche.y - longueurSousCube;
		sousCube.arriere.haut.gauche.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 5 */
		sousCube.arriere.haut.droite.x = original.arriere.haut.gauche.x + longueurSousCube;
		sousCube.arriere.haut.droite.y = original.arriere.haut.droite.y - longueurSousCube;
		sousCube.arriere.haut.droite.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 6 */
		sousCube.arriere.bas.droite.x = original.arriere.haut.gauche.x + longueurSousCube;
		sousCube.arriere.bas.droite.y = original.arriere.haut.gauche.y - 2*longueurSousCube;
		sousCube.arriere.bas.droite.z = original.avant.haut.gauche.z - 3*longueurSousCube;

		/* point 7 */
		sousCube.arriere.bas.gauche.x = original.arriere.bas.gauche.x;
		sousCube.arriere.bas.gauche.y = original.avant.haut.gauche.y - 2*longueurSousCube;
		sousCube.arriere.bas.gauche.z = original.avant.haut.gauche.z - 3*longueurSousCube;
    }
	final.append(sousCube);
	NEXT_STEP()

    {	// Cube n° 17	:	milieu	haut	gauche
			// Calcul des faces cachées
		sousCube.hiddenFaces = static_cast<Cube::Faces>(Cube::Avant | Cube::Arriere);

		PARENT_FACE(Cube::Haut)
		PARENT_FACE(Cube::Gauche)

			// Calcul des points
		/* point 0 */
		sousCube.avant.haut.gauche.x = original.avant.haut.gauche.x;
		sousCube.avant.haut.gauche.y = original.avant.haut.gauche.y;
		sousCube.avant.haut.gauche.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 1 */
		sousCube.avant.haut.droite.x = original.avant.haut.gauche.x + longueurSousCube;
		sousCube.avant.haut.droite.y = original.avant.haut.droite.y;
		sousCube.avant.haut.droite.z = original.avant.haut.droite.z - longueurSousCube;

		/* point 2 */
		sousCube.avant.bas.droite.x = original.avant.haut.gauche.x + longueurSousCube;
		sousCube.avant.bas.droite.y = original.avant.bas.droite.y + 2 * longueurSousCube;
		sousCube.avant.bas.droite.z = original.avant.bas.droite.z - longueurSousCube;

		/* point 3 */
		sousCube.avant.bas.gauche.x = original.avant.bas.gauche.x;
		sousCube.avant.bas.gauche.y = original.avant.haut.gauche.y - longueurSousCube;
		sousCube.avant.bas.gauche.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 4 */
		sousCube.arriere.haut.gauche.x = original.arriere.haut.gauche.x;
		sousCube.arriere.haut.gauche.y = original.arriere.haut.gauche.y;
		sousCube.arriere.haut.gauche.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 5 */
		sousCube.arriere.haut.droite.x = original.arriere.haut.gauche.x + longueurSousCube;
		sousCube.arriere.haut.droite.y = original.arriere.haut.droite.y;
		sousCube.arriere.haut.droite.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 6 */
		sousCube.arriere.bas.droite.x = original.arriere.haut.gauche.x + longueurSousCube;
		sousCube.arriere.bas.droite.y = original.arriere.haut.gauche.y - longueurSousCube;
		sousCube.arriere.bas.droite.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 7 */
		sousCube.arriere.bas.gauche.x = original.arriere.bas.gauche.x;
		sousCube.arriere.bas.gauche.y = original.avant.haut.gauche.y - longueurSousCube;
		sousCube.arriere.bas.gauche.z = original.avant.haut.gauche.z - 2*longueurSousCube;
    }
	final.append(sousCube);
	NEXT_STEP()

	{	// Cube n° 18	:	milieu	haut	droite
			// Calcul des faces cachées
		sousCube.hiddenFaces = static_cast<Cube::Faces>(Cube::Avant | Cube::Arriere);

		PARENT_FACE(Cube::Haut)
		PARENT_FACE(Cube::Droite)

			// Calcul des points
		/* point 0 */
		sousCube.avant.haut.gauche.x = original.avant.haut.gauche.x + 2*longueurSousCube;
		sousCube.avant.haut.gauche.y = original.avant.haut.gauche.y;
		sousCube.avant.haut.gauche.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 1 */
		sousCube.avant.haut.droite.x = original.avant.haut.gauche.x + 3*longueurSousCube;
		sousCube.avant.haut.droite.y = original.avant.haut.droite.y;
		sousCube.avant.haut.droite.z = original.avant.haut.droite.z - longueurSousCube;

		/* point 2 */
		sousCube.avant.bas.droite.x = original.avant.haut.gauche.x + 3*longueurSousCube;
		sousCube.avant.bas.droite.y = original.avant.bas.droite.y + 2 * longueurSousCube;
		sousCube.avant.bas.droite.z = original.avant.bas.droite.z - longueurSousCube;

		/* point 3 */
		sousCube.avant.bas.gauche.x = original.avant.bas.gauche.x + 2*longueurSousCube;
		sousCube.avant.bas.gauche.y = original.avant.haut.gauche.y - longueurSousCube;
		sousCube.avant.bas.gauche.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 4 */
		sousCube.arriere.haut.gauche.x = original.arriere.haut.gauche.x + 2*longueurSousCube;
		sousCube.arriere.haut.gauche.y = original.arriere.haut.gauche.y;
		sousCube.arriere.haut.gauche.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 5 */
		sousCube.arriere.haut.droite.x = original.arriere.haut.gauche.x + 3*longueurSousCube;
		sousCube.arriere.haut.droite.y = original.arriere.haut.droite.y;
		sousCube.arriere.haut.droite.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 6 */
		sousCube.arriere.bas.droite.x = original.arriere.haut.gauche.x + 3*longueurSousCube;
		sousCube.arriere.bas.droite.y = original.arriere.haut.gauche.y - longueurSousCube;
		sousCube.arriere.bas.droite.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 7 */
		sousCube.arriere.bas.gauche.x = original.arriere.bas.gauche.x + 2*longueurSousCube;
		sousCube.arriere.bas.gauche.y = original.avant.haut.gauche.y - longueurSousCube;
		sousCube.arriere.bas.gauche.z = original.avant.haut.gauche.z - 2*longueurSousCube;
	}
	final.append(sousCube);
	NEXT_STEP()

    {	// Cube n° 19	:	milieu	bas		droite
			// Calcul des faces cachées
		sousCube.hiddenFaces = static_cast<Cube::Faces>(Cube::Avant | Cube::Arriere);

		PARENT_FACE(Cube::Bas)
		PARENT_FACE(Cube::Droite)

			// Calcul des points
		/* point 0 */
		sousCube.avant.haut.gauche.x = original.avant.haut.gauche.x + 2*longueurSousCube;
		sousCube.avant.haut.gauche.y = original.avant.haut.gauche.y - 2*longueurSousCube;
		sousCube.avant.haut.gauche.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 1 */
		sousCube.avant.haut.droite.x = original.avant.haut.gauche.x + 3*longueurSousCube;
		sousCube.avant.haut.droite.y = original.avant.haut.droite.y - 2*longueurSousCube;
		sousCube.avant.haut.droite.z = original.avant.haut.droite.z - longueurSousCube;

		/* point 2 */
		sousCube.avant.bas.droite.x = original.avant.haut.gauche.x + 3*longueurSousCube;
		sousCube.avant.bas.droite.y = original.avant.bas.droite.y;
		sousCube.avant.bas.droite.z = original.avant.bas.droite.z - longueurSousCube;

		/* point 3 */
		sousCube.avant.bas.gauche.x = original.avant.bas.gauche.x + 2*longueurSousCube;
		sousCube.avant.bas.gauche.y = original.avant.haut.gauche.y - 3*longueurSousCube;
		sousCube.avant.bas.gauche.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 4 */
		sousCube.arriere.haut.gauche.x = original.arriere.haut.gauche.x + 2*longueurSousCube;
		sousCube.arriere.haut.gauche.y = original.arriere.haut.gauche.y - 2*longueurSousCube;
		sousCube.arriere.haut.gauche.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 5 */
		sousCube.arriere.haut.droite.x = original.arriere.haut.gauche.x + 3*longueurSousCube;
		sousCube.arriere.haut.droite.y = original.arriere.haut.droite.y - 2*longueurSousCube;
		sousCube.arriere.haut.droite.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 6 */
		sousCube.arriere.bas.droite.x = original.arriere.haut.gauche.x + 3*longueurSousCube;
		sousCube.arriere.bas.droite.y = original.arriere.haut.gauche.y - 3*longueurSousCube;
		sousCube.arriere.bas.droite.z = original.avant.haut.gauche.z - 2*longueurSousCube;

		/* point 7 */
		sousCube.arriere.bas.gauche.x = original.arriere.bas.gauche.x + 2*longueurSousCube;
		sousCube.arriere.bas.gauche.y = original.avant.haut.gauche.y - 3*longueurSousCube;
		sousCube.arriere.bas.gauche.z = original.avant.haut.gauche.z - 2*longueurSousCube;
    }
	final.append(sousCube);
	NEXT_STEP()

    {	// Cube n° 20	:	milieu	bas		gauche
			// Calcul des faces cachées
		sousCube.hiddenFaces = static_cast<Cube::Faces>(Cube::Avant | Cube::Arriere);

		PARENT_FACE(Cube::Bas)
		PARENT_FACE(Cube::Gauche)

			// Calcul des points
		/* point 0 */
		sousCube.avant.haut.gauche.x = original.avant.haut.gauche.x;
		sousCube.avant.haut.gauche.y = original.avant.haut.gauche.y - 2 * longueurSousCube;
		sousCube.avant.haut.gauche.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 1 */
		sousCube.avant.haut.droite.x = original.avant.haut.gauche.x + longueurSousCube;
		sousCube.avant.haut.droite.y = original.avant.haut.droite.y - 2 * longueurSousCube;
		sousCube.avant.haut.droite.z = original.avant.haut.droite.z - longueurSousCube;

		/* point 2 */
		sousCube.avant.bas.droite.x = original.avant.haut.gauche.x + longueurSousCube;
		sousCube.avant.bas.droite.y = original.avant.bas.droite.y;
		sousCube.avant.bas.droite.z = original.avant.bas.droite.z - longueurSousCube;

		/* point 3 */
		sousCube.avant.bas.gauche.x = original.avant.bas.gauche.x;
		sousCube.avant.bas.gauche.y = original.avant.haut.gauche.y - 3 * longueurSousCube;
		sousCube.avant.bas.gauche.z = original.avant.haut.gauche.z - longueurSousCube;

		/* point 4 */
		sousCube.arriere.haut.gauche.x = original.arriere.haut.gauche.x;
		sousCube.arriere.haut.gauche.y = original.arriere.haut.gauche.y - 2 * longueurSousCube;
		sousCube.arriere.haut.gauche.z = original.avant.haut.gauche.z - 2 * longueurSousCube;

		/* point 5 */
		sousCube.arriere.haut.droite.x = original.arriere.haut.gauche.x + longueurSousCube;
		sousCube.arriere.haut.droite.y = original.arriere.haut.droite.y - 2 * longueurSousCube;
		sousCube.arriere.haut.droite.z = original.avant.haut.gauche.z - 2 * longueurSousCube;

		/* point 6 */
		sousCube.arriere.bas.droite.x = original.arriere.haut.gauche.x + longueurSousCube;
		sousCube.arriere.bas.droite.y = original.arriere.haut.gauche.y - 3 * longueurSousCube;
		sousCube.arriere.bas.droite.z = original.avant.haut.gauche.z - 2 * longueurSousCube;

		/* point 7 */
		sousCube.arriere.bas.gauche.x = original.arriere.bas.gauche.x;
		sousCube.arriere.bas.gauche.y = original.avant.haut.gauche.y - 3 * longueurSousCube;
		sousCube.arriere.bas.gauche.z = original.avant.haut.gauche.z - 2 * longueurSousCube;
    }
	final.append(sousCube);
	NEXT_STEP()
}

Q_EXPORT_PLUGIN2(DiscoFractale, DiscoFractale)
