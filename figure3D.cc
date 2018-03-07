/*
 * figure3D.cc
 *
 *  Created on: Feb 27, 2018
 *      Author: thibaut
 */

#include "figure3D.h"
#include "face3D.h"
#include "Color.h"
#include "vector3d.h"
#include <cmath>
#include <iostream>
void figure3D::addFace(face3D face){ // @suppress("Member declaration not found")
	faces.push_back(face);
}

void figure3D::addPoint(Vector3D v){
	points.push_back(v);
}

void figure3D::scaleFigure(const double scaleFactor){
	Matrix scaleM;
	scaleM(1,1)=scaleFactor;
	scaleM(2,2)=scaleFactor;
	scaleM(3,3)=scaleFactor;
	for(Vector3D& vec:points){
		vec=vec*scaleM;
	}
}

void figure3D::rotateX(const double angle){
	Matrix rotx;
	rotx(2,2)=cos(angle);
	rotx(2,3)=sin(angle);
	rotx(3,2)=-sin(angle);
	rotx(3,3)=cos(angle);
	for(Vector3D& vec:points){
			vec=vec*rotx;
		}
}

void figure3D::rotateY(const double angle){
	Matrix roty;
	roty(1,1)=cos(angle);
	roty(1,3)=-sin(angle);
	roty(3,1)=sin(angle);
	roty(3,3)=cos(angle);
	for(Vector3D& vec:points){
			vec=vec*roty;
		}
}

void figure3D::rotateZ(const double angle){
	Matrix roty;
	roty(1,1)=cos(angle);
	roty(2,1)=-sin(angle);
	roty(1,2)=sin(angle);
	roty(2,2)=cos(angle);
	for(Vector3D& vec:points){
			vec=vec*roty;
		}
}

void figure3D::translate(const Vector3D vec){
	Matrix translate;
	translate(4,1)=vec.x;
	translate(4,2)=vec.y;
	translate(4,3)=vec.z;
	for(Vector3D& point:points){
			point=point*translate;
		}
}


