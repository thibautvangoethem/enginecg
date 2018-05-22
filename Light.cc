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
#include "To2DConverter.h"


#include <iostream>
#include <cmath>
#include <math.h>
#include <limits>
#include <list>

typedef std::list<Line2D> Lines2D;



inline int roundToInt(double d)
{
	int x = static_cast<int>(round(d));
	return x;
}
Vector3D Light::getSourceVector(){
	return Vector3D::point(0,0,0);
}

Vector3D InfLight::getSourceVector(){
	return InfLight::ldVector;
}

Vector3D PointLight::getSourceVector(){
	return PointLight::location;
}

void Light::setSourceVector(Vector3D vec){
	vec.x+=1;
}

void InfLight::setSourceVector(Vector3D vec){
	ldVector=vec;
}

void PointLight::setSourceVector(Vector3D vec){
	location=vec;
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
			b=b*eye;
		}
	}
	Lines2D projectedImg=To2DConverter::figuresToLines2D(newfigures,true);
	double size=shadowmask.zBuffer.size();
	double xmax=std::numeric_limits<double>::min();
	double xmin=std::numeric_limits<double>::max();
	double ymax=std::numeric_limits<double>::min();
	double ymin=std::numeric_limits<double>::max();
	To2DConverter::moveToPos(projectedImg,xmin,ymin,xmax,ymax);
	double xrange=std::abs(xmax-xmin);
	double yrange=std::abs(ymax-ymin);
	double imagex=size*(xrange/std::max(xrange,yrange));
	double imagey=size*(yrange/std::max(xrange,yrange));
	shadowmask=ZBuffer(imagex,imagey);
	d=0.95*(imagex/xrange);
	double DCx=d*(xmin+xmax)/2.0;
	double DCy=d*(ymin+ymax)/2.0;
	dx=(imagex/2.0)-DCx;
	dy=(imagey/2.0)-DCy;
	for(figure3D driehoek:figures){
//		std::cout<<driehoek.points.size()<<" "<<driehoek.faces.size()<<std::endl;
		std::vector<Vector3D> points=driehoek.points;
		for(face3D driehoekFace:driehoek.faces){
			std::vector<int> index=driehoekFace.pointsIndex;
			this->ShadowMaskTriangle(points[index[0]],points[index[1]],points[index[2]]);
		}
	}
}

void Light::ShadowMaskTriangle(Vector3D const& A, Vector3D const& B, Vector3D const& C){
	Point2D A2=Point2D((d*A.x/(-A.z))+dx,(d*A.y/(-A.z))+dy);
		Point2D B2=Point2D((d*B.x/(-B.z))+dx,(d*B.y/(-B.z))+dy);
		Point2D C2=Point2D((d*C.x/(-C.z))+dx,(d*C.y/(-C.z))+dy);
		double xg=(A2.x+B2.x+C2.x)/3.0;
		double yg=(A2.y+B2.y+C2.y)/3.0;
		double zg=(A.z+B.z+C.z)/3.0;
		Vector3D u=B-A;
		Vector3D v=C-A;
		double w1=(u.y*v.z)-(u.z*v.y);
		double w2=(u.z*v.x)-(u.x*v.z);
		double w3=(u.x*v.y)-(u.y*v.x);
		double k=w1*A.x+w2*A.y+w3*A.z;
		if(k!=0){
			double dzdx=w1/((-d)*k);
			double dzdy=w2/((-d)*k);
			for(double i=roundToInt(std::min(A2.y,std::min(B2.y,C2.y))+0.5);i<=roundToInt(std::max(A2.y,std::max(B2.y,C2.y))-0.5);i++){
				double xrab=std::numeric_limits<double>::min();
				double xrac=std::numeric_limits<double>::min();
				double xrbc=std::numeric_limits<double>::min();
				double xlab=std::numeric_limits<double>::max();
				double xlac=std::numeric_limits<double>::max();
				double xlbc=std::numeric_limits<double>::max();
				//A=P B=Q
				if((i-A2.y)*(i-B2.y)<=0){
					if(A2.y!=B2.y){
						xrab=B2.x+(A2.x-B2.x)*((i-B2.y)/(A2.y-B2.y));
						xlab=xrab;
					}
				}
	//			A=P C=Q
				if((i-A2.y)*(i-C2.y)<=0){
					if(A2.y!=C2.y){
						xrac=C2.x+(A2.x-C2.x)*((i-C2.y)/(A2.y-C2.y));
						xlac=xrac;
					}
				}
				//B=P C=Q
				if((i-B2.y)*(i-C2.y)<=0){
					if(B2.y!=C2.y){
						xrbc=C2.x+(B2.x-C2.x)*((i-C2.y)/(B2.y-C2.y));
						xlbc=xrbc;
					}
				}

				double xl=round(std::min(xlab,std::min(xlac,xlbc)));
				double xr=round(std::max(xrab,std::max(xrac,xrbc)));
				xl=(xl>shadowmask.zBuffer.size())?shadowmask.zBuffer.size():xl;
				xr=(xr<0)?0:xr;
//				std::cout<<xl<<" "<<xr<<std::endl;
				for(unsigned int pix=xl;pix<=xr;pix++){
					double z=(1/zg)+(pix-xg)*dzdx+(i-yg)*dzdy;
					if(shadowmask.zBuffer.size()>pix&&shadowmask.zBuffer[pix].size()>i&&shadowmask.zBuffer[pix][i]>z){
						shadowmask.zBuffer[pix][i]=z;
//						std::cout<<pix<<" "<<i<<std::endl;
					}
				}
			}
		}

	}
