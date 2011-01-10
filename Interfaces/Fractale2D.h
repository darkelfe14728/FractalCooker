/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	Program
 * Fichier					:	Fractale2D.h
 *
 * Date de création			:	mercredi 24 février 2010
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

#ifndef HEADERGUARD_PROGRAM_FRACTALE2D_H
#define HEADERGUARD_PROGRAM_FRACTALE2D_H

    #include <QtCore/QMutex>
    #include <QtCore/QPoint>
    #include <QtCore/QPointF>
    #include <QtCore/QRectF>
    #include <QtCore/QSize>
    #include <QtCore/QVector>

    #include <QtGui/QColor>
    #include <QtGui/QImage>

    #include <cstdio>

    QT_BEGIN_HEADER

    /**
     *	Interface générique à toutes les fractales 2D. \n
     *	Chaque plugin de fractale 2D <u>doit</u> hériter de cette interface.
     */
    class Fractale2D :
        public QObject {

        Q_OBJECT

        public:
            virtual ~Fractale2D () {}

            void init (const QRect & drawZone = QRect(0, 0, 400, 300), const QPointF & centre = QPointF(-1.0, 0.0), const qreal & zoom = 100.0, const quint32 & nbIterations = 255) {
                m_drawZone = drawZone;
                m_clipZone = QRect(QPoint(0, 0), m_drawZone.size());
                m_centre = centre;
                m_zoom = zoom;
                m_nbIterations = nbIterations;
                m_cancel = false;
                m_symetric = false;

                m_image = QImage(drawZone.size(), QImage::Format_RGB32);
            }

			/**
			 *	Crée les options du plugin.
			 *
			 *	\param[in]	parent	Le widget parent des options.
			 */
			virtual void createOptions (QWidget * parent) = 0;

            virtual void generer () = 0;
            virtual QString name () const = 0;

            inline const QImage & resultat () const {
                return m_image;
            }

            inline QRect drawZone () const {
                return m_drawZone;
            }
            void setDrawZone (const QRect & nRect) {
//                printf("\t\tCopying new rect\n");
                m_drawZone = nRect;
//                printf("\t\tCalculating clip zone\n");
                m_clipZone = QRect(QPoint(0, 0), nRect.size());
//                printf("\t\tTemp QSize \n");
                QSize temp = nRect.size();
//                printf("\t\tCreating new image : %dx%d\n", temp.width(), temp.height());
                m_image = QImage(temp, QImage::Format_RGB32);
//                printf("\t\tNew Image created\n");
            }

            inline qreal zoom () const {
                return m_zoom;
            }
            inline qreal  & rzoom () {
                return m_zoom;
            }
            inline void setZoom (const qreal & nZoom) {
                m_zoom = qMax(nZoom, 0.0);
            }

            inline quint32 nbIterations () const {
                return m_nbIterations;
            }
            inline void setNbIterations (const quint32 & nNbIteration) {
                m_nbIterations = nNbIteration;
            }

			inline QPointF centre () const {
				return m_centre;
			}
			inline void setCentre (const QPointF & nCentre) {
				m_centre = nCentre;
			}
            /**
             * Fonction qui déplace le centre de l'image dans le plan.
             */
            inline void translateCentre(const QPoint & decalage) {
                m_centre.rx() += decalage.x() / m_zoom;
                m_centre.ry() += decalage.y() / m_zoom;
            }

        public slots:
            inline void cancel () {
                m_mutex.lock();
                m_cancel = true;
                m_mutex.unlock();
            }

        signals:
            void maximum (int max);
            void progression (int fait);

        protected:
			inline void uncancel () {
                m_mutex.lock();
                m_cancel = false;
                m_mutex.unlock();
            }
            void addPoint (const QPoint & point, const quint32 & step) {

                QRgb color = couleurFromStep(step).rgb();
                *(reinterpret_cast<QRgb *>(m_image.scanLine(point.y())) + point.x()) = color;

                if(m_symetric) {
                    QPoint sym = symetricOf(point);
                    if (m_clipZone.contains(sym))
                        *(reinterpret_cast<QRgb *>(m_image.scanLine(sym.y())) + sym.x()) = color;
                }
            }
            virtual QPoint symetricOf (const QPoint & pixel) const = 0;
            /**
             * Fonction qui renvoie la couleur correspondant au nombre d'itérations effectué.
             * @param Nombre d'itérations effectuées.
             * @return La couleur à attribuer.
             */
            virtual QColor couleurFromStep (const quint32 & step) const = 0;

        protected:
            QRect	m_drawZone;
            QRect   m_clipZone;
            qreal	m_zoom;
            QPointF	m_centre;
            quint32	m_nbIterations;
            bool	m_cancel;
            bool	m_symetric;
            QMutex	m_mutex;

        private:
            QImage m_image;
    };

    Q_DECLARE_INTERFACE(Fractale2D, "fractales.aspe.fractale2D/1.5.0")

    QT_END_HEADER

#endif
