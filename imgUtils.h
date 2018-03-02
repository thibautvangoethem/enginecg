/*
 * imgUtils.h
 *
 *  Created on: Mar 1, 2018
 *      Author: thibaut
 */
#include "easy_image.h"
#include "ini_configuration.h"
#include "Color.h"
#include "Point2D.h"
#include "Line2D.h"
#include "Line2D.h"
#include "l_parser.h"
#include "vector3d.h"
#include "figure3D.h"
#include "simpleGenerations.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>
#include <list>
#include <utility>

using namespace img;
#ifndef IMGUTILS_H_
#define IMGUTILS_H_
typedef std::list<Line2D> Lines2D;
namespace std {

class imgUtils {
public:
	imgUtils();
	virtual ~imgUtils();
	EasyImage LinesToImg(const ini::Configuration &configuration,Lines2D& lines);
};

} /* namespace img */

#endif /* IMGUTILS_H_ */
