/*
 * Auteur	                :	RICHARD Thomas
 *
 * Projet	                :	Mandelbrot
 * Fichier	                :	Mandelbrot.cpp
 *
 * Date de modification	    :	dimanche 14 mars 2010
 */

/* Copyright (C) 2010 Groccia Patricia, Lévigne Florent, Richard Thomas, Rosset Julien
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
#include "Mandelbrot.h"
#include <cstdio>

using namespace std;

quint32 Mandelbrot::calculerPixel(const qreal &x, const qreal &y) const
{
    complex<qreal> z(0, 0),
                   c(x, y);
    quint32 i = nbIterations();

    while (i > 0 && abs(z) < 2)
    {
        z = z * z + c;
        i--;
    }
    //si i = m_nbIterations --> c appartient à l'ensemble --> couleur d'arrière-plan
    //sinon                 --> c n'apartient pas à l'ensemble --> couleur dépendant de i
    return i;
}

QColor Mandelbrot::couleurFromStep (const quint32 & step) const {
    quint32 r = step % 256,
            v = step % 256,
            b = (20 + step) % 256;

    return QColor(r, v, b);
}

void Mandelbrot::generer()
{
    qint32 j = 0,
           offset = 0,
           conditionDArret;
    qreal  debut,
           fin;
    QRectF bornes(m_centre.x() + (m_drawZone.x() - 0.5 * m_drawZone.width()) / m_zoom,
				  m_centre.y() + (m_drawZone.y() - 0.5 * m_drawZone.height()) / m_zoom,
				  m_drawZone.width() / m_zoom,
				  m_drawZone.height() / m_zoom);
    QPoint pointToAdd;
    bool escape;

    uncancel();

    // Pour déterminer où se trouve la plus grande partie de la fractale par rapport à l'axe des réel
    if (abs(bornes.top()) < abs(bornes.bottom()))
    {
        //partie positive
//printf("Positif\n");
        debut = qRound(bornes.bottom() * m_zoom) / m_zoom;
        fin = qMax(bornes.top(), 0.0);

        conditionDArret = qRound((debut - fin) * m_zoom) + 1;

        m_yAxeReels = conditionDArret - 1;
    }
    else
    {
        //partie négative
//printf("Negatif\n");
        debut = qMin(bornes.bottom(), 0.0);
        fin = bornes.top();

        conditionDArret = qRound((debut - fin) * m_zoom);

        offset = m_drawZone.height() - conditionDArret;

        m_yAxeReels = offset;
    }
    emit maximum(conditionDArret * m_drawZone.width());

    // indication de la symétrie
    m_symetric = (m_yAxeReels > 0 && m_yAxeReels < m_drawZone.height());
//printf("debut= %f\tfin= %f\tconditionDArret= %d\tm_yAxeReels= %d\n", debut, fin, conditionDArret, m_yAxeReels);
    while (j < conditionDArret)
    {
        for (qint32 i=0; i<m_drawZone.width(); i++)
        {
//printf("i= %d\tj= %d\n", i, j);
            pointToAdd = QPoint(i, j + offset);
//printf("after point:ToAdd\n");
            quint32 step = calculerPixel(bornes.left() + i / m_zoom, debut - j / m_zoom);
//printf("after calculerPixel()\n");
            addPoint(pointToAdd, step);
//printf("after addPoint()\n");
            emit progression(i + m_drawZone.width() * j);
//printf("after emit progression()\n");
            m_mutex.lock();
            escape = m_cancel;
            m_mutex.unlock();

            if(escape)
                return;
        }
        j++;
//printf("End while()\n");
    }
}

Q_EXPORT_PLUGIN2(Mandelbrot, Mandelbrot)
