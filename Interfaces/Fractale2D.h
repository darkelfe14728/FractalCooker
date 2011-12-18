/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	FractalCooker/Interfaces
 * Fichier					:	Fractale2D.h
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

#ifndef HEADERGUARD_INTERFACES_FRACTALE2D_H
#define HEADERGUARD_INTERFACES_FRACTALE2D_H

	#include "GenericFractale.h"

	#include <QtCore/QPoint>
	#include <QtCore/QPointF>
	#include <QtCore/QRectF>
	#include <QtCore/QSize>
	#include <QtCore/QVector>

	#include <QtGui/QColor>
	#include <QtGui/QImage>

	namespace Interfaces {
		class Fractale2D :
			public GenericFractale {

			Q_OBJECT

			public:
				virtual ~Fractale2D () {}

				void init (	const QRect		& drawZone	= QRect(0, 0, 400, 300),
							const QPointF	& centre	= QPointF(-1.0, 0.0),
							const qreal		& zoom		= 100.0,
							const quint32	& nbIte		= 255);

				virtual void generer () = 0;

				const QImage & resultat () const;

				const QRect drawZone () const;
				void setDrawZone (const QRect & nRect);

				qreal zoom () const;
				qreal & rzoom ();
				void setZoom (const qreal & nZoom);

				const QPointF centre () const;
				void setCentre (const QPointF & nCentre);
				void translateCentre(const QPoint & decalage);

			signals:
				void maximum (int max);

			protected:
				void addPoint (const QPoint		& point,
							   const quint32	& step);

				virtual QPoint symetricOf (const QPoint & pixel) const = 0;
				virtual QColor couleurFromStep (const quint32 & step) const = 0;

			protected:
				QRect	m_drawZone;
				QRect   m_clipZone;
				qreal	m_zoom;
				QPointF	m_centre;
				bool	m_symetric;

			private:
				QImage m_image;
		};
	}

	Q_DECLARE_INTERFACE(Interfaces::Fractale2D, "fractalcooker.interfaces.fractale2d/1.0.0")

#endif

