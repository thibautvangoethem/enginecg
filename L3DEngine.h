/*
 * L3DEngine.h
 *
 *  Created on: Mar 22, 2018
 *      Author: thibaut
 */

#ifndef L3DENGINE_H_
#define L3DENGINE_H_
#include "easy_image.h"
#include "ini_configuration.h"
#include "Line2D.h"
class figure3D;

class L3DEngine {
public:
	L3DEngine();
	virtual ~L3DEngine();
	static figure3D L3D_ToFigure(const ini::Configuration &configuration, int figcount);
};



#endif /* L3DENGINE_H_ */
