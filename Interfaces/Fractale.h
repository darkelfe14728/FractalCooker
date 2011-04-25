/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	Program
 * Fichier					:	Fractale2D.h
 *
 * Date de création			:	lundi 10 janvier 2011
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

#ifndef HEADERGUARD_INTERFACES_FRACTALE_H
#define HEADERGUARD_INTERFACES_FRACTALE_H

    #include <QtCore/QObject>
    #include <QtCore/QMutex>
    #include <QtCore/QMutexLocker>
    #include <QtCore/QString>

    QT_BEGIN_HEADER

    /**
     *	Interface générique à toutes les fractales. \n
     *
     *	\warning Aucun plugin ne peut être créé \a directement à partir de cette interface.
     */
    class Fractale :
        public QObject {

        Q_OBJECT

        public:
			Fractale () : m_cancel(false) {}
            virtual ~Fractale () {}

			// Une fonction d'initialisation. Ne peux pas être déclarée ici car les paramètres varient d'une interface à une autre.
            // virtual void init (XXX) = 0;

			/**
			 *	Crée les options du plugin.
			 *
			 *	\param[in]	parent	Le widget parent des options.
			 */
			virtual void createOptions (QWidget * parent) = 0;

			/**
             *	\return Le nom de la fractale.
             */
            virtual QString name () const = 0;

            // Fonction de résultat. Ne peux pas être déclarée ici car le type de retour varie en fonction d'une interface à une autre.
            //virtual const XXX & resultat () const = 0;

            // Déclarer ici ?
            inline quint32 nbIterations () const {
                return m_nbIterations;
            }
            inline void setNbIterations (const quint32 nNbIteration) {
                m_nbIterations = nNbIteration;
            }

		public slots:
			/**
			 *	Annule la génération de la fractale.
			 *
			 *	\sa m_cancel.
			 */
            inline void cancel () {
                QMutexLocker locker(&m_mutex_cancel);
                m_cancel = true;
            }

        signals:
			/**
             *	Transmet la valeur de la progression.
             *	Doit être inférieur ou égal à la valeur transmise par maximum.
             */
            void progression (int fait);

        protected:
			/**
			 *	\return Vrai si la génération doit être annulée<br/>
			 *			Faux sinon.
			 */
			bool isCancel () {
				QMutexLocker locker(&m_mutex_cancel);
                return m_cancel;
			}

        protected slots:
			/**
			 *	Remet à zéro la variable d'annulation.
			 */
			inline void resetCancel () {
                QMutexLocker locker(&m_mutex_cancel);
                m_cancel = false;
            }

		private:
			/**
			 *	Est-ce que la génération doit-être annulée ?
			 *
			 *	\sa cancel et resetCancel.
			 */
            bool	m_cancel;
            /**
             *	Mutex protégeant la variable m_cancel.
             */
            QMutex	m_mutex_cancel;

			/**
			 *	Le nombre d'itération (profondeur du calcul).
			 */
			quint32	m_nbIterations;
    };

	// Il ne s'agit pas réellement d'une interface pour plugin.
    //Q_DECLARE_INTERFACE(Fractale, "fractales.aspe.fractale/1.0.0")

    QT_END_HEADER

#endif

