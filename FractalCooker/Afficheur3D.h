/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	FractalCooker/FractalCooker
 * Fichier					:	Afficheur3D.h
 *
 * Date de création			:	vendredi 25 mai 2012
 *
 * Description				:	Classe gérant l'affichage des fractales 3D
 */

/* Copyright (C) 2010-2012 LEVIGNE Florent, GROCCIA Patricia, RICHARD Thomas, ROSSET Julien
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

#ifndef HEADERGUARD_FRACTALCOOKER_AFFICHEUR3D_H
#define HEADERGUARD_FRACRALCOOKER_AFFICHEUR3D_H

#include <QtOpenGL/QGLWidget>

class QGLShaderProgram;
namespace Interfaces {
	class Fractale3D;
}

class Afficheur3D : public QGLWidget
{
		Q_OBJECT

	public:
		explicit Afficheur3D(QWidget * parent = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0);

		void loadFractale (Interfaces::Fractale3D * fract);
		
	protected:
		void initializeGL ();
		void paintGL ();

		void wheelEvent (QWheelEvent * event);

	private:
		Interfaces::Fractale3D * m_fractale;
		QGLShaderProgram * m_shaders;

		bool m_initialized;

		int m_location_projection;
		int m_location_vertex;
		int m_location_calcul;
		int m_location_color;

		float m_zoom;

		QPoint m_transfoReference;


		void clear ();
};

#endif // HEADERGUARD_FRACTALCOOKER_AFFICHEUR3D_H
