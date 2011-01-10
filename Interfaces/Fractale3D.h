/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	Program
 * Fichier					:	Fractale3D.h
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

#ifndef HEADERGUARD_INTERFACES_FRACTALE3D_H
#define HEADERGUARD_INTERFACES_FRACTALE3D_H

	#include <QtCore/QList>
	#include <QtCore/QMutex>
	#include <QtCore/QObject>
	#include <QtCore/QString>

	#include <cstdio>

    QT_BEGIN_HEADER

    class Fractale3D :
        public QObject {

        Q_OBJECT

		public:
			struct Cube {
				/*
					   ___________
					  /4        5/|
					 /          / |
					/__________/  |
					|0        1|  |
					|          |  |
					|    7     | 6/
					|          | /
					|3________2|/

				*/

				struct Hauteur {
					struct Largeur {
						struct Point3D {
							Point3D () : x(0.0), y(0.0), z(0.0) {}

							float x;
							float y;
							float z;
						};

						Point3D gauche;
						Point3D droite;
					};

					Largeur haut;
					Largeur bas;
				};
				enum Face {
					Aucune	    =   0b0000000,

					Haut        =   0b0000001,
					Bas         =   0b0000010,
					Gauche      =   0b0000100,
					Droite      =   0b0001000,
					Avant       =   0b0010000,
					Arriere     =   0b0100000,

					Toutes      =   Haut | Bas | Gauche | Droite | Avant | Arriere
				};
				Q_DECLARE_FLAGS(Faces, Face);

				Cube () : hiddenFaces(Aucune) {}

				Hauteur avant;
				Hauteur arriere;

				Faces hiddenFaces;
			};
			typedef QList<Cube> CubeList;

        public:
            virtual ~Fractale3D () {}

            void init (const quint32 & nbIteration) {
				m_nbIterations = nbIteration;
				m_cancel = false;
            }

			/**
			 *	Crée les options du plugin.
			 *
			 *	\param[in]	parent	Le widget parent des options.
			 */
			virtual void createOptions (QWidget * parent) = 0;

			virtual void generer () = 0;
			virtual QString name () const = 0;

			virtual void clear () {
				m_forme.clear();
			}

			inline const CubeList & resultat () const {
				return m_forme;
			}

            inline quint32 nbIterations () const {
                return m_nbIterations;
            }
            inline void setNbIterations (const quint32 & nNbIteration) {
                m_nbIterations = nNbIteration;
            }

		public slots:
            inline void cancel () {
            	m_mutex.lock();
                m_cancel = true;
                m_mutex.unlock();
            }

		signals:
			void maximum (int max);
			void progression (int val);

		protected:
			quint32		m_nbIterations;
            CubeList	m_forme;

		protected:
			inline void uncancel () {
				m_mutex.lock();
                m_cancel = false;
                m_mutex.unlock();
			}
			bool isCancel () {
				bool escape = true;

				m_mutex.lock();
                escape = m_cancel;
                m_mutex.unlock();

                return escape;
			}

		private:
			bool	m_cancel;
            QMutex	m_mutex;
    };

    Q_DECLARE_INTERFACE(Fractale3D, "fractales.aspe.fractale3D/1.0.0")

    QT_END_HEADER

#endif

