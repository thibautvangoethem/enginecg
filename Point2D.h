/*
 * Point2D.h
 *
 *  Created on: Feb 20, 2018
 *      Author: thibaut
 *  A class that represents a point in a 2D image
 */

#ifndef POINT2D_H_
#define POINT2D_H_

class Point2D {
public:
	double x;
	double y;

	/**
	 * \brief constructor for a point that initalizes everything
	 * @param xco,yxo the two coordinates
	 */
	Point2D(double xco,double yxo):x(xco),y(yxo){};

	/**
	 * \brief default destructor
	 */
	virtual ~Point2D(){}

	/**
	 * \brief getter for x-coordinate
	 */
	double getx();

	/**
	 * \brief getter for y-coordinate
	 */
	double gety();
};

#endif /* POINT2D_H_ */
