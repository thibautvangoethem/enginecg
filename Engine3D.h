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
#include "Light.h"
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
	static figure3D LineDrawing(const ini::Configuration &configuration,int figcount);
	static figure3D DrawCube(const ini::Configuration &configuration,int figcount);
	static figure3D DrawTetrahedron(const ini::Configuration &configuration,int figcount);
	static figure3D DrawOctahedron(const ini::Configuration &configuration,int figcount);
	static figure3D DrawIcosahedron(const ini::Configuration &configuration,int figcount);
	static figure3D DrawDodecahedron(const ini::Configuration &configuration,int figcount);
	static figure3D DrawSphere(const ini::Configuration &configuration, const int figcount,const int n);
	static figure3D DrawCone(const ini::Configuration &configuration, const int figcount);
	static figure3D DrawCylinder(const ini::Configuration &configuration, const int figcount,const int n,const double height);
	static figure3D DrawTorus(const ini::Configuration &configuration, const int figcount);
	static figure3D DrawBuckyBall(const ini::Configuration &configuration, const int figcount);
	static void DrawThickFigure(const ini::Configuration &configuration, const int figcount,figure3D& fig,std::vector<figure3D>& figures);
	static void applyTransformation(figure3D &fig, const Matrix &mat);
	static void applyAllTransformation(std::vector<figure3D> &figs, const Matrix &mat);
	static Matrix eyePointTrans(const Vector3D &eyepoint);
	static void Topolar(const Vector3D &eyepoint,double& theta,double& phi,double& r);
	double toRadian(double angle);
	static figure3D combineFigures(std::vector<figure3D>& figures);
	static std::vector<Light*> readLights(const ini::Configuration &configuration);


private:
	static void AddCylinderHeight(figure3D& cylinder,double addition,double n);
};


#endif /* ENGINE3D_H_ */
