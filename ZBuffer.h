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
	ZBuffer();
	ZBuffer(int width, int height);
	virtual ~ZBuffer();
	std::vector<std::vector<double>> zBuffer;
};


#endif /* ZBUFFER_H_ */
