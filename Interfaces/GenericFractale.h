/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	FractalCooker/Interfaces
 * Fichier					:	GenericFractale.h
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

#ifndef HEADERGUARD_INTERFACES_FRACTALE_H
#define HEADERGUARD_INTERFACES_FRACTALE_H

    #include <QtCore/QObject>
    #include <QtCore/QMutex>

    class QString;

    namespace Interfaces {
		class GenericFractale :
			public QObject {

			Q_OBJECT

			public:
				GenericFractale () : m_cancel(false), m_cancel_mutex(), m_nbIterations(0) {}
				virtual ~GenericFractale () {}

				//virtual void initialise (const quint32 nbIte) = 0;

				virtual const QString name () const = 0;

			private:
				bool	m_cancel;
				QMutex	m_cancel_mutex;

				quint32 m_nbIterations;
		};
    }

	// Il ne s'agit pas réellement d'une interface pour plugin.
    //Q_DECLARE_INTERFACE(Fractale, "fractales.aspe.fractale/1.0.0")

#endif

