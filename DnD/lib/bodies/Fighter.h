/*
 * Player.h
 *
 *  Created on: Nov 22, 2012
 *      Author: ndy
 */

#ifndef FIGHTER_H_
#define FIGHTER_H_

#include "Character.h"
#include <list>

class Fighter: public Character {
private:
	std::list<Action> AtackActions;
public:
	Fighter(int X, int Y, SquareGrid* Grid) :
			Character(X, Y, Grid) {
	}
	void turn() {
	}
};

#endif /* FIGHTER_H_ */
