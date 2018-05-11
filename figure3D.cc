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

void figure3D::scaleFigure(double scaleFactor){
	Matrix scaleM;
	scaleM(1,1)=scaleFactor;
	scaleM(2,2)=scaleFactor;
	scaleM(3,3)=scaleFactor;
	for(Vector3D& vec:points){
		vec=vec*scaleM;
	}
}

void figure3D::rotateX(double angle,bool isradian){
	Matrix rotx;
	double radAngle =(isradian)?angle:figure3D::toRadian(angle);
	rotx(2,2)=cos(radAngle);
	rotx(2,3)=sin(radAngle);
	rotx(3,2)=-sin(radAngle);
	rotx(3,3)=cos(radAngle);
	for(Vector3D& vec:points){
			vec=vec*rotx;
		}
}

void figure3D::rotateY(double angle,bool isradian){
	Matrix roty;
	double radAngle =(isradian)?angle:figure3D::toRadian(angle);
	roty(1,1)=cos(radAngle);
	roty(1,3)=-sin(radAngle);
	roty(3,1)=sin(radAngle);
	roty(3,3)=cos(radAngle);
	for(Vector3D& vec:points){
			vec=vec*roty;
		}
}

void figure3D::rotateZ(const double angle,bool isradian){
	Matrix roty;
	double radAngle =(isradian)?angle:figure3D::toRadian(angle);
	roty(1,1)=cos(radAngle);
	roty(2,1)=-sin(radAngle);
	roty(1,2)=sin(radAngle);
	roty(2,2)=cos(radAngle);
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

double figure3D::toRadian(double angle){
	return angle/180.0*M_PI;
}

void figure3D::triangulate(){
	std::vector<face3D> nieuwfaces;
	for(auto face:faces){
		for(unsigned int i=1;i<face.pointsIndex.size()-1;i++){
			std::vector<int> nieuwPunten={face.pointsIndex[0],face.pointsIndex[i],face.pointsIndex[i+1]};
			nieuwfaces.push_back(face3D(nieuwPunten));
		}
	}
	faces=nieuwfaces;
}
