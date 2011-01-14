/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	Program
 * Fichier					:	Afficheur3D.h
 *
 * Date de création			:	mardi 18 mai 2010
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

#ifndef HEADERGUARD_PROGRAM_AFFICHEUR3D_H
#define HEADERGUARD_PROGRAM_AFFICHEUR3D_H

    #include <Fractale3D.h>

    #include <QtGui/QKeyEvent>
    #include <QtGui/QWheelEvent>

    #include <QtOpenGL/QGLWidget>

    QT_BEGIN_HEADER

    class Afficheur3D :
        public QGLWidget {

        Q_OBJECT

        public:
            Afficheur3D (QWidget * parent = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0);

            void loadFractal (Fractale3D * fract);

            inline void clear () {
                if(m_fractale != 0)
                    m_fractale->clear();
            }
            inline bool canceled () {
                return m_canceled;
            }

        protected:
            void paintGL ();

            void keyPressEvent (QKeyEvent * event);
            void mouseMoveEvent (QMouseEvent * event);
            inline void mousePressEvent (QMouseEvent * event) {
                m_transfoReference = event->pos();
            }
            void wheelEvent (QWheelEvent * event);

        private:
            struct Triplet {
                Triplet () : x(0), y(0), z(0) {}

                float x;
                float y;
                float z;
            };

        private:
            Fractale3D * m_fractale;
            bool m_canceled;

            Triplet m_rotation;
            Triplet m_translation;
            float m_zoom;

            QPoint m_transfoReference;

        private:
            void generate ();
            void reset ();

            inline void setColor (const QColor & couleur) {
                glColor3ub(couleur.red(), couleur.green(), couleur.blue());
            }
            inline void setPoint (const Fractale3D::Cube::FaceType::ArreteType::SommetType & pt) {
                glVertex3f(pt.x, pt.y, pt.z);
            }
    };

    QT_END_HEADER

#endif
