/*
 * L2DEngine.h
 *
 *  Created on: Mar 1, 2018
 *      Author: thibaut
 *  A class that creates a list of line2D's by following a set of L2D rules
 */
#include "easy_image.h"
#include "ini_configuration.h"
#include "Line2D.h"

#include <cmath>
#include <list>
#include <utility>

#ifndef L2DENGINE_H_
#define L2DENGINE_H_

typedef std::list<Line2D> Lines2D;
class L2DEngine {
public:
	L2DEngine();
	virtual ~L2DEngine();
	Lines2D L2D_ToLines(const ini::Configuration &configuration); // converts a .L2D file into a list of lines if it is parsed correctly
};


#endif /* L2DENGINE_H_ */
