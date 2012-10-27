/*
 * SquareGrid.H
 *
 *  Created on: Oct 27, 2012
 *      Author: ndy
 */

#ifndef SQUAREGRID_H_
#define SQUAREGRID_H_

#include "../bodies/Terrain.h"

class SquareGrid {
private:
	Terrain*** grid;
public:
	enum {
		STDWIDTH = 20, STDHEIGHT = 10
	};
	SquareGrid() {

		std::cout << "Entra al constructor " << std::endl;
		grid = new Terrain**[STDWIDTH];

		std::cout << "Crea el vector de punteros dobles " << std::endl;
		for (int var = 0; var < STDWIDTH; ++var) {
			grid[var] = new Terrain *[STDHEIGHT];
			for (int vartwo = 0; vartwo < STDHEIGHT; ++vartwo) {
				grid[var][vartwo] = new Terrain(var, vartwo);
			}
		}
	}

	Body*& getBody(int x, int y) {
		return this->grid[x][y]->upon();
	}

	bool switchPointers(int startX, int startY, int finishX, int finishY) {
		if (!grid[finishX][finishY]->stepOver())
			return false;
		if (grid[finishX][finishY]->upon() != NULL) {
			return false;
		}
		grid[finishX][finishY]->upon() = grid[startX][startY]->upon();

		grid[startX][startY]->upon() = NULL;
		return true;
	}

};

#endif /* SQUAREGRID_H_ */
