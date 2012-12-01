/*
 * Action.h
 *
 *  Created on: Nov 25, 2012
 *      Author: ndy
 */

#ifndef ACTION_H_
#define ACTION_H_

#include "../bodies/Body.h"
class Action {
private:
	Body* user;
	Body* target;
	short int type;
	short int Vstype;
	int value;
	int MAXvalue;
	int goalX, goalY;
public:

	enum {
		MOVEMENT, ATTACK, STR, CONST, DEX, INT, WIS, CHA
	};

	Action(Body* User, short int Type, int goalX, int goalY) {
		this->user = User;
		this->type = Type;
		this->goalX = goalX;
		this->goalY = goalY;
	}

	Action(Body* User, Body* Target, short int Type, short int VsType,
			int Value) {
		this->user = User;
		this->target = Target;
		this->Vstype = VsType;
		this->type = Type;
		this->value = Value;
	}

	short int getType() {
		return this->type;
	}
	int getGoalX() {
		return this->goalX;
	}
	int getGoalY() {
		return this->goalY;
	}
	int getMaxValue() {
		return this->MAXvalue;
	}

};

#endif /* ACTION_H_ */
