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


/**	\property bool Interfaces::GenericFractale::m_cancel
 *
 *	Est-ce que le calcul de la fractale doit être interrompu ?
 */
/** \property QMutex Interfaces::GenericFractale::m_cancel_mutex
 *
 *	Mutex pour l'accès à la variable Interfaces::GenericFractale::m_cancel.
 */

