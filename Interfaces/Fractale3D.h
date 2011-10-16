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

	#include "Fractale.h"

	#include <QtCore/QList>

    QT_BEGIN_HEADER

	/**
	 *	Interface générique à toutes les fractales 3D. \n
	 *	Chaque plugins de fractales 3D <u>doit</u> hériter de cette interface.
	 *
	 *	\warning Chaque plugin crée avec cette interface doit utiliser OpenGL. Pensez à modifier le projet en conséquence.
	 */
    class Fractale3D :
        public Fractale {

        Q_OBJECT

		public:
			/**
			 *	Déclaration de la forme sur laquelle opère la fractale : un cube.
			 *
			 *	Numérotation des sommets :
			 *	   ___________
				  /4        5/|
				 /          / |
				/__________/  |
				|0        1|  |
				|          |  |
				|    7     | 6/
				|          | /
				|3________2|/
			 *
			 *	\note A priori, cette structure devrait changer pour créer une interface générique.
			 */
			struct Cube {
				/**
				 *	Permet d'acceder aux arrêtes (ici haute et basse) d'une face.
				 */
				struct FaceType {
					/**
					 *	Permet d'accéder aux sommets d'une arrête d'une face.
					 */
					struct ArreteType {
						/**
						 *	Représente un sommet (c'est_à-dire un point dans un espace 3D).
						 *
						 *	\note Les coordonnées seront exprimées comme ceci : (x, y, z).
						 */
						struct SommetType {
							/**
							 *	Création d'un point : coordonées (0, 0, 0).
							 */
							Point3D () : x(0.0), y(0.0), z(0.0) {}

							/**
							 *	Alias pour le type d'une coordonnée.
							 */
							typedef float CoordonneeType;

							/**
							 *	Coordonnée en X (axe horizontal).
							 */
							CoordonneeType x;
							/**
							 *	Coordonnée en Y (axe des profondeurs).
							 */
							CoordonneeType y;
							/**
							 *	Coordonnée en Z (axe vertical).
							 */
							CoordonneeType z;
						};

						/**
						 *	Sommet gauche de l'arrête actuelle.
						 */
						SommetType gauche;
						/**
						 *	Sommet droit de l'arrête actuelle.
						 */
						SommetType droit;
					};

					/**
					 *	Arrête haute de la face actuelle.
					 */
					ArreteType haut;
					/**
					 *	Arrête basse de la face actuelle.
					 */
					ArreteType bas;
				};

				/**
				 *	Enumère toutes les faces d'un cube.
				 */
				enum FaceFlag {
					Aucune	    =   0b0000000,		/**< Pas de face. Cf hiddenFaces. */

					Haut        =   0b0000001,		/**< Face du haut		(sommets 0 - 4 - 5 - 1). */
					Bas         =   0b0000010,		/**< Face du bas		(sommets 3 - 7 - 6 - 2). */
					Gauche      =   0b0000100,		/**< Face de gauche		(sommets 0 - 4 - 7 - 3). */
					Droite      =   0b0001000,		/**< Face de droite		(sommets 1 - 5 - 6 - 2). */
					Avant       =   0b0010000,		/**< Face avant			(sommets 0 - 1 - 2 - 3). */
					Arriere     =   0b0100000,		/**< Face arrière		(sommets 4 - 5 - 6 - 7). */

					Toutes      =   Haut | Bas | Gauche | Droite | Avant | Arriere		/**< L'ensemble des faces. Cf hiddenFaces. */
				};
				/**
				 *	Réprésente une liste de faces (sans doublons).
				 */
				Q_DECLARE_FLAGS(Faces, FaceFlags);

				/**
				 *	Crée un cube de taille nulle (tous les sommets au même endroit, aucune face cachée).
				 */
				Cube () : hiddenFaces(Aucune) {}

				/**
				 *	Face avant du cube actuel.
				 */
				FaceType avant;
				/**
				 *	Face arrière du cube actuel.
				 */
				FaceType arriere;

				/**
				 *	Liste des faces cachées du cube actuel.
				 */
				Faces hiddenFaces;
			};
			/**
			 *	Alias pour une liste de cubes.
			 */
			typedef QList<Cube> CubeList;

        public:
            virtual ~Fractale3D () {}

			/**
			 *	Initialise le plugin.
			 *
			 *	\param[in]	nbItération		Le nombre d'itération (la profondeur du calcul).
			 */
            void init (const quint32 & nbIteration) {
				m_nbIterations = nbIteration;
				resetCancel();
            }

			/**
			 *	\return Le résultat de la génération, c'est-à-dire la fractale.
			 */
			inline const CubeList & resultat () const {
				return m_forme;
			}

			/**
			 *	Nettoie la fractale.
			 *
			 *	\note A placer dans la classe mère ?
			 */
			virtual void clear () {
				m_forme.clear();
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

		protected:
			/**
			 *	Le nombre d'itération (profondeur du calcul).
			 */
			quint32		m_nbIterations;
			/**
			 *	La forme de la fractale.
			 */
            CubeList	m_forme;
    };

    Q_DECLARE_INTERFACE(Fractale3D, "fractales.aspe.fractale3D/1.1.0")

    QT_END_HEADER

#endif

