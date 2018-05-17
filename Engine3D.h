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
	/**
	 * \brief the main function of the Engine3D class that takes a configuration with 3D figures and reads them in, it also instantly rotates and transfrom them
	 */
	static std::vector<figure3D> draw3D(const ini::Configuration &configuration);

	/**
	 * \brief The function that draws simple line drawings
	 * @param configuration the config where the figure is located at
	 * @param figcount an int that represents the number where the figure is at in the config
	 */
	static figure3D LineDrawing(const ini::Configuration &configuration,int figcount);

	/**
	 * \brief this function draws a cube
	 * @param configuration the config where the figure is located at
	 * @param figcount an int that represents the number where the figure is at in the config
	 *
	 */
	static figure3D DrawCube(const ini::Configuration &configuration,int figcount);

	/**
	 * \brief The function that draws a tetrahedron
	 * @param configuration the config where the figure is located at
	 * @param figcount an int that represents the number where the figure is at in the config
	 */
	static figure3D DrawTetrahedron(const ini::Configuration &configuration,int figcount);

	/**
	 * \brief The function that draws an octahedron
	 * @param configuration the config where the figure is located at
	 * @param figcount an int that represents the number where the figure is at in the config
	 */
	static figure3D DrawOctahedron(const ini::Configuration &configuration,int figcount);

	/**
	 * \brief The function that draws an icosahedron
	 * @param configuration the config where the figure is located at
	 * @param figcount an int that represents the number where the figure is at in the config
	 */
	static figure3D DrawIcosahedron(const ini::Configuration &configuration,int figcount);

	/**
	 * \brief The function that draws a dodecahedron
	 * @param configuration the config where the figure is located at
	 * @param figcount an int that represents the number where the figure is at in the config
	 */
	static figure3D DrawDodecahedron(const ini::Configuration &configuration,int figcount);

	/**
	 * \brief The function that draws a aproximation of a sphere trough an icosahedron
	 * @param configuration the config where the figure is located at
	 * @param figcount an int that represents the number where the figure is at in the config
	 * @param n an int that represent the amount of times it need to recursively enhaance the shape of the sphere
	 */
	static figure3D DrawSphere(const ini::Configuration &configuration, const int figcount,const int n);

	/**
	 * \brief The function that draws a cone
	 * @param configuration the config where the figure is located at
	 * @param figcount an int that represents the number where the figure is at in the config
	 */
	static figure3D DrawCone(const ini::Configuration &configuration, const int figcount);

	/**
	 * \brief The function that draws a cylinder
	 * @param configuration the config where the figure is located at
	 * @param figcount an int that represents the number where the figure is at in the config
	 * @param n an int that represents the amount of faces the side of the cylinder is made of
	 * @param height a double that represents the height of the cyilinder
	 */
	static figure3D DrawCylinder(const ini::Configuration &configuration, const int figcount,const int n,const double height);

	/**
	 * \brief The function that draws simple line drawings
	 * @param configuration the config where the figure is located at
	 * @param figcount an int that represents the number where the figure is at in the config
	 */
	static figure3D DrawTorus(const ini::Configuration &configuration, const int figcount);

	/**
	 * \brief The function that draws a bucky ball
	 * @param configuration the config where the figure is located at
	 * @param figcount an int that represents the number where the figure is at in the config
	 *
	 * note: currently the top face has it's points given in clockwise direction which gives a bug with the lightinh
	 */
	static figure3D DrawBuckyBall(const ini::Configuration &configuration, const int figcount);

	/**
	 * \brief this function takes a figure and makes it a combination of spheres and cylinders
	 * @param configuration the config where the figure is located at
	 * @param figcount an int that represents the number where the figure is at in the config
	 * @param fig a figure3D that is the original figure
	 * @param figures a vector of figure3D where the new figrues are going to be placed
	 */
	static void DrawThickFigure(const ini::Configuration &configuration, const int figcount,figure3D& fig,std::vector<figure3D>& figures);

	/**
	 * \brief this function aplies a matrix transformation on 1 figure
	 * @param fig a figure that is going to be transformed
	 * @param mat the matrix which defines the transformation
	 */
	static void applyTransformation(figure3D &fig, const Matrix &mat);

	/**
	 * \brief this function aplies a matrix transformation on multiple figures
	 * @param figs figures that are going to be transformed
	 * @param mat the matrix which defines the transformation
	 */
	static void applyAllTransformation(std::vector<figure3D> &figs, const Matrix &mat);

	/**
	 * \brief this function calculates the eyePoint matrix and returns it
	 * @param eyepoint a point in the 3D space that represents the eye point
	 */
	static Matrix eyePointTrans(const Vector3D &eyepoint);

	/**
	 * \brief this function turns eyepoint coordinates into poloar coordinates
	 * @param eyepoint a vector3D that is going to be turned into polar coordinates
	 * @param theta, phi, r reference to the what will bevom the polar coordinates
	 */
	static void Topolar(const Vector3D &eyepoint,double& theta,double& phi,double& r);

	/**
	 * \brief this function turns coordinates into radian coordinates
	 * @param angle a double that will be turned into radian
	 */
	double toRadian(double angle);

	/**
	 * \brief this function takes a bunch of figure and turns it into 1 figure
	 * @param figures the figures that will be turned into 1 figure
	 */
	static figure3D combineFigures(std::vector<figure3D>& figures);

	/**
	 * \brief this function reads all light correctly and initializes them onto the stack
	 * @param configuration the config that contains the lights
	 */
	static std::vector<Light*> readLights(const ini::Configuration &configuration);

	/**
	 * \brief this function creates a figure without faces or points but with color
	 * @param configuration the config conatining the colour
	 * @param figure the string representing the figcount in the config
	 */
	static figure3D createEmptyColorFigure(const ini::Configuration &configuration,std::string figure);


private:
	/**
	 * \brief this function ads a certain height to a non transformed cylinder (used in drawthickfigure function)
	 * @param cylinder the cylinder you are adding height to
	 * @param addition the amount of height you are adding
	 * @param n the amount of faces that are in the circumference of the cylinder
	 */
	static void AddCylinderHeight(figure3D& cylinder,double addition,double n);
};


#endif /* ENGINE3D_H_ */
