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
	int value;
public:

	enum {
		NONE, STR, CONST, DEX, INT, WIS, CHA
	};
	Action(Body* User, Body* Target, short int Type, short int VsType,
			int Value) {
		this->user = User;
		this->target = Target;
		this->type = Type;
		this->value = Value;
	}
};

#endif /* ACTION_H_ */
