/*
 * Terrain.h
 *
 *  Created on: Oct 27, 2012
 *      Author: ndy
 */

#ifndef TERRAIN_H_
#define TERRAIN_H_
#include "Body.h"

class Terrain: public Body {
private:
	int Type;
	Body* onTop;
public:
	enum {
		PLAIN, DIFFICULT
	};

	Terrain(int X, int Y):Body(X,Y) {

	}

	void setType(int type) {
		this->Type = type;
	}

	Body*& upon() {
		return this->onTop;
	}

};

#endif /* TERRAIN_H_ */
