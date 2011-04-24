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

#ifndef HEADERGUARD_INTERFACES_FRACTALE2D_H
#define HEADERGUARD_INTERFACES_FRACTALE2D_H

	#include "Fractale.h"

	#include <QtCore/QPoint>
	#include <QtCore/QPointF>
	#include <QtCore/QRectF>
	#include <QtCore/QSize>
	#include <QtCore/QVector>

	#include <QtGui/QColor>
	#include <QtGui/QImage>

	QT_BEGIN_HEADER

	/**
	 *	Interface générique à toutes les fractales 2D. \n
	 *	Chaque plugins de fractales 2D <u>doit</u> hériter de cette interface.
	 */
	class Fractale2D :
		public Fractale {

		Q_OBJECT

		public:
			virtual ~Fractale2D () {}

			/**
			 *	Initialise le plugin.
			 *
			 *	\param[in]	drawZone		La (taille de la) zone à générer ?
			 *	\param[in]	centre			Le point central de la fractale générée.
			 *	\param[in]	zoom			Le zoom appliqué.
			 *	\param[in]	nbIterations	Le nombre d'itération (profondeur du calcul).
			 */
			void init (	const QRect & drawZone = QRect(0, 0, 400, 300),
						const QPointF & centre = QPointF(-1.0, 0.0),
						const qreal & zoom = 100.0,
						const quint32 & nbIterations = 255) {
				m_drawZone = drawZone;
				m_clipZone = QRect(QPoint(0, 0), m_drawZone.size());
				m_centre = centre;
				m_zoom = zoom;
				m_nbIterations = nbIterations;
				m_symetric = false;

				resetCancel();

				m_image = QImage(drawZone.size(), QImage::Format_RGB32);
			}

			/**
			 *	Lance la génération de la fractale.
			 *
			 *	\sa cancel.
			 */
            virtual void generer () = 0;

			/**
			 *	\return Le résultat de la génération, c'est-à-dire la fractale.
			 */
			inline const QImage & resultat () const {
				return m_image;
			}

			/**
			 *	\return La (taille de la) zone à générer ?
			 */
			inline QRect drawZone () const {
				return m_drawZone;
			}
			/**
			 *	Change la (taille de la) zone à générer ?
			 *
			 *	\param[in]	nRect	La nouvelle (taille de la) zone à générer ?
			 */
			void setDrawZone (const QRect & nRect) {
				m_drawZone = nRect;
				m_clipZone = QRect(QPoint(0, 0), nRect.size());

				QSize temp = nRect.size();
				m_image = QImage(temp, QImage::Format_RGB32);
			}

			/**
			 *	\return Le facteur de zoom.
			 */
			inline qreal zoom () const {
				return m_zoom;
			}
			/**
			 *	\return Une référence vers le facteur de zoom.
			 */
			inline qreal  & rzoom () {
				return m_zoom;
			}
			/**
			 *	Change le facteur de zoom.
			 *
			 *	\param[in]	nZoom	Le nouveau facteur de zoom.
			 */
			inline void setZoom (const qreal & nZoom) {
				m_zoom = qMax(nZoom, 0.0);
			}

			/**
			 *	\return Le nombre d'itération, c'est-à-dire la \a profondeur du calcul.
			 */
			inline quint32 nbIterations () const {
				return m_nbIterations;
			}
			/**
			 *	Change le nombre d'itération, c'est-à-dire la \a profondeur du calcul.
			 *
			 *	\param[in]	nNbIteration	Le nouveau nombre d'itération.
			 */
			inline void setNbIterations (const quint32 & nNbIteration) {
				m_nbIterations = nNbIteration;
			}

			/**
			 *	\return Le point central de la fractale générée.
			 */
			inline QPointF centre () const {
				return m_centre;
			}
			/**
			 *	Change le point central de la fractale générée.
			 *
			 *	\param[in]	nCentre		Le nouveau centre.
			 */
			inline void setCentre (const QPointF & nCentre) {
				m_centre = nCentre;
			}
			/**
			 *	Fonction qui déplace le centre de l'image dans le plan.
			 *
			 *	\param[in]	decalage	L'offset du déplacement.
			 */
			inline void translateCentre(const QPoint & decalage) {
				m_centre.rx() += decalage.x() / m_zoom;
				m_centre.ry() += decalage.y() / m_zoom;
			}

		signals:
			/*!
			 *	Transmet la valeur maximale pour la progression (c'est-à-dire la valeur correspondante à 100 %).
			 *
			 *	\param[in]	max		La valeur à transmettre.
			 */
            void maximum (int max);

		protected:
			/**
			 *	Ajoute un point à l'image finale.
			 *
			 *	\param[in]	point	Les coordonnées du point à ajouter.
			 *	\param[in]	step	Le nombre d'itération qui ont été nécessaire à la génération du point (permet de connaître sa couleur).
			 */
			void addPoint (const QPoint & point, const quint32 & step) {

				QRgb color = couleurFromStep(step).rgb();
				*(reinterpret_cast<QRgb *>(m_image.scanLine(point.y())) + point.x()) = color;

				if(m_symetric) {
					QPoint sym = symetricOf(point);
					if (m_clipZone.contains(sym))
						*(reinterpret_cast<QRgb *>(m_image.scanLine(sym.y())) + sym.x()) = color;
				}
			}

			/**
			 *	Calcule le point symétrique d'un autre point.
			 *
			 *	\param[in]	pixel	Le point dont nous voulons le symétrique.
			 *
			 *	\return Le point symétrique.
			 */
			virtual QPoint symetricOf (const QPoint & pixel) const = 0;
			/**
			 *	Fonction qui calcule la couleur correspondante au nombre d'itérations effectuées pour générer un point.
			 *
			 *	\param[in]	step	Le nombre d'itérations effectuées.
			 *
			 *	\return La couleur correspondante.
			 */
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

	Q_DECLARE_INTERFACE(Fractale2D, "fractalcooker.fractale2D/1.6.0")

	QT_END_HEADER

#endif

