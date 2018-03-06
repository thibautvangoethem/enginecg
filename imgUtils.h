/*
 * imgUtils.h
 *
 *  Created on: Mar 1, 2018
 *      Author: thibaut
 *  A class that is used to contain a bunch of methods that helps with creating an image
 */
#include "easy_image.h"
#include "Color.h"
#include "Line2D.h"

#include <list>

using namespace img;
#ifndef IMGUTILS_H_
#define IMGUTILS_H_
typedef std::list<Line2D> Lines2D;
namespace std {

class imgUtils {
public:
	imgUtils();
	virtual ~imgUtils();
	EasyImage LinesToImg(const ini::Configuration &configuration,Lines2D& lines);	// converts a list of line2D's into an image
};

} /* namespace img */

#endif /* IMGUTILS_H_ */
