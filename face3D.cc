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


face3D::face3D() {
	// TODO Auto-generated constructor stub

}

face3D::~face3D() {
	// TODO Auto-generated destructor stub
}
void face3D::addPoint(int p){ // @suppress("Member declaration not found")
	pointsIndex.push_back(p);


}