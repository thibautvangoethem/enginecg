/*
 * simpleGenerations.h
 *
 *  Created on: Mar 1, 2018
 *      Author: thibaut
<<<<<<< HEAD
 *  A class that is used to create some very simple 2d drawing sand convert those to an image
=======
>>>>>>> 26da4b895d9671d3b3bcd107ab97715703238eca
 */
#include "easy_image.h"
#include "ini_configuration.h"

using namespace img;

#ifndef SIMPLEGENERATIONS_H_
#define SIMPLEGENERATIONS_H_

<<<<<<< HEAD
=======
namespace std {

>>>>>>> 26da4b895d9671d3b3bcd107ab97715703238eca
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

<<<<<<< HEAD
=======
} /* namespace std */

>>>>>>> 26da4b895d9671d3b3bcd107ab97715703238eca
#endif /* SIMPLEGENERATIONS_H_ */
