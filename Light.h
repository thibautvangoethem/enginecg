/*
 * Light.h
 *
 *  Created on: Apr 24, 2018
 *      Author: thibaut
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include "Color.h"
#include "vector3d.h"
#include "ZBuffer.h"
#include "figure3D.h"
#include <iostream>



class Light {
  public:
	Light(figColor::Color am,figColor::Color diff,figColor::Color spec): ambientLight(am),diffuseLight(diff), specularLight(spec) {
		d=0;
		dx=0;
		dy=0;
	}
	virtual ~Light(){};
	//de ambiente licht component
	figColor::Color ambientLight;
	//de diffuse licht component
	figColor::Color diffuseLight;
	//de diffuse licht component
	figColor::Color specularLight;

	ZBuffer shadowmask;

	Matrix eye;

	double d;
	double dx;
	double dy;

	virtual Vector3D getSourceVector();

	void MakeShadowMask(std::vector<figure3D>& figures);

	void ShadowMAskTriangle(Vector3D const& A, Vector3D const& B, Vector3D const& C);

	static Matrix eyepointtrans(Vector3D eyepoint);
};

class InfLight: public Light
{
  public:
	InfLight(figColor::Color am,figColor::Color diff,figColor::Color spec,Vector3D ld):Light(am,diff,spec),ldVector(ld){};
	//de richting waarin het
	//licht schijnt
	Vector3D ldVector;

	Vector3D getSourceVector() override;
};

class PointLight: public Light
{
  public:
	PointLight(figColor::Color am,figColor::Color diff,figColor::Color spec,Vector3D loc):Light(am,diff,spec),location(loc){
		eye=Light::eyepointtrans(location);
	};
	//de locatie van de puntbron
	Vector3D location;

	Vector3D getSourceVector() override;
};
#endif /* LIGHT_H_ */
