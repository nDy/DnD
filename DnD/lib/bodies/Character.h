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
#include <cmath>
#include <iostream>
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

	void __getAstarPath(int**path, int X, int Y, int goalX, int goalY,
			int size) {
		std::cout << "Lanza la funcion privada" << std::endl;
		int listSize;
		int** priorityPositionList;
		double* priorityList;
		int pos = 0;

		/*if (X > 0 && Y > 0 && X < SquareGrid::STDWIDTH
		 && Y < SquareGrid::STDHEIGHT) {*/
		listSize = 8;
		/*} else {
		 listSize = 6;
		 }*/
		std::cout << "Llega a la instanciacion de los vectores de prioridad"
				<< std::endl;
		priorityList = new double[listSize];
		std::cout << "crea el vector de prioridad" << std::endl;
		priorityPositionList = new int*[listSize];
		std::cout << "crea el vector de pares prioridad" << std::endl;
		for (int var = 0; var < listSize; ++var) {
			priorityPositionList[var] = new int[2];
			std::cout << "Inicializa vector de par de prioridad" << std::endl;
		}
		std::cout << "crea los vectores de prioridad" << std::endl;

		if (X > 0 && Y > 0 && this->grid->getBody(X - 1, Y - 1) == NULL) {
			if (!this->grid->getTerrain(X - 1, Y - 1)->wasVisited()) {
				this->grid->getTerrain(X - 1, Y - 1)->visit();
				priorityPositionList[pos][0] = X - 1;
				priorityPositionList[pos][1] = X - 1;
				priorityList[pos] = sqrt(
						pow(goalX - X - 1, 2) + pow(goalY - X - 1, 2));
				pos++;
			}
		}

		if (Y > 0 && this->grid->getBody(X, Y - 1) == NULL) {
			if (!this->grid->getTerrain(X, Y - 1)->wasVisited()) {
				this->grid->getTerrain(X, Y - 1)->visit();
				priorityPositionList[pos][0] = X;
				priorityPositionList[pos][1] = Y - 1;
				priorityList[pos] = sqrt(
						pow(goalX - X, 2) + pow(goalY - Y - 1, 2));
				pos++;
			}
		}

		if (X < SquareGrid::STDWIDTH&& Y > 0
		&& this->grid->getBody(X + 1, Y - 1) == NULL) {if(X > 0 && Y > 0 && this->grid->getBody(X + 1, Y - 1) == NULL) {
			if (!this->grid->getTerrain(X + 1, Y - 1)->wasVisited()) {
				this->grid->getTerrain(X + 1, Y - 1)->visit();
				priorityPositionList[pos][0] = X + 1;
				priorityPositionList[pos][1] = Y - 1;
				priorityList[pos] = sqrt(
				pow(goalX - X + 1, 2) + pow(goalY - Y - 1, 2));
				pos++;
			}
		}

		if (X < SquareGrid::STDWIDTH && this->grid->getBody(X + 1, Y) == NULL) {
			if (X > 0 && Y > 0 && this->grid->getBody(X + 1, Y) == NULL) {
				if (!this->grid->getTerrain(X + 1, Y)->wasVisited()) {
					this->grid->getTerrain(X + 1, Y)->visit();
					priorityPositionList[pos][0] = X + 1;
					priorityPositionList[pos][1] = Y;
					priorityList[pos] = sqrt(
					pow(goalX - X + 1, 2) + pow(goalY - Y, 2));
					pos++;
				}
			}
		}

		if (X < SquareGrid::STDWIDTH&& Y < SquareGrid::STDHEIGHT
		&& this->grid->getBody(X + 1, Y + 1) == NULL) {if (X > 0 && Y > 0 && this->grid->getBody(X + 1, Y + 1) == NULL) {
				if (!this->grid->getTerrain(X + 1, Y + 1)->wasVisited()) {
					this->grid->getTerrain(X + 1, Y + 1)->visit();
					priorityPositionList[pos][0] = X + 1;
					priorityPositionList[pos][1] = Y + 1;
					priorityList[pos] = sqrt(
					pow(goalX - X + 1, 2) + pow(goalY - Y + 1, 2));
					pos++;
				}
			}
		}

		if (Y < SquareGrid::STDHEIGHT && this->grid->getBody(X, Y + 1) == NULL) {
			if (X > 0 && Y > 0 && this->grid->getBody(X, Y + 1) == NULL) {
				if (!this->grid->getTerrain(X, Y + 1)->wasVisited()) {
					this->grid->getTerrain(X, Y + 1)->visit();
					priorityPositionList[pos][0] = X;
					priorityPositionList[pos][1] = Y + 1;
					priorityList[pos] = sqrt(
					pow(goalX - X, 2) + pow(goalY - Y + 1, 2));
					pos++;
				}
			}
		}

		if (X > 0&& Y < SquareGrid::STDHEIGHT
		&& this->grid->getBody(X - 1, Y + 1) == NULL) {if (X > 0 && Y > 0 && this->grid->getBody(X - 1, Y + 1) == NULL) {
				if (!this->grid->getTerrain(X - 1, Y + 1)->wasVisited()) {
					this->grid->getTerrain(X - 1, Y + 1)->visit();
					priorityPositionList[pos][0] = X - 1;
					priorityPositionList[pos][1] = Y + 1;
					priorityList[pos] = sqrt(
					pow(goalX - X - 1, 2) + pow(goalY - Y + 1, 2));
					pos++;
				}
			}
		}

		if (X > 0 && this->grid->getBody(X - 1, Y) == NULL) {
			if (X > 0 && Y > 0 && this->grid->getBody(X - 1, Y) == NULL) {
				if (!this->grid->getTerrain(X - 1, Y)->wasVisited()) {
					this->grid->getTerrain(X - 1, Y)->visit();
					priorityPositionList[pos][0] = X - 1;
					priorityPositionList[pos][1] = Y;
					priorityList[pos] = sqrt(
					pow(goalX - X - 1, 2) + pow(goalY - Y, 2));
					pos++;
				}
			}
		}
		std::cout << "revisa los espacios adyacentes" << std::endl;
		//ordenar
		for (int i = 0; i < listSize; ++i) {
			for (int j = i + 1; j < listSize; ++j) {
				if (priorityList[i] > priorityList[j])
				for (int k = j; k > 0; --k) {
					double temp = priorityList[k];
					int tempx = priorityPositionList[k][0];
					int tempy = priorityPositionList[k][1];
					priorityList[k] = priorityList[k - 1];
					priorityPositionList[k][0] =
					priorityPositionList[k - 1][0];
					priorityPositionList[k][1] =
					priorityPositionList[k - 1][1];
					priorityList[k - 1] = temp;
					priorityPositionList[k - 1][0] = tempx;
					priorityPositionList[k - 1][1] = tempy;
				}
			}
		}

		if (priorityList[0] == 0) {
			path = new int*[size];
			for (int var = 0; var < size; ++var) {
				path[var] = new int[2];
			}
			path[size - 1][0] = priorityPositionList[0][0];
			path[size - 1][1] = priorityPositionList[0][1];
		} else {
			for (int var = 0; var < pos; ++var) {
				__getAstarPath(path, priorityPositionList[var][0],
				priorityPositionList[var][1], goalX, goalY, size + 1);
				if (path != NULL) {
					path[size - 1][0] = priorityPositionList[var][0];
					path[size - 1][1] = priorityPositionList[var][1];
					break;
				}
			}
		}
	}
}
int** getAstarPath(int X, int Y) {
	std::cout << "lanza la interfaz" << std::endl;
	int** path;
	path = NULL;
	std::cout << "se trata de lanzar la funcion privada" << std::endl;
	__getAstarPath(path, this->getPosX(), this->getPosY(), X, Y, 0);
	return path;
}
}
;

#endif /* CHARACTER_H_ */
