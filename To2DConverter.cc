/*
 * To2DConverter.cc
 *
 *  Created on: May 17, 2018
 *      Author: thibaut
 */

#include "easy_image.h"
#include "Color.h"
#include "ini_configuration.h"
#include "Color.h"
#include "Point2D.h"
#include "Line2D.h"
#include "Line2D.h"
#include "l_parser.h"
#include "vector3d.h"
#include "figure3D.h"
#include "simpleGenerations.h"
#include "ZBuffer.h"
#include "Light.h"

#include <tgmath.h>
#include <cstdlib>
#include <random>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>
#include <list>
#include <utility>
#include <limits>

#include "To2DConverter.h"

inline int roundToInt(double d)
{
	int x = static_cast<int>(round(d));
	return x;
}
void To2DConverter::moveToPos(Lines2D& lines,double& xmin,double& ymin,double& xmax,double& ymax){

	for(Line2D i:lines){
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
	if(xmin<0||ymin<0){
		Lines2D nieuwLines;
		if(xmin<0&&ymin>=0){
			for(Line2D& line:lines){
				double tempx1=line.p1.x-xmin;
				double tempx2=line.p2.x-xmin;
				line.setp1(tempx1,line.p1.y);
				line.setp2(tempx2,line.p2.y);
				continue;
						}
			xmax-=xmin;
			xmin=0.0;
		}else if(ymin<0&&xmin>=0){
			for(Line2D& line:lines){
				double tempy1=line.p1.y-ymin;
				double tempy2=line.p2.y-ymin;
				line.setp1(line.p1.x,tempy1);
				line.setp2(line.p2.x,tempy2);
				continue;
			}
			ymax-=ymin;
			ymin=0.0;
		}else if(ymin<0&&xmin<0){
			for(Line2D& line:lines){
				double tempy1=line.p1.y-ymin;
				double tempy2=line.p2.y-ymin;
				double tempx1=line.p1.x-xmin;
				double tempx2=line.p2.x-xmin;
				line.setp1(tempx1,tempy1);
				line.setp2(tempx2,tempy2);
				continue;
			}
			xmax-=xmin;
			ymax-=ymin;
			ymin=0.0;
			xmin=0.0;
		}

	}
}


Lines2D To2DConverter::figuresToLines2D(std::vector<figure3D> &figures,bool WithZBuffer){
	Lines2D lines;
	for(figure3D fig:figures){
		std::vector<Point2D> projectedPoints;
		std::vector<double> ZBufferVec;
		for(Vector3D vec:fig.points){
			projectedPoints.push_back(To2DConverter::projectPoint(vec,1));
			if(WithZBuffer){
				ZBufferVec.push_back(vec.z);
			}
		}

		for(face3D face:fig.faces){
			for(unsigned int i=0;i<face.pointsIndex.size();i++){
				if(WithZBuffer){
					if(i==face.pointsIndex.size()-1){
						lines.push_back(Line2D(projectedPoints[face.pointsIndex[i]],projectedPoints[face.pointsIndex[0]],
						figColor::Color(roundToInt(fig.ambientReflection.red*255),roundToInt(fig.ambientReflection.green*255),roundToInt(fig.ambientReflection.blue*255))
						,ZBufferVec[face.pointsIndex[i]],ZBufferVec[face.pointsIndex[0]]));
					}else{
						lines.push_back(Line2D(projectedPoints[face.pointsIndex[i]],projectedPoints[face.pointsIndex[i+1]],
						figColor::Color(roundToInt(fig.ambientReflection.red*255),roundToInt(fig.ambientReflection.green*255),roundToInt(fig.ambientReflection.blue*255)),
						ZBufferVec[face.pointsIndex[i]],ZBufferVec[face.pointsIndex[i+1]]));
					}

				}else{
					if(i==face.pointsIndex.size()-1){
						lines.push_back(Line2D(projectedPoints[face.pointsIndex[i]],projectedPoints[face.pointsIndex[0]],
						figColor::Color(roundToInt(fig.ambientReflection.red*255),roundToInt(fig.ambientReflection.green*255),roundToInt(fig.ambientReflection.blue*255))));
					}else{
						lines.push_back(Line2D(projectedPoints[face.pointsIndex[i]],projectedPoints[face.pointsIndex[i+1]],
						figColor::Color(roundToInt(fig.ambientReflection.red*255),roundToInt(fig.ambientReflection.green*255),roundToInt(fig.ambientReflection.blue*255))));
					}
				}
			}
		}
	}
	return lines;
}


Point2D To2DConverter::projectPoint(const Vector3D &point,const double d){
	double x;
	double y;
	if(point.z==0){
		x= d*point.x/-1.0;
		y= d*point.y/-1.0;
	}else{
		x= d*point.x/-point.z;
		y= d*point.y/-point.z;
	}
	return Point2D(x,y);

}

