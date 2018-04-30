/*
 * Light.cc
 *
 *  Created on: Apr 24, 2018
 *      Author: thibaut
 */

#include "Light.h"
#include "Color.h"
#include "vector3d.h"

Vector3D Light::getSourceVector(){
	return Vector3D::point(0,0,0);
}

Vector3D InfLight::getSourceVector(){
	return InfLight::ldVector;
}

Vector3D PointLight::getSourceVector(){
	return PointLight::location;
}
