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

		}

}

figure3D Engine3D::LineDrawing(const ini::Configuration &configuration,int figcount){

}

figure3D Engine3D::applyTransformation(figure3D &fig, const Matrix &mat){
	for(Vector3D& point:fig.points){
		point=point*mat;
	}
}
