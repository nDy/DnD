//============================================================================
// Name        : main.cpp
// Author      : nDy
// Version     : Alpha 1.0
// Description : DnD
//============================================================================

#include "../lib/game/DnD.h"
#include "../lib/bodies/Body.h"
#include "../lib/bodies/Character.h"
#include "../lib/grid/SquareGrid.H"

#include <iostream>

int main(int argc, char **argv) {
	SquareGrid* grid;
	grid = new SquareGrid();

	Character * player;
	player = new Character(4, 1, grid);

	/* A* TEST
	 grid->getTerrain(3,2)->stepOver(false);
	 grid->getTerrain(3,3)->stepOver(false);
	 grid->getTerrain(3,4)->stepOver(false);
	 grid->getTerrain(3,5)->stepOver(false);

	 grid->getTerrain(7,2)->stepOver(false);
	 grid->getTerrain(7,3)->stepOver(false);
	 grid->getTerrain(7,4)->stepOver(false);
	 grid->getTerrain(7,5)->stepOver(false);
	 grid->getTerrain(4,5)->stepOver(false);
	 grid->getTerrain(5,5)->stepOver(false);
	 grid->getTerrain(6,5)->stepOver(false);


	 std::list<Character::node> path = player->getAstarPath(9, 8);
	 std::cout
	 << "Al llenarse la lista del camino, se pueden ver en ella las propiedades que fueron declaradas"
	 << std::endl;
	 std::cout
	 << " en el vertice, en caso de querer revisar el padre de cada uno de los nodos podria hacerse usando"
	 << std::endl;
	 std::cout << "el valor parentX y parent Y de la estructura node."
	 << std::endl;
	 for (std::list<Character::node>::iterator i = path.begin(); i != path.end();
	 ++i) {
	 std::cout << " Pos X " << (*i).x << " Pos Y " << (*i).y << std::endl;
	 }

	 END OF TEST
	 */
	return 0;
}
