//============================================================================
// Name        : Dungeons and Dragons: Open-Insider
// Author      : nDy & Mau
// Version     : 1.0
// Description : Agente Inteligente para juego de Calabozos y Dragones.
//============================================================================

#include "../lib/game/ConsoleDnD.h"

#include <iostream>

int main(int argc, char **argv) {

	ConsoleDnD* game;

	game = new ConsoleDnD();

	while (game->isPlayerAlive() && game->isDragonAlive()) {

		game->render();

		game->PlayerLoop();

		if (!game->isPlayerAlive() || !game->isDragonAlive()) {
			break;
		}

		game->render();

		game->DragonLoop();

	}

	game->close();

	return 0;
}
