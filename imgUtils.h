/*
 * imgUtils.h
 *
 *  Created on: Mar 1, 2018
 *      Author: thibaut
<<<<<<< HEAD
 *  A class that is used to contain a bunch of methods that helps with creating an image
 */
#include "easy_image.h"
#include "Color.h"
#include "Line2D.h"

#include <list>
=======
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
>>>>>>> 26da4b895d9671d3b3bcd107ab97715703238eca

using namespace img;
#ifndef IMGUTILS_H_
#define IMGUTILS_H_
typedef std::list<Line2D> Lines2D;
namespace std {

class imgUtils {
public:
	imgUtils();
	virtual ~imgUtils();
<<<<<<< HEAD
	EasyImage LinesToImg(const ini::Configuration &configuration,Lines2D& lines);	// converts a list of line2D's into an image
=======
	EasyImage LinesToImg(const ini::Configuration &configuration,Lines2D& lines);
>>>>>>> 26da4b895d9671d3b3bcd107ab97715703238eca
};

} /* namespace img */

#endif /* IMGUTILS_H_ */
