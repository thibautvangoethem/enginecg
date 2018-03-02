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
#include "imgUtils.h"
using namespace img;
typedef std::list<Line2D> Lines2D;
inline int roundToInt(double d)
{
	return static_cast<int>(round(d));
}
namespace std {

imgUtils::imgUtils() {
	// TODO Auto-generated constructor stub

}

imgUtils::~imgUtils() {
	// TODO Auto-generated destructor stub
}

 /* namespace img */
EasyImage imgUtils::LinesToImg(const ini::Configuration &configuration,Lines2D& lines){
	std::vector<double> achtergrond=configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
	std::cout<<"start scaling lines"<<std::endl;
	double xmax=-999999999;
	double xmin=999999999;
	double ymax=-99999999;
	double ymin=99999999;
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
			for(Line2D line:lines){
				double tempx1=line.p1.x-xmin;
				double tempx2=line.p2.x-xmin;
				line.setp1(tempx1,line.p1.y);
				line.setp2(tempx2,line.p2.y);
				nieuwLines.push_back(line);
				continue;
						}
			roundToInt(xmax-=xmin);
			xmin=0;
		}else if(ymin<0&&xmin>=0){
			for(Line2D line:lines){
				double tempy1=line.p1.y-ymin;
				double tempy2=line.p2.y-ymin;
				line.setp1(line.p1.x,tempy1);
				line.setp2(line.p2.x,tempy2);
				nieuwLines.push_back(line);
				continue;
			}
			roundToInt(ymax-=ymin);
			ymin=0;
		}else if(ymin<0&&xmin<0){
			for(Line2D line:lines){
				double tempy1=line.p1.y-ymin;
				double tempy2=line.p2.y-ymin;
				double tempx1=line.p1.x-xmin;
				double tempx2=line.p2.x-xmin;
				line.setp1(tempx1,tempy1);
				line.setp2(tempx2,tempy2);
				nieuwLines.push_back(line);
				continue;
			}
			roundToInt(xmax-=xmin);
			roundToInt(ymax-=ymin);
			ymin=0;
			xmin=0;
		}
		lines=nieuwLines;
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
	img::EasyImage image(roundToInt(imagex),roundToInt(imagey));
	for(unsigned int i = 1; i < imagex-1; i++)
						{
						for(unsigned int j = 1; j < imagey-1; j++)
							{
							image(i,j).red = roundToInt(achtergrond[0]*255);
							image(i,j).green = roundToInt(achtergrond[1]*255);
							image(i,j).blue = roundToInt(achtergrond[2]*255);
							}
						}
	double scale=0.95*(imagex/xmax-xmin);
	double xmiddle=scale*(xmin+xmax)/2;
	double ymiddle=scale*(ymin+ymax)/2;
	double dx= (imagex/2)-xmiddle;
	double dy=(imagey/2)-ymiddle;
	std::cout<<"converting lines to the image"<<std::endl;
	for(Line2D i:lines){
		int x1=roundToInt((i.getp1().x*scale)+dx);
		int y1=roundToInt((i.getp1().y*scale)+dy);
		int x2=roundToInt((i.getp2().x*scale)+dx);
		int y2=roundToInt((i.getp2().y*scale)+dy);
		i.setp1(x1,y1);
		i.setp2(x2,y2);
		image.draw_line(x1,y1,x2,y2,img::Color(i.color.red,i.color.green,i.color.blue));

	}
	std::cout<<"image created"<<std::endl;
	return image;

}
}
