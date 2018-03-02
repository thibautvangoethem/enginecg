/*
 * L2DEngine.h
 *
 *  Created on: Mar 1, 2018
 *      Author: thibaut
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
	Lines2D L2D_ToLines(const ini::Configuration &configuration);
};


#endif /* L2DENGINE_H_ */
