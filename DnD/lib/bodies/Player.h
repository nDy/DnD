/*
 * Player.h
 *
 *  Created on: Nov 22, 2012
 *      Author: ndy
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "Character.h"

class Player: public Character {
public:
	Player(int X, int Y, SquareGrid* Grid) :
			Character(X, Y, Grid) {
	}
private:
};

#endif /* PLAYER_H_ */
