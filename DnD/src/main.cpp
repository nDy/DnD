//============================================================================
// Name        : main.cpp
// Author      : nDy
// Version     : Alpha 1.0
// Description : DnD
//============================================================================

#include "../lib/game/DnD.h"

int main(int argc, char **argv) {

	DnD* Game;

	Game = new DnD();

	return Game->Execute();

}
