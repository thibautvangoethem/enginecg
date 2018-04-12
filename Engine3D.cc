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
#include <vector>
#include "Line2D.h"
#include "L3DEngine.h"

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
			if(configuration[figure]["type"].as_string_or_die()=="LineDrawing"){
				newfig=Engine3D::LineDrawing(configuration,figcount);
			}else if(configuration[figure]["type"].as_string_or_die()=="Cube"){
				newfig=Engine3D::DrawCube(configuration,figcount);
			}else if(configuration[figure]["type"].as_string_or_die()=="Tetrahedron"){
				newfig=Engine3D::DrawTetrahedron(configuration,figcount);
			}else if(configuration[figure]["type"].as_string_or_die()=="Icosahedron"){
				newfig=Engine3D::DrawIcosahedron(configuration,figcount);
			}else if(configuration[figure]["type"].as_string_or_die()=="Octahedron"){
				newfig=Engine3D::DrawOctahedron(configuration,figcount);
			}else if(configuration[figure]["type"].as_string_or_die()=="Dodecahedron"){
				newfig=Engine3D::DrawDodecahedron(configuration,figcount);
			}else if(configuration[figure]["type"].as_string_or_die()=="Sphere"){
				newfig=Engine3D::DrawSphere(configuration,figcount);
			}else if(configuration[figure]["type"].as_string_or_die()=="Cone"){
				newfig=Engine3D::DrawCone(configuration,figcount);
			}else if(configuration[figure]["type"].as_string_or_die()=="Cylinder"){
				newfig=Engine3D::DrawCylinder(configuration,figcount);
			}else if(configuration[figure]["type"].as_string_or_die()=="Torus"){
				newfig=Engine3D::DrawTorus(configuration,figcount);
			}else if(configuration[figure]["type"].as_string_or_die()=="3DLSystem"){
				newfig=L3DEngine::L3D_ToFigure(configuration,figcount);
			}
			int rotatex=configuration[figure]["rotateX"].as_double_or_die();
			int rotatey=configuration[figure]["rotateY"].as_double_or_die();
			int rotatez=configuration[figure]["rotateZ"].as_double_or_die();
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
figure3D Engine3D::DrawCube(const ini::Configuration &configuration,int figcount){
	std::string figure="Figure"+std::to_string(figcount);
	std::vector<double> kleur=configuration[figure]["color"].as_double_tuple_or_die();
	figure3D newfig=figure3D(figColor::Color(roundToInt(255*kleur[0]),roundToInt(255*kleur[1]),roundToInt(255*kleur[2])));
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
	std::vector<double> kleur=configuration[figure]["color"].as_double_tuple_or_die();
	figure3D newfig=figure3D(figColor::Color(roundToInt(255*kleur[0]),roundToInt(255*kleur[1]),roundToInt(255*kleur[2])));
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
	std::vector<double> kleur=configuration[figure]["color"].as_double_tuple_or_die();
	figure3D newfig=figure3D(figColor::Color(roundToInt(255*kleur[0]),roundToInt(255*kleur[1]),roundToInt(255*kleur[2])));
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
	std::vector<double> kleur=configuration[figure]["color"].as_double_tuple_or_die();
	figure3D newfig=figure3D(figColor::Color(roundToInt(255*kleur[0]),roundToInt(255*kleur[1]),roundToInt(255*kleur[2])));
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
	std::vector<double> kleur=configuration[figure]["color"].as_double_tuple_or_die();
	figure3D newfig=figure3D(figColor::Color(roundToInt(255*kleur[0]),roundToInt(255*kleur[1]),roundToInt(255*kleur[2])));
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
		x/=3;
		y/=3;
		z/=3;
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

figure3D Engine3D::DrawSphere(const ini::Configuration &configuration,const int figcount){
	std::string figure="Figure"+std::to_string(figcount);
	std::vector<double> kleur=configuration[figure]["color"].as_double_tuple_or_die();
	int n=configuration[figure]["n"].as_int_or_die();
	figure3D oldfig=Engine3D::DrawIcosahedron(configuration,figcount);
	for(int i=0;i<n;i++){
		std::vector<Vector3D> nieuwpoints;
		std::vector<face3D> nieuwface;
		std::vector<Vector3D> oldpoints=oldfig.points;
		int pointcounter=0;
		for(face3D temp:oldfig.faces){
			Vector3D A=oldpoints[temp.pointsIndex[0]];
			Vector3D B=oldpoints[temp.pointsIndex[1]];
			Vector3D C=oldpoints[temp.pointsIndex[2]];
			Vector3D D=(A+B)/2;
			Vector3D E=(A+C)/2;
			Vector3D F=(B+C)/2;
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
		figure3D newfig(nieuwface,figColor::Color(roundToInt(255*kleur[0]),roundToInt(255*kleur[1]),roundToInt(255*kleur[2])));
		for(auto p:nieuwpoints){
			newfig.addPoint(p);
		}
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
	std::vector<double> kleur=configuration[figure]["color"].as_double_tuple_or_die();
	figure3D newfig=figure3D(figColor::Color(roundToInt(255*kleur[0]),roundToInt(255*kleur[1]),roundToInt(255*kleur[2])));
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

figure3D Engine3D::DrawCylinder(const ini::Configuration &configuration, const int figcount){
	std::string figure="Figure"+std::to_string(figcount);
	std::vector<double> kleur=configuration[figure]["color"].as_double_tuple_or_die();
	figure3D newfig=figure3D(figColor::Color(roundToInt(255*kleur[0]),roundToInt(255*kleur[1]),roundToInt(255*kleur[2])));
	int n=configuration[figure]["n"].as_int_or_die();
	double height=configuration[figure]["height"].as_double_or_die();
	for(int i=1;i<n+1;i++){
		double x=cos(2*i*M_PI/n);
		double y=sin(2*i*M_PI/n);
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
		std::vector<int> tempvec={i,(i+1)%n,(n+(i+1)%n),n+i};
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
	std::vector<double> kleur=configuration[figure]["color"].as_double_tuple_or_die();
	figure3D newfig=figure3D(figColor::Color(roundToInt(255*kleur[0]),roundToInt(255*kleur[1]),roundToInt(255*kleur[2])));
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
	double r=sqrt(pow(eyepoint.x,2)+pow(eyepoint.y,2)+pow(eyepoint.z,2));
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
