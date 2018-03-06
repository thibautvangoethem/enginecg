/*
 * face3D.h
 *
 *  Created on: Mar 1, 2018
 *      Author: thibaut
<<<<<<< HEAD
 *  A class that represents faces of a 3Dfigure
=======
>>>>>>> 26da4b895d9671d3b3bcd107ab97715703238eca
 */

#ifndef FACE3D_H_
#define FACE3D_H_
#include <iostream>
#include <vector>
#include "Point2D.h"



class face3D {
public:
	std::vector<int> pointsIndex;
	face3D();
	face3D(std::vector<int> ps):pointsIndex(ps){}
	virtual ~face3D();
	face3D( const face3D & ) = default;
	void addPoint(int p);
};

#endif /* FACE3D_H_ */
