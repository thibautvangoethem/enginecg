/*
 * Color.h
 *
 *  Created on: Feb 20, 2018
 *      Author: thibaut
 *
 *  A simple class to store colors of the rgb spectrum
 */

#ifndef COLOR_H_
#define COLOR_H_

namespace figColor{
	class Color {
	public:
		Color(double r,double g,double b): red(r),green(g),blue(b){};
		bool operator ==(const Color &b) const;
		bool operator !=(const Color &b) const;
		virtual ~Color(){}
		double red;
		double green;
		double blue;
	};
}

#endif /* COLOR_H_ */
