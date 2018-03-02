/*
 * line2D.cpp
 *
 *  Created on: Feb 20, 2018
 *      Author: thibaut
 */

#include "Line2D.h"
#include "Point2D.h"
#include "Color.h"

const Point2D Line2D::getp1(){
	return Line2D::p1;
}
const Point2D Line2D::getp2(){
	return Line2D::p2;
}
const figColor::Color Line2D::getColor(){
	return Line2D::color;
}
void Line2D::setp1(double x, double y){
	Line2D::p1=Point2D(x,y);
}
void Line2D::setp2(double x, double y){
	Line2D::p2=Point2D(x,y);
}
