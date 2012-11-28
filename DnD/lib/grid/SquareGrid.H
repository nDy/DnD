/*
 * SquareGrid.H
 *
 *  Created on: Oct 27, 2012
 *      Author: ndy
 */

#ifndef SQUAREGRID_H_
#define SQUAREGRID_H_

#include <cstdlib>
#include "../bodies/Terrain.h"

class SquareGrid {
private:
	Terrain*** grid;
	int width;
	int height;
public:
	enum {
		STDWIDTH = 20, STDHEIGHT = 10
	};

	SquareGrid() {

		grid = new Terrain**[STDWIDTH];

		width = STDWIDTH;
		height = STDHEIGHT;

		for (int var = 0; var < STDWIDTH; ++var) {
			grid[var] = new Terrain *[STDHEIGHT];
			for (int vartwo = 0; vartwo < STDHEIGHT; ++vartwo) {
				grid[var][vartwo] = new Terrain(var, vartwo);
			}
		}

	}

	int getWidth() {
		return this->width;
	}

	int getHeight() {
		return this->height;
	}

	Body*& getBody(int x, int y) {
		return this->grid[x][y]->upon();
	}

	Terrain*& getTerrain(int x, int y) {
		return this->grid[x][y];
	}

	bool switchPointers(int startX, int startY, int finishX, int finishY) {
		if (!grid[finishX][finishY]->stepOver())
			return false;
		if (this->getBody(finishX,finishY) != NULL) {
			return false;
		}
		this->getBody(finishX,finishY) = this->getBody(startX,startY);

		this->getBody(startX,startY) = NULL;
		return true;
	}

	void clearVisits() {
		for (int varH = 0; varH < this->getHeight(); ++varH) {
			for (int varW = 0; varW < this->getWidth(); ++varW) {
				this->getTerrain(varW, varH)->clearVisited();
			}
		}
	}

};

#endif /* SQUAREGRID_H_ */
