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
	/**
	 * \brief this function generates a quarter circle
	 * @param configuration the config
	 */
	EasyImage generate_QuarterCircle(const ini::Configuration &configuration);

	/**
	 * \brief this function generates an eye like construct
	 * @param configuration the config
	 */
	EasyImage generate_Eye(const ini::Configuration &configuration);

	/**
	 * \brief this function generates a diamond like construct
	 * @param configuration the config
	 */
	EasyImage generate_Diamond(const ini::Configuration &configuration);

	/**
	 * \brief this function generates a colored chessboard
	 * @param configuration the config
	 */
	EasyImage generate_ColorDambord(const ini::Configuration &configuration);

	/**
	 * \brief this function generates a rectangle
	 * @param configuration the config
	 */
	EasyImage generate_ColorRectangle(const ini::Configuration &configuration);
};

#endif /* SIMPLEGENERATIONS_H_ */
