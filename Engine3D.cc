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
	std::vector<figure3D> figures;
	int nrfigures=configuration["general"]["nrFigures"].as_int_or_die();
	for(int figcount=0;figcount<nrfigures;figcount++){
			std::string figureType=configuration["Figure"+figcount]["type"].as_string_or_die();
			figure3D newfig=Engine3D::LineDrawing(configuration,figcount);
			int rotatex=configuration["Figure"+figcount]["rotateX"].as_int_or_die();
			int rotatey=configuration["Figure"+figcount]["rotateY"].as_int_or_die();
			int rotatez=configuration["Figure"+figcount]["rotateZ"].as_int_or_die();
			double scale=configuration["Figure"+figcount]["scale"].as_double_or_die();
			std::vector<int> center=configuration["Figure"+figcount]["center"].as_int_tuple_or_die();
			if(scale!=1){
				if(center[0]!=0||center[1]!=0||center[2]!=0){
					newfig.translate(Vector3D(-center[0],-center[1],-center[2]));
					newfig.scaleFigure(scale);
					newfig.translate(Vector3D(center[0],center[1],center[2]));
				}else{
					newfig.scaleFigure(scale);
				}
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
			figures.push_back(newfig);


		}

}

figure3D Engine3D::LineDrawing(const ini::Configuration &configuration,int figcount){
	std::vector<double> kleur=configuration["figure"+figcount]["color"].as_double_tuple_or_die();
	figure3D newfig=figure3D(figColor::Color(kleur[0],kleur[1],kleur[2]));
	int nrPoints=configuration["figure"+figcount]["nrPoints"].as_int_or_die();
	int nrLines=configuration["figure"+figcount]["nrLines"].as_int_or_die();
	for(int pointcount=0;pointcount<nrPoints;pointcount++){
			std::vector<double> pointcoords=configuration["figure"+figcount]["point"+pointcount].as_double_tuple_or_die();
			newfig.addPoint(Vector3D(pointcoords[0],pointcoords[1],pointcoords[2]));
	}
	for(int linecount=0;linecount<nrLines;linecount++){
		std::vector<int> pointIndex=configuration["figure"+figcount]["line"+linecount].as_int_tuple_or_die();
		newfig.addFace(face3D(pointIndex));
	}
}

figure3D Engine3D::applyTransformation(figure3D &fig, const Matrix &mat){
	for(Vector3D& point:fig.points){
		point=point*mat;
	}
}
