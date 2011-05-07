/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	Program
 * Fichier					:	Afficheur3D.cpp
 *
 * Date de modification		:	mardi 18 mai 2010
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

#include "Afficheur3D.h"

#include <QtGui/QMessageBox>
#include <QtGui/QPainter>
#include <QtGui/QProgressDialog>

#include <cstdio>

Afficheur3D::Afficheur3D (	QWidget * parent,
							const QGLWidget * shareWidget,
							Qt::WindowFlags f) :
    QGLWidget(parent, shareWidget, f),
    m_fractale(0),
    m_shaders(new QGLShaderProgram(this)),
    m_initialized(false),
    m_location_projection(-1),
    m_location_vertex(-1),
    m_location_calcul(-1),
    m_location_color(-1),
    m_zoom(0.0f),
    m_transfoReference()
{
    setFocusPolicy(Qt::StrongFocus);				// Pour que les touches du clavier soient prises en compte
}


void Afficheur3D::loadFractal (Fractale3D * fract) {

	if(!m_initialized)		// Initialisation échouée
		return;					// Abandon

    if(!fract)				// Si le pointeur n'est pas valide
        return;					// Abandonne

    m_fractale = fract;
    reset();

	// Initialise la fractale
    m_fractale->init(m_shaders, m_location_calcul, m_location_color, 3);

	// Force l'affichage
    updateGL();
}



void Afficheur3D::initializeGL () {
	QGLWidget::initializeGL();

	glEnable(GL_DEPTH_TEST);				// Active le test de profondeur pour l'affichage des surfaces.

	m_initialized = false;

	// Charge les divers éléments du shader
	if(!m_shaders->addShaderFromSourceFile(QGLShader::Vertex, ":/Shaders/Simple.vert")) {
		QMessageBox::critical(
			this,
			tr("Fractale 3D - Erreur chargement"),
			tr("Impossible de charger l'élément '%1' du shader : %2")
				.arg("vertex")
				.arg(m_shaders->log())
		);
		return;
	}
	if(!m_shaders->addShaderFromSourceFile(QGLShader::Fragment, ":/Shaders/Simple.frag")) {
		QMessageBox::critical(
			this,
			tr("Fractale 3D - Erreur chargement"),
			tr("Impossible de charger l'élément '%1' du shader : %2")
				.arg("fragment")
				.arg(m_shaders->log())
		);
		return;
	}

	// Activation du shader
	if(!m_shaders->link()) {
		QMessageBox::critical(
			this,
			tr("Fractale 3D - Erreur liaison"),
			tr("Impossible de lier le shader : %1")
				.arg(m_shaders->log())
		);
		return;
	}
	if(m_shaders->bind()) {
		QMessageBox::critical(
			this,
			tr("Fractale 3D - Erreur d'activation"),
			tr("Impossible d'activer le shader")
		);
		return;
	}

	// Récupération des localisations
	m_location_projection = m_shaders->attributeLocation("projection");
	if(m_location_projection == -1) {
		QMessageBox::critical(
			this,
			tr("Fractale 3D - Erreur de localisation"),
			tr("Impossible de localiser la variable '%1' dans le shader")
				.arg("projection")
		);
		return;
	}

	m_location_vertex = m_shaders->attributeLocation("vertex");
	if(m_location_vertex == -1) {
		QMessageBox::critical(
			this,
			tr("Fractale 3D - Erreur de localisation"),
			tr("Impossible de localiser la variable '%1' dans le shader")
				.arg("vertex")
		);
		return;
	}

	m_location_calcul = m_shaders->attributeLocation("modelView");
	if(m_location_calcul == -1) {
		QMessageBox::critical(
			this,
			tr("Fractale 3D - Erreur de localisation"),
			tr("Impossible de localiser la variable '%1' dans le shader")
				.arg("modelView")
		);
		return;
	}

	m_location_color = m_shaders->attributeLocation("color");
	if(m_location_color == -1) {
		QMessageBox::critical(
			this,
			tr("Fractale 3D - Erreur de localisation"),
			tr("Impossible de localiser la variable '%1' dans le shader")
				.arg("color")
		);
		return;
	}

	// Désactivation du shader
	m_shaders->release();

	m_initialized = true;
}

void Afficheur3D::paintGL () {
    QGLWidget::paintGL();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(!m_initialized)				// Initialisation échouée
		return;							// Ne dessine rien

    if(m_fractale == 0)				// Si la fractale 'n'existe' pas
		return;							// Nous ne dessinons rien

	QMatrix4x4 projection;
    const QSize taille(geometry().size());

	// Réglage de la matrice de projection
    projection.perspective(m_zoom, static_cast<float>(taille.width()) / taille.height(), m_fractale->nearDistance(), m_fractale->farDistance());

	// Active le shader
    if(m_shaders->bind()) {
		QMessageBox::critical(
			this,
			tr("Fractale 3D - Erreur d'activation"),
			tr("Impossible d'activer le shader")
		);
		return;
	}

	static const QVector<GLfloat> vertices(m_fractale->getVertices());

	// Réglage des valeurs
	m_shaders->enableAttributeArray(m_location_vertex);
	m_shaders->setAttributeArray(m_location_vertex, vertices.data(), 3);

	m_shaders->setUniformValue(m_location_projection, projection);

	QMatrix4x4 modelView;
	modelView.lookAt(QVector3D(50, 50, 50), QVector3D(0, 0, 0), QVector3D(0, 1, 0));

	QProgressDialog barre(tr("Génération de la fractale en cours..."), tr("Annuler"), 0, m_fractale->maximum(), this);
    barre.setModal(true);

    connect(&barre, SIGNAL(canceled()), m_fractale, SLOT(cancel()));
    connect(m_fractale, SIGNAL(progression(int)), &barre, SLOT(setValue(int)));

	if(m_fractale->paint(modelView))
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shaders->disableAttributeArray(m_location_vertex);
	m_shaders->release();
}


void Afficheur3D::wheelEvent (QWheelEvent * event) {

    m_zoom -= (event->delta() / 120.0) * 2;
    updateGL();
}


void Afficheur3D::reset () {
    if(m_fractale == 0)
		m_zoom = 70;
	else
		m_zoom = m_fractale->zoom();
}
