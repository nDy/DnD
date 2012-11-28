/*
 * Dragon.h
 *
 *  Created on: Nov 22, 2012
 *      Author: ndy
 */

#ifndef DRAGON_H_
#define DRAGON_H_

#include "Character.h"
#include <cstdlib>

class Dragon: public Character {
public:
	Dragon(int X, int Y, SquareGrid* Grid) :
			Character(X, Y, Grid) {
		this->setSpeed(6);
	}

	float Utility(){

	}

	void turn() {
		int auxX = rand() % this->getSpeed(); //ubicacion deseada del movimiento
		int auxY = rand() % this->getSpeed(); //ubicacion deseada del movimiento
		int signX = rand() % 2;
		int signY = rand() % 2;

		if (signX == 0) {
			if (this->getPosX() - auxX >= 0) {
				auxX = this->getPosX() - auxX;
			} else {
				auxX = this->getPosX() + auxX;
			}
		} else {
			if (this->getPosX() + auxX < this->getGrid()->getWidth()) {
				auxX = this->getPosX() + auxX;
			} else {
				auxX = this->getPosX() - auxX;
			}
		}

		if (signY == 0) {
			if (this->getPosY() - auxY >= 0) {
				auxY = this->getPosY() - auxY;
			} else {
				auxY = this->getPosY() + auxY;
			}
		} else {
			if (this->getPosY() + auxY < this->getGrid()->getHeight()) {
				auxY = this->getPosY() + auxY;
			} else {
				auxY = this->getPosY() - auxY;
			}
		}

		if (!this->moveTo(auxX, auxY)) {
			std::cout << "Direccion invalida de movimiento" << this->getGrid()->getWidth() <<std::endl;
		}
	}

private:
};

#endif /* DRAGON_H_ */
