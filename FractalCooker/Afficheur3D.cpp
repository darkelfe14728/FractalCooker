/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	FractalCooker/FractalCooker
 * Fichier					:	Afficheur3D.cpp
 *
 * Date de création			:	vendredi 25 mai 2012
 */

/* Copyright (C) 2010-2012 LEVIGNE Florent, GROCCIA Patricia, RICHARD Thomas, ROSSET Julien
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

#include <Interfaces/Fractale3D.h>

#include <QtGui/QMessageBox>
#include <QtGui/QProgressDialog>
#include <QtGui/QWheelEvent>

Afficheur3D::Afficheur3D(QWidget *parent, const QGLWidget *shareWidget, Qt::WindowFlags f) :
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
	setFocusPolicy (Qt::StrongFocus);			// Active la prise en compte des touches du clavier
}


void Afficheur3D::loadFractale (Interfaces::Fractale3D *fract) {
	if(!m_initialized)		// Afficheur mal initialisé ?
		return;					// Abandon

	if(!fract)				// Fracatale invalide
		return;					// Ne fait rien

	m_fractale = fract;		// A partir de maintenant, on utilise la nouvelle fractale
	clear();				// Nettoie / remet à zéro l'afficheur

	m_fractale->init (m_shaders, m_location_calcul, m_location_color, 3);		// Initialise la fractale
	updateGL ();			// Rafraîchit l'afficheur : force l'affichage de la nouvelle fractale (cf. paintGL)
}



void Afficheur3D::initializeGL () {
	m_initialized = false;

	// Initialisation de l'environnement
	QGLWidget::initializeGL ();								// Initialisation via la classe mère
	glEnable(GL_DEPTH_TEST);								// Active le test de profondeur pour l'affichage des surfaces.

	// Charge les shaders
	if(!m_shaders->addShaderFromSourceFile (QGLShader::Vertex, ":/Shaders/Simple.vert")) {
		QMessageBox::critical (
			this,
			tr("Afficheur de fractales 3D - Erreur d'initilisation"),
			tr("Impossible de charger '%1' du shader.\n\nLog : %2")
				.arg("vertex")
				.arg(m_shaders->log ())
		);
		return;
	}
	if(!m_shaders->addShaderFromSourceFile (QGLShader::Fragment, ":/Shaders/Simple.frag")) {
		QMessageBox::critical (
			this,
			tr("Afficheur de fractales 3D - Erreur d'initilisation"),
			tr("Impossible de charger '%1' du shader.\n\nLog : %2")
				.arg("fragment")
				.arg(m_shaders->log ())
		);
		return;
	}

	// Active les shaders
	if(!m_shaders->link ()) {
		QMessageBox::critical (
			this,
			tr("Afficheur de fractales 3D - Erreur d'initialisation"),
			tr("Impossible de lier les shaders.\n\nLog : %1")
				.arg(m_shaders->log ())
		);
		return;
	}
	if(!m_shaders->bind ()) {
		QMessageBox::critical (
			this,
			tr("Afficheur de fractales 3D - Erreur d'initialisation"),
					tr("Impossible d'activer les shaders.\n\nLog : %1")
				.arg(m_shaders->log ())
		);
		return;
	}

	// Récupération des diverses localisations
	m_location_projection = m_shaders->uniformLocation ("projection");
	/*if(m_location_projection == -1) {
		QMessageBox::critical (
			this,
			tr("Afficheur de fractales 3D - Erreur d'initialisation"),
			tr("Impossible de localiser la variable '%1' dans les shaders")
				.arg("projection")
		);
		return;
	}*/

	m_location_vertex = m_shaders->attributeLocation ("vertex");
	if(m_location_vertex == -1) {
		QMessageBox::critical (
			this,
			tr("Afficheur de fractales 3D - Erreur d'initialisation"),
			tr("Impossible de localiser la variable '%1' dans les shaders")
				.arg("vertex")
		);
		return;
	}

	m_location_calcul = m_shaders->uniformLocation ("modelview");
	if(m_location_calcul == -1) {
		QMessageBox::critical (
			this,
			tr("Afficheur de fractales 3D - Erreur d'initialisation"),
			tr("Impossible de localiser la variable '%1' dans les shaders")
				.arg("modelview")
		);
		return;
	}

	m_location_color = m_shaders->uniformLocation ("color");
	if(m_location_color == -1) {
		QMessageBox::critical (
			this,
			tr("Afficheur de fractales 3D - Erreur d'initialisation"),
			tr("Impossible de localiser la variable '%1' dans les shaders")
				.arg("color")
		);
		return;
	}

	m_shaders->release ();									// "Désactive" les shaders

	m_initialized = true;									// Initialisation réussie
}
void Afficheur3D::paintGL () {
	// Initialise l'environnement
	QGLWidget::paintGL ();									// Dessine la "zone" OpenGL via la classe mère
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Initialise OpenGL

	if(m_fractale == 0)										// Pas de fractale ?
		return;													// On s'arrête là
	if(!m_initialized)										// Afficheur mal initialisé
		return;													// Idem : on s'arrête là

	// Active les shaders
	if(!m_shaders->bind ()) {
		QMessageBox::critical (
			this,
			tr("Afficheur de fractales 3D - Erreur lors de l'affichage de la fractale"),
			tr("Impossible d'activer les shaders")
		);
		return;
	}
	m_shaders->enableAttributeArray (m_location_vertex);

	// Construction de la matrice de projection : l' "espace" OpenGL dans lequel se situe la fractale
	const QSize taille(geometry ().size ());				// La taille de la "zone" OpenGL
	QMatrix4x4 projection;									// L' "espace" d'affichage OpenGL

	projection.perspective (
		m_zoom,
		static_cast<float>(taille.width ()) / taille.height (),
		m_fractale->nearDistance (),
		m_fractale->farDistance ()
	);

	m_shaders->setUniformValue (m_location_projection, projection);		// Transmet de la matrice de projection

	// Transmission de la forme de base de la fractale (coordonéees à 3 points : x y z)
	m_shaders->setAttributeArray (m_location_vertex, m_fractale->getVertices().data(), 3);

	// Crée et initialise la barre de progression
//	QProgressDialog barre(
//		tr("Génération de la fractale en cours..."),		// Message
//		tr("Annuler"),										// Label du bouton d'annulation
//		0,													// La valeur minimale
//		m_fractale->maximum (),								// La valeur maximale : dépend de la fractale...
//		0												// La boite de dialogue dépend de l'afficheur
//	);
//	barre.setModal (true);									// Bloque toutes les opérations lors de l'affichage
//	barre.show ();

//	connect (&barre, SIGNAL(canceled()), m_fractale, SLOT(cancel()));				// Clic sur le bouton annuler : annule
//	connect (m_fractale, SIGNAL(progression(int)), &barre, SLOT(setValue(int)));	// Transmission de la progression

	// Dessin de la fractale
	QMatrix4x4 modelView;									// Matrice pour les calculs d'affichage
	modelView.lookAt (										// Initialisation du point de départ
		QVector3D(50, 50, 50),
		QVector3D( 0,  0,  0),
		QVector3D( 0,  1,  0)									// Axe y vertical
	);

	if(m_fractale->paint (modelView))						// Le dessin lui-même
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// "Désactive" les shaders
	m_shaders->disableAttributeArray (m_location_vertex);
	m_shaders->release ();
}

void Afficheur3D::wheelEvent (QWheelEvent *event) {
	// Change le zoom en fonction de la distance "parcourue" par la molette de la souris
	m_zoom -= (event->delta () / 120.0) * 2;
	updateGL ();								// Rafraichît l'affichage
}



void Afficheur3D::clear () {
	if(m_fractale == 0)				// Aucune fractale
		m_zoom = 70.0f;					// Zoom par défaut
	else							// Sinon
		m_zoom = m_fractale->zoom ();	// Zoom conseillé par la fractale
}
