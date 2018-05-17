/*
 * face3D.cpp
 *
 *  Created on: Mar 1, 2018
 *      Author: thibaut
 *
 */
#include "face3D.h"

#include <list>
#include <iostream>
#include <vector>
using namespace std;
#include "Point2D.h"


face3D::face3D() {}

face3D::~face3D() {}

void face3D::addPoint(int p){
	pointsIndex.push_back(p);
}
