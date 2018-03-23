/*
 * L3DEngine.cc
 *
 *  Created on: Mar 22, 2018
 *      Author: thibaut
 */

#include "L3DEngine.h"
#include <iostream>
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
#include "l_parser.h"
#include <fstream>
inline int roundToInt(double d)
{
	return static_cast<int>(round(d));
}
L3DEngine::L3DEngine() {
	// TODO Auto-generated constructor stub

}

L3DEngine::~L3DEngine() {
	// TODO Auto-generated destructor stub
}

figure3D L3DEngine::L3D_ToFigure(const ini::Configuration &configuration,int figcount){
	std::string figure="Figure"+std::to_string(figcount);
	std::vector<double> kleur=configuration[figure]["color"].as_double_tuple_or_die();
	figure3D newfig=figure3D(figColor::Color(roundToInt(255*kleur[0]),roundToInt(255*kleur[1]),roundToInt(255*kleur[2])));
	std::string toRead=configuration[figure]["inputfile"].as_string_or_die();
	LParser::LSystem3D l_system;
	std::cout<<"reading: "<< toRead << std::endl;
	std::ifstream input_stream(toRead);
	input_stream >> l_system;
	input_stream.close();
	double angle=l_system.get_angle()/180*M_PI;
	Vector3D H=Vector3D::vector(1,0,0);
	Vector3D L=Vector3D::vector(0,1,0);
	Vector3D U=Vector3D::vector(0,0,1);
	std::string initiator=l_system.get_initiator();
	int iterations=l_system.get_nr_iterations();
	std::string replacedInitiator="";
	for(char ichar:initiator){
		if(ichar=='+'||ichar=='-'||ichar=='('||ichar==')'||ichar=='&'||ichar=='/'||ichar=='^'||ichar=='\\'||ichar=='|'){
			replacedInitiator+=ichar;
		}else{
			replacedInitiator+=l_system.get_replacement(ichar);
		}
	}
	for(int i=0;i<iterations-1;i++){
		std::string nieuwreplaced="";
		for(char richar:replacedInitiator){
			if(richar=='+'||richar=='-'||richar=='('||richar==')'||richar=='&'||richar=='/'||richar=='^'||richar=='\\'||richar=='|'){
					nieuwreplaced+=richar;
				}else{
					nieuwreplaced+=l_system.get_replacement(richar);
				}
		}
		replacedInitiator=nieuwreplaced;
	}
	std::vector<Vector3D> previousPos;
	Vector3D currentpos=Vector3D::point(0,0,0);
	unsigned int pointcounter=0;
	for(char lchar:replacedInitiator){
		if(lchar=='+'){
			Vector3D Hnew=H*cos(angle)+L*sin(angle);
			Vector3D Lnew=(-H)*sin(angle)+L*cos(angle);
			H=Hnew;
			L=Lnew;
		}else if(lchar=='-'){
			Vector3D Hnew=H*cos(-angle)+L*sin(-angle);
			Vector3D Lnew=(-H)*sin(-angle)+L*cos(-angle);
			H=Hnew;
			L=Lnew;
		}else if(lchar=='^'){
			Vector3D Hnew=H*cos(angle)+U*sin(angle);
			Vector3D Unew=(-H)*sin(angle)+U*cos(angle);
			H=Hnew;
			U=Unew;
		}else if(lchar=='&'){
			Vector3D Hnew=H*cos(-angle)+U*sin(-angle);
			Vector3D Unew=(-H)*sin(-angle)+U*cos(-angle);
			H=Hnew;
			U=Unew;
		}else if(lchar=='\\'){
			Vector3D Lnew=L*cos(angle)-U*sin(angle);
			Vector3D Unew=L*sin(angle)+U*cos(angle);
			L=Lnew;
			U=Unew;
		}else if(lchar=='/'){
			Vector3D Lnew=L*cos(-angle)-U*sin(-angle);
			Vector3D Unew=L*sin(-angle)+U*cos(-angle);
			L=Lnew;
			U=Unew;
		}else if(lchar=='|'){
			H=-H;
			L=-L;

		}else if(lchar=='('){
			previousPos.push_back(currentpos);
			previousPos.push_back(H);
			previousPos.push_back(U);
			previousPos.push_back(L);
		}else if(lchar==')'){
			currentpos=previousPos[previousPos.size()-4];
			H=previousPos[previousPos.size()-3];
			U=previousPos[previousPos.size()-2];
			L=previousPos[previousPos.size()-1];
			for(unsigned int i=0;i<4;i++){
				previousPos.pop_back();
			}

		}else{
			for(char alphaChar:l_system.get_alphabet()){
				if(alphaChar==lchar){
					if(l_system.draw(lchar)){
						newfig.addPoint(currentpos);
						currentpos+=H;
						newfig.addPoint(currentpos);
						face3D newface;
						newface.addPoint(pointcounter);
						newface.addPoint(pointcounter+1);
						pointcounter+=2;
						newfig.addFace(newface);
					}else{
						currentpos+=H;
					}
				}
		    }
		}
	}
return newfig;
}
