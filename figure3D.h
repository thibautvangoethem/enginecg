/*
 * figure3D.h
 *
 *  Created on: Feb 27, 2018
 *      Author: thibaut
<<<<<<< HEAD
 * A class that represents a 3D figure
 * Not yet finished, still needs 3D transformations and such
=======
>>>>>>> 26da4b895d9671d3b3bcd107ab97715703238eca
 */

#ifndef FIGURE3D_H_
#define FIGURE3D_H_
#include <iostream>
#include <vector>
#include "Color.h"
#include "face3D.h"
<<<<<<< HEAD
#include "vector3d.h"

=======
#include "vector3d.h";
>>>>>>> 26da4b895d9671d3b3bcd107ab97715703238eca
class figure3D {
public:
	figure3D(figColor::Color co ): color(co){
		std::vector<face3D> faces;
	};
	figure3D(std::vector<face3D> fa,figColor::Color co ): faces(fa), color(co){};
	std::vector<Vector3D> points;
	std::vector<face3D> faces;
	figColor::Color color;
	void addPoint(Vector3D v);
	virtual ~figure3D(){};
<<<<<<< HEAD
	void scaleFigure(const double scaleFactor);
	void rotateX(const double angle);
	void rotatey(const double angle);
	void rotatez(const double angle);
	void translate(const Vector3D vec);
	void center();
=======
>>>>>>> 26da4b895d9671d3b3bcd107ab97715703238eca

	void addFace(face3D face);
};


#endif /* FIGURE3D_H_ */
