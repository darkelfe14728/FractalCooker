/*
 * Auteur				:	Rosset Julien
 *
 * Projet				:	EpongeMenger
 * Fichier				:	EpongeMenger.cpp
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

#include "EpongeMenger.h"

EpongeMenger::EpongeMenger () :
	Fractale3D(),
	m_currentProgress(0)
{}


const QVector<GLfloat> EpongeMenger::getVertices () const  {
	QVector<GLfloat> vertices;				// Cube : 8 points de 3 coordonnées

	vertices[0] = -1;
	vertices[1] = -1;
	vertices[2] = -1;

	vertices[3] =  1;
	vertices[4] = -1;
	vertices[5] = -1;

	vertices[6] =  1;
	vertices[7] =  1;
	vertices[8] = -1;

	vertices[9] = -1;
	vertices[10] =  1;
	vertices[11] = -1;

	vertices[12] = -1;
	vertices[13] = -1;
	vertices[14] =  1;

	vertices[15] =  1;
	vertices[16] = -1;
	vertices[17] =  1;

	vertices[18] =  1;
	vertices[19] =  1;
	vertices[20] =  1;

	vertices[21] = -1;
	vertices[22] =  1;
	vertices[23] =  1;

	return vertices;
}


bool EpongeMenger::paint (const QMatrix4x4 & modelView) {

	QMatrix4x4 calcul(modelView);

	m_currentProgress = 0;									// Réinitialise le compteur de progression
	return paintIteration(calcul, nbIterations());
}


bool EpongeMenger::paintCube (const QMatrix4x4 & calcul) {

	// Déclaration des variables statiques constantes
	static const unsigned int indices[] = {
		0, 1, 2,	0, 2, 3,				// Face 1
		5, 1, 2,	2, 5, 6,				// Face 2
		0, 1, 5,	5, 0, 4,				// Face 3
		4, 5, 6,	6, 4, 7,				// Face 4
		4, 7, 3,	3, 4, 0,				// Face 5
		6, 2, 3,	3, 6, 7					// Face 6
	};
	static const QColor	rouge(Qt::red),
						jaune(Qt::yellow),
						blanc(Qt::white),
						cyan(Qt::cyan),
						bleu(Qt::blue),
						magenta(Qt::magenta);

	// Mise en place de la "vue" pour le cube actuel
	shaders()->setUniformValue(getCalculLocation(), calcul);

	// Dessin du cube
		// Face 1
	shaders()->setUniformValue(getColorLocation(), rouge);					// Change la couleur du "pinceau" pour la face actuelle
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &(indices[0]));		// Dessine deux triangles successifs pour la face, en se basant sur les indices spécifiés

		// Face 2
	shaders()->setUniformValue(getColorLocation(), jaune);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &(indices[6]));

		// Face 3
	shaders()->setUniformValue(getColorLocation(), blanc);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &(indices[12]));

		// Face 4
	shaders()->setUniformValue(getColorLocation(), cyan);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &(indices[18]));

		// Face 5
	shaders()->setUniformValue(getColorLocation(), bleu);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &(indices[24]));

		// Face 6
	shaders()->setUniformValue(getColorLocation(), magenta);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &(indices[30]));

	emit progression(++m_currentProgress);									// Une étape de progression par cube

	return isCancel();
}

bool EpongeMenger::paintIteration (	QMatrix4x4 & calcul,
									const quint8 level) {

	if(level == 0) {
		return paintCube(calcul);
	}

	const quint16 offset(pow(3, (level - 1)));

	// Couche 1
		if(paintIterationLayer(calcul, level))
			return true;

	// Couche 2
		// Itération 1
		calcul.translate(-2 * offset, 2 * offset, 0);
		if(paintIteration(calcul, level - 1))
			return true;

		// Itération 2
		calcul.translate(0, 0, -4 * offset);
		if(paintIteration(calcul, level - 1))
			return true;

		// Itération 2
		calcul.translate(4 * offset, 0, 0);
		if(paintIteration(calcul, level - 1))
			return true;

		// Itération 4
		calcul.translate(0, 0, 4 * offset);
		if(paintIteration(calcul, level - 1))
			return true;

	// Couche 2
		calcul.translate(-4 * offset, 2 * offset, 0);
		if(paintIterationLayer(calcul, level))
			return true;

	calcul.translate(-2 * offset, -4 * offset, 0);					// Replace à la vue pour l'itération suivante
	return false;
}

bool EpongeMenger::paintIterationLayer (QMatrix4x4 & calcul,
										const quint8 level) {

	const quint16 offset(pow(3, (level - 1)));

	// Itération 1
	if(paintIteration(calcul, level - 1))
		return true;

	// Itération 2
	calcul.translate(0, 0, -2 * offset);
	if(paintIteration(calcul, level - 1))
		return true;

	// Itération offset
	calcul.translate(0, 0, -2 * offset);
	if(paintIteration(calcul, level - 1))
		return true;

	// Itération 4
	calcul.translate(2 * offset, 0, 0);
	if(paintIteration(calcul, level - 1))
		return true;

	// Itération 5
	calcul.translate(2 * offset, 0, 0);
	if(paintIteration(calcul, level - 1))
		return true;

	// Itération 6
	calcul.translate(0, 0, 2 * offset);
	if(paintIteration(calcul, level - 1))
		return true;

	// Itération 7
	calcul.translate(0, 0, 2 * offset);
	if(paintIteration(calcul, level - 1))
		return true;

	// Itération 8
	calcul.translate(-2 * offset, 0, 0);
	if(paintIteration(calcul, level - 1))
		return true;

	return false;
}



#include <QtPlugin>

Q_EXPORT_PLUGIN2(EpongeMenger, EpongeMenger)
