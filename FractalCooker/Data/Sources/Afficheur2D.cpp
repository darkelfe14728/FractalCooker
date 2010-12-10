/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	Program
 * Fichier					:	Afficheur2D.cpp
 *
 * Date de modification		:	lundi 22 mars 2010
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

#include "Afficheur2D.h"

#include <QtGui/QPainter>
#include <QtGui/QProgressDialog>

Afficheur2D::Afficheur2D (QWidget * parent/* = 0*/,
						  Qt::WindowFlags f/* = 0*/) :
	QWidget(parent, f)
{
	clear();
	setFocusPolicy(Qt::StrongFocus);		// Pour que les touches du clavier soient prises en compte

}


bool Afficheur2D::loadFractal (Fractale2D * fract) {

	if(!fract)				// Si le pointeur n'est pas valide
		return false;			// Abandonne

	m_fractale = fract;

	m_fractale->init(QRect(QPoint(0, 0), geometry().size()), QPointF(-0.5, 0.0), 100.0, 255);
//	m_fractale->translateCentre(QPoint(0, 0));

	const bool reussie = generate();

	if(reussie)
		m_image = m_fractale->resultat();
	else
		clear();

	update();

	return reussie;
}



void Afficheur2D::paintEvent (QPaintEvent * event) {

	QWidget::paintEvent(event);

	if(!m_image.isNull()) {
		QPainter painter(this);
		painter.drawImage(QPoint(0, 0), m_image);
	}
}

void Afficheur2D::wheelEvent (QWheelEvent * event) {

	const qreal zoom = m_fractale->zoom();
	const QPointF centre = m_fractale->centre();

	const QPoint deltaCentre(
		event->pos().x() - m_image.rect().center().x(),
		m_image.rect().center().y() - event->pos().y()
	);

	m_fractale->translateCentre(deltaCentre);
	m_fractale->rzoom() += 50 * (event->delta() / (15 * 8));

	if(generate())
		m_image = m_fractale->resultat();
	else {
		m_fractale->setZoom(zoom);
		m_fractale->setCentre(centre);
	}

	//update();
}

/*void Afficheur2D::mouseMoveEvent (QMouseEvent * event) {

printf("Mouse mouve event triggered\n");
	const QPoint distance = m_translationOrigin - event->pos();
	const QRect drawZone = m_fractale->drawZone();
	m_translationOrigin = event->pos();

	QImage nouv(drawZone.size(), QImage::Format_RGB32);
	QPainter painter(&nouv);

	QPoint src	(qMax(distance.x(), 0),			qMax(distance.y(), 0)),
		   dest	(qAbs(qMin(distance.x(), 0)),	qAbs(qMin(distance.y(), 0)));
	const QSize	 taille	(qMax(drawZone.width() - qAbs(distance.x()), 0),
						 qMax(drawZone.height() - qAbs(distance.y()), 0));

	painter.drawImage(QRect(dest, taille), m_image, QRect(src, taille));

	QRect calcul;

	// Calcul du côté gauche/droite
	if(distance.x() != 0) {
		calcul.setWidth(qMin(qAbs(distance.x()), drawZone.width()));
		calcul.setHeight(drawZone.height());

		if(distance.x() < 0)  {
			calcul.setTopLeft(QPoint(qMax(distance.x(), drawZone.right()), distance.y()));
			src = QPoint(qMax(drawZone.width() - qAbs(distance.x()), 0), 0);
		}
		else {
			calcul.setTopLeft(QPoint(0, 0));
			src = QPoint(0, 0);
		}

		m_fractale->setDrawZone(calcul);
		if(!generate())
			return;

		painter.drawImage(QRect(src, calcul.size()), m_fractale->resultat());
	}
	// Prise en compte effective  de la nouvelle image
	m_fractale->setDrawZone(QRect(distance, drawZone.size()));
	m_image = nouv;
	update();
}*/

void Afficheur2D::keyPressEvent (QKeyEvent * event) {

//printf("Key press event triggered\n");

	QPoint distance;

	if(event->key() == Qt::Key_Left)
		distance = QPoint(-20, 0);
	else if(event->key() == Qt::Key_Right)
		distance = QPoint(20, 0);
	else
		return;

	const QRect drawZone = m_fractale->drawZone();

	QImage nouv(drawZone.size(), QImage::Format_RGB32);
	QPainter painter(&nouv);

	const QPoint src	(qMax(-distance.x(), 0),		qMax(-distance.y(), 0)),
				 dest	(qAbs(qMin(-distance.x(), 0)),	qAbs(qMin(-distance.y(), 0)));
	const QSize	 taille	(qMax(drawZone.width() - qAbs(distance.x()), 0),
						 qMax(drawZone.height() - qAbs(distance.y()), 0));

	m_fractale->translateCentre(-distance);
	painter.drawImage(QRect(dest, taille), m_image, QRect(src, taille));

	QRect calcul;
	QPoint pos;

	// Calcul du côté gauche/droite
	if(distance.x() != 0) {
		calcul.setWidth(qMin(qAbs(distance.x()), drawZone.width()));
		calcul.setHeight(drawZone.height());

		if(distance.x() < 0)  {
			calcul.moveTo((distance.x() + drawZone.width()) / 2, 0);
			pos = QPoint(qMax(drawZone.width() - qAbs(distance.x()), 0), 0);
		}
		else {
			calcul.moveTo((distance.x() - drawZone.width()) / 2, 0);
			pos = QPoint(0, 0);
		}

		m_fractale->setDrawZone(calcul);
		if(!generate())
			return;

		painter.drawImage(QRect(pos, calcul.size()), m_fractale->resultat());
	}

	// Calcul du côté haut/bas
	/*if(distance.y() != 0 && qAbs(distance.x()) < drawZone.width()) {
		calcul.setWidth(drawZone.width() - qAbs(distance.x()));
		calcul.setHeight(qMin(qAbs(distance.y()), drawZone.height()));

		if(distance.y() < 0)  {
			calcul.moveTo(0, (distance.y() + drawZone.height()) / 2);
			pos = QPoint(0, qMax(drawZone.height() - qAbs(distance.y()), 0));
		}
		else {
			calcul.moveTo(0, (distance.y() + drawZone.height()) / 2);
			pos = QPoint(0, 0);
		}

		m_fractale->setDrawZone(calcul);
		if(!generate())
			return;

//		printf("\tPaint image ?\n");
		painter.drawImage(QRect(pos, calcul.size()), m_fractale->resultat());
//		printf("\tImage painted\n");
	}*/

	// Prise en compte effective  de la nouvelle image
//	printf("\tRestauring draw zone\n");
	m_fractale->setDrawZone(QRect(distance, drawZone.size()));
//	printf("\tCopying result\n");
	m_image = nouv;
//	printf("\tUdating screen\n");
	update();
//	printf("\tScreen updated\n");
}


bool Afficheur2D::generate () {

	QProgressDialog barre(tr("Génération de la fractale en cours..."), tr("Annuler"), 0, 0, this);
	barre.setModal(true);

	connect(&barre, SIGNAL(canceled()), m_fractale, SLOT(cancel()));

	connect(m_fractale, SIGNAL(maximum(int)), &barre, SLOT(setMaximum(int)));
	connect(m_fractale, SIGNAL(progression(int)), &barre, SLOT(setValue(int)));

	m_fractale->generer();
	printf("\tFractale generated\n");
	return !(barre.wasCanceled());
}


void Afficheur2D::clear () {
	m_image = QImage();
}
