/*
 * 3DEngine.cc
 *
 *  Created on: Mar 1, 2018
 *      Author: thibaut
 *  A class to render 3D images
 *  Not yet finished
 */

#include "Engine3D.h"
#include "imgUtils.h"
#include "figure3D.h"
#include "face3D.h"
#include "Color.h"
#include "vector3d.h"
#include "ini_configuration.h"
#include <string>
#include <vector>
#include <list>
#include <cmath>
#include <vector>
#include "Line2D.h"

typedef std::list<Line2D> Lines2D;
inline int roundToInt(double d)
{
	return static_cast<int>(round(d));
}

Engine3D::~Engine3D() {
	// TODO Auto-generated destructor stub
}

std::vector<figure3D> Engine3D::draw3D(const ini::Configuration &configuration){
	std::cout<<"Starting initializing 3D image"<<std::endl;
	std::vector<figure3D> figures;
	int nrfigures=configuration["General"]["nrFigures"].as_int_or_die();
	std::cout<<"Start reading figures"<<std::endl;
	for(int figcount=0;figcount<nrfigures;figcount++){
			std::string figure="Figure"+std::to_string(figcount);
			std::string figureType=configuration[figure]["type"].as_string_or_die();
			figure3D newfig=Engine3D::LineDrawing(configuration,figcount);
			int rotatex=configuration[figure]["rotateX"].as_int_or_die();
			int rotatey=configuration[figure]["rotateY"].as_int_or_die();
			int rotatez=configuration[figure]["rotateZ"].as_int_or_die();
			double scale=configuration[figure]["scale"].as_double_or_die();
			std::vector<double> center=configuration[figure]["center"].as_double_tuple_or_die();

			if(scale!=1){
				newfig.scaleFigure(scale);
			}
			if(rotatex!=0){
				newfig.rotateX(rotatex);
			}
			if(rotatey!=0){
				newfig.rotateY(rotatey);
			}
			if(rotatez!=0){
				newfig.rotateZ(rotatez);
			}
			Vector3D transVector=Vector3D::vector(center[0],center[1],center[2]);
			newfig.translate(transVector);
			figures.push_back(newfig);
		}
	std::cout<<"starting eye-transformation"<<std::endl;
	std::vector<double> eyeCoords=configuration["General"]["eye"].as_double_tuple_or_die();
	Vector3D eyeVector=Vector3D::vector(eyeCoords[0],eyeCoords[1],eyeCoords[2]);
	Matrix eyeMatrix=Engine3D::eyePointTrans(eyeVector);
	Engine3D::applyAllTransformation(figures ,eyeMatrix );
	return figures;

}

figure3D Engine3D::LineDrawing(const ini::Configuration &configuration,int figcount){
	std::string figure="Figure"+std::to_string(figcount);
	std::vector<double> kleur=configuration[figure]["color"].as_double_tuple_or_die();
	figure3D newfig=figure3D(figColor::Color(roundToInt(255*kleur[0]),roundToInt(255*kleur[1]),roundToInt(255*kleur[2])));
	int nrPoints=configuration[figure]["nrPoints"].as_int_or_die();
	int nrLines=configuration[figure]["nrLines"].as_int_or_die();
	for(int pointcount=0;pointcount<nrPoints;pointcount++){
			std::vector<double> pointcoords=configuration[figure]["point"+std::to_string(pointcount)].as_double_tuple_or_die();
			newfig.addPoint(Vector3D::point(pointcoords[0],pointcoords[1],pointcoords[2]));
	}
	for(int linecount=0;linecount<nrLines;linecount++){

		std::vector<int> pointIndex=configuration[figure]["line"+std::to_string(linecount)].as_int_tuple_or_die();
		newfig.addFace(face3D(pointIndex));
	}
	return newfig;
}

void Engine3D::applyTransformation(figure3D &fig, const Matrix &mat){
	for(Vector3D& point:fig.points){
		point=point*mat;
	}
}

void Engine3D::applyAllTransformation(std::vector<figure3D> &figs, const Matrix &mat){
	for(figure3D &fig:figs){
		Engine3D::applyTransformation(fig ,mat );
	}
}

double Engine3D::toRadian(double angle){
	return angle/180*M_PI;
}

Matrix Engine3D::eyePointTrans(const Vector3D &eyepoint){
	double r=pow(pow(eyepoint.x,2)+pow(eyepoint.y,2)+pow(eyepoint.z,2),0.5);
	double theta=std::atan2(eyepoint.y,eyepoint.x);
	double phi=std::acos(eyepoint.z/r);
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
