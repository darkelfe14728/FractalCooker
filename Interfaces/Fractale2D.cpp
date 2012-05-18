/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	FractalCooker/Interfaces
 * Fichier					:	Fractale2D.cpp
 *
 * Date de création			:	samedi 17 décembre 2011
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

#include "Fractale2D.h"
using namespace Interfaces;

void Fractale2D::init(const QRect	&drawZone,
					  const QPointF	&centre,
					  const qreal	&zoom,
					  const quint32	&nbIte) {
	m_drawZone = drawZone;
	m_clipZone = QRect(QPoint(0, 0), m_drawZone.size());
	m_centre = centre;
	m_zoom = zoom;
	m_symetric = false;

	setNbIterations(nbIte);

	resetCancel();

	m_image = QImage(drawZone.size(), QImage::Format_RGB32);
}
Fractale2D::~Fractale2D () {}

const QImage & Fractale2D::resultat () const {
	return m_image;
}

const QRect Fractale2D::drawZone () const {
	return m_drawZone;
}
void Fractale2D::setDrawZone (const QRect & nRect) {
	m_drawZone = nRect;
	m_clipZone = QRect(QPoint(0, 0), nRect.size());

	QSize temp = nRect.size();
	m_image = QImage(temp, QImage::Format_RGB32);
}

qreal Fractale2D::zoom () const {
	return m_zoom;
}
qreal & Fractale2D::rzoom () {
	return m_zoom;
}
void Fractale2D::setZoom (const qreal & nZoom) {
	m_zoom = qMax(nZoom, 0.0);
}

const QPointF Fractale2D::centre () const {
	return m_centre;
}
void Fractale2D::setCentre (const QPointF & nCentre) {
	m_centre = nCentre;
}
void Fractale2D::translateCentre (const QPoint & decalage) {
	m_centre.rx() += decalage.x() / m_zoom;
	m_centre.ry() += decalage.y() / m_zoom;
}


void Fractale2D::addPoint (const QPoint		& point,
						   const quint32	& step) {
	QRgb color = couleurFromStep(step).rgb();
	*(reinterpret_cast<QRgb *>(m_image.scanLine(point.y())) + point.x()) = color;

	if(m_symetric) {
		QPoint sym = symetricOf(point);
		if (m_clipZone.contains(sym))
			*(reinterpret_cast<QRgb *>(m_image.scanLine(sym.y())) + sym.x()) = color;
	}
}
