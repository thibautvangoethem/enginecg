/*
 * 3DEngine.cc
 *
 *  Created on: Mar 1, 2018
 *      Author: thibaut
 *  A class to render 3D images
 *  Not yet finished
 */

#include "Engine3D.h"
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

Engine3D::~Engine3D() {
	// TODO Auto-generated destructor stub
}

Lines2D Engine3D::draw3D(const ini::Configuration &configuration){
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
				newfig.rotateX(rotatex/180*M_PI);
			}
			if(rotatey!=0){
				newfig.rotateY(rotatex/180*M_PI);
			}
			if(rotatez!=0){
				newfig.rotateZ(rotatex/180*M_PI);
			}
			Vector3D transVector=Vector3D::vector(center[0],center[1],center[2]);
			newfig.translate(transVector);
			figures.push_back(newfig);
		}
}

figure3D Engine3D::LineDrawing(const ini::Configuration &configuration,int figcount){
	std::string figure="Figure"+std::to_string(figcount);
	std::vector<double> kleur=configuration[figure]["color"].as_double_tuple_or_die();
	figure3D newfig=figure3D(figColor::Color(kleur[0],kleur[1],kleur[2]));
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
