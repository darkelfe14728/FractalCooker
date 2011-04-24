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
	m_currentProgress(0),
	m_shaders(0),
	m_modelViewLocation(-1),
	m_colorLocation(-1)
{}

void EpongeMenger::init (QGLShaderProgram * shaders, int modelView_loc, int color_loc, int nbIte) {

	m_shaders = shaders;
	m_modelViewLocation = modelView_loc;
	m_colorLocation = color_loc;

	setNbIterations(nbIte);
}


const QVector<GLFloat> EpongeMenger::getVertices () const {

	QVector<GLFloat> vertices(24);				// Cube : 8 points de 3 coordonnées

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


void EpongeMenger::paint () {

	QMatrix4x4 modelView;
	modelView.lookAt(Vector(50, 50, 50), Vector(0, 0, 0), Vector(0, 1, 0));

	m_currentProgress = 0;							// Réinitialise le compteur de progression
	paintIteration(modelView, nbIterations());
}


void EpongeMenger::paintCube (const QMatrix4x4 & modelView) {

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
	m_shaders->setUniformValue(getModelViewLocation(), modelView);

	// Dessin du cube
		// Face 1
	m_shaders->setUniformValue(getColorLocation(), rouge);					// Change la couleur du "pinceau" pour la face actuelle
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &(indices[0]));		// Dessine deux triangles successifs pour la face, en se basant sur les indices spécifiés

		// Face 2
	m_shaders->setUniformValue(color, jaune);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &(indices[6]));

		// Face 3
	m_shaders->setUniformValue(color, blanc);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &(indices[12]));

		// Face 4
	m_shaders->setUniformValue(color, cyan);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &(indices[18]));

		// Face 5
	m_shaders->setUniformValue(color, bleu);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &(indices[24]));

		// Face 6
	m_shaders->setUniformValue(color, magenta);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &(indices[30]));

	emit progression(++m_currentProgress);
}

void EpongeMenger::paintIteration (	QMatrix4x4 & modelView,
									const quint8 level) {

	if(level == 0) {
		paintCube(modelView);
		return;
	}

	const quint16 offset(pow(3, (level - 1)));

	// Couche 1
		paintIterationLayer(modelView, level);

	// Couche 2
		// Itération 1
		modelView.translate(-2 * offset, 2 * offset, 0);
		paintIteration(modelView, level - 1);

		// Itération 2
		modelView.translate(0, 0, -4 * offset);
		paintIteration(modelView, level - 1);

		// Itération 2
		modelView.translate(4 * offset, 0, 0);
		paintIteration(modelView, level - 1);

		// Itération 4
		modelView.translate(0, 0, 4 * offset);
		paintIteration(modelView, level - 1);

	// Couche 2
		modelView.translate(-4 * offset, 2 * offset, 0);
		paintIterationLayer(modelView, level);

	modelView.translate(-2 * offset, -4 * offset, 0);					// Replace à la vue pour l'itération suivante
}

void EpongeMenger::paintIterationLayer (QMatrix4x4 & modelView,
										const quint8 level) {

	const quint16 offset(pow(3, (level - 1)));

	// Itération 1
	paintIteration(modelView, level - 1);

	// Itération 2
	modelView.translate(0, 0, -2 * offset);
	paintIteration(modelView, level - 1);

	// Itération offset
	modelView.translate(0, 0, -2 * offset);
	paintIteration(modelView, level - 1);

	// Itération 4
	modelView.translate(2 * offset, 0, 0);
	paintIteration(modelView, level - 1);

	// Itération 5
	modelView.translate(2 * offset, 0, 0);
	paintIteration(modelView, level - 1);

	// Itération 6
	modelView.translate(0, 0, 2 * offset);
	paintIteration(modelView, level - 1);

	// Itération 7
	modelView.translate(0, 0, 2 * offset);
	paintIteration(modelView, level - 1);

	// Itération 8
	modelView.translate(-2 * offset, 0, 0);
	paintIteration(modelView, level - 1);
}

Q_EXPORT_PLUGIN2(EpongeMenger, EpongeMenger)
