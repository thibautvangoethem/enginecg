/*
 * simpleGenerations.h
 *
 *  Created on: Mar 1, 2018
 *      Author: thibaut
 *  A class that is used to create some very simple 2d drawing sand convert those to an image
 */
#include "easy_image.h"
#include "ini_configuration.h"

using namespace img;

#ifndef SIMPLEGENERATIONS_H_
#define SIMPLEGENERATIONS_H_

class simpleGenerations {
public:
	simpleGenerations();
	virtual ~simpleGenerations();
	EasyImage generate_QuarterCircle(const ini::Configuration &configuration);
	EasyImage generate_Eye(const ini::Configuration &configuration);
	EasyImage generate_Diamond(const ini::Configuration &configuration);
	EasyImage generate_ColorDambord(const ini::Configuration &configuration);
	EasyImage generate_ColorRectangle(const ini::Configuration &configuration);
};

#endif /* SIMPLEGENERATIONS_H_ */
