/*
 * ZBuffer.h
 *
 *  Created on: Mar 25, 2018
 *      Author: thibaut
 */

#ifndef ZBUFFER_H_
#define ZBUFFER_H_
#include <vector>


class ZBuffer {
public:
	std::vector<std::vector<double>> zBuffer;

	/**
	 * \brief default constructor
	 */
	ZBuffer();

	/**
	 * \brief constructor that initializes the zbuffer
	 */
	ZBuffer(int width, int height);

	/**
	 * \brief default desstrucotr
	 */
	virtual ~ZBuffer();

};


#endif /* ZBUFFER_H_ */
