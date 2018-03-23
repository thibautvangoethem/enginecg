/*
 * imgUtils.cpp
 *
 *  Created on: Mar 1, 2018
 *      Author: thibaut
 */
#include "easy_image.h"
#include "ini_configuration.h"
#include "Color.h"
#include "Point2D.h"
#include "Line2D.h"
#include "Line2D.h"
#include "l_parser.h"
#include "vector3d.h"
#include "figure3D.h"
#include "simpleGenerations.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>
#include <list>
#include <utility>
#include <limits>
#include "imgUtils.h"
using namespace img;
typedef std::list<Line2D> Lines2D;
inline int roundToInt(double d)
{
	return static_cast<int>(round(d));
}

imgUtils::imgUtils() {
	// TODO Auto-generated constructor stub

}

imgUtils::~imgUtils() {
	// TODO Auto-generated destructor stub
}

EasyImage imgUtils::LinesToImg(const ini::Configuration &configuration,Lines2D& lines){
	std::vector<double> achtergrond=configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
	std::cout<<"start scaling lines"<<std::endl;
	double xmax=std::numeric_limits<double>::min();
	double xmin=std::numeric_limits<double>::max();
	double ymax=std::numeric_limits<double>::min();
	double ymin=std::numeric_limits<double>::max();
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
			xmin=0;
		}else if(ymin<0&&xmin>=0){
			for(Line2D& line:lines){
				double tempy1=line.p1.y-ymin;
				double tempy2=line.p2.y-ymin;
				line.setp1(line.p1.x,tempy1);
				line.setp2(line.p2.x,tempy2);
				continue;
			}
			ymax-=ymin;
			ymin=0;
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
			ymin=0;
			xmin=0;
		}

	}

	double imagex;
	double imagey;
	int size=configuration["General"]["size"].as_int_or_die();
	if(xmax>ymax){
		imagex=size*((xmax-xmin)/xmax);
		imagey=size*((ymax-ymin)/xmax);
	}else{
		imagex=size*((xmax-xmin)/ymax);
		imagey=size*((ymax-ymin)/ymax);
	}
	img::EasyImage image(roundToInt(imagex),roundToInt(imagey),Color(roundToInt(achtergrond[0]*255),roundToInt(achtergrond[1]*255),roundToInt(achtergrond[2]*255)));
	double scale=0.95*(imagex/xmax-xmin);
	double xmiddle=scale*(xmin+xmax)/2;
	double ymiddle=scale*(ymin+ymax)/2;
	double dx= (imagex/2)-xmiddle;
	double dy=(imagey/2)-ymiddle;
	std::cout<<"converting lines to the image"<<std::endl;
	for(Line2D &i:lines){
		i.p1.x*=scale;
		i.p1.y*=scale;
		i.p2.x*=scale;
		i.p2.y*=scale;
	}
	for(Line2D i:lines){
		int x1=roundToInt((i.getp1().x)+dx);
		int y1=roundToInt((i.getp1().y)+dy);
		int x2=roundToInt((i.getp2().x)+dx);
		int y2=roundToInt((i.getp2().y)+dy);
		i.setp1(x1,y1);
		i.setp2(x2,y2);
		image.draw_line(x1,y1,x2,y2,img::Color(i.color.red,i.color.green,i.color.blue));

	}
	std::cout<<"image created"<<std::endl;
	return image;

}


Lines2D imgUtils::figuresToLines2D(const ini::Configuration &configuration, std::vector<figure3D> &figures){
	std::cout<<"begin converting figures to lines"<<std::endl;
	Lines2D lines;
	for(figure3D fig:figures){
		std::vector<Point2D> projectedPoints;
		for(Vector3D vec:fig.points){
			projectedPoints.push_back(imgUtils::projectPoint(vec,1));
		}
		for(face3D face:fig.faces){
			for(unsigned int i=0;i<face.pointsIndex.size();i++){
				if(i==face.pointsIndex.size()-1){
					lines.push_back(Line2D(projectedPoints[face.pointsIndex[i]],projectedPoints[face.pointsIndex[0]],fig.color));
				}else{
					lines.push_back(Line2D(projectedPoints[face.pointsIndex[i]],projectedPoints[face.pointsIndex[i+1]],fig.color));
				}
			}
		}
	}

	return lines;
}


Point2D imgUtils::projectPoint(const Vector3D &point,const double d){
	double x;
	double y;
	if(point.z==0){
		x= d*point.x/-1;
		y= d*point.y/-1;
	}else{
		x= d*point.x/-point.z;
		y= d*point.y/-point.z;
	}
	return Point2D(x,y);

}

