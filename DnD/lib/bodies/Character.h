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
#include "cmath"

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

	void __getAstarPath(int**, int X, int Y, int goalX, int goalY, int size) {
		int listSize;
		int** priorityPositionList;
		double* priorityList;
		int pos = 0;

		if (x > 0 && y > 0 && x < SquareGrid::STDWIDTH
				&& y < SquareGrid::STDHEIGHT) {
			listSize = 8;
		} else {
			listSize = 6;
		}

		priorityList = new double[listSize];
		priorityPositionList = new int[listSize][2];

		if (x > 0 && y > 0 && this->grid->getBody(x - 1, y - 1) == NULL) {
			if (!this->grid->getTerrain(x - 1, y - 1)->wasVisited()) {
				this->grid->getTerrain(x - 1, y - 1)->visit();
				priorityPositionList[pos][0] = x - 1;
				priorityPositionList[pos][1] = y - 1;
				priorityList[pos] = sqrt(
						pow(goalX - x - 1, 2) + pow(goalY - y - 1, 2));
				pos++;
			}
		}

		if (y > 0 && this->grid->getBody(x, y - 1) == NULL) {
			if (!this->grid->getTerrain(x, y - 1)->wasVisited()) {
				this->grid->getTerrain(x, y - 1)->visit();
				priorityPositionList[pos][0] = x;
				priorityPositionList[pos][1] = y - 1;
				priorityList[pos] = sqrt(
						pow(goalX - x, 2) + pow(goalY - y - 1, 2));
				pos++;
			}
		}

		if (x < SquareGrid::STDWIDTH && y > 0
				&& this->grid->getBody(x + 1, y - 1) == NULL) {
			if (x > 0 && y > 0 && this->grid->getBody(x + 1, y - 1) == NULL) {
				if (!this->grid->getTerrain(x + 1, y - 1)->wasVisited()) {
					this->grid->getTerrain(x + 1, y - 1)->visit();
					priorityPositionList[pos][0] = x + 1;
					priorityPositionList[pos][1] = y - 1;
					priorityList[pos] = sqrt(
							pow(goalX - x + 1, 2) + pow(goalY - y - 1, 2));
					pos++;
				}
			}
		}

		if (x < SquareGrid::STDWIDTH && this->grid->getBody(x + 1, y) == NULL) {
			if (x > 0 && y > 0 && this->grid->getBody(x + 1, y) == NULL) {
				if (!this->grid->getTerrain(x + 1, y)->wasVisited()) {
					this->grid->getTerrain(x + 1, y)->visit();
					priorityPositionList[pos][0] = x + 1;
					priorityPositionList[pos][1] = y;
					priorityList[pos] = sqrt(
							pow(goalX - x + 1, 2) + pow(goalY - y, 2));
					pos++;
				}
			}
		}

		if (x < SquareGrid::STDWIDTH && y < SquareGrid::STDHEIGHT
				&& this->grid->getBody(x + 1, y + 1) == NULL) {
			if (x > 0 && y > 0 && this->grid->getBody(x + 1, y + 1) == NULL) {
				if (!this->grid->getTerrain(x + 1, y + 1)->wasVisited()) {
					this->grid->getTerrain(x + 1, y + 1)->visit();
					priorityPositionList[pos][0] = x + 1;
					priorityPositionList[pos][1] = y + 1;
					priorityList[pos] = sqrt(
							pow(goalX - x + 1, 2) + pow(goalY - y + 1, 2));
					pos++;
				}
			}
		}

		if (y < SquareGrid::STDHEIGHT
				&& this->grid->getBody(x, y + 1) == NULL) {
			if (x > 0 && y > 0 && this->grid->getBody(x, y + 1) == NULL) {
				if (!this->grid->getTerrain(x, y + 1)->wasVisited()) {
					this->grid->getTerrain(x, y + 1)->visit();
					priorityPositionList[pos][0] = x;
					priorityPositionList[pos][1] = y + 1;
					priorityList[pos] = sqrt(
							pow(goalX - x, 2) + pow(goalY - y + 1, 2));
					pos++;
				}
			}
		}

		if (x > 0 && y < SquareGrid::STDHEIGHT
				&& this->grid->getBody(x - 1, y + 1) == NULL) {
			if (x > 0 && y > 0 && this->grid->getBody(x - 1, y + 1) == NULL) {
				if (!this->grid->getTerrain(x - 1, y + 1)->wasVisited()) {
					this->grid->getTerrain(x - 1, y + 1)->visit();
					priorityPositionList[pos][0] = x - 1;
					priorityPositionList[pos][1] = y + 1;
					priorityList[pos] = sqrt(
							pow(goalX - x - 1, 2) + pow(goalY - y + 1, 2));
					pos++;
				}
			}
		}

		if (x > 0 && this->grid->getBody(x - 1, y) == NULL) {
			if (x > 0 && y > 0 && this->grid->getBody(x - 1, y) == NULL) {
				if (!this->grid->getTerrain(x - 1, y)->wasVisited()) {
					this->grid->getTerrain(x - 1, y)->visit();
					priorityPositionList[pos][0] = x - 1;
					priorityPositionList[pos][1] = y;
					priorityList[pos] = sqrt(
							pow(goalX - x - 1, 2) + pow(goalY - y, 2));
					pos++;
				}
			}
		}
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

		//Aplicar __getAstarPath al nodo con mayor prioridad
		//agregar x y y al camino
	}

	int** getAstarPath() {
		int** path;

		return path;
	}

};

#endif /* CHARACTER_H_ */
