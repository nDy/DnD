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
	bool visited;
public:
	enum {
		PLAIN, DIFFICULT
	};

	Terrain(int X, int Y) :
			Body(X, Y) {
		this->onTop = NULL;
		this->visited = false;
	}

	void setType(int type) {
		this->Type = type;
	}

	Body*& upon() {
		return this->onTop;
	}

	void clearVisited() {
		this->visited = false;
	}

	void visit() {
		this->visited = true;
	}

	bool wasVisited() {
		return this->visited;
	}

};

#endif /* TERRAIN_H_ */
