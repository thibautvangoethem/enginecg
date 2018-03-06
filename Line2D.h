/*
 * line2D.h
 *
 *  Created on: Feb 20, 2018
 *      Author: thibaut
<<<<<<< HEAD
 *  A class that represents a 2DLine
=======
>>>>>>> 26da4b895d9671d3b3bcd107ab97715703238eca
 */

#ifndef LINE2D_H_
#define LINE2D_H_
#include "Point2D.h"
#include "Color.h"

class Line2D {
public:

	Line2D(Point2D een,Point2D twee,figColor::Color kleur):p1(een), p2(twee), color(kleur){}
	virtual ~Line2D(){}
	Point2D p1;
	Point2D p2;
	figColor::Color color;
	const Point2D getp1();
	const Point2D getp2();
	void setp1(double x, double y);
	void setp2(double x, double y);
	const figColor::Color getColor();


};

#endif /* LINE2D_H_ */
