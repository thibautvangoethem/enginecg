/*
 * ZBuffer.cc
 *
 *  Created on: Mar 25, 2018
 *      Author: thibaut
 */

#include "ZBuffer.h"
#include <iostream>
#include <vector>
#include <limits>

ZBuffer::ZBuffer(int width, int height) {
	std::vector<std::vector<double>> zBuf;
	for(int i=0;i<height;i++){
		std::vector<double> row;
		for(int j=0;j<width;j++){
			row.push_back(std::numeric_limits<double>::infinity());
		}
		zBuf.push_back(row);
	}
	ZBuffer::zBuffer=zBuf;

}

ZBuffer::ZBuffer(){}

ZBuffer::~ZBuffer() {
	// TODO Auto-generated destructor stub
}
