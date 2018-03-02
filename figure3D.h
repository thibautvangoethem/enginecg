/*
 * figure3D.h
 *
 *  Created on: Feb 27, 2018
 *      Author: thibaut
 */

#ifndef FIGURE3D_H_
#define FIGURE3D_H_
#include <iostream>
#include <vector>
#include "Color.h"
#include "face3D.h"
#include "vector3d.h";
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

	void addFace(face3D face);
};


#endif /* FIGURE3D_H_ */
