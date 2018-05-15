/*
 * Light.cc
 *
 *  Created on: Apr 24, 2018
 *      Author: thibaut
 */

#include "Light.h"
#include "Color.h"
#include "vector3d.h"
#include "figure3D.h"
#include "Line2D.h"


#include <iostream>
#include <cmath>
#include <math.h>
#include <limits>
#include <list>

typedef std::list<Line2D> Lines2D;

Vector3D Light::getSourceVector(){
	return Vector3D::point(0,0,0);
}

Vector3D InfLight::getSourceVector(){
	return InfLight::ldVector;
}

Vector3D PointLight::getSourceVector(){
	return PointLight::location;
}

Matrix Light::eyepointtrans(Vector3D eyepoint){
	double r;
	double theta;
	double phi;
//	Engine3D::Topolar(eyepoint,theta,phi,r);
	r=sqrt(pow(eyepoint.x,2)+pow(eyepoint.y,2)+pow(eyepoint.z,2));
	theta=std::atan2(eyepoint.y,eyepoint.x);
	phi=std::acos(eyepoint.z/r);
	Matrix eyePointMatrix;
	eyePointMatrix(1,1)=-sin(theta);
	eyePointMatrix(2,1)=cos(theta);
	eyePointMatrix(1,2)=-cos(theta)*cos(phi);
	eyePointMatrix(2,2)=-sin(theta)*cos(phi);
	eyePointMatrix(3,2)=sin(phi);
	eyePointMatrix(1,3)=cos(theta)*sin(phi);
	eyePointMatrix(2,3)=sin(theta)*sin(phi);
	eyePointMatrix(3,3)=cos(phi);
	eyePointMatrix(4,3)=-r;
	return eyePointMatrix;
}

void Light::MakeShadowMask(std::vector<figure3D>& figures){
	std::vector<figure3D> newfigures=figures;
	for(figure3D& i:newfigures){
		for(auto& b:i.points){
			b*eye;
		}
	}
	Lines2D projectedImg=imgUtils::figuresToLines2D(figures,true);
	double size=shadowmask.zBuffer.size();
	double xmax=std::numeric_limits<double>::min();
	double xmin=std::numeric_limits<double>::max();
	double ymax=std::numeric_limits<double>::min();
	double ymin=std::numeric_limits<double>::max();
	for(Line2D i:projectedImg){
		if(i.p1.x>xmax){
			xmax=i.p1.x;
		}
		if(i.p1.x<xmin){
			xmin=i.p1.x;
		}
		if(i.p1.y>ymax){
			ymax=i.p1.y;
		}
		if(i.p1.y<ymin){
			ymin=i.p1.y;
		}
		if(i.p2.x>xmax){
			xmax=i.p2.x;
		}
		if(i.p2.x<xmin){
			xmin=i.p2.x;
		}
		if(i.p2.y>ymax){
			ymax=i.p2.y;
		}
		if(i.p2.y<ymin){
			ymin=i.p2.y;
		}
	}
	double xrange=std::abs(xmax-xmin);
	double yrange=std::abs(ymax-ymin);
	double imagex=size*(xrange/std::max(xrange,yrange));
	double imagey=size*(yrange/std::max(xrange,yrange));
	d=0.95*(imagex/xrange);
	double DCx=d*(xmin+xmax)/2.0;
	double DCy=d*(ymin+ymax)/2.0;
	dx=(imagex/2.0)-DCx;
	dy=(imagey/2.0)-DCy;
}

void Light::ShadowMAskTriangle(Vector3D const& A, Vector3D const& B, Vector3D const& C){

}
