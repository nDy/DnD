//============================================================================
// Name        : Dungeons and Dragons: Open-Insider
// Author      : nDy & Mau
// Version     : Beta 2.0
// Description : Agente Inteligente para juego de Calabozos y Dragones.
//============================================================================

#include "../lib/game/ConsoleDnD.h"
#include "../lib/bodies/Body.h"
#include "../lib/bodies/Character.h"

#include <iostream>

void render(SquareGrid* grid) {
	std::system("clear");
	std::cout << "Dungeons and Dragons: Open-Insider" << std::endl;
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
	player = new Fighter(2, 2, grid);
	grid->getBody(player->getPosX(), player->getPosY()) = player;

	dragon = new Dragon(18, 4, grid, player);
	player->setEnemy(dragon);
	grid->getBody(dragon->getPosX(), dragon->getPosY()) = dragon;

	setMap(grid);
	dragon->cargarvalores();

	while (!player->Dead() && !dragon->Dead()) {
		render(grid);
		sleep(2);

		std::cout << "Empieza el turno del agente." << std::endl;
		std::list<Dragon::Action> accionesDeAgente = dragon->turn();
		for (std::list<Dragon::Action>::iterator i = accionesDeAgente.begin();
				i != accionesDeAgente.end(); ++i) {
			switch ((*i).actionType) {
			case Dragon::MOVEMENT:
				std::cout << "El Agente decidio tener una accion de movimiento."
						<< std::endl;
				dragon->moveTo((*i).goalX, (*i).goalY);
				break;
			case Dragon::ATTACK:
				std::cout
						<< "El Agente decidio tener una accion de ataque con la que hace: "
						<< (*i).value << " puntos de dano." << std::endl;
				player->hit((*i).value);
				break;
			default:
				break;
			}
		}
		std::cout << "Termina el turno del Agente." << std::endl;
		dragon->alimentarConocimiento(accionesDeAgente);
		if (player->Dead() || dragon->Dead()) {
			break;
		}
		render(grid);
		sleep(2);
		std::cout << "Empieza el turno del Jugador." << std::endl;
		std::list<Fighter::Action> accionesDePlayer = player->turn();
		for (std::list<Fighter::Action>::iterator i = accionesDePlayer.begin();
				i != accionesDePlayer.end(); ++i) {
			switch ((*i).actionType) {
			case Fighter::MOVEMENT:
				if (player->moveTo((*i).goalX, (*i).goalY))
					std::cout << "El Jugador se mueve." << std::endl;
				else
					std::cout << "El Jugador no se mueve." << std::endl; // Movimiento invalido
				break;
			case Fighter::ATTACK:
				std::cout << "El Jugador Realiza un ataque que hace "
						<< (*i).value << " puntos de dano." << std::endl;
				dragon->hit((*i).value);
				break;
			default:
				break;
			}
		}
	}

	dragon->actualizarvalores();
	if (player->Dead())
		std::cout << "El jugador ha muerto, el agente ha ganado" << std::endl;
	if (dragon->Dead())
		std::cout << "El agente ha muerto, el jugador ha ganado" << std::endl;

	return 0;
}
