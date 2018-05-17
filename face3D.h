/*
 * face3D.h
 *
 *  Created on: Mar 1, 2018
 *      Author: thibaut
 *  A class that represents faces of a 3Dfigure
 */

#ifndef FACE3D_H_
#define FACE3D_H_
#include <iostream>
#include <vector>
#include "Point2D.h"



class face3D {
public:
	std::vector<int> pointsIndex;

	/**
	 * \brief default constructor
	 */

	face3D();
	/**
	 * \brief constructor with pointindex
	 * @param ps a vector of int that represent the indexes of the points
	 */
	face3D(std::vector<int> ps):pointsIndex(ps){}

	/**
	 * \brief default destructor
	 */
	virtual ~face3D();
	face3D( const face3D & ) = default;

	/**
	 * \brief a function that adds a point
	 * @param an int that is the index of the new point
	 */
	void addPoint(int p);
};

#endif /* FACE3D_H_ */
