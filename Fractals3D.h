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
	void generateFractal(figure3D& fig, std::vector<figure3D>& fractal,const int nr_iterations, const double scale);
};


#endif /* FRACTALS3D_H_ */
