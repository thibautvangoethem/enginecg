/*
 * imgUtils.cpp
 *
 *  Created on: Mar 1, 2018
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

EasyImage imgUtils::LinesToImg(const ini::Configuration &configuration,Lines2D& lines,bool WithZBuf){
	std::vector<double> achtergrond=configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
	std::cout<<"start scaling lines"<<std::endl;
	double xmax=std::numeric_limits<double>::min();
	double xmin=std::numeric_limits<double>::max();
	double ymax=std::numeric_limits<double>::min();
	double ymin=std::numeric_limits<double>::max();
	double Zmin=std::numeric_limits<double>::max();
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
//		if(WithZBuf){
//			if(i.z1<Zmin){
//				Zmin=i.z1;
//			}
//			if(i.z2<Zmin){
//				Zmin=i.z2;
//			}
//		}

	}
//	if(WithZBuf){
//		if(Zmin<0){
//			for(Line2D& line:lines){
//				line.z1+=Zmin;
//				line.z2+=Zmin;
//			}
//		}
//	}
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
			ymin=0.0;
			xmin=0.0;
		}

	}

	double imagex;
	double imagey;
	double size=configuration["General"]["size"].as_double_or_die();
	if(xmax>ymax){
		imagex=size*((xmax-xmin)/xmax);
		imagey=size*((ymax-ymin)/xmax);
	}else{
		imagex=size*((xmax-xmin)/ymax);
		imagey=size*((ymax-ymin)/ymax);
	}
	ZBuffer zbuf;
	if(WithZBuf){
		zbuf=ZBuffer(roundToInt(imagey),roundToInt(imagex));
	}
	img::EasyImage image(roundToInt(imagex),roundToInt(imagey),Color(roundToInt(achtergrond[0]*255),roundToInt(achtergrond[1]*255),roundToInt(achtergrond[2]*255)));
	double scale=0.95*(imagex/xmax-xmin);
	double xmiddle=scale*(xmin+xmax)/2.0;
	double ymiddle=scale*(ymin+ymax)/2.0;
	double dx= (imagex/2.0)-xmiddle;
	double dy=(imagey/2.0)-ymiddle;
	std::cout<<"converting lines to the image"<<std::endl;
	for(Line2D &i:lines){
		i.p1.x*=scale;
		i.p1.y*=scale;
		i.p2.x*=scale;
		i.p2.y*=scale;
	}
	for(Line2D i:lines){
		unsigned int x1=roundToInt((i.getp1().x)+dx);
		unsigned int y1=roundToInt((i.getp1().y)+dy);
		unsigned int x2=roundToInt((i.getp2().x)+dx);
		unsigned int y2=roundToInt((i.getp2().y)+dy);
		if(!WithZBuf){
			image.draw_line(x1,y1,x2,y2,img::Color(i.color.red,i.color.green,i.color.blue));
		}else{
			if(i.z1>0||i.z2>0){
				std::cout<<x1<<" "<<y1<<" "<<i.z1<<"waarde"<<x2<<" "<<y2<<" "<<i.z2<<std::endl;
			}
			img::Color col=img::Color(i.getColor().red,i.getColor().green,i.getColor().blue);
			imgUtils::draw_zbuf_line(zbuf,image,x1,y1,i.z1,x2,y2,i.z2,col);
		}

	}
	std::cout<<"image created"<<std::endl;
	return image;

}


Lines2D imgUtils::figuresToLines2D(const ini::Configuration &configuration, std::vector<figure3D> &figures,bool WithZBuffer){
//	srand(figures.size());
	std::cout<<"begin converting figures to lines"<<std::endl;
	Lines2D lines;
	for(figure3D fig:figures){
		std::vector<Point2D> projectedPoints;
		std::vector<double> ZBufferVec;
		for(Vector3D vec:fig.points){
			projectedPoints.push_back(imgUtils::projectPoint(vec,1));
			if(WithZBuffer){
				ZBufferVec.push_back(vec.z);
			}
		}

		for(face3D face:fig.faces){
//			double r = (double)rand();
//			double g = (double)rand();
//			double b = (double)rand();
//			fig.color=figColor::Color(r,g,b);
			for(unsigned int i=0;i<face.pointsIndex.size();i++){
				if(WithZBuffer){
					if(i==face.pointsIndex.size()-1){
						lines.push_back(Line2D(projectedPoints[face.pointsIndex[i]],projectedPoints[face.pointsIndex[0]],fig.color,ZBufferVec[face.pointsIndex[i]],ZBufferVec[face.pointsIndex[0]]));
					}else{
						lines.push_back(Line2D(projectedPoints[face.pointsIndex[i]],projectedPoints[face.pointsIndex[i+1]],fig.color,ZBufferVec[face.pointsIndex[i]],ZBufferVec[face.pointsIndex[i+1]]));
					}

				}else{
					if(i==face.pointsIndex.size()-1){
						lines.push_back(Line2D(projectedPoints[face.pointsIndex[i]],projectedPoints[face.pointsIndex[0]],fig.color));
					}else{
						lines.push_back(Line2D(projectedPoints[face.pointsIndex[i]],projectedPoints[face.pointsIndex[i+1]],fig.color));
					}
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

void imgUtils::draw_zbuf_line(ZBuffer & ZBuf, img::EasyImage & img,unsigned int x0,unsigned int y0,double z0,
				unsigned int x1,unsigned int y1,double z1,const img::Color &color){

//	if(z0>0||z1>0){
//		std::cout<<z0<<"waarde"<<z1<<std::endl;
//	}
	if (x0 == x1)
		{

			//special case for x0 == x1
			for (unsigned int i = std::min(y0, y1); i <= std::max(y0, y1); i++)
			{
				if(y0>y1){
					std::swap(y0,y1);
					std::swap(z0,z1);
				}
				double zfactor=imgUtils::calculatePFactor(z0,z1,i-std::min(y0, y1),(std::max(y0, y1)-std::min(y0, y1)));
//				std::cout<<zi<<" "<<ZBuf.zBuffer[x0][i]<<" "<<x0<<" "<<i<<" "<<"0"<<std::endl;
				if(zfactor<ZBuf.zBuffer[x0][i]){
					ZBuf.zBuffer[x0][i]=zfactor;
					img(x0, i) = color;
				}
			}
		}
		else if (y0 == y1)
		{
			if(x0>x1){
				std::swap(x0,x1);
				std::swap(z0,z1);
			}
			//special case for y0 == y1
			for (unsigned int i = std::min(x0, x1); i <= std::max(x0, x1); i++)
			{
				double zfactor=imgUtils::calculatePFactor(z0,z1,i-std::min(x0, x1),(std::max(x0, x1)-std::min(x0, x1)));
//				std::cout<<zi<<" "<<ZBuf.zBuffer[i][y0]<<" "<<i<<" "<<y0<<" "<<"1"<<std::endl;
				if(zfactor<ZBuf.zBuffer[i][y0]){
					ZBuf.zBuffer[i][y0]=zfactor;
					img(i, y0) = color;
				}
			}
		}
		else
		{
			if (x0 > x1)
			{
				//flip points if x1>x0: we want x0 to have the lowest value
				std::swap(x0, x1);
				std::swap(y0, y1);
				std::swap(z0,z1);
			}
			double m = ((double) y1 - (double) y0) / ((double) x1 - (double) x0);
			if (-1.0 <= m && m <= 1.0)
			{
				for (unsigned int i = 0; i <= (x1 - x0); i++)
				{
					double zfactor=imgUtils::calculatePFactor(z0,z1,i,x1-x0);
//					std::cout<<zi<<std::endl;
					if(zfactor<ZBuf.zBuffer[x0+i][round(y0 + m * i)]){
						ZBuf.zBuffer[x0+i][round(y0 + m * i)]=zfactor;
						img(x0 + i, (unsigned int) round(y0 + m * i)) = color;
					}
				}
			}
			else if (m > 1.0)
			{
				for (unsigned int i = 0; i <= (y1 - y0); i++)
				{
					double zfactor=imgUtils::calculatePFactor(z0,z1,i,y1-y0);

					if(zfactor<ZBuf.zBuffer[round(x0 + (i / m))][y0 + i]){
//						std::cout<<zfactor<<" "<<ZBuf.zBuffer[round(x0 + (i / m))][y0 + i]<<" "<<round(x0 + (i / m))<<" "<<y0 + i<<" "<<"3"<<std::endl;
						ZBuf.zBuffer[round(x0 + (i / m))][y0 + i]=zfactor;
						img((unsigned int) round(x0 + (i / m)), y0 + i) = color;
					}
				}
			}
			else if (m < -1.0)
			{
				for (unsigned int i = 0; i <= (y0 - y1); i++)
				{
					double zfactor=imgUtils::calculatePFactor(z0,z1,i,y0-y1);
//					std::cout<<zi<<" "<<ZBuf.zBuffer[round(x0 - (i / m))][y0 - i]<<" "<<round(x0 - (i / m))<<" "<<y0 - i<<" "<<"4"<<std::endl;
					if(zfactor<ZBuf.zBuffer[round(x0 - (i / m))][y0 - i]){
						ZBuf.zBuffer[round(x0 - (i / m))][y0 - i]=zfactor;
						img((unsigned int) round(x0 - (i / m)), y0 - i) = color;
					}
				}
			}
		}
}

double imgUtils::calculatePFactor(double za,double zb,double i,double a){
//	std::cout<<za<<"factor"<<zb<<std::endl;
	double p=((1-(i/a))/za)+i/a/zb;
	return p;
}


