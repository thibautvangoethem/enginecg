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
	/**
	 * \brief this functions generates fractal figures recursively
	 * @param fig the original figure
	 * @param fractal a vector of figures that is going to be the fractals at the end
	 * @param nr_iterations the amount of times the fractals need to be made recursively
	 * @param scale the relative scale of a fractal to it's previous iteration
	 */
	static void generateFractal(figure3D& fig, std::vector<figure3D>& fractal,const int nr_iterations, const double scale);

	/**
	 * \brief this function creates a menger sponge and it fractals
	 * @param fig the original figure (must be a cube for a good menger sponge)
	 * @param nr_iteration the amount of times you need to replace the figures with new menger sponges
	 */
	static void createMengerSponge(figure3D& fig,int nr_iterations);

	/**
	 * \brief a simpel funtion with 1 menger sponge hardcoded
	 * @param fig the base figure that is going to be copied 16 times
	 */
	static std::vector<figure3D> mengerAid(figure3D& fig);
};


#endif /* FRACTALS3D_H_ */
