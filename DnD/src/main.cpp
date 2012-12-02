//============================================================================
// Name        : main.cpp
// Author      : nDy
// Version     : Alpha 1.0
// Description : DnD
//============================================================================

#include "../lib/game/ConsoleDnD.h"
#include "../lib/bodies/Body.h"
#include "../lib/bodies/Character.h"

#include <iostream>

void render(SquareGrid* grid) {
	for (int varH = 0; varH < grid->getHeight(); ++varH) {
		for (int varL = 0; varL < grid->getWidth(); ++varL) {
			if (!grid->getTerrain(varL, varH)->stepOver()) {
				std::cout << "W ";
			} else {
				if (grid->getBody(varL, varH) == NULL) {
					std::cout << ". ";
				} else {
					std::cout << "O ";
				}
			}

		}
		std::cout << std::endl;
	}
}

void setMap(SquareGrid* grid) {
	grid->getTerrain(5, 2)->stepOver(false);
	grid->getTerrain(5, 3)->stepOver(false);
	grid->getTerrain(5, 4)->stepOver(false);
	grid->getTerrain(5, 5)->stepOver(false);

	grid->getTerrain(2, 5)->stepOver(false);
	grid->getTerrain(3, 5)->stepOver(false);
	grid->getTerrain(4, 5)->stepOver(false);

	grid->getTerrain(6, 4)->stepOver(false);
	grid->getTerrain(7, 4)->stepOver(false);
	grid->getTerrain(8, 4)->stepOver(false);

}

int main(int argc, char **argv) {
	SquareGrid* grid;
	grid = new SquareGrid();
	Fighter* player;
	player = new Fighter(5, 1, grid);
	grid->getBody(player->getPosX(), player->getPosY()) = player;
	Dragon * dragon;
	dragon = new Dragon(2, 2, grid, player);
	grid->getBody(dragon->getPosX(), dragon->getPosY()) = dragon;

	setMap(grid);

	while (true) {
		//player->turn;
		//dragon->turn;
		std::cout << "empieza el turno" << std::endl;
		std::list<Dragon::Action> accionesDeAgente = dragon->turn();
		for (std::list<Dragon::Action>::iterator i = accionesDeAgente.begin();
				i != accionesDeAgente.end(); ++i) {
			switch ((*i).actionType) {
			case Dragon::MOVEMENT:
				std::cout << "Hay una accion de movimiento" << std::endl;
			case Dragon::ATTACK:
				std::cout << "Hay una accion de ataque de " <<(*i).value<< std::endl;
				break;
			default:
				break;
			}
		}
		for (std::list<Dragon::Action>::iterator i = accionesDeAgente.begin();
				i != accionesDeAgente.end(); ++i) {
			switch ((*i).actionType) {
			case Dragon::MOVEMENT:
				dragon->moveTo((*i).goalX, (*i).goalY);
			case Dragon::ATTACK:
				player->hit((*i).value);
				break;
			default:
				break;
			}
		}
		std::cout << "pasa el turno" << std::endl;
		render(grid);
		sleep(2);
	}
	return 0;
}

/* A* TEST
 SquareGrid* grid;
 grid = new SquareGrid();

 Character * player;
 player = new Character(2, 2, grid);
 grid->getTerrain(5, 2)->stepOver(false);
 grid->getTerrain(5, 3)->stepOver(false);
 grid->getTerrain(5, 4)->stepOver(false);
 grid->getTerrain(5, 5)->stepOver(false);

 grid->getTerrain(2, 5)->stepOver(false);
 grid->getTerrain(3, 5)->stepOver(false);
 grid->getTerrain(4, 5)->stepOver(false);

 std::list<Character::node> path = player->getAstarPath(7, 7);
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

