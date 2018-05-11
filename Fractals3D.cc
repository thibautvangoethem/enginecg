/*
 * Fractals3D.cc
 *
 *  Created on: Apr 17, 2018
 *      Author: thibaut
 */

#include "Fractals3D.h"
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

Fractals3D::Fractals3D() {
	// TODO Auto-generated constructor stub

}

Fractals3D::~Fractals3D() {
	// TODO Auto-generated destructor stub

}

void Fractals3D::generateFractal(figure3D& fig, std::vector<figure3D>& fractal,const int nr_iterations, const double scale){
	if(fractal.size()==0){
		fractal.push_back(fig);
	}
	if(nr_iterations>0){
		std::vector<figure3D> newfractal;
		for(figure3D frac:fractal){
			for(unsigned int i=0;i<fig.points.size();i++){
				figure3D newfig =fig;
				newfig.scaleFigure(1/scale);
				Vector3D translate=frac.points[i]-newfig.points[i];
				newfig.translate(translate);
				newfractal.push_back(newfig);
			}
		}

		fractal=newfractal;
		if(nr_iterations>0){
			std::vector<figure3D> newerfractal;
			for(figure3D tempfig:fractal){
				std::vector<figure3D> newnewfractal;
				Fractals3D::generateFractal(tempfig,newnewfractal,nr_iterations-1,scale);
				for(figure3D i:newnewfractal){
					newerfractal.push_back(i);
				}
			}
			fractal=newerfractal;
		}
	}
}

void Fractals3D::createMengerSponge(figure3D& fig, int nr_iterations){
	std::vector<figure3D> fractal;
	if(fractal.size()==0){
		fractal.push_back(fig);
	}
	while(nr_iterations>0){
		if(fractal.size()==1){
			fractal=Fractals3D::mengerAid(fig);
		}else{
			std::vector<figure3D> newfractal;
			for(figure3D mengercube:fractal){
				std::vector<figure3D> newcube=mengerAid(mengercube);
				for(figure3D& fig:newcube){
					newfractal.push_back(fig);
				}

			}
			fractal=newfractal;
		}
		nr_iterations-- ;
	}
	fig=Engine3D::combineFigures(fractal);
}
std::vector<figure3D> Fractals3D::mengerAid(figure3D fig){
	std::vector<figure3D> menger;
	figure3D newcube=fig;
	double scalefactor=1.0/3.0;
	newcube.scaleFigure(scalefactor);
	double trans=2.0/3.0;
	Vector3D vec=Vector3D::vector(trans,trans,-trans);
	newcube.translate(vec);
	menger.push_back(newcube);
	vec=Vector3D::vector(-trans,0,0);
	newcube.translate(vec);
	menger.push_back(newcube);
	newcube.translate(vec);
	menger.push_back(newcube);
	vec=Vector3D::vector(0,-trans,0);
	newcube.translate(vec);
	menger.push_back(newcube);
	newcube.translate(vec);
	menger.push_back(newcube);
	vec=Vector3D::vector(trans,0,0);
	newcube.translate(vec);
	menger.push_back(newcube);
	newcube.translate(vec);
	menger.push_back(newcube);
	vec=Vector3D::vector(0,trans,0);
	newcube.translate(vec);
	menger.push_back(newcube);
	newcube.translate(vec);
	vec=Vector3D::vector(0,0,trans);
	newcube.translate(vec);
	menger.push_back(newcube);
	vec=Vector3D::vector(-2*trans,0,0);
	newcube.translate(vec);
	menger.push_back(newcube);
	vec=Vector3D::vector(0,-2*trans,0);
	newcube.translate(vec);
	menger.push_back(newcube);
	vec=Vector3D::vector(2*trans,0,0);
	newcube.translate(vec);
	menger.push_back(newcube);
	vec=Vector3D::vector(0,2*trans,0);
	newcube.translate(vec);
	vec=Vector3D::vector(0,0,trans);
	newcube.translate(vec);
	menger.push_back(newcube);
	vec=Vector3D::vector(-trans,0,0);
	newcube.translate(vec);
	menger.push_back(newcube);
	newcube.translate(vec);
	menger.push_back(newcube);
	vec=Vector3D::vector(0,-trans,0);
	newcube.translate(vec);
	menger.push_back(newcube);
	newcube.translate(vec);
	menger.push_back(newcube);
	vec=Vector3D::vector(trans,0,0);
	newcube.translate(vec);
	menger.push_back(newcube);
	newcube.translate(vec);
	menger.push_back(newcube);
	vec=Vector3D::vector(0,trans,0);
	newcube.translate(vec);
	menger.push_back(newcube);
	newcube.translate(vec);
	return menger;
}
