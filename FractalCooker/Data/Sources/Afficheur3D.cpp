/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	Program
 * Fichier					:	Afficheur3D.cpp
 *
 * Date de modification		:	mardi 18 mai 2010
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

#include "Afficheur3D.h"

#include <QtGui/QPainter>
#include <QtGui/QProgressDialog>

#include <cstdio>

Afficheur3D::Afficheur3D (QWidget * parent/* = 0*/,
                          const QGLWidget * shareWidget/* = 0*/,
                          Qt::WindowFlags f/* = 0*/) :
    QGLWidget(parent, shareWidget, f)
{
    setFocusPolicy(Qt::StrongFocus);		// Pour que les touches du clavier soient prises en compte
    reset();

    m_canceled = true;
}


void Afficheur3D::loadFractal (Fractale3D * fract) {

    if(!fract)				// Si le pointeur n'est pas valide
        return;					// Abandonne

    reset();
    m_canceled = true;
    m_fractale = fract;

    m_fractale->init(3);

    generate();

    if(m_canceled)
        reset();

    updateGL();
}



void Afficheur3D::paintGL () {

    QGLWidget::paintGL();

    const QSize taille = geometry().size();

    glViewport(0, 0, taille.width(), taille.height());

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    gluPerspective(m_zoom, static_cast<float>(taille.width()) / taille.height(), 0.01, 1000);

    gluLookAt(0, 2, 2, 0, 0, 0, 0, 1, 0);

    glRotated(m_rotation.z, 0, 0, 1);				// Rotation sur Z
    glRotated(m_rotation.y, 0, 1, 0);				// Rotation sur Y
    glRotated(m_rotation.x, 1, 0, 0);				// Rotation sur X

    glTranslated(m_translation.x, m_translation.y, m_translation.z);

    if(!m_canceled)
    {
        Fractale3D::CubeList::const_iterator it;
        const Fractale3D::CubeList::const_iterator fin = m_fractale->resultat().end();

        Fractale3D::Cube actuel;

        for(it = m_fractale->resultat().begin(); it != fin; it++) {
            actuel = *it;

            glBegin(GL_QUADS);				// Démarre le dessin

            /* Face de devant	:	rouge */
            if(!actuel.hiddenFaces.testFlag(Fractale3D::Cube::Avant)) {

                setColor(Qt::red);

                setPoint(actuel.avant.haut.gauche);
                setPoint(actuel.avant.haut.droit);
                setPoint(actuel.avant.bas.droit);
                setPoint(actuel.avant.bas.gauche);
            }

            /* Face de droite	:	jaune */
            if(!actuel.hiddenFaces.testFlag(Fractale3D::Cube::Droite)) {

                setColor(Qt::yellow);

                setPoint(actuel.avant.haut.droit);
                setPoint(actuel.arriere.haut.droit);
                setPoint(actuel.arriere.bas.droit);
                setPoint(actuel.avant.bas.droit);
            }

            /* Face de derrière	:	blanc */
            if(!actuel.hiddenFaces.testFlag(Fractale3D::Cube::Arriere)) {

                setColor(Qt::white);

                setPoint(actuel.arriere.haut.droit);
                setPoint(actuel.arriere.haut.gauche);
                setPoint(actuel.arriere.bas.gauche);
                setPoint(actuel.arriere.bas.droit);
            }

            /* Face de gauche	:	cyan */
            if(!actuel.hiddenFaces.testFlag(Fractale3D::Cube::Gauche)) {

                setColor(Qt::cyan);

                setPoint(actuel.arriere.haut.gauche);
                setPoint(actuel.avant.haut.gauche);
                setPoint(actuel.avant.bas.gauche);
                setPoint(actuel.arriere.bas.gauche);
            }

            /* Face de dessus	:	bleu */
            if(!actuel.hiddenFaces.testFlag(Fractale3D::Cube::Haut)) {

                setColor(Qt::blue);

                setPoint(actuel.avant.haut.gauche);
                setPoint(actuel.arriere.haut.gauche);
                setPoint(actuel.arriere.haut.droit);
                setPoint(actuel.avant.haut.droit);
            }

            /* Face de dessous	:	magenta */
            if(!actuel.hiddenFaces.testFlag(Fractale3D::Cube::Bas)) {

                setColor(Qt::magenta);

                setPoint(actuel.avant.bas.gauche);
                setPoint(actuel.arriere.bas.gauche);
                setPoint(actuel.arriere.bas.droit);
                setPoint(actuel.avant.bas.droit);
            }

            glEnd();						// Termine le dessin
        }

        glFlush();
    }

    glPopMatrix();
}


void Afficheur3D::keyPressEvent (QKeyEvent * event) {

    const bool shiftPressed = event->modifiers().testFlag(Qt::ShiftModifier);

    const float mouvRotation = 2.0,
                mouvTransla = 0.2,
                mouvZoom = 2.0;

    switch(event->key()) {
        /* Rotations */
        case Qt::Key_Q: {
            if(shiftPressed)
                m_rotation.x -= mouvRotation;
            else
                m_rotation.x += mouvRotation;

            updateGL();
            break;
        }
        case Qt::Key_S: {
            if(shiftPressed)
                m_rotation.y -= mouvRotation;
            else
                m_rotation.y += mouvRotation;

            updateGL();
            break;
        }
        case Qt::Key_D: {
            if(shiftPressed)
                m_rotation.z -= mouvRotation;
            else
                m_rotation.z += mouvRotation;

            updateGL();
            break;
        }

        /* Translations */
        case Qt::Key_A: {
            if(shiftPressed)
                m_translation.x -= mouvTransla;
            else
                m_translation.x += mouvTransla;

            updateGL();
            break;
        }
        case Qt::Key_Z: {
            if(shiftPressed)
                m_translation.y -= mouvTransla;
            else
                m_translation.y += mouvTransla;

            updateGL();
            break;
        }
        case Qt::Key_E: {
            if(shiftPressed)
                m_translation.z -= mouvTransla;
            else
                m_translation.z += mouvTransla;

            updateGL();
            break;
        }

        /* Zoom */
        case Qt::Key_R: {
            if(shiftPressed)
                m_zoom += mouvZoom;
            else
                m_zoom -= mouvZoom;

            updateGL();
            break;
        }

        default:
            break;
    }

    QGLWidget::keyPressEvent(event);
}

void Afficheur3D::mouseMoveEvent (QMouseEvent * event) {

    const QPoint distance = event->pos() - m_transfoReference;
    m_transfoReference = event->pos();

    const Qt::MouseButtons boutons = event->buttons();

    if(boutons.testFlag(Qt::LeftButton)) {
        m_translation.x += distance.x() / 100.0;
        m_translation.y -= distance.y() / 100.0;
        updateGL();
    }
    else if(boutons.testFlag(Qt::RightButton)) {
        m_rotation.x += distance.y();
        m_rotation.y += distance.x();
        updateGL();
    }
}

void Afficheur3D::wheelEvent (QWheelEvent * event) {

    m_zoom -= (event->delta() / 120.0) * 2;
    updateGL();
}


void Afficheur3D::generate () {

    QProgressDialog barre(tr("Génération de la fractale en cours..."), tr("Annuler"), 0, 0, this);
    barre.setModal(true);

    connect(&barre, SIGNAL(canceled()), m_fractale, SLOT(cancel()));

    connect(m_fractale, SIGNAL(maximum(int)), &barre, SLOT(setMaximum(int)));
    connect(m_fractale, SIGNAL(progression(int)), &barre, SLOT(setValue(int)));

    m_fractale->generer();

    m_canceled = barre.wasCanceled();
}

void Afficheur3D::reset () {
    m_rotation = Triplet();
    m_translation = Triplet();
    m_zoom = 70;
}
