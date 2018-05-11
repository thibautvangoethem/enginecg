/*
 * figure3D.h
 *
 *  Created on: Feb 27, 2018
 *      Author: thibaut
 * A class that represents a 3D figure
 * Not yet finished, still needs 3D transformations and such
 */

#ifndef FIGURE3D_H_
#define FIGURE3D_H_
#include <iostream>
#include <vector>
#include "Color.h"
#include "face3D.h"
#include "vector3d.h"

class figure3D {
public:
	figure3D(figColor::Color amr,figColor::Color difr=figColor::Color(0,0,0),figColor::Color specr=figColor::Color(0,0,0), double ref=0):
			ambientReflection(amr), difusseReflection(difr), specularReflection(specr), reflectionCoefficient(ref){
			std::vector<face3D> faces;
	};
	figure3D(std::vector<face3D> fa,figColor::Color amr,figColor::Color difr,figColor::Color specr,double ref ):
		faces(fa),ambientReflection(amr), difusseReflection(difr),specularReflection(specr),reflectionCoefficient(ref){};
	std::vector<Vector3D> points;
	std::vector<face3D> faces;
	figColor::Color ambientReflection;
	figColor::Color difusseReflection;
	figColor::Color specularReflection;
	double reflectionCoefficient;

	virtual ~figure3D(){};
	void scaleFigure(const double scaleFactor);
	void rotateX(double angle,bool isradian=false);
	void rotateY(double angle,bool isradian=false);
	void rotateZ(double angle,bool isradian=false);
	void translate(const Vector3D vec);
	void addFace(face3D face);
	void addPoint(Vector3D v);
	void triangulate();
	static double toRadian(double angle);
};


#endif /* FIGURE3D_H_ */
