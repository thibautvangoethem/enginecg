/*
 * Point2D.h
 *
 *  Created on: Feb 20, 2018
 *      Author: thibaut
 */

#ifndef POINT2D_H_
#define POINT2D_H_

class Point2D {
public:
	Point2D(double xco,double yxo):x(xco),y(yxo){};
	virtual ~Point2D(){}
	double x;
	double y;
	double getx();
	double gety();
};

#endif /* POINT2D_H_ */
