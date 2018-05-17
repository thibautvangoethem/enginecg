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
#include "Light.h"
#include "To2DConverter.h"
#include "Engine3D.h"

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
#include "imgUtils.h"
using namespace img;
typedef std::list<Line2D> Lines2D;

inline int roundToInt(double d)
{
	int x = static_cast<int>(round(d));
	return x;
}

EasyImage imgUtils::LinesToImg(const ini::Configuration &configuration,Lines2D& lines,bool WithZBuf){
	std::vector<double> achtergrond=configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
	double xmax=std::numeric_limits<double>::min();
	double xmin=std::numeric_limits<double>::max();
	double ymax=std::numeric_limits<double>::min();
	double ymin=std::numeric_limits<double>::max();
	To2DConverter::moveToPos(lines,xmin,ymin,xmax,ymax);
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
	for(Line2D &i:lines){
		i.p1.x*=scale;
		i.p1.y*=scale;
		i.p2.x*=scale;
		i.p2.y*=scale;
	}
	for(Line2D i:lines){
//		if(i.getp1().x>imagex||i.getp1().y>imagey||i.getp2().x>imagex||i.getp2().y>imagey||i.getp1().x<0||i.getp1().y<0||i.getp2().x<0||i.getp2().y<0){
//			std::cout<<i.getp1().x<<" "<<i.getp1().y<<" "<<i.getp2().x<<" "<<i.getp2().y<<std::endl;
//		}
		unsigned int dx1=i.p1.x+dx;
		unsigned int dx2=i.p2.x+dx;
		unsigned int dy1=i.p1.y+dy;
		unsigned int dy2=i.p2.y+dy;
//		if(i.getp1().x>imagex||i.getp1().y>imagey||i.getp2().x>imagex||i.getp2().y>imagey||i.getp1().x<0||i.getp1().y<0||i.getp2().x<0||i.getp2().y<0){
//			std::cout<<i.getp1().x<<" "<<i.getp1().y<<" "<<i.getp2().x<<" "<<i.getp2().y<<std::endl;
//		}
		unsigned int x1=roundToInt(dx1);
		unsigned int y1=roundToInt(dy1);
		unsigned int x2=roundToInt(dx2);
		unsigned int y2=roundToInt(dy2);
		if(!WithZBuf){
			image.draw_line(x1,y1,x2,y2,img::Color(i.color.red,i.color.green,i.color.blue));
		}else{
			img::Color col=img::Color(i.getColor().red,i.getColor().green,i.getColor().blue);
			imgUtils::draw_zbuf_line(zbuf,image,x1,y1,i.z1,x2,y2,i.z2,col);
		}

	}
	return image;

}

void imgUtils::draw_zbuf_line(ZBuffer & ZBuf, img::EasyImage & img,unsigned int x0,unsigned int y0,double z0,
				unsigned int x1,unsigned int y1,double z1,const img::Color &color){
	if (x0 == x1)
		{

			//special case for x0 == x1
			for (unsigned int i = std::min(y0, y1); i <= std::max(y0, y1); i++)
			{
				if(y0>y1){
					std::swap(y0,y1);
					std::swap(z0,z1);
				}
				double zfactor=imgUtils::calculateZFactor(z0,z1,i-std::min(y0, y1),(std::max(y0, y1)-std::min(y0, y1)));
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
				double zfactor=imgUtils::calculateZFactor(z0,z1,i-std::min(x0, x1),(std::max(x0, x1)-std::min(x0, x1)));
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
					double zfactor=imgUtils::calculateZFactor(z0,z1,i,x1-x0);
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
					double zfactor=imgUtils::calculateZFactor(z0,z1,i,y1-y0);

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
					double zfactor=imgUtils::calculateZFactor(z0,z1,i,y0-y1);
//					std::cout<<zi<<" "<<ZBuf.zBuffer[round(x0 - (i / m))][y0 - i]<<" "<<round(x0 - (i / m))<<" "<<y0 - i<<" "<<"4"<<std::endl;
					if(zfactor<ZBuf.zBuffer[round(x0 - (i / m))][y0 - i]){
						ZBuf.zBuffer[round(x0 - (i / m))][y0 - i]=zfactor;
						img((unsigned int) round(x0 - (i / m)), y0 - i) = color;
					}
				}
			}
		}
}

double imgUtils::calculateZFactor(double za,double zb,double i,double a){
//	std::cout<<za<<"factor"<<zb<<std::endl;
	double z=((1.0-(i/a))/za)+i/a/zb;
	return z;
}

EasyImage imgUtils::TrianglesToImg(const ini::Configuration &configuration,std::vector<figure3D>& figures,bool WithZBuf,std::vector<Light*>& Lights){
	Lines2D projectedImg=To2DConverter::figuresToLines2D(figures,WithZBuf);
	double size=configuration["General"]["size"].as_double_or_die();
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
	double d=0.95*(imagex/xrange);
	double DCx=d*(xmin+xmax)/2.0;
	double DCy=d*(ymin+ymax)/2.0;
	double dx=(imagex/2.0)-DCx;
	double dy=(imagey/2.0)-DCy;
	std::vector<double> achtergrond=configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
	img::EasyImage image(roundToInt(imagex+1),roundToInt(imagey+1),Color(roundToInt(achtergrond[0]*255),roundToInt(achtergrond[1]*255),roundToInt(achtergrond[2]*255)));
	ZBuffer zbuf;
//	std::cout<<figures.size()<<std::endl;
	if(WithZBuf){
		zbuf=ZBuffer(roundToInt(imagey),roundToInt(imagex));
	}
	bool withShadow=false;
	bool shadowExists=configuration["General"]["shadowEnabled"].as_bool_if_exists(withShadow);
	if(shadowExists&&withShadow){
		for(unsigned int i=0;i<Lights.size();i++){
			if(Lights[i]->getSourceVector().is_point()){
				Lights[i]->MakeShadowMask(figures);
			}
		}
	}
	for(figure3D driehoek:figures){
//		std::cout<<driehoek.points.size()<<" "<<driehoek.faces.size()<<std::endl;
		if(imgUtils::isTriangle(driehoek)){
			std::vector<Vector3D> points=driehoek.points;
			for(face3D driehoekFace:driehoek.faces){
				std::vector<int> index=driehoekFace.pointsIndex;
				imgUtils::draw_zbuf_triag(zbuf,image,points[index[0]],points[index[1]],points[index[2]],d,dx,dy,
						driehoek.ambientReflection,driehoek.difusseReflection,driehoek.specularReflection,driehoek.reflectionCoefficient,Lights,
						configuration, withShadow);
			}
		}
	}
	return image;
}

void imgUtils::draw_zbuf_triag(ZBuffer& buf, img::EasyImage& image,
		Vector3D const& A, Vector3D const& B, Vector3D const& C,
		double d, double dx, double dy,
		figColor::Color& ambientReflection,
		figColor::Color& diffuseReflection,
		figColor::Color& specularReflection, double reflectionCoeff,
		std::vector<Light*>& lights,
		const ini::Configuration &configuration,
		bool withShadow){

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
	Vector3D n=Vector3D::vector(w1,w2,w3);
	n.normalise();
	double k=w1*A.x+w2*A.y+w3*A.z;
	if(k!=0){

		//bereken kleuren die op heel het vlak werken
			double redd=0;
			double greend=0;
			double blued=0;
			for(auto i:lights){
				redd+=i->ambientLight.red*ambientReflection.red;
				greend+=i->ambientLight.green*ambientReflection.green;
				blued+=i->ambientLight.blue*ambientReflection.blue;
				if(i->diffuseLight!=figColor::Color(0,0,0)){
					Vector3D ld=i->getSourceVector();
					if(ld.is_vector()){
						Vector3D l=-ld;
						l.normalise();
						double cosAlpha=n.dot(l);
						if(cosAlpha>0){
							redd+=i->diffuseLight.red*diffuseReflection.red*cosAlpha;
							greend+=i->diffuseLight.green*diffuseReflection.green*cosAlpha;
							blued+=i->diffuseLight.blue*diffuseReflection.blue*cosAlpha;
						}
					}
				}
			}

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

			double xl=round(std::min(xlab,std::min(xlac,xlbc))+0.5);
			double xr=round(std::max(xrab,std::max(xrac,xrbc))-0.5);
			xl=(xl>buf.zBuffer.size())?buf.zBuffer.size():xl;
			xr=(xr<0)?0:xr;
//			std::cout<<xl<<" "<<xr<<std::endl;
			for(unsigned int pix=xl;pix<=xr;pix++){
				double redp=redd;
				double greenp=greend;
				double bluep=blued;
				double z=(1/zg)+(pix-xg)*dzdx+(i-yg)*dzdy;
				Vector3D point=Vector3D::point(((pix-dx)*-(1/z))/d,((i-dy)*-(1/z))/d,1/z);
				std::vector<double> eyeCoords=configuration["General"]["eye"].as_double_tuple_or_die();
				Vector3D eyeVector=Vector3D::vector(eyeCoords[0],eyeCoords[1],eyeCoords[2]);
				Matrix eyeMatrix=Engine3D::eyePointTrans(eyeVector);
				eyeMatrix=eyeMatrix.inv(eyeMatrix);
				Vector3D shadowPoint=point*eyeMatrix;
				if(buf.zBuffer.size()>pix&&buf.zBuffer[pix].size()>i&&buf.zBuffer[pix][i]>z){
					buf.zBuffer[pix][i]=z;
					for(auto light:lights){
						if(!withShadow){
							Vector3D ld=light->getSourceVector();

							Vector3D l=(ld.is_point())?ld-point:-ld;
							l.normalise();
							double cosAlpha=n.dot(l);
			//				std::cout<<cosAlpha<<std::endl;
							if(cosAlpha>0&&ld.is_point()){
								redp+=light->diffuseLight.red*diffuseReflection.red*cosAlpha;
								greenp+=light->diffuseLight.green*diffuseReflection.green*cosAlpha;
								bluep+=light->diffuseLight.blue*diffuseReflection.blue*cosAlpha;
							}
							Vector3D r=(2*cosAlpha*n)-l;
							r.normalise();
							Vector3D toEye=-point;
							toEye.normalise();
							double cosBeta=r.dot(toEye);
							if(cosBeta>=0){
								redp+= light->specularLight.red*specularReflection.red*pow(cosBeta,reflectionCoeff);
								greenp+= light->specularLight.green*specularReflection.green*pow(cosBeta,reflectionCoeff);
								bluep+= light->specularLight.blue*specularReflection.blue*pow(cosBeta,reflectionCoeff);
							}
						}else{
							Vector3D ld=light->getSourceVector();
							bool isShadow=false;
							if(ld.is_point()){
								Vector3D lightpoint=point*light->eye;
								int xl=light->d*lightpoint.x/(-lightpoint.z);
								int yl=light->d*lightpoint.y/(-lightpoint.z);
								double za=light->shadowmask.zBuffer[int(floor(xl))][int(floor(yl))];
								double zb=light->shadowmask.zBuffer[int(ceil(xl))][int(floor(yl))];
								double zc=light->shadowmask.zBuffer[int(floor(xl))][int(ceil(yl))];
								double zd=light->shadowmask.zBuffer[int(ceil(xl))][int(ceil(yl))];
								double ax=xl-int(floor(xl));
								double ay=ay-int(floor(ay));
								double ze=(1-ax)*za+ax*zb;
								double zf=(1-ax)*zc+ax*zd;
								double depth=(1-ay)*ze+ay*zf;
								if(za==depth){
									isShadow=true;
								}

							}
							if(!isShadow){
								Vector3D l=(ld.is_point())?ld-point:-ld;
								l.normalise();
								double cosAlpha=n.dot(l);
				//				std::cout<<cosAlpha<<std::endl;
								if(cosAlpha>0&&ld.is_point()){
									redp+=light->diffuseLight.red*diffuseReflection.red*cosAlpha;
									greenp+=light->diffuseLight.green*diffuseReflection.green*cosAlpha;
									bluep+=light->diffuseLight.blue*diffuseReflection.blue*cosAlpha;
								}
								Vector3D r=(2*cosAlpha*n)-l;
								r.normalise();
								Vector3D toEye=-point;
								toEye.normalise();
								double cosBeta=r.dot(toEye);
								if(cosBeta>=0){
									redp+= light->specularLight.red*specularReflection.red*pow(cosBeta,reflectionCoeff);
									greenp+= light->specularLight.green*specularReflection.green*pow(cosBeta,reflectionCoeff);
									bluep+= light->specularLight.blue*specularReflection.blue*pow(cosBeta,reflectionCoeff);
								}
							}
						}
					}
					if(redp>1){
						redp=1;
					}
					if(greenp>1){
						greenp=1;
					}
					if(bluep>1){
						bluep=1;
					}
					int red=roundToInt(redp*255);
					int green=roundToInt(greenp*255);
					int blue=roundToInt(bluep*255);
					image(pix, i) = Color(red,green,blue);
				}
			}
		}
	}

}

bool imgUtils::isTriangle(figure3D fig){
	for(auto i:fig.faces){
		if(i.pointsIndex.size()!=3){
			return false;
		}
	}
	return true;
}

