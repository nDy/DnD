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
#include <vector>
#include <list>
class Character: public Body {
private:
	int life;
	unsigned int speed;
	SquareGrid* grid;

public:

	struct node {
		int x, y, parentX, parentY, length;
		bool eliminated;
	};

	Character(int X, int Y, SquareGrid* Grid) :
			Body(X, Y) {
		this->grid = Grid;
		this->speed = 0;
	}

	int getSpeed() {
		return this->speed;
	}

	SquareGrid* getGrid() {
		return this->grid;
	}

	void setSpeed(int Speed) {
		this->speed = Speed;
	}

	bool moveTo(int X, int Y) {
		std::list<node> path = this->getAstarPath(X, Y);
		for (std::list<Character::node>::iterator i = path.begin();
				i != path.end(); ++i) {
			std::cout << " Pos X " << (*i).x << " Pos Y " << (*i).y
					<< std::endl;
		}
		std::list<node>::iterator auxIterator = path.begin();
		int testX, testY;
		testX = (*auxIterator).x;
		testY = (*auxIterator).y;
		if ((*auxIterator).x == X && (*auxIterator).y == Y) {
			if (path.size() <= this->getSpeed()) {
				if (!grid->switchPointers(this->getPosX(), this->getPosY(), X,
						Y))
					return false;
				this->setPosX(X);
				this->setPosY(Y);
				return true;
			}
		}
		return false;

	}

	float heuristic_function(int startX, int startY, int currentX, int currentY,
			int goalX, int goalY) {
		return sqrt(
				(currentX - startX) * (currentX - startX)
						+ (currentY - startY) * (currentY - startY))
				+ sqrt(
						(currentX - goalX) * (currentX - goalX)
								+ (currentY - goalY) * (currentY - goalY));
	}

	std::list<node> getAstarPath(int goalX, int goalY) {

		this->grid->clearVisits();

		std::list<node> open_list;
		std::list<node> closed_list;

		int currentX = this->getPosX();
		int currentY = this->getPosY();

		node posA;
		int pathlength = 0;

		posA.x = currentX;
		posA.y = currentY;
		posA.parentX = currentX;
		posA.parentY = currentY;
		posA.length = pathlength;
		posA.eliminated = false;

		closed_list.push_back(posA);

		while (1
				&& pathlength
						<= this->grid->getHeight() * this->grid->getWidth()) {

			pathlength++;

			//arriba izquierda
			if ((currentX > 0) && (currentY > 0)
					&& (this->grid->getBody(currentX - 1, currentY - 1) == NULL)
					&& this->grid->getTerrain(currentX - 1, currentY - 1)->stepOver()
					&& !this->grid->getTerrain(currentX - 1, currentY - 1)->wasVisited()) {
				//meter a la lista abierta
				this->grid->getTerrain(currentX - 1, currentY - 1)->visit();
				node pos;
				pos.x = currentX - 1;
				pos.y = currentY - 1;
				pos.parentX = currentX;
				pos.parentY = currentY;
				pos.length = pathlength;
				pos.eliminated = false;
				open_list.push_back(pos);
			}

			//arriba
			if ((currentY > 0)
					&& (this->grid->getBody(currentX, currentY - 1) == NULL)
					&& this->grid->getTerrain(currentX, currentY - 1)->stepOver()
					&& !this->grid->getTerrain(currentX, currentY - 1)->wasVisited()) {
				//meter a la lista abierta
				this->grid->getTerrain(currentX, currentY - 1)->visit();
				node pos;
				pos.x = currentX;
				pos.y = currentY - 1;
				pos.parentX = currentX;
				pos.parentY = currentY;
				pos.length = pathlength;
				pos.eliminated = false;
				open_list.push_back(pos);
			}

			//arriba derecha
			if ((currentX < this->grid->getWidth()) && (currentY > 0)
					&& (this->grid->getBody(currentX + 1, currentY - 1) == NULL)
					&& this->grid->getTerrain(currentX + 1, currentY - 1)->stepOver()
					&& !this->grid->getTerrain(currentX + 1, currentY - 1)->wasVisited()) {
				//meter a la lista abierta
				this->grid->getTerrain(currentX + 1, currentY - 1)->visit();
				node pos;
				pos.x = currentX + 1;
				pos.y = currentY - 1;
				pos.parentX = currentX;
				pos.parentY = currentY;
				pos.length = pathlength;
				pos.eliminated = false;
				open_list.push_back(pos);

			}

			//derecha
			if ((currentX < this->grid->getWidth())
					&& (this->grid->getBody(currentX + 1, currentY) == NULL)
					&& this->grid->getTerrain(currentX + 1, currentY)->stepOver()
					&& !this->grid->getTerrain(currentX + 1, currentY)->wasVisited()) {
				//meter a la lista abierta
				this->grid->getTerrain(currentX + 1, currentY)->visit();
				node pos;
				pos.x = currentX - 1;
				pos.y = currentY - 1;
				pos.parentX = currentX;
				pos.parentY = currentY;
				pos.length = pathlength;
				pos.eliminated = false;
				open_list.push_back(pos);
			}

			//abajo derecha
			if ((currentX < this->grid->getWidth())
					&& (currentY < this->grid->getHeight())
					&& (this->grid->getBody(currentX + 1, currentY + 1) == NULL)
					&& this->grid->getTerrain(currentX + 1, currentY + 1)->stepOver()
					&& !this->grid->getTerrain(currentX + 1, currentY + 1)->wasVisited()) {
				//meter a la lista abierta
				this->grid->getTerrain(currentX + 1, currentY + 1)->visit();
				node pos;
				pos.x = currentX + 1;
				pos.y = currentY + 1;
				pos.parentX = currentX;
				pos.parentY = currentY;
				pos.length = pathlength;
				pos.eliminated = false;
				open_list.push_back(pos);
			}

			//abajo
			if ((currentY < this->grid->getHeight())
					&& (this->grid->getBody(currentX, currentY + 1) == NULL)
					&& this->grid->getTerrain(currentX, currentY + 1)->stepOver()
					&& !this->grid->getTerrain(currentX, currentY + 1)->wasVisited()) {
				//meter a la lista abierta
				this->grid->getTerrain(currentX, currentY + 1)->visit();
				node pos;
				pos.x = currentX;
				pos.y = currentY + 1;
				pos.parentX = currentX;
				pos.parentY = currentY;
				pos.length = pathlength;
				pos.eliminated = false;
				open_list.push_back(pos);
			}

			//abajo izquierda
			if ((currentX > 0) && (currentY < this->grid->getHeight())
					&& (this->grid->getBody(currentX - 1, currentY + 1) == NULL)
					&& this->grid->getTerrain(currentX - 1, currentY + 1)->stepOver()
					&& !this->grid->getTerrain(currentX - 1, currentY + 1)->wasVisited()) {
				//meter a la lista abierta
				this->grid->getTerrain(currentX - 1, currentY + 1)->visit();
				node pos;
				pos.x = currentX - 1;
				pos.y = currentY + 1;
				pos.parentX = currentX;
				pos.parentY = currentY;
				pos.length = pathlength;
				pos.eliminated = false;
				open_list.push_back(pos);
			}

			//izquierda
			if ((currentX > 0)
					&& (this->grid->getBody(currentX - 1, currentY) == NULL)
					&& this->grid->getTerrain(currentX - 1, currentY)->stepOver()
					&& !this->grid->getTerrain(currentX - 1, currentY)->wasVisited()) {
				//meter a la lista abierta
				this->grid->getTerrain(currentX - 1, currentY)->visit();
				node pos;
				pos.x = currentX - 1;
				pos.y = currentY;
				pos.parentX = currentX;
				pos.parentY = currentY;
				pos.length = pathlength;
				pos.eliminated = false;
				open_list.push_back(pos);
			}

//revisar el que tenga la menor F de los que se encuentran en la lista abierta

			node aux;
			std::list<node>::iterator auxIterator = open_list.begin();

			for (std::list<node>::iterator i = open_list.begin();
					i != open_list.end(); ++i) {
				if (!(*i).eliminated) {
					if (i == open_list.begin()) {
						aux = *i;
					} else {
						if (heuristic_function(this->getPosX(), this->getPosY(),
								(*i).x, (*i).y, goalX, goalY)
								<= heuristic_function(this->getPosX(),
										this->getPosY(), aux.x, aux.y, goalX,
										goalY)) {
							aux = (*i);
							auxIterator = i;
						}
					}
				}
			}

			(*auxIterator).eliminated = true;

			closed_list.push_back(*auxIterator);

			if (heuristic_function(goalX, goalY, aux.x, aux.y, goalX, goalY)
					== 0)
				break;

			currentX = aux.x;
			currentY = aux.y;

		}
		//Eliminar nodos basura en la lista cerrada a partir del nodo de llegada
		std::list<node> return_list;
		int auxX, auxY;
		for (std::list<node>::iterator i = closed_list.end();
				i != closed_list.begin(); --i) {
			if (i == closed_list.end()) {
				i--;
				return_list.push_back(*i);
				auxX = (*i).parentX;
				auxY = (*i).parentY;
			} else {
				if (auxX == (*i).x && auxY == (*i).y) {

					return_list.push_back(*i);
					auxX = (*i).parentX;
					auxY = (*i).parentY;
				}
			}
		}
		return_list.push_back(*closed_list.begin());

		return return_list;
	}
}
;

#endif /* CHARACTER_H_ */
