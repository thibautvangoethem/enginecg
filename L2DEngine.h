/*
 * L2DEngine.h
 *
 *  Created on: Mar 1, 2018
 *      Author: thibaut
<<<<<<< HEAD
 *  A class that creates a list of line2D's by following a set of L2D rules
=======
>>>>>>> 26da4b895d9671d3b3bcd107ab97715703238eca
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
<<<<<<< HEAD
	Lines2D L2D_ToLines(const ini::Configuration &configuration); // converts a .L2D file into a list of lines if it is parsed correctly
=======
	Lines2D L2D_ToLines(const ini::Configuration &configuration);
>>>>>>> 26da4b895d9671d3b3bcd107ab97715703238eca
};


#endif /* L2DENGINE_H_ */
