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
		/**
		 * \brief constructor that initialises all variabels
		 *
		 * @param r,g,b double that represent their repsectiee color
		 */
		Color(double r,double g,double b): red(r),green(g),blue(b){};

		/**
		 * \brief equality operators
		 */
		bool operator ==(const Color &b) const;
		bool operator !=(const Color &b) const;

		/**
		 * \brief basic destructor
		 */
		virtual ~Color(){}
		double red;
		double green;
		double blue;
	};
}

#endif /* COLOR_H_ */
