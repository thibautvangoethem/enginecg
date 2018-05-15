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
#include <math.h>
#include "Line2D.h"
#include "L3DEngine.h"
#include "Fractals3D.h"
#include <algorithm>


typedef std::list<Line2D> Lines2D;
inline int roundToInt(double d)
{
	return static_cast<int>(round(d));
}

Engine3D::~Engine3D() {
	// TODO Auto-generated destructor stub
}

std::vector<figure3D> Engine3D::draw3D(const ini::Configuration &configuration){
	std::vector<figure3D> figures;
	int nrfigures=configuration["General"]["nrFigures"].as_int_or_die();
	for(int figcount=0;figcount<nrfigures;figcount++){
			std::string figure="Figure"+std::to_string(figcount);
			std::string figureType=configuration[figure]["type"].as_string_or_die();
			figure3D newfig=figure3D(figColor::Color(0,0,0));
			std::string type=configuration[figure]["type"].as_string_or_die();

			if(0==type.compare(type.length()-4,4,"Cone")){
				newfig=Engine3D::DrawCone(configuration,figcount);
			}else if(0==type.compare(type.length()-4,4,"Cube")){
				newfig=Engine3D::DrawCube(configuration,figcount);
			}else if(0==type.compare(type.length()-5,5,"Torus")){
				newfig=Engine3D::DrawTorus(configuration,figcount);
			}else if(0==type.compare(type.length()-6,6,"Sphere")){
				int n=configuration[figure]["n"].as_int_or_die();
				newfig=Engine3D::DrawSphere(configuration,figcount,n);
			}else if(0==type.compare(type.length()-8,8,"Cylinder")){
				int n=configuration[figure]["n"].as_int_or_die();
				double height=configuration[figure]["height"].as_double_or_die();
				newfig=Engine3D::DrawCylinder(configuration,figcount,n,height);
			}else if(0==type.compare(type.length()-9,9,"3DLSystem")){
				newfig=L3DEngine::L3D_ToFigure(configuration,figcount);
			}else if(0==type.compare(type.length()-9,9,"BuckyBall")){
				newfig=Engine3D::DrawBuckyBall(configuration,figcount);
			}else if(0==type.compare(type.length()-10,10,"Octahedron")){
				newfig=Engine3D::DrawOctahedron(configuration,figcount);
			}else if(0==type.compare(type.length()-11,11,"Tetrahedron")){
				newfig=Engine3D::DrawTetrahedron(configuration,figcount);
			}else if(0==type.compare(type.length()-11,11,"LineDrawing")){
				newfig=Engine3D::LineDrawing(configuration,figcount);
			}else if(0==type.compare(type.length()-11,11,"Icosahedron")){
				newfig=Engine3D::DrawIcosahedron(configuration,figcount);
			}else if(0==type.compare(type.length()-12,12,"Dodecahedron")){
				newfig=Engine3D::DrawDodecahedron(configuration,figcount);
			}else if(0==type.compare(type.length()-12,12,"MengerSponge")){
				newfig=Engine3D::DrawCube(configuration,figcount);
				int iterations=configuration[figure]["nrIterations"].as_int_or_die();
				Fractals3D::createMengerSponge(newfig,iterations);
			}

			if(0==type.compare(0,7,"Fractal")){
				std::vector<figure3D> fractals;
				int iterations=configuration[figure]["nrIterations"].as_int_or_die();
				double scale=configuration[figure]["fractalScale"].as_double_or_die();
				Fractals3D::generateFractal(newfig,fractals,iterations,scale);
				figures.insert(figures.end(),fractals.begin(),fractals.end());
//				&&0!=type.compare(type.length()-9,9,"BuckyBall")
			}else if(0==type.compare(0,5,"Thick")){
				Engine3D::DrawThickFigure(configuration,figcount,newfig,figures);
			}else{
			int rotatex=configuration[figure]["rotateX"].as_double_or_die();
			int rotatey=configuration[figure]["rotateY"].as_double_or_die();
			int rotatez=configuration[figure]["rotateZ"].as_double_or_die();
			double scale=configuration[figure]["scale"].as_double_or_die();
			std::vector<double> center=configuration[figure]["center"].as_double_tuple_or_die();
//			std::cout<<newfig.faces.size()<<" "<<newfig.points.size()<<std::endl;
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
	}
	std::vector<double> eyeCoords=configuration["General"]["eye"].as_double_tuple_or_die();
	Vector3D eyeVector=Vector3D::vector(eyeCoords[0],eyeCoords[1],eyeCoords[2]);
	Matrix eyeMatrix=Engine3D::eyePointTrans(eyeVector);
	Engine3D::applyAllTransformation(figures ,eyeMatrix );
	return figures;

}

figure3D Engine3D::LineDrawing(const ini::Configuration &configuration,int figcount){
	std::string figure="Figure"+std::to_string(figcount);
	std::vector<double> kleur;
		std::vector<double> kleur2;
		std::vector<double> kleur3;
		bool kleurbool=configuration[figure]["color"].as_double_tuple_if_exists(kleur);
		double ref;
		if(kleurbool){
			kleur=configuration[figure]["color"].as_double_tuple_or_die();
			kleur2={0,0,0};
			kleur3={0,0,0};
			ref=0;
		}else{
			kleur=configuration[figure]["ambientReflection"].as_double_tuple_or_die();
			bool testbool=configuration[figure]["diffuseReflection"].as_double_tuple_if_exists(kleur2);
			if(testbool){
				kleur2=configuration[figure]["diffuseReflection"].as_double_tuple_or_die();
			}else{
				kleur2={0,0,0};
			}
			testbool=configuration[figure]["specularReflection"].as_double_tuple_if_exists(kleur3);
			if(testbool){
				kleur3=configuration[figure]["specularReflection"].as_double_tuple_or_die();
			ref=configuration[figure]["reflectionCoefficient"].as_double_or_die();
			}else{
				kleur3={0,0,0};
				ref=0;
			}
		}
	figure3D newfig=figure3D(
		figColor::Color(kleur[0],kleur[1],kleur[2]),
		figColor::Color(kleur2[0],kleur2[1],kleur2[2]),
		figColor::Color(kleur3[0],kleur3[1],kleur3[2]),ref);
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
figure3D Engine3D::DrawCube(const ini::Configuration &configuration,int figcount){
	std::string figure="Figure"+std::to_string(figcount);
	std::vector<double> kleur;
		std::vector<double> kleur2;
		std::vector<double> kleur3;
		bool kleurbool=configuration[figure]["color"].as_double_tuple_if_exists(kleur);
		double ref;
		if(kleurbool){
			kleur=configuration[figure]["color"].as_double_tuple_or_die();
			kleur2={0,0,0};
			kleur3={0,0,0};
			ref=0;
		}else{
			kleur=configuration[figure]["ambientReflection"].as_double_tuple_or_die();
			bool testbool=configuration[figure]["diffuseReflection"].as_double_tuple_if_exists(kleur2);
			if(testbool){
				kleur2=configuration[figure]["diffuseReflection"].as_double_tuple_or_die();
			}else{
				kleur2={0,0,0};
			}
			testbool=configuration[figure]["specularReflection"].as_double_tuple_if_exists(kleur3);
			if(testbool){
				kleur3=configuration[figure]["specularReflection"].as_double_tuple_or_die();
			ref=configuration[figure]["reflectionCoefficient"].as_double_or_die();
			}else{
				kleur3={0,0,0};
				ref=0;
			}
		}
	figure3D newfig=figure3D(
		figColor::Color(kleur[0],kleur[1],kleur[2]),
		figColor::Color(kleur2[0],kleur2[1],kleur2[2]),
		figColor::Color(kleur3[0],kleur3[1],kleur3[2]),ref);
	newfig.addPoint(Vector3D::point(1,-1,-1));
	newfig.addPoint(Vector3D::point(-1,1,-1));
	newfig.addPoint(Vector3D::point(1,1,1));
	newfig.addPoint(Vector3D::point(-1,-1,1));
	newfig.addPoint(Vector3D::point(1,1,-1));
	newfig.addPoint(Vector3D::point(-1,-1,-1));
	newfig.addPoint(Vector3D::point(1,-1,1));
	newfig.addPoint(Vector3D::point(-1,1,1));
	std::vector<int> v={0,4,2,6};
	newfig.addFace(face3D(v));
	v={4,1,7,2};
	newfig.addFace(face3D(v));
 	v={1,5,3,7};
	newfig.addFace(face3D(v));
	v={5,0,6,3};
	newfig.addFace(face3D(v));
	v={6,2,7,3};
	newfig.addFace(face3D(v));
	v={0,5,1,4};
	newfig.addFace(face3D(v));
	return newfig;
}
figure3D Engine3D::DrawTetrahedron(const ini::Configuration &configuration,int figcount){
	std::string figure="Figure"+std::to_string(figcount);
	std::vector<double> kleur;
		std::vector<double> kleur2;
		std::vector<double> kleur3;
		bool kleurbool=configuration[figure]["color"].as_double_tuple_if_exists(kleur);
		double ref;
		if(kleurbool){
			kleur=configuration[figure]["color"].as_double_tuple_or_die();
			kleur2={0,0,0};
			kleur3={0,0,0};
			ref=0;
		}else{
			kleur=configuration[figure]["ambientReflection"].as_double_tuple_or_die();
			bool testbool=configuration[figure]["diffuseReflection"].as_double_tuple_if_exists(kleur2);
			if(testbool){
				kleur2=configuration[figure]["diffuseReflection"].as_double_tuple_or_die();
			}else{
				kleur2={0,0,0};
			}
			testbool=configuration[figure]["specularReflection"].as_double_tuple_if_exists(kleur3);
			if(testbool){
				kleur3=configuration[figure]["specularReflection"].as_double_tuple_or_die();
			ref=configuration[figure]["reflectionCoefficient"].as_double_or_die();
			}else{
				kleur3={0,0,0};
				ref=0;
			}
		}
		figure3D newfig=figure3D(
		figColor::Color(kleur[0],kleur[1],kleur[2]),
		figColor::Color(kleur2[0],kleur2[1],kleur2[2]),
		figColor::Color(kleur3[0],kleur3[1],kleur3[2]),ref);
	newfig.addPoint(Vector3D::point(1,-1,-1));
	newfig.addPoint(Vector3D::point(-1,1,-1));
	newfig.addPoint(Vector3D::point(1,1,1));
	newfig.addPoint(Vector3D::point(-1,-1,1));
	std::vector<int> v={0,1,2};
	newfig.addFace(face3D(v));
	v={1,3,2};
	newfig.addFace(face3D(v));
	v={0,3,1};
	newfig.addFace(face3D(v));
	v={0,2,3};
	newfig.addFace(face3D(v));
	return newfig;
}
figure3D Engine3D::DrawOctahedron(const ini::Configuration &configuration,int figcount){
	std::string figure="Figure"+std::to_string(figcount);
	std::vector<double> kleur;
		std::vector<double> kleur2;
		std::vector<double> kleur3;
		bool kleurbool=configuration[figure]["color"].as_double_tuple_if_exists(kleur);
		double ref;
		if(kleurbool){
			kleur=configuration[figure]["color"].as_double_tuple_or_die();
			kleur2={0,0,0};
			kleur3={0,0,0};
			ref=0;
		}else{
			kleur=configuration[figure]["ambientReflection"].as_double_tuple_or_die();
			bool testbool=configuration[figure]["diffuseReflection"].as_double_tuple_if_exists(kleur2);
			if(testbool){
				kleur2=configuration[figure]["diffuseReflection"].as_double_tuple_or_die();
			}else{
				kleur2={0,0,0};
			}
			testbool=configuration[figure]["specularReflection"].as_double_tuple_if_exists(kleur3);
			if(testbool){
				kleur3=configuration[figure]["specularReflection"].as_double_tuple_or_die();
			ref=configuration[figure]["reflectionCoefficient"].as_double_or_die();
			}else{
				kleur3={0,0,0};
				ref=0;
			}
		}
	figure3D newfig=figure3D(
		figColor::Color(kleur[0],kleur[1],kleur[2]),
		figColor::Color(kleur2[0],kleur2[1],kleur2[2]),
		figColor::Color(kleur3[0],kleur3[1],kleur3[2]),ref);
	newfig.addPoint(Vector3D::point(1,0,0));
	newfig.addPoint(Vector3D::point(0,1,0));
	newfig.addPoint(Vector3D::point(-1,0,0));
	newfig.addPoint(Vector3D::point(0,-1,0));
	newfig.addPoint(Vector3D::point(0,0,-1));
	newfig.addPoint(Vector3D::point(0,0,1));
	std::vector<int> v={0,1,5};
	newfig.addFace(face3D(v));
	v={1,2,5};
	newfig.addFace(face3D(v));
	v={2,3,5};
	newfig.addFace(face3D(v));
	v={3,0,5};
	newfig.addFace(face3D(v));
	v={1,0,4};
	newfig.addFace(face3D(v));
	v={2,1,4};
	newfig.addFace(face3D(v));
	v={3,2,4};
	newfig.addFace(face3D(v));
	v={0,3,4};
	newfig.addFace(face3D(v));
	return newfig;
}
figure3D Engine3D::DrawIcosahedron(const ini::Configuration &configuration,int figcount){
	std::string figure="Figure"+std::to_string(figcount);
	std::vector<double> kleur;
		std::vector<double> kleur2;
		std::vector<double> kleur3;
		bool kleurbool=configuration[figure]["color"].as_double_tuple_if_exists(kleur);
		double ref;
		if(kleurbool){
			kleur=configuration[figure]["color"].as_double_tuple_or_die();
			kleur2={0,0,0};
			kleur3={0,0,0};
			ref=0;
		}else{
			kleur=configuration[figure]["ambientReflection"].as_double_tuple_or_die();
			bool testbool=configuration[figure]["diffuseReflection"].as_double_tuple_if_exists(kleur2);
			if(testbool){
				kleur2=configuration[figure]["diffuseReflection"].as_double_tuple_or_die();
			}else{
				kleur2={0,0,0};
			}
			testbool=configuration[figure]["specularReflection"].as_double_tuple_if_exists(kleur3);
			if(testbool){
				kleur3=configuration[figure]["specularReflection"].as_double_tuple_or_die();
			ref=configuration[figure]["reflectionCoefficient"].as_double_or_die();
			}else{
				kleur3={0,0,0};
				ref=0;
			}
		}
	figure3D newfig=figure3D(
		figColor::Color(kleur[0],kleur[1],kleur[2]),
		figColor::Color(kleur2[0],kleur2[1],kleur2[2]),
		figColor::Color(kleur3[0],kleur3[1],kleur3[2]),ref);
	newfig.addPoint(Vector3D::point(0,0,pow(5,0.5)/2));
	for(int i=2;i<7;i++){
		double x=cos((i-2)*(2*M_PI)/5);
		double y=sin((i-2)*(2*M_PI)/5);
		newfig.addPoint(Vector3D::point(x,y,0.5));
	}
	for(int i=7;i<12;i++){
		double x=cos((M_PI/5)+(i-7)*2*(M_PI/5));
		double y=sin((M_PI/5)+(i-7)*2*(M_PI/5));
		newfig.addPoint(Vector3D::point(x,y,-0.5));
}
	newfig.addPoint(Vector3D::point(0,0,-pow(5,0.5)/2));
	std::vector<int> v={0,1,2};
	newfig.addFace(face3D(v));
	v={0,2,3};
	newfig.addFace(face3D(v));
	v={0,3,4};
	newfig.addFace(face3D(v));
	v={0,4,5};
	newfig.addFace(face3D(v));
	v={0,5,1};
	newfig.addFace(face3D(v));
	v={1,6,2};
	newfig.addFace(face3D(v));
	v={2,6,7};
	newfig.addFace(face3D(v));
	v={2,7,3};
	newfig.addFace(face3D(v));
	v={3,7,8};
	newfig.addFace(face3D(v));
	v={3,8,4};
	newfig.addFace(face3D(v));
	v={4,8,9};
	newfig.addFace(face3D(v));
	v={4,9,5};
	newfig.addFace(face3D(v));
	v={5,9,10};
	newfig.addFace(face3D(v));
	v={5,10,1};
	newfig.addFace(face3D(v));
	v={1,10,6};
	newfig.addFace(face3D(v));
	v={11,7,6};
	newfig.addFace(face3D(v));
	v={11,8,7};
	newfig.addFace(face3D(v));
	v={11,9,8};
	newfig.addFace(face3D(v));
	v={11,10,9};
	newfig.addFace(face3D(v));
	v={11,6,10};
	newfig.addFace(face3D(v));
	return newfig;
}
figure3D Engine3D::DrawDodecahedron(const ini::Configuration &configuration,int figcount){
	std::string figure="Figure"+std::to_string(figcount);
		std::vector<double> kleur;
		std::vector<double> kleur2;
		std::vector<double> kleur3;
		bool kleurbool=configuration[figure]["color"].as_double_tuple_if_exists(kleur);
		double ref;
		if(kleurbool){
			kleur=configuration[figure]["color"].as_double_tuple_or_die();
			kleur2={0,0,0};
			kleur3={0,0,0};
			ref=0;
		}else{
			kleur=configuration[figure]["ambientReflection"].as_double_tuple_or_die();
			bool testbool=configuration[figure]["diffuseReflection"].as_double_tuple_if_exists(kleur2);
			if(testbool){
				kleur2=configuration[figure]["diffuseReflection"].as_double_tuple_or_die();
			}else{
				kleur2={0,0,0};
			}
			testbool=configuration[figure]["specularReflection"].as_double_tuple_if_exists(kleur3);
			if(testbool){
				kleur3=configuration[figure]["specularReflection"].as_double_tuple_or_die();
			ref=configuration[figure]["reflectionCoefficient"].as_double_or_die();
			}else{
				kleur3={0,0,0};
				ref=0;
			}
		}
	figure3D newfig=figure3D(
		figColor::Color(kleur[0],kleur[1],kleur[2]),
		figColor::Color(kleur2[0],kleur2[1],kleur2[2]),
		figColor::Color(kleur3[0],kleur3[1],kleur3[2]),ref);
	figure3D icosahedron=Engine3D::DrawIcosahedron(configuration,figcount);
	for(face3D face:icosahedron.faces){
		double x=0;
		double y=0;
		double z=0;
		for(int i:face.pointsIndex){
			x+=icosahedron.points[i].x;
			y+=icosahedron.points[i].y;
			z+=icosahedron.points[i].z;
		}
		x/=3.0;
		y/=3.0;
		z/=3.0;
		newfig.addPoint(Vector3D::point(x,y,z));
	}
	std::vector<int> v={0,1,2,3,4};
	newfig.addFace(face3D(v));
	v={0,5,6,7,1};
	newfig.addFace(face3D(v));
	v={1,7,8,9,2};
	newfig.addFace(face3D(v));
	v={2,9,10,11,3};
	newfig.addFace(face3D(v));
	v={3,11,12,13,4};
	newfig.addFace(face3D(v));
	v={4,13,14,5,0};
	newfig.addFace(face3D(v));
	v={19,18,17,16,15};
	newfig.addFace(face3D(v));
	v={19,14,13,12,18};
	newfig.addFace(face3D(v));
	v={18,12,11,10,17};
	newfig.addFace(face3D(v));
	v={17,10,9,8,16};
	newfig.addFace(face3D(v));
	v={16,8,7,6,15};
	newfig.addFace(face3D(v));
	v={15,6,5,14,19};
	newfig.addFace(face3D(v));
	return newfig;
}

figure3D Engine3D::DrawSphere(const ini::Configuration &configuration,const int figcount,const int n){
	std::string figure="Figure"+std::to_string(figcount);
	std::vector<double> kleur;
			std::vector<double> kleur2;
			std::vector<double> kleur3;
			bool kleurbool=configuration[figure]["color"].as_double_tuple_if_exists(kleur);
			double ref;
			if(kleurbool){
				kleur=configuration[figure]["color"].as_double_tuple_or_die();
				kleur2={0,0,0};
				kleur3={0,0,0};
				ref=0;
			}else{
				kleur=configuration[figure]["ambientReflection"].as_double_tuple_or_die();
				bool testbool=configuration[figure]["diffuseReflection"].as_double_tuple_if_exists(kleur2);
				if(testbool){
					kleur2=configuration[figure]["diffuseReflection"].as_double_tuple_or_die();
				}else{
					kleur2={0,0,0};
				}
				testbool=configuration[figure]["specularReflection"].as_double_tuple_if_exists(kleur3);
				if(testbool){
					kleur3=configuration[figure]["specularReflection"].as_double_tuple_or_die();
				ref=configuration[figure]["reflectionCoefficient"].as_double_or_die();
				}else{
					kleur3={0,0,0};
					ref=0;
				}
			}


	figure3D oldfig=Engine3D::DrawIcosahedron(configuration,figcount);
	for(int i=0;i<n;i++){
		figure3D newfig=figure3D(
			figColor::Color(kleur[0],kleur[1],kleur[2]),
			figColor::Color(kleur2[0],kleur2[1],kleur2[2]),
			figColor::Color(kleur3[0],kleur3[1],kleur3[2]),ref);
		std::vector<Vector3D> nieuwpoints;
		std::vector<face3D> nieuwface;
		std::vector<Vector3D> oldpoints=oldfig.points;
		int pointcounter=0;
		for(face3D temp:oldfig.faces){
			Vector3D A=oldpoints[temp.pointsIndex[0]];
			Vector3D B=oldpoints[temp.pointsIndex[1]];
			Vector3D C=oldpoints[temp.pointsIndex[2]];
			Vector3D D=(A+B)/2.0;
			Vector3D E=(A+C)/2.0;
			Vector3D F=(B+C)/2.0;
			nieuwpoints.push_back(A);
			nieuwpoints.push_back(B);
			nieuwpoints.push_back(C);
			nieuwpoints.push_back(D);
			nieuwpoints.push_back(E);
			nieuwpoints.push_back(F);
			std::vector<int> vec={pointcounter,pointcounter+3,pointcounter+4};
			nieuwface.push_back(face3D(vec));
			vec={pointcounter+1,pointcounter+5,pointcounter+3};
			nieuwface.push_back(face3D(vec));
			vec={pointcounter+2,pointcounter+4,pointcounter+5};
			nieuwface.push_back(face3D(vec));
			vec={pointcounter+3,pointcounter+5,pointcounter+4};
			nieuwface.push_back(face3D(vec));
			pointcounter+=6;
		}
		for(auto p:nieuwpoints){
			newfig.addPoint(p);
		}
		newfig.faces=nieuwface;
		oldfig=newfig;
	}
	for(Vector3D& point:oldfig.points){
//		std::cout<<point.x<<std::endl;
		point.normalise();
	}
	return oldfig;
}

figure3D Engine3D::DrawCone(const ini::Configuration &configuration, const int figcount){
	std::string figure="Figure"+std::to_string(figcount);
	std::vector<double> kleur;
		std::vector<double> kleur2;
		std::vector<double> kleur3;
		bool kleurbool=configuration[figure]["color"].as_double_tuple_if_exists(kleur);
		double ref;
		if(kleurbool){
			kleur=configuration[figure]["color"].as_double_tuple_or_die();
			kleur2={0,0,0};
			kleur3={0,0,0};
			ref=0;
		}else{
			kleur=configuration[figure]["ambientReflection"].as_double_tuple_or_die();
			bool testbool=configuration[figure]["diffuseReflection"].as_double_tuple_if_exists(kleur2);
			if(testbool){
				kleur2=configuration[figure]["diffuseReflection"].as_double_tuple_or_die();
			}else{
				kleur2={0,0,0};
			}
			testbool=configuration[figure]["specularReflection"].as_double_tuple_if_exists(kleur3);
			if(testbool){
				kleur3=configuration[figure]["specularReflection"].as_double_tuple_or_die();
			ref=configuration[figure]["reflectionCoefficient"].as_double_or_die();
			}else{
				kleur3={0,0,0};
				ref=0;
			}
		}
	figure3D newfig=figure3D(
		figColor::Color(kleur[0],kleur[1],kleur[2]),
		figColor::Color(kleur2[0],kleur2[1],kleur2[2]),
		figColor::Color(kleur3[0],kleur3[1],kleur3[2]),ref);
	int n=configuration[figure]["n"].as_int_or_die();
	double height=configuration[figure]["height"].as_double_or_die();
	for(int i=1;i<n+1;i++){
		double x=cos(2*i*M_PI/n);
		double y=sin(2*i*M_PI/n);
		newfig.addPoint(Vector3D::point(x,y,0));
	}
	newfig.addPoint(Vector3D::point(0,0,height));
	face3D megaface;
	for(int i=0;i<n;i++){
		std::vector<int> tempvec={i,(i+1)%n,n};
		newfig.addFace(face3D(tempvec));
		megaface.addPoint((n-i)-1);
	}
	newfig.addFace(megaface);
	return newfig;
}

figure3D Engine3D::DrawCylinder(const ini::Configuration &configuration, const int figcount,const int n,const double height){
	std::string figure="Figure"+std::to_string(figcount);
	std::vector<double> kleur;
		std::vector<double> kleur2;
		std::vector<double> kleur3;
		bool kleurbool=configuration[figure]["color"].as_double_tuple_if_exists(kleur);
		double ref;
		if(kleurbool){
			kleur=configuration[figure]["color"].as_double_tuple_or_die();
			kleur2={0,0,0};
			kleur3={0,0,0};
			ref=0;
		}else{
			kleur=configuration[figure]["ambientReflection"].as_double_tuple_or_die();
			bool testbool=configuration[figure]["diffuseReflection"].as_double_tuple_if_exists(kleur2);
			if(testbool){
				kleur2=configuration[figure]["diffuseReflection"].as_double_tuple_or_die();
			}else{
				kleur2={0,0,0};
			}
			testbool=configuration[figure]["specularReflection"].as_double_tuple_if_exists(kleur3);
			if(testbool){
				kleur3=configuration[figure]["specularReflection"].as_double_tuple_or_die();
			ref=configuration[figure]["reflectionCoefficient"].as_double_or_die();
			}else{
				kleur3={0,0,0};
				ref=0;
			}
		}
	figure3D newfig=figure3D(
		figColor::Color(kleur[0],kleur[1],kleur[2]),
		figColor::Color(kleur2[0],kleur2[1],kleur2[2]),
		figColor::Color(kleur3[0],kleur3[1],kleur3[2]),ref);
	for(int i=1;i<n+1;i++){
		double x=cos(2.0*i*M_PI/n);
		double y=sin(2.0*i*M_PI/n);
		newfig.addPoint(Vector3D::point(x,y,0));
	}
	for(int i=1;i<n+1;i++){
		double x=cos(2*i*M_PI/n);
		double y=sin(2*i*M_PI/n);
		newfig.addPoint(Vector3D::point(x,y,height));
	}
	face3D megafaceTop;
	face3D megafaceBottom;
	for(int i=0;i<n;i++){
		std::vector<int> tempvec={i,1*(i+1)%n,1*(n+(i+1)%n),1*n+i};
		newfig.addFace(face3D(tempvec));
		megafaceTop.addPoint(n+i);
		megafaceBottom.addPoint(i);
	}
	newfig.addFace(megafaceBottom);
	newfig.addFace(megafaceTop);
	return newfig;
}

figure3D Engine3D::DrawTorus(const ini::Configuration &configuration, const int figcount){
	std::string figure="Figure"+std::to_string(figcount);
	std::vector<double> kleur;
		std::vector<double> kleur2;
		std::vector<double> kleur3;
		bool kleurbool=configuration[figure]["color"].as_double_tuple_if_exists(kleur);
		double ref;
		if(kleurbool){
			kleur=configuration[figure]["color"].as_double_tuple_or_die();
			kleur2={0,0,0};
			kleur3={0,0,0};
			ref=0;
		}else{
			kleur=configuration[figure]["ambientReflection"].as_double_tuple_or_die();
			bool testbool=configuration[figure]["diffuseReflection"].as_double_tuple_if_exists(kleur2);
			if(testbool){
				kleur2=configuration[figure]["diffuseReflection"].as_double_tuple_or_die();
			}else{
				kleur2={0,0,0};
			}
			testbool=configuration[figure]["specularReflection"].as_double_tuple_if_exists(kleur3);
			if(testbool){
				kleur3=configuration[figure]["specularReflection"].as_double_tuple_or_die();
			ref=configuration[figure]["reflectionCoefficient"].as_double_or_die();
			}else{
				kleur3={0,0,0};
				ref=0;
			}
		}
	figure3D newfig=figure3D(
			figColor::Color(kleur[0],kleur[1],kleur[2]),
			figColor::Color(kleur2[0],kleur2[1],kleur2[2]),
			figColor::Color(kleur3[0],kleur3[1],kleur3[2]),ref);
	double r=configuration[figure]["r"].as_double_or_die();
	double R=configuration[figure]["R"].as_double_or_die();
	int m=configuration[figure]["m"].as_int_or_die();
	int n=configuration[figure]["n"].as_int_or_die();
	for(int i=0;i<n;i++){
		for(int j=1;j<m+1;j++){
			double u=2*i*M_PI/n;
			double v=2*j*M_PI/m;
			double x=(R+r*cos(v))*cos(u);
			double y=(R+r*cos(v))*sin(u);
			double z=r*(sin(v));
			newfig.addPoint(Vector3D::point(x,y,z));
		}
	}
	for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				std::vector<int> points;
				points.push_back((i*m)+j);
				points.push_back((((i+1)%n)*m)+j);
				points.push_back((((i+1)%n)*m)+((j+1)%m));
				points.push_back((i*n+((j+1)%m)));
				newfig.addFace(face3D(points));
			}
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
	double r;
	double theta;
	double phi;
	Engine3D::Topolar(eyepoint,theta,phi,r);
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

void Engine3D::Topolar(const Vector3D &eyepoint,double& theta,double& phi,double& r){
	r=sqrt(pow(eyepoint.x,2)+pow(eyepoint.y,2)+pow(eyepoint.z,2));
	theta=std::atan2(eyepoint.y,eyepoint.x);
	phi=std::acos(eyepoint.z/r);
}

figure3D Engine3D::combineFigures(std::vector<figure3D>& figures){
	figure3D newfig=figure3D(figures[0].ambientReflection,figures[0].difusseReflection,figures[0].specularReflection,figures[0].reflectionCoefficient);
	int pointcount=0;
	for(figure3D fig:figures){
		for(auto i:fig.points){
			newfig.addPoint(i);
		}
		for(auto i:fig.faces){
			face3D newface;
			for(int newpoint:i.pointsIndex){
				newface.addPoint(newpoint+pointcount);
			}
			newfig.addFace(newface);
		}
		pointcount+=fig.points.size();
	}
	return newfig;
}

figure3D Engine3D::DrawBuckyBall(const ini::Configuration &configuration, const int figcount){
	std::string figure="Figure"+std::to_string(figcount);
	std::vector<double> kleur;
		std::vector<double> kleur2;
		std::vector<double> kleur3;
		bool kleurbool=configuration[figure]["color"].as_double_tuple_if_exists(kleur);
		double ref;
		if(kleurbool){
			kleur=configuration[figure]["color"].as_double_tuple_or_die();
			kleur2={0,0,0};
			kleur3={0,0,0};
			ref=0;
		}else{
			kleur=configuration[figure]["ambientReflection"].as_double_tuple_or_die();
			bool testbool=configuration[figure]["diffuseReflection"].as_double_tuple_if_exists(kleur2);
			if(testbool){
				kleur2=configuration[figure]["diffuseReflection"].as_double_tuple_or_die();
			}else{
				kleur2={0,0,0};
			}
			testbool=configuration[figure]["specularReflection"].as_double_tuple_if_exists(kleur3);
			if(testbool){
				kleur3=configuration[figure]["specularReflection"].as_double_tuple_or_die();
			ref=configuration[figure]["reflectionCoefficient"].as_double_or_die();
			}else{
				kleur3={0,0,0};
				ref=0;
			}
		}
	figure3D icosahedron=Engine3D::DrawIcosahedron(configuration,figcount);
	std::vector<face3D> triangles;
	std::vector<face3D> hexagons;
	int pointcounter=0;
	figure3D bucky(
			figColor::Color(kleur[0],kleur[1],kleur[2]),
			figColor::Color(kleur2[0],kleur2[1],kleur2[2]),
			figColor::Color(kleur3[0],kleur3[1],kleur3[2]),ref);
	for(face3D face:icosahedron.faces){
		for(unsigned int i=0;i<face.pointsIndex.size();i++){
			bucky.addPoint(icosahedron.points[face.pointsIndex[i]]);
			Vector3D linelength=icosahedron.points[(face.pointsIndex[(i+1)%3])]-icosahedron.points[face.pointsIndex[i]];
			linelength.x=linelength.x/3;
			linelength.y=linelength.y/3;
			linelength.z=linelength.z/3;
			bucky.addPoint(icosahedron.points[face.pointsIndex[i]]+linelength);
			bucky.addPoint(icosahedron.points[(face.pointsIndex[(i+1)%3])]-linelength);
		}
		std::vector<int> tempPoints;
		face3D newface;
		tempPoints={pointcounter+1,pointcounter+2,pointcounter+4,pointcounter+5,pointcounter+7,pointcounter+8};
		newface.pointsIndex=tempPoints;
		hexagons.push_back(newface);
		tempPoints={pointcounter+0,pointcounter+1,pointcounter+8};
		newface.pointsIndex=tempPoints;
		triangles.push_back(newface);
		tempPoints={pointcounter+3,pointcounter+2,pointcounter+4};
		newface.pointsIndex=tempPoints;
		triangles.push_back(newface);
		tempPoints={pointcounter+5,pointcounter+6,pointcounter+7};
		newface.pointsIndex=tempPoints;
		triangles.push_back(newface);
		pointcounter+=9;

	}
	std::vector<int> alreadyused;
	for(auto triang:triangles){

		for(int outerpoint:triang.pointsIndex){
			std::vector<face3D> founded={triang};
			std::vector<int> samepoints;
			bool found=false;
			for(int b:alreadyused){
				if(b==outerpoint){
					found=true;
				}
			}
			if(!found){
				for(auto innertriang:triangles){
					if(innertriang.pointsIndex!=triang.pointsIndex){
						for(int innerpoint:innertriang.pointsIndex){
							if(bucky.points[outerpoint].x==bucky.points[innerpoint].x&&bucky.points[outerpoint].y==bucky.points[innerpoint].y&&bucky.points[outerpoint].z==bucky.points[innerpoint].z){
								samepoints.push_back(outerpoint);
								samepoints.push_back(innerpoint);
								founded.push_back(innertriang);
							}
						}
					}
				}
			}
		if(founded.size()==5){
			face3D newface;
			for(face3D face:founded){
				for(int testpoint:face.pointsIndex){
					bool insamepoint=false;
					bool inface=false;
					for(int i:samepoints){
						if(testpoint==i){
							insamepoint=true;
						}

					}
					for(int i:newface.pointsIndex){
						if(testpoint==i){
							inface=true;
						}
						if(bucky.points[i].x==bucky.points[testpoint].x&&bucky.points[i].y==bucky.points[testpoint].y&&bucky.points[i].z==bucky.points[testpoint].z){
							inface=true;
						}
					}
					if(!insamepoint&&!inface){
						newface.addPoint(testpoint);
					}
				}
			}
			face3D newerface;
			int startpoint=newface.pointsIndex[0];
			int currentpoint=newface.pointsIndex[0];
			std::vector<int> alreadyfound={startpoint};
			for(unsigned int point=0;point<5;point++){
				for(auto hex:hexagons){
					for(auto hexpoint:hex.pointsIndex){
						if(bucky.points[hexpoint].x==bucky.points[currentpoint].x&&bucky.points[hexpoint].y==bucky.points[currentpoint].y&&bucky.points[hexpoint].z==bucky.points[currentpoint].z){
							for(int hexpoint2:hex.pointsIndex){
								for(int facepoint:newface.pointsIndex){
									if(bucky.points[hexpoint2].x==bucky.points[facepoint].x&&bucky.points[hexpoint2].y==bucky.points[facepoint].y&&bucky.points[hexpoint2].z==bucky.points[facepoint].z){
										bool alreadyfoundbool=false;
										for(int search:alreadyfound){
											if(bucky.points[search].x==bucky.points[facepoint].x&&bucky.points[search].y==bucky.points[facepoint].y&&bucky.points[search].z==bucky.points[facepoint].z){
												alreadyfoundbool=true;
											}
										}
										if(!alreadyfoundbool){
											newerface.addPoint(hexpoint);
											newerface.addPoint(hexpoint2);
											alreadyfound.push_back(hexpoint2);
											currentpoint=hexpoint2;
										}
									}
								}
							}
						}
					}
				}
			}
			std::reverse(newerface.pointsIndex.begin(),newerface.pointsIndex.end());
			bucky.addFace(newerface);
		}
			for(int i:samepoints){
				alreadyused.push_back(i);
			}

		}
	}
	for(auto i:hexagons){
		bucky.addFace(i);
	}
	std::vector<int> usedpoints;
	for(face3D face:bucky.faces){
		for(int point:face.pointsIndex){
			bool found=false;
			for(int i:usedpoints){
				if(i==point){
					found=true;
				}
			}
			if(!found){
				usedpoints.push_back(point);
			}
		}
	}
	for(unsigned int i=0;i<bucky.points.size();i++){
		bool used=false;
		for(int b:usedpoints){
			if(i==b){
				used=true;
			}
		}
		if(!used){
			for(face3D& face:bucky.faces){
					for(int& point:face.pointsIndex){
						if(point>i){
							point--;
						}
					}
				}
			for(int& point:usedpoints){
				if(point>i){
					point--;
				}
			}
			bucky.points.erase (bucky.points.begin()+i);
			i--;
		}
	}
	return bucky;
}

std::vector<Light*> Engine3D::readLights(const ini::Configuration &configuration){
	unsigned int nrLights=configuration["General"]["nrLights"].as_int_or_die();
	std::vector<Light*> lights;
	std::vector<double> eyeCoords=configuration["General"]["eye"].as_double_tuple_or_die();
	Vector3D eyeVector=Vector3D::vector(eyeCoords[0],eyeCoords[1],eyeCoords[2]);
	Matrix eyeMatrix=Engine3D::eyePointTrans(eyeVector);
	for(unsigned int i=0;i<nrLights;i++){
		bool infinity;
		std::string light="Light"+std::to_string(i);
		bool exists=configuration[light]["infinity"].as_bool_if_exists(infinity);
		std::vector<double> ambientvec=configuration[light]["ambientLight"].as_double_tuple_or_die();
		figColor::Color ambient(ambientvec[0],ambientvec[1],ambientvec[2]);
		figColor::Color diffuse(0,0,0);
		figColor::Color specular(0,0,0);
		std::vector<double> spec;
		bool specexists=configuration[light]["specularLight"].as_double_tuple_if_exists(spec);
		if(specexists){
			specular=figColor::Color(spec[0],spec[1],spec[2]);
		}
		if(exists){
			std::vector<double> diffusevec=configuration[light]["diffuseLight"].as_double_tuple_or_die();
			diffuse=figColor::Color(diffusevec[0],diffusevec[1],diffusevec[2]);
			if(infinity){
				std::vector<double> locationd=configuration[light]["direction"].as_double_tuple_or_die();
				Vector3D loc=Vector3D::vector(Vector3D::vector(locationd[0],locationd[1],locationd[2]));
				loc=loc*eyeMatrix;
				Light *l=new InfLight(ambient,diffuse,specular,loc);
				lights.push_back(l);
			}else{
				std::vector<double> locationd=configuration[light]["location"].as_double_tuple_or_die();
				Vector3D loc=Vector3D::point(Vector3D::vector(locationd[0],locationd[1],locationd[2]));
				loc=loc*eyeMatrix;
				Light *l=new PointLight(ambient,diffuse,specular,loc);
				bool withShadow=false;
				bool shadowExists=configuration["general"]["shadowEnabled"].as_bool_if_exists(withShadow);
				if(shadowExists&&withShadow){
					int shadowmask=configuration["general"]["shadowMask"].as_int_or_die();
					l->shadowmask=ZBuffer(shadowmask,shadowmask);
				}
				lights.push_back(l);
			}
		}else{
			Light* l=new Light(ambient,diffuse,specular);
			lights.push_back(l);
		}


	}
	return lights;
}

void Engine3D::DrawThickFigure(const ini::Configuration &configuration, const int figcount,figure3D& fig,std::vector<figure3D>& figures){
	std::string figure="Figure"+std::to_string(figcount);
	int m=configuration[figure]["m"].as_int_or_die();
	int n=configuration[figure]["n"].as_int_or_die();
	double radius=configuration[figure]["radius"].as_double_or_die();
//	std::vector<figure3D> figures;
	//de bol tekenen
	figure3D figSphere=Engine3D::DrawSphere(configuration,figcount,m);
	figSphere.scaleFigure(radius);
	for(unsigned int i=0;i<fig.points.size();i++){
		figure3D newfigSphere=figSphere;
		newfigSphere.translate(Vector3D::point(0,0,0)+fig.points[i]);
		figures.push_back(newfigSphere);
	}
//	figure3D cylinder=Engine3D::DrawCylinder(configuration,figcount,n,1);
	for(face3D face:fig.faces){
		for(unsigned int i=0;i<face.pointsIndex.size();i++){
			Vector3D p1=fig.points[face.pointsIndex[i]];
			Vector3D p2=fig.points[face.pointsIndex[(i+1)%face.pointsIndex.size()]];
			Vector3D p1p2=p2-p1;
//			figure3D newfig=cylinder;
			//cylinders tekekenen
			double distance=p1p2.length()/radius;
//			Engine3D::AddCylinderHeight(newfig,distance-1,n);
			figure3D newfig=Engine3D::DrawCylinder(configuration,figcount,n,distance);

			newfig.scaleFigure(radius);
//			Matrix trans=Engine3D::eyePointTrans(p1p2);
			double theta;
			double phi;
			double nothing;
			Engine3D::Topolar(p1p2,theta,phi,nothing);
			newfig.rotateY(phi,true);
			newfig.rotateZ(theta,true);
			newfig.translate(Vector3D::point(0,0,0)+p1);
			figures.push_back(newfig);



		}
	}

}

void Engine3D::AddCylinderHeight(figure3D& cylinder,double addition,double n){
	for(int i=0;i<cylinder.points.size();i++){
		cylinder.points[n+i].y+=addition;
	}
}

