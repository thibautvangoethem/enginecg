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
	std::vector<figure3D> draw3D(const ini::Configuration &configuration);
	figure3D LineDrawing(const ini::Configuration &configuration,int figcount);
	figure3D DrawCube(const ini::Configuration &configuration,int figcount);
	figure3D DrawTetrahedron(const ini::Configuration &configuration,int figcount);
	figure3D DrawOctahedron(const ini::Configuration &configuration,int figcount);
	figure3D DrawIcosahedron(const ini::Configuration &configuration,int figcount);
	figure3D DrawDodecahedron(const ini::Configuration &configuration,int figcount);
	figure3D createSphere(const double radius, const int n);
	static void applyTransformation(figure3D &fig, const Matrix &mat);
	static void applyAllTransformation(std::vector<figure3D> &figs, const Matrix &mat);
	Matrix eyePointTrans(const Vector3D &eyepoint);
	double toRadian(double angle);
};


#endif /* ENGINE3D_H_ */
