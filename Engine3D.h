/*
 * Engine3D.h
 *
 *  Created on: Mar 1, 2018
 *      Author: thibaut
 *  A class to render 3D images
 *  Not yet finished
 */

#ifndef ENGINE3D_H_
#define ENGINE3D_H_
#include "figure3D.h"
#include "face3D.h"
#include "Color.h"
#include "vector3d.h"
#include "ini_configuration.h"
#include <vector>
#include <list>
#include <cmath>
#include "Line2D.h"

typedef std::list<Line2D> Lines2D;

class Engine3D {
public:
	Engine3D(){};
	virtual ~Engine3D();
	Lines2D draw3D(const ini::Configuration &configuration);
	figure3D LineDrawing(const ini::Configuration &configuration);
	figure3D applyTransformation(figure3D &fig, const Matrix &mat);
};


#endif /* ENGINE3D_H_ */
