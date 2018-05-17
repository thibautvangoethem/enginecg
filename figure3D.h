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
	std::vector<Vector3D> points;
	std::vector<face3D> faces;
	figColor::Color ambientReflection;
	figColor::Color difusseReflection;
	figColor::Color specularReflection;
	double reflectionCoefficient;

	/**
	 * \brief a constructor that can initializes everything
	 * @param amr the ambient color
	 * @param difr the differential color
	 * @param specr the specular color
	 * @param ref the reflection coefficient
	 */
	figure3D(figColor::Color amr,figColor::Color difr=figColor::Color(0,0,0),figColor::Color specr=figColor::Color(0,0,0), double ref=0):
			ambientReflection(amr), difusseReflection(difr), specularReflection(specr), reflectionCoefficient(ref){
			std::vector<face3D> faces;
	};

	/**
	 * \brief a constructor that mist initializes everything
	 * @param amr the ambient color
	 * @param difr the differential color
	 * @param specr the specular color
	 * @param ref the reflection coefficient
	 */
	figure3D(std::vector<face3D> fa,figColor::Color amr,figColor::Color difr,figColor::Color specr,double ref ):
		faces(fa),ambientReflection(amr), difusseReflection(difr),specularReflection(specr),reflectionCoefficient(ref){};

	/**
	 * \brief default destructor
	 */
	virtual ~figure3D(){};

	/**
	 * \brief a function that scales the figure
	 * @param a double that the figure is going to be scaled with
	 */
	void scaleFigure(const double scaleFactor);

	/**
	 * \brief this function perform a rotation over the x-axis
	 * @param angle the angle that you are rotating over
	 * @param isradian a bool that says whether the angle is in radian form or not
	 */
	void rotateX(double angle,bool isradian=false);

	/**
	 * \brief this function perform a rotation over the y-axis
	 * @param angle the angle that you are rotating over
	 * @param isradian a bool that says whether the angle is in radian form or not
	 */
	void rotateY(double angle,bool isradian=false);

	/**
	 * \brief this function perform a rotation over the z-axis
	 * @param angle the angle that you are rotating over
	 * @param isradian a bool that says whether the angle is in radian form or not
	 */
	void rotateZ(double angle,bool isradian=false);

	/**
	 * \brief this funtion translates the figure over a vector
	 * @param vec the vector you are translating over
	 */
	void translate(const Vector3D vec);

	/**
	 * \brief this function adds a face3D
	 * @param face the face you are adding
	 */
	void addFace(face3D face);

	/**
	 * \brief this function adds a point
	 * @param v the point you are adding
	 */
	void addPoint(Vector3D v);

	/**
	 * \brief this function turns all faces in this figure into triangles
	 */
	void triangulate();

	/**
	 * \brief this function turns an angle into radian
	 *  @param angle the angel that wil be turned into radian
	 */
	static double toRadian(double angle);
};


#endif /* FIGURE3D_H_ */
