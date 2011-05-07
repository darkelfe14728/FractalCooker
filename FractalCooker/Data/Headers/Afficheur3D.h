/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	Program
 * Fichier					:	Afficheur3D.h
 *
 * Date de création			:	mardi 18 mai 2010
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

#ifndef HEADERGUARD_PROGRAM_AFFICHEUR3D_H
#define HEADERGUARD_PROGRAM_AFFICHEUR3D_H

    #include <Fractale3D.h>

    #include <QtGui/QKeyEvent>
    #include <QtGui/QVector3D>
    #include <QtGui/QWheelEvent>

    #include <QtOpenGL/QGLWidget>

    QT_BEGIN_HEADER

    class Afficheur3D :
        public QGLWidget {

        Q_OBJECT

        public:
            Afficheur3D (QWidget * parent = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0);

            void loadFractal (Fractale3D * fract);

        protected:
			void initializeGL ();
            void paintGL ();

            void wheelEvent (QWheelEvent * event);

        private:
            Fractale3D * m_fractale;
            QGLShaderProgram * m_shaders;

            bool m_initialized;

			int m_location_projection;
            int m_location_vertex;
            int m_location_calcul;
            int m_location_color;

            float m_zoom;

            QPoint m_transfoReference;

        private:
            void reset ();
    };

    QT_END_HEADER

#endif
