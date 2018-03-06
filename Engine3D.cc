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
			int nrfigures=configuration["Figure"+figcount][""].as_int_or_die();
		}
}

figure3D Engine3D::LineDrawing(const ini::Configuration &configuration){

}

figure3D Engine3D::applyTransformation(figure3D &fig, const Matrix &mat){
	for(Vector3D& point:fig.points){
		point=point*mat;
	}
}
