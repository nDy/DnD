/*
 * Player.h
 *
 *  Created on: Nov 22, 2012
 *      Author: ndy
 */

#ifndef WARLOCK_H_
#define WARLOCK_H_

#include "Character.h"
#include "../common/Action.h"
#include <list>

class Warlock: public Character {
private:
	std::list<Action> AvailableActionList;
public:
	Warlock(int X, int Y, SquareGrid* Grid) :
			Character(X, Y, Grid) {
	}
	void turn(){}
};

#endif /* PLAYER_H_ */
