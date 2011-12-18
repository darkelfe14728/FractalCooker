/*
 * Auteur					:	Rosset Julien
 *
 * Projet					:	FractalCooker/Interfaces
 * Fichier					:	Fractale3D.cpp
 *
 * Date de création			:	samedi 17 décembre 2011
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

#include "Fractale3D.h"
using namespace Interfaces;

Fractale3D::Fractale3D () :
	m_shaders(0),
	m_location_calcul(-1),
	m_location_color(-1)
{}

void Fractale3D::init (QGLShaderProgram * shaders,
					   const int loc_calcul,
					   const int loc_color,
					   const quint32 nbIteration) {
	m_shaders = shaders;

	m_location_calcul = loc_calcul;
	m_location_color = loc_color;

	setNbIterations(nbIteration);
	resetCancel();
}

int Fractale3D::zoom () const {
	return 70;
}
int Fractale3D::nearDistance () const {
	return 1;
}
int Fractale3D::farDistance () const {
	return 1000;
}

int Fractale3D::getCalculLocation () const {
	return m_location_calcul;
}
int Fractale3D::getColorLocation () const {
	return m_location_color;
}

QGLShaderProgram * Fractale3D::shaders () {
	return m_shaders;
}
