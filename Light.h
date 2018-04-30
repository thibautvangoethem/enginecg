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
class Light {
  public:
	Light(figColor::Color am,figColor::Color diff,figColor::Color spec): ambientLight(am),diffuseLight(diff), specularLight(spec) {}
	virtual ~Light(){};
	//de ambiente licht component
	figColor::Color ambientLight;
	//de diffuse licht component
	figColor::Color diffuseLight;
	//de diffuse licht component
	figColor::Color specularLight;

	virtual Vector3D getSourceVector();
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
	PointLight(figColor::Color am,figColor::Color diff,figColor::Color spec,Vector3D loc):Light(am,diff,spec),location(loc){};
	//de locatie van de puntbron
	Vector3D location;

	Vector3D getSourceVector() override;
};
#endif /* LIGHT_H_ */
