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
#include "Light.h"

#include <list>


using namespace img;
#ifndef IMGUTILS_H_
#define IMGUTILS_H_
typedef std::list<Line2D> Lines2D;

class imgUtils {
public:
	/**
	 * \brief this functions turns a bunch of lines into a picture
	 * @param configuration the original config that contained all the figures
	 * @param lines the lines that will be converted
	 * @param WithZBuf a bool that represent whether there must be zbuffering or not
	 */
	static EasyImage LinesToImg(const ini::Configuration &configuration,Lines2D& lines,bool WithZBuf=false);

	/**
	 * \brief this function draws a z-buffered line on an image
	 * @param ZBuf the zbuffer that this function will use to store the z-values
	 * @param img the image that you are drawing on
	 * @param x0,y0,x1,y1 the points on the image that represent the line
	 * @param color the color that the line willbe drawn in
	 */
	static void draw_zbuf_line(ZBuffer & ZBuf, img::EasyImage & img, unsigned int x0, unsigned int y0,double z0,
				unsigned int x1, unsigned int y1,double z1,const img::Color &color);

	/**
	 * \brief a simple funtion that calculates the z-value
	 * @param za,zb the z-value of the two original points of the line
	 * @param i the amount of points that have been drawn
	 * @param a the amount of points that will be drawn in total
	 */
	static double calculateZFactor(double za,double zb,double i,double a);

	/**
	 * \brief this function takes a bunch of figrues that have been triangulated and turns them into an iamge
	 * @param configuration the original configuration
	 * @param figures the figure that will be drawn
	 * @param WithZBuff a bool that represents whether there shoold be zbuffering or not
	 * @param Lights pointer to lights that will be used for the drawing
	 */
	static EasyImage TrianglesToImg(const ini::Configuration &configuration,std::vector<figure3D>& figures,bool WithZBuf,std::vector<Light*>& Lights);

	/**
	 * \brief this function draws a single zbuffered triangle
	 * @param buf the zbuffer that will be used
	 * @param image the image where the triangle will be drawn
	 * @param A,B,C the  points of the triangle
	 * @param d the distance between the eye and the triangle
	 * @param dx the distance between outer x values
	 * @param dy the distance between i-outer y values
	 * @param ambientreflection the ambient reflection
	 * @param diffusereflection the diffuse reflection
	 * @param speculardeflection the specular reflection
	 * @param reflectionCoef the reflectioncoeficient
	 * @param lights pointers to all the lights
	 * @param configuration the original config
	 * @param withShadow a bool that represents whether shadows should be taken into account
	 */
	static void draw_zbuf_triag(ZBuffer& buf, img::EasyImage& image,
			Vector3D const& A, Vector3D const& B, Vector3D const& C,
			double d, double dx, double dy,
			figColor::Color& ambientReflection,
			figColor::Color& diffuseReflection,
			figColor::Color& specularReflection, double reflectionCoeff,
			std::vector<Light*>& lights,
			const ini::Configuration &configuration,
			bool withShadow
			);

private:
	/**
	 * \brief a quick function thats check if a fig consists of triangles
	 */
	static bool isTriangle(figure3D fig);
};
#endif /* IMGUTILS_H_ */
