/*
 * To2DConverter.h
 *
 *  Created on: May 17, 2018
 *      Author: thibaut
 */

#ifndef TO2DCONVERTER_H_
#define TO2DCONVERTER_H_

#include "Line2D.h"
#include "figure3D.h"

#include <list>
#include <iostream>
#include <vector>


typedef std::list<Line2D> Lines2D;
class To2DConverter {
public:
	/**
	 * \brief this function takes a bunch if lines2D and moves them all to positive coordinates while noting the max and min values
	 * @param lines the lines that will be moved
	 * @param xmin,xmax,ymin,ymax the min and max values that will be returned
	 */
	static void moveToPos(Lines2D& lines,double& xmin,double& ymin,double& xmax,double& ymax);

	/**
	 * \brief this functions takes a vector of figure3D and turns them into 2dimensional lines
	 * @param figures the figures that will be projected to 2d
	 * @param withZbuffer a bool that says whether the z-values should be kept or not
	 */
	static Lines2D figuresToLines2D(std::vector<figure3D> &figures,bool WithZBuffer=false);

	/**
	 * \brief this function project a single point to 2D
	 * @param point the 3D point that is priojected
	 * @param d the distance between the point and the projection face
	 */
	static Point2D projectPoint(const Vector3D &point,const double d);
};


#endif /* TO2DCONVERTER_H_ */
