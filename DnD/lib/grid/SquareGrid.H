/*
 * SquareGrid.H
 *
 *  Created on: Oct 27, 2012
 *      Author: ndy
 */

#ifndef SQUAREGRID_H_
#define SQUAREGRID_H_

#include "../bodies/Body.h"

class SquareGrid {
private:
	Body*** grid;
public:
	enum {STDWIDTH=20,STDHEIGHT=10};
	SquareGrid() {

		std::cout<<"Entra al constructor "<<std::endl;
		grid = new Body**[STDWIDTH];

		std::cout<<"Crea el vector de punteros dobles "<<std::endl;
		for (int var = 0; var < STDWIDTH; ++var) {
			grid[var] = new Body *[STDHEIGHT];
			for (int vartwo = 0; vartwo < STDHEIGHT; ++vartwo) {
				grid[var][vartwo] = new Body(var, vartwo);
			}
		}
	}

	Body* getBody(int x, int y){
		return grid[x][y];
	}
};

#endif /* SQUAREGRID_H_ */
