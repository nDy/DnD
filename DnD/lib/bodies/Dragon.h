/*
 * Dragon.h
 *
 *  Created on: Nov 22, 2012
 *      Author: ndy
 */

#ifndef DRAGON_H_
#define DRAGON_H_

#include "Character.h"

class Dragon: public Character {
public:
	Dragon(int X, int Y, SquareGrid* Grid) :
			Character(X, Y, Grid) {
	}
private:
};

#endif /* DRAGON_H_ */
