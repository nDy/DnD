/*
 * Character.h
 *
 *  Created on: Oct 27, 2012
 *      Author: ndy
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Body.h"
#include "../grid/SquareGrid.H"

class Character: public Body {
private:
	int life;
	int speed;
	SquareGrid* grid;

public:
	Character(int X, int Y, SquareGrid* Grid) :
			Body(X, Y) {
		this->grid = Grid;
		this->speed = 0;
	}

	void setSpeed(int Speed) {
		this->speed = Speed;
	}

	bool moveTo(int X, int Y) {
		if (!grid->switchPointers(this->getPosX(), this->getPosY(), X, Y))
			return false;
		this->setPosX(X);
		this->setPosY(Y);
		return true;
	}

	void __getAstarPath(int**,int x, int y){
		//Revisar prioridad
		//Aplicar __getAstarPath al nodo con mayor prioridad
		//agregar x y y al camino
	}

	int** getAstarPath() {
		int** path;




		return path;
	}

};

#endif /* CHARACTER_H_ */
