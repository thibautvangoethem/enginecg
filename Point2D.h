/*
 * Point2D.h
 *
 *  Created on: Feb 20, 2018
 *      Author: thibaut
<<<<<<< HEAD
 *  A class that represents a point in a 2D image
=======
>>>>>>> 26da4b895d9671d3b3bcd107ab97715703238eca
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
