/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	FractalCooker/Interfaces
 * Fichier					:	Fractale2D.doc.cpp
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

/**	\class Interfaces::Fractale2D
 *	\brief Interfaces des plugins fractale 2D.
 */



/** \fn virtual Interfaces::Fractale2D::~Fractale2D ()
 *
 *	Détruit le plugin.
 */



/** \fn void Interfaces::Fractale2D::init (	const QRect		& drawZone	= QRect(0, 0, 400, 300),
 *											const QPointF	& centre	= QPointF(-1.0, 0.0),
 *											const qreal		& zoom		= 100.0,
 *											const quint32	& nbIte		= 255)
 *
 *	Initialise le plugin.
 *
 *	\warning Cette fonction \b doit être appelée avant generate.
 *
 *	\param[in]	drawZone		La (taille de la) zone à générer ?
 *	\param[in]	centre			Le point central de la fractale générée (autour de quel point se génère-t-elle ?).
 *	\param[in]	zoom			Le facteur de zoom appliqué.
 *	\param[in]	nbIte			Le nombre d'itération (profondeur du calcul).
 */

/** \fn virtual void Interfaces::Fractale2D::generer () = 0
 *
 *	Lance la génération de la fractale.
 *
 *	\sa cancel.
 */

/** \fn const QImage & Interfaces::Fractale2D::resultat () const
 *
 *	\return Le résultat de la génération, c'est-à-dire la fractale.
 */

/** \fn const QRect Interfaces::Fractale2D::drawZone () const
 *
 *	\return La (taille de la) zone à générer ?
 */
/** \fn void Interfaces::Fractale2D::setDrawZone (const QRect & nRect)
 *	Change la (taille de la) zone à générer ?
 *
 *	\param[in]	nRect	La nouvelle (taille de la) zone à générer ?
 */

/** \fn qreal Interfaces::Fractale2D::zoom () const
 *
 *	\return Le facteur de zoom.
 *
 *  \sa rzoom.
 */
/** \fn qreal & Interfaces::Fractale2D::rzoom ()
 *
 *	\return Une référence vers le facteur de zoom.
 */
/** \fn void Interfaces::Fractale2D::setZoom (const qreal & nZoom)
 *
 *	Change le facteur de zoom.
 *
 *	\param[in]	nZoom	Le nouveau facteur de zoom.
 */

/** \fn const QPointF Interfaces::Fractale2D::centre () const
 *
 *	\return Le point central de la fractale générée.
 */
/** \fn void Interfaces::Fractale2D::setCentre (const QPointF & nCentre)
 *
 *	Change le point central de la fractale générée.
 *
 *	\param[in]	nCentre		Le nouveau centre.
 */
/** \fn void Interfaces::Fractale2D::translateCentre(const QPoint & decalage)
 *
 *	Fonction qui déplace le centre de l'image dans le plan.
 *
 *	\param[in]	decalage	L'offset du déplacement.
 */


/** \signal void Interfaces::Fractale2D::maximum (int max)
 *
 *	Transmet la valeur maximale pour la progression (c'est-à-dire la valeur correspondante à 100 %).
 *
 *	\param[in]	max		La valeur à transmettre.
 *
 *  \todo Remplacer par une fonction virtuelle pure ?
 *
 *	\emitted Quand la valeur maximale est disponible.
 */


/** \fn void Interfaces::Fractale2D::addPoint (	const QPoint	& point,
 *						const quint32	& step)
 *
 *	Ajoute un point à l'image finale.
 *
 *	\param[in]	point	Les coordonnées du point à ajouter.
 *	\param[in]	step	Le nombre d'itération qui ont été nécessaire à la génération du point (permet de connaître sa couleur).
 */

/** \fn virtual QPoint Interfaces::Fractale2D::symetricOf (const QPoint & pixel) const = 0
 *
 *	Calcule le point symétrique d'un autre point.
 *
 *	\param[in]	pixel	Le point dont nous voulons le symétrique.
 *
 *	\return Le point symétrique.
 */
/** \fn virtual QColor Interfaces::Fractale2D::couleurFromStep (const quint32 & step) const = 0
 *
 *	Fonction qui calcule la couleur correspondante au nombre d'itérations effectuées pour générer un point.
 *
 *	\param[in]	step	Le nombre d'itérations effectuées.
 *
 *	\return La couleur correspondante.
 */


/** \property QRect Interfaces::Fractale2D::m_drawZone
 *
 *  La taille de la zone à générer.
 *
 *  \getter \ref Interfaces::Fractale2D::drawZone "drawZone". \n
 *  \setter \ref Interfaces::Fractale2D::setDrawZone "setDrawZone".
 */
/** \property QRect Interfaces::Fractale2D::m_clipZone
 *  \todo Renseigner le doc...
 */
/** \property qreal Interfaces::Fractale2D::m_zoom
 *
 *  Valeur du zoom
 *
 *  \getter \ref Interfaces::Fractale2D::zoom "zoom", \ref Interfaces::Fractale2D::rzoom "rzoom". \n
 *  \setter \ref Interfaces::Fractale2D::setZoom "setZoom".
 */
/** \property QPointF Interfaces::Fractale2D::m_centre
 *
 *  Centre de la fractale, c'est-à-dire le point visé par la génération.
 *
 *  \getter \ref Interfaces::Fractale2D::centre "centre". \n
 *  \setter \ref Interfaces::Fractale2D::setCentre "setCentre".
 */
/** \property bool Interfaces::Fractale2D::m_symetric
 *
 *  Est-ce que la fractale est symétrique ?
 *
 *  \sa symetricOf.
 */


/** \property QImage Interfaces::Fractale2D::m_image
 *
 *  La fractale généré.
 *
 *  \getter \ref Interfaces::Fractale2D::resultat "resultat".
 *
 *  \sa addPoint.
 */
