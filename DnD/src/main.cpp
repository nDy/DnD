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
	Fighter* player;
	Dragon * dragon;
	grid = new SquareGrid();
	player = new Fighter(2, 1, grid, dragon);
	grid->getBody(player->getPosX(), player->getPosY()) = player;

	dragon = new Dragon(2, 2, grid, player);
	grid->getBody(dragon->getPosX(), dragon->getPosY()) = dragon;

	setMap(grid);

	while (!player->Dead()) {
		render(grid);
		sleep(2);

		std::cout << "Empieza el turno del agente." << std::endl;
		std::list<Dragon::Action> accionesDeAgente = dragon->turn();
		for (std::list<Dragon::Action>::iterator i = accionesDeAgente.begin();
				i != accionesDeAgente.end(); ++i) {
			switch ((*i).actionType) {
			case Dragon::MOVEMENT:
				std::cout << "Hay una accion de movimiento" << std::endl;
				break;
			case Dragon::ATTACK:
				std::cout << "Hay una accion de ataque de " << (*i).value
						<< std::endl;
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
				break;
			case Dragon::ATTACK:
				player->hit((*i).value);
				break;
			default:
				break;
			}
		}
		std::cout << "Termina el turno del agente." << std::endl;
		render(grid);
		sleep(2);
		std::cout << "empieza el turno del player" << std::endl;
		std::list<Fighter::Action> accionesDePlayer = player->turn();
		for (std::list<Fighter::Action>::iterator i = accionesDePlayer.begin();
				i != accionesDePlayer.end(); ++i) {
			switch ((*i).actionType) {
			case Fighter::MOVEMENT:
				if (player->moveTo((*i).goalX, (*i).goalY))
					std::cout << "El player se mueve" << std::endl;
				else
					std::cout << "El player no se mueve" << std::endl;
				break;
			case Fighter::ATTACK:
				dragon->hit((*i).value);
				break;
			default:
				break;
			}
		}
	}
	std::cout << "El player ha muerto, el agente ha ganado" << std::endl;
	return 0;
}
