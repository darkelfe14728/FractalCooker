/*
 * Auteur					:	Rosset Julien / Richard Thomas
 *
 * Projet					:	FractalCooker/Plugins/2D
 * Fichier					:	Mandelbrot.h
 *
 * Date de modification		:	samedi 24 décembre 2011
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

#ifndef HEADERGUARD_PLUGINS_2D_MANDELBROT_H
#define HEADERGUARD_PLUGINS_2D_MANDELBROT_H

	#include <Fractale2D.h>

	#include <QtCore/QtPlugin>

	#include <complex>

	namespace Plugins {
		namespace _2D {
			class Mandelbrot :
					public Interfaces::Fractale2D
			{
				Q_OBJECT
				Q_INTERFACES(Interfaces::Fractale2D)

				public:
					Mandelbrot ();

					// Interface
					virtual bool buildOptions (QWidget * parent);
					virtual const QString name() const {
						return QString("Mandelbrot");
					}
					virtual void generate();

				protected:
					// Interface
					virtual const QPoint symetricOf(const QPoint & pixel) const;
					virtual const QColor couleurFromStep (const quint32 & step) const;

					quint32 calculerPixel(const qreal &x, const qreal &y) const;

				private:
					qint32 m_yAxeReels;
			};
		}
	}

#endif // HEADER_GUARD_MANDELBROT_H
