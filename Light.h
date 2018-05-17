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

	/**
	 * \brief a constructor that initializes the colors and the reflection coeficcinet
	 */
	Light(figColor::Color am,figColor::Color diff,figColor::Color spec): ambientLight(am),diffuseLight(diff), specularLight(spec) {
		d=0;
		dx=0;
		dy=0;
	}

	/**
	 * \brief base destructor
	 */
	virtual ~Light(){};

	/**
	 * \brief a function that returns the soruce vector, should be overwritten in the inhereted classes
	 */
	virtual Vector3D getSourceVector();

	/**
	 * \brief a function that makes the shadowmask for this light
	 * @param figures all the figures that are used to create the shadowmask
	 */
	void MakeShadowMask(std::vector<figure3D>& figures);

	/**
	 * \brief a function that makes adds a triangle to the shadowmask
	 * @param A,B,C the points of the triangle
	 */
	void ShadowMaskTriangle(Vector3D const& A, Vector3D const& B, Vector3D const& C);

	/**
	 * \brief a function that calculates the eyepoint vector for this light
	 * @param eyepoint the eyepoint of this light
	 */
	static Matrix eyepointtrans(Vector3D eyepoint);
};

class InfLight: public Light
{
  public:
	Vector3D ldVector;

	/**
	 * \brief a constructor for a light in infinity  that initializes everythin
	 */
	InfLight(figColor::Color am,figColor::Color diff,figColor::Color spec,Vector3D ld):Light(am,diff,spec),ldVector(ld){};

	Vector3D getSourceVector() override;
};

class PointLight: public Light
{
  public:
	Vector3D location;

	/**
	 * \brief a constructor for a pointlight that initializes everything
	 */
	PointLight(figColor::Color am,figColor::Color diff,figColor::Color spec,Vector3D loc):Light(am,diff,spec),location(loc){
		eye=Light::eyepointtrans(location);
	};


	Vector3D getSourceVector() override;
};
#endif /* LIGHT_H_ */
