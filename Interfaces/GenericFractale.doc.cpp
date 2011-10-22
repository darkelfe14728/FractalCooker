/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	FractalCooker/Interfaces
 * Fichier					:	GenericFractale.doc.cpp
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

/** \namespace Interfaces
 *	\brief Espace de nom pour les interfaces des plugins.
 */

/**	\class Interfaces::GenericFractale
 *	\brief Classe générique pour les interfaces fractales.
 *
 *	\warning Aucun plugin ne peut être créé à partir de cette interface.
 */



/** \fn Interfaces::GenericFractale::GenericFractale ()
 *
 *	Construit un nouveau plugin pour fractale (générique).
 */
/** \fn virtual Interfaces::GenericFractale::~GenericFractale ()
 *
 *	Détruit le plugin.
 */


/*	\fn virtual void Interfaces::GenericFractale::initialise (const quint32 nbIte)
 *
 *	Initialise la fractale.
 *
 *	\param[in]	nbIte	Le nombre d'itération de la fractale.
 */
/**	\fn virtual bool Interfaces::GenericFractale::buildOptions (QWidget * parent) = 0
 *
 *	Construit l'interface graphique dédié aux options. Celle-ci doit être le fils de \a parent.
 *
 *	\param[in]	parent		Le widget parent de l'interface des options.
 *
 *	\return Vrai si la factale dispose d'options, sinon Faux.
 */

/**	\fn virtual const QString Interfaces::GenericFractale::name () const = 0
 *
 *	\return Le nom de la fractale.
 */

/**	\fn quint32 Interfaces::GenericFractale::nbIterations () const
 *
 *	\return Le nombre d'itération de la fractale.
 */
/**	\fn void Interfaces::GenericFractale::setNbIterations (quint32 nbIte)
 *
 *	Change le nombre d'itération de la fractale.
 *
 *	\param[in]	nbIte	Le nouveau nombre d'itérations.
 */

/**	\fn virtual void Interfaces::GenericFractale::generate () = 0
 *
 *	Lance la génération de la fractale.
 */


/**	\slot void Interfaces::GenericFractale::cancel ()
 *
 *	Annule le calcul de la fractale.
 */


/**	\fn bool Interfaces::GenericFractale::isCancel ()
 *
 *	\return Vrai si le calcul de la fractale à été annulé, sinon Faux.
 */


/**	\signal void Interfaces::GenericFractale::progression (quint32 fait)
 *
 *	Transmet la progression du calcul.
 *
 *	\param[out]	fait	Quantité du calcul réalisé. N'est pas un pourcentage !
 *
 *	\emitted Quand le calcul progresse.
 */


/** \slot void Interfaces::GenericFractale::resetCancel ()
 *
 *	Supprime l'annulation du calcul de la fractale.
 */


/**	\property bool Interfaces::GenericFractale::m_cancel
 *
 *	Est-ce que le calcul de la fractale doit être interrompu ?
 *
 *	\getter \ref Interfaces::GenericFractale::isCancel "isCancel". \n
 *	\setter	\ref Interfaces::GenericFractale::cancel "cancel". \n
 *	\resetter \ref Interfaces::GenericFractale::resetCancel "resetCancel".
 */
/** \property QMutex Interfaces::GenericFractale::m_cancel_mutex
 *
 *	Mutex pour l'accès à la variable Interfaces::GenericFractale::m_cancel.
 */

/**	\property quint32 Interfaces::GenericFractale::m_nbIterations
 *
 *	Nombre d'itérations pour le calcul de la fractale (profondeur du calcul).
 *
 *	\getter \ref Interfaces::GenericFractale::nbIterations "nbIterations". \n
 *	\setter \ref Interfaces::GenericFractale::setNbIterations "setNbIterations".
 */

