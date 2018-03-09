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
#include "figure3D.h"

#include <list>

using namespace img;
#ifndef IMGUTILS_H_
#define IMGUTILS_H_
typedef std::list<Line2D> Lines2D;

class imgUtils {
public:
	imgUtils();
	virtual ~imgUtils();
	static EasyImage LinesToImg(const ini::Configuration &configuration,Lines2D& lines);	// converts a list of line2D's into an images
	static Lines2D figuresToLines2D(const ini::Configuration &configuration, std::vector<figure3D> &figures);
	static Point2D projectPoint(const Vector3D &point,const double d);
};
#endif /* IMGUTILS_H_ */
