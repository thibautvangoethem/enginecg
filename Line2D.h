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

	Point2D p1;
	Point2D p2;
	figColor::Color color;
	double z1;
	double z2;

	/**
	 * \brief a constructor that initializes everything except z-values
	 * @param een,twee the two points
	 * @param kleur the color
	 */
	Line2D(Point2D een,Point2D twee,figColor::Color kleur):p1(een), p2(twee), color(kleur){
		z1=0;
		z2=0;
	}

	/**
	 * \brief a constructor that initializes everything
	 * @param een,twee the two points
	 * @param kleur the color
	 * @param Z1,Z2 the z values of the two points
	 */
	Line2D(Point2D een,Point2D twee,figColor::Color kleur,double Z1,double Z2):p1(een), p2(twee), color(kleur), z1(Z1), z2(Z2){}

	/**
	 * \brief default destructor
	 */
	virtual ~Line2D(){}

	/**
	 * \brief getter for p1
	 */
	Point2D getp1();

	/**
	 * \brief getter for p2
	 */
	Point2D getp2();

	/**
	 * \brief setter for p1
	 */
	void setp1(double x, double y);

	/**
	 * \brief setter for p2
	 */
	void setp2(double x, double y);

	/**
	 * \brief getter for color
	 */
	const figColor::Color getColor();


};

#endif /* LINE2D_H_ */
