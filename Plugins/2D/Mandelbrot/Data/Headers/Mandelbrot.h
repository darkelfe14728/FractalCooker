/*
 * Auteur					:	Richard Thomas
 *
 * Projet					:	Mandelbrot
 * Fichier					:	Mandelbrot.h
 *
 * Date de modification		:	mercredi 24 février 2010
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

#ifndef HEADER_GUARD_MANDELBROT_H
#define HEADER_GUARD_MANDELBROT_H

    #include <complex>
    #include <QtPlugin>
    #include <Fractale2D.h>

    /**
     * Classe permettant de générer l'image d'une fractale de Mandelbrot.
     *
     */
    class Mandelbrot : public Fractale2D
    {
        Q_OBJECT
        Q_INTERFACES(Fractale2D)

        public:
            /**
             * Fonction qui donne le nom de la fractale.
             * @return "Mandelbrot"
             */
            inline QString name() const {
                return QString("Mandelbrot");
            }

            /**
             * Procédure qui génère l'image de la fractale de mandelbrot.
             * @see calculerPixel(const QPoint&)
             */
            void generer();

        protected:
            /**
             * Fonction qui renvoie le symétrique d'un pixel.
             *
             */
            inline QPoint symetricOf(const QPoint &pixel) const {
                return QPoint(pixel.x(), 2 * m_yAxeReels - pixel.y());
            }

            /**
             * Fonction qui calcule le nombre d'étapes avant la divergence (ou non) de la suite pour un pixel donné.
             * Elle calcule les termes de la suite de mandelbrot jusqu'à ce qu'elle diverge ou que le nombre maximal d'itérations soit atteint.
             * @param Coordonnees Les coordonnées du pixel à traiter.
             * @return Le nombre d'itérations effectuées (compris entre 0 et le nombre max. d'itérations).
             * @see generer()
             */
            quint32 calculerPixel(const qreal &x, const qreal &y) const;

            /**
             * Fonction qui renvoie la couleur correspondant au nombre d'itérations effectué.
             * @param Nombre d'itérations effectuées.
             * @return La couleur à attribuer.
             */
            QColor couleurFromStep (const quint32 & step) const;

        private:
            qint32 m_yAxeReels;
    };

#endif // HEADER_GUARD_MANDELBROT_H
