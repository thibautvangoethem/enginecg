/*
 * Color.h
 *
 *  Created on: Feb 20, 2018
 *      Author: thibaut
 */

#ifndef COLOR_H_
#define COLOR_H_

namespace figColor{
	class Color {
	public:
		Color(double r,double g,double b): red(r),green(g),blue(b){};
		virtual ~Color(){}
		double red;
		double green;
		double blue;
	};
}

#endif /* COLOR_H_ */
