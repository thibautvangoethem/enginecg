/*
 * line2D.h
 *
 *  Created on: Feb 20, 2018
 *      Author: thibaut
 *  A class that represents a 2DLine
 */

#ifndef LINE2D_H_
#define LINE2D_H_
#include "Point2D.h"
#include "Color.h"

class Line2D {
public:

	Line2D(Point2D een,Point2D twee,figColor::Color kleur):p1(een), p2(twee), color(kleur){}
	Line2D(Point2D een,Point2D twee,figColor::Color kleur,double Z1,double Z2):p1(een), p2(twee), color(kleur), z1(Z1), z2(Z2){}
	virtual ~Line2D(){}
	Point2D p1;
	Point2D p2;
	figColor::Color color;
	double z1;
	double z2;
	Point2D getp1();
	Point2D getp2();
	void setp1(double x, double y);
	void setp2(double x, double y);
	const figColor::Color getColor();


};

#endif /* LINE2D_H_ */
