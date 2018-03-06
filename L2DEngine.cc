/*
 * L2DEngine.cpp
 *
 *  Created on: Mar 1, 2018
 *      Author: thibaut
 */

#include "L2DEngine.h"
#include "easy_image.h"
#include "ini_configuration.h"
#include "Color.h"
#include "Point2D.h"
#include "Line2D.h"
#include "l_parser.h"
#include "imgUtils.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <list>
#include <utility>
using namespace std;
typedef std::list<Line2D> Lines2D;
inline int roundToInt(double d)
{
	return static_cast<int>(round(d));
}

L2DEngine::L2DEngine() {
	// TODO Auto-generated constructor stub

}

L2DEngine::~L2DEngine() {
	// TODO Auto-generated destructor stub
}

Lines2D L2DEngine::L2D_ToLines(const ini::Configuration &configuration){
	std::string toRead=configuration["2DLSystem"]["inputfile"].as_string_or_die();
	LParser::LSystem2D l_system;
	std::ifstream input_stream(toRead);
    input_stream >> l_system;
    input_stream.close();

    std::vector<double> achtergrondKleur=configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
    std::vector<double> lijnKleur=configuration["2DLSystem"]["color"].as_double_tuple_or_die();
    Lines2D lines;
    std::set<char> alphabet=l_system.get_alphabet();
    double angleDegree=l_system.get_angle();
    double startAngleDegree=l_system.get_starting_angle();
    std::string initiator=l_system.get_initiator();
    int iterations=l_system.get_nr_iterations();
    double currentx=0;
    double currenty=0;
    double currentAngle=startAngleDegree/180*M_PI;
    double angleRad=angleDegree/180*M_PI;
    std::string replacedInitiator="";
    std::vector<double> keepPos;
    for(char ichar:initiator){
    	if(ichar=='+'||ichar=='-'||ichar=='('||ichar==')'){
    		replacedInitiator+=ichar;
    	}else{
    		replacedInitiator+=l_system.get_replacement(ichar);
    	}
    }
    for(int i=0;i<iterations-1;i++){
    	std::string nieuwreplaced="";
    	for(char richar:replacedInitiator){
    		if(richar=='+'||richar=='-'||richar=='('||richar==')'){
    				nieuwreplaced+=richar;
    		    }else{
    		   		nieuwreplaced+=l_system.get_replacement(richar);
    		    }
    	}
    	replacedInitiator=nieuwreplaced;
    }
    int counter =0;
    for(char lchar:replacedInitiator){
    	counter++;
    	if(lchar=='+'){
    		currentAngle+=angleRad;
    		if(currentAngle>2*M_PI){
    			currentAngle-=2*M_PI;
    		}
    	}else if(lchar=='-'){
    		currentAngle-=angleRad;
    		   	if(currentAngle<0){
    		   		currentAngle=2*M_PI+currentAngle;
    		}

    	}else if(lchar=='('){
    		keepPos.push_back(currenty);
    		keepPos.push_back(currentx);
    		keepPos.push_back(currentAngle);

    	}else if(lchar==')'){

    		currentx=keepPos[keepPos.size()-2];
    		currenty=keepPos[keepPos.size()-3];
    		currentAngle=keepPos[keepPos.size()-1];
    		keepPos.pop_back();
    		keepPos.pop_back();
    		keepPos.pop_back();
    	}else{
    		for(char alphaChar:alphabet){
    			if(alphaChar==lchar){
    				if(l_system.draw(lchar)){
    					lines.push_back(Line2D(Point2D(currentx,currenty),Point2D(currentx+std::cos(currentAngle),currenty+std::sin(currentAngle)),figColor::Color(roundToInt(lijnKleur[0]*255),roundToInt(lijnKleur[1]*255),roundToInt(lijnKleur[2]*255))));
    				}
    				currentx=currentx+std::cos(currentAngle);
    				currenty=currenty+std::sin(currentAngle);
    				}
    			}
    		}
    }
    std::cout<<"lines created"<<std::endl;

	return lines;
}


