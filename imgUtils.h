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
#include "ZBuffer.h"

#include <list>

using namespace img;
#ifndef IMGUTILS_H_
#define IMGUTILS_H_
typedef std::list<Line2D> Lines2D;

class imgUtils {
public:
	imgUtils();
	virtual ~imgUtils();
	static EasyImage LinesToImg(const ini::Configuration &configuration,Lines2D& lines,bool WithZBuf=false);	// converts a list of line2D's into an images
	static Lines2D figuresToLines2D(const ini::Configuration &configuration, std::vector<figure3D> &figures,bool WithZBuffer=false);
	static Point2D projectPoint(const Vector3D &point,const double d);
	static void draw_zbuf_line(ZBuffer & ZBuf, img::EasyImage & img, unsigned int x0, unsigned int y0,double z0,
				unsigned int x1, unsigned int y1,double z1,const img::Color &color);
	static double calculatePFactor(double za,double zb,double i,double a);
};
#endif /* IMGUTILS_H_ */
