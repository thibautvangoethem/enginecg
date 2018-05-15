/*
 * Fractals3D.h
 *
 *  Created on: Apr 17, 2018
 *      Author: thibaut
 */

#ifndef FRACTALS3D_H_
#define FRACTALS3D_H_
#include "figure3D.h"
#include "face3D.h"
#include "Color.h"
#include "vector3d.h"
#include "ini_configuration.h"
#include <vector>
#include <list>
#include <cmath>
#include "Line2D.h"

class Fractals3D {
public:
	Fractals3D();
	virtual ~Fractals3D();
	static void generateFractal(figure3D& fig, std::vector<figure3D>& fractal,const int nr_iterations, const double scale);
	static void createMengerSponge(figure3D& fig,int nr_iterations);
	static std::vector<figure3D> mengerAid(figure3D& fig);
};


#endif /* FRACTALS3D_H_ */
