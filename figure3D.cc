/*
 * figure3D.cc
 *
 *  Created on: Feb 27, 2018
 *      Author: thibaut
 */

#include "figure3D.h"
#include "face3D.h"
#include "Color.h"

void figure3D::addFace(face3D face){ // @suppress("Member declaration not found")
	faces.push_back(face);
}

void figure3D::addPoint(Vector3D v){
	points.push_back(v);
}


