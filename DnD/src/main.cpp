//============================================================================
// Name        : main.cpp
// Author      : nDy
// Version     : Alpha 1.0
// Description : DnD
//============================================================================

#include "../lib/game/DnD.h"
#include "../lib/bodies/Body.h"
#include "../lib/grid/SquareGrid.H"
#include <iostream>

int main(int argc, char **argv) {

	SquareGrid* grid;
	std::cout<<"Se crea el puntero "<<std::endl;
	grid = new SquareGrid();
	std::cout<<"Se instancia el grid "<<std::endl;

	for (int var = 0; var < 20; ++var) {
		for (int vartwo = 0; vartwo < 10; ++vartwo) {
			std::cout<<"Cuerpo que se supone debe estar en "<<var<<" "<<vartwo<<std::endl;
			std::cout<<"Se encuentra en "<<grid->getBody(var,vartwo)->getPosX()<<" "<<grid->getBody(var,vartwo)->getPosY()<<std::endl;
		}
	}

	/*
	 DnD* Game;

	 Game = new DnD();

	 return Game->Execute();
	 */
}
