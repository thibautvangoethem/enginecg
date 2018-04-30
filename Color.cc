/*
 * Color.cpp
 *
 *  Created on: Feb 20, 2018
 *      Author: thibaut
 */

#include "Color.h"
bool figColor::Color::operator ==(const Color &b) const{
	return red==b.red&&green==b.green&&blue==b.blue;
}
bool figColor::Color::operator !=(const Color &b) const{
	return red!=b.red||green!=b.green||blue!=b.blue;
}
