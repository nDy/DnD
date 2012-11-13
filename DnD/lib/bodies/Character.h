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
	int speed;
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

	float heuristic_function(int currentX, int currentY, int goalX, int goalY) {
		return sqrt(pow(currentX - goalX, 2) + pow(currentY - goalY, 2));
	}

	std::list<node> getAstarPath(int goalX, int goalY) {

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
						if ( heuristic_function((*i).x, (*i).y, goalX,
										goalY)
								<= heuristic_function(aux.x, aux.y,
												goalX, goalY)) {
							aux = (*i);
							auxIterator = i;
						}
					}
				}
			}

			(*auxIterator).eliminated = true;

			closed_list.push_back(*auxIterator);

			if (heuristic_function(aux.x, aux.y, goalX, goalY) == 0)
				break;

			std::cout << closed_list.size() << std::endl;
			currentX = aux.x;
			currentY = aux.y;

		}
		//Eliminar nodos basura en la lista cerrada a partir del nodo de llegada

		return closed_list;
	}
}
;

#endif /* CHARACTER_H_ */
