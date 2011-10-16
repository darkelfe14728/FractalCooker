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
			public Fractale {

			Q_OBJECT

			public:
				virtual ~Fractale2D () {}


		};
	}

	Q_DECLARE_INTERFACE(Interfaces::Fractale2D, "fractalecooker.interfaces.fractale2D/1.0.0")

#endif

