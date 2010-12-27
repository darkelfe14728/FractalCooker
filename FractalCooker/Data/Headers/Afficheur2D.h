/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	Program
 * Fichier					:	Afficheur2D.h
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

#ifndef HEADERGUARD_PROGRAM_AFFICHEUR2D_H
#define HEADERGUARD_PROGRAM_AFFICHEUR2D_H

	#include <Fractale2D.h>

	#include <QtGui/QPaintEvent>
	#include <QtGui/QWidget>

	QT_BEGIN_HEADER

	class Afficheur2D :
		public QWidget {

		Q_OBJECT

		public:
			Afficheur2D (QWidget * parent = 0, Qt::WindowFlags f = 0);

			bool loadFractal (Fractale2D * fract);

		protected:
			void paintEvent (QPaintEvent * event);
			void wheelEvent (QWheelEvent * event);
			void keyPressEvent (QKeyEvent * event);
			//void mouseMoveEvent (QMouseEvent * event);
			inline void mousePressEvent (QMouseEvent * event) {
				m_translationOrigin = event->pos();
			}

		private:
			Fractale2D * m_fractale;
			QImage m_image;

			QPoint m_translationOrigin;

		private:
			bool generate ();
			void clear ();
	};

	QT_END_HEADER

#endif
