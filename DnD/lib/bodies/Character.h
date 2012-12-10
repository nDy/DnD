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
	int maxlife;
	int currentLife;
	int speed;
	SquareGrid* grid;

public:
	enum {
		MOVEMENT,
		ATTACK,
		STR,
		CONST,
		DEX,
		INT,
		WIS,
		CHA,
		AC,
		FORT,
		WILL,
		REF,
		NONE,
		BITE,
		CLAW,
		FURY,
		CLEAVE,
		SURESTRIKE,
		REAPINGSTRIKE
	};
	struct node {
		int x, y, parentX, parentY, length;
		bool eliminated;
	};

	struct Action {
		int actionType;
		int type;
		int Vstype;
		int value;
		int MAXvalue;
		int goalX, goalY;
		int name;
	};

	Character(int X, int Y, SquareGrid* Grid) :
			Body(X, Y) {
		this->grid = Grid;
		this->speed = 0;
	}

	void setLife(int life) {
		this->currentLife = life;
	}

	void hit(int k) {
		this->currentLife -= k;
	}

	int getSpeed() {
		return this->speed;
	}

	bool Bloodied() {
		if (currentLife < maxlife / 2)
			return true;
		return false;
	}

	bool Dead() {
		if (this->currentLife <= 0)
			return true;
		return false;
	}

	SquareGrid* getGrid() {
		return this->grid;
	}

	void setSpeed(int Speed) {
		this->speed = Speed;
	}

	bool moveTo(int X, int Y) {
		if (!this->grid->getTerrain(X, Y)->stepOver())
			return false;
		std::list<node> path = this->getAstarPath(X, Y, this->getPosX(),
				this->getPosY());
		std::cout
				<< "El agente realiza una accion de movimiento que pasa por las siguientes casillas."
				<< std::endl;
		for (std::list<Character::node>::iterator i = path.begin();
				i != path.end(); ++i) {
			std::cout << " Pos X " << (*i).x << " Pos Y " << (*i).y
					<< std::endl;
		}
		std::list<node>::iterator auxIterator = path.begin();

		if ((*auxIterator).x == X && (*auxIterator).y == Y) {
			if ((int) path.size() - 1 <= this->getSpeed()) {
				if (!grid->switchPointers(this->getPosX(), this->getPosY(), X,
						Y)) {

					std::cout << "ERROR de switch pointers" << std::endl;
					;
					return false;
				}
				this->setPosX(X);
				this->setPosY(Y);
				return true;
			} else {
				std::cout << "ERROR de tama;os, el path mide " << path.size()
						<< " y la velocidad es " << this->getSpeed()
						<< std::endl;
			}
		} else {

			std::cout << "La lista no coincide con la meta" << X << " "
					<< (*auxIterator).x << " " << Y << " " << (*auxIterator).y
					<< std::endl;
			;
		}
		return false;
	}

	bool validMove(int X, int Y) {
		if (!this->grid->getTerrain(X, Y)->stepOver())
			return false;
		std::list<node> path = this->getAstarPath(X, Y, this->getPosX(),
				this->getPosY());
		std::list<node>::iterator auxIterator = path.begin();

		if ((*auxIterator).x == X && (*auxIterator).y == Y) {
			if ((int) path.size() <= this->getSpeed()) {
				return true;
			}
		}
		return false;
	}

	bool Adjacent(int X, int Y, int goalX, int goalY) {
		if (X == goalX - 1) {
			if (Y == goalY - 1 || Y == goalY || Y == goalY + 1)
				return true;
		}
		if (X == goalX) {
			if (Y == goalY - 1 || Y == goalY + 1)
				return true;
		}
		if (X == goalX + 1) {
			if (Y == goalY - 1 || Y == goalY || Y == goalY + 1)
				return true;
		}
		return false;
	}

	bool isAdjacentTo(int X, int Y) {
		if (this->getPosX() == X - 1) {
			if (this->getPosY() == Y - 1 || this->getPosY() == Y
					|| this->getPosY() == Y + 1)
				return true;
		}
		if (this->getPosX() == X) {
			if (this->getPosY() == Y - 1 || this->getPosY() == Y + 1)
				return true;

		}
		if (this->getPosX() == X + 1) {
			if (this->getPosY() == Y - 1 || this->getPosY() == Y
					|| this->getPosY() == Y + 1)
				return true;
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

	std::list<node> getAstarPath(int goalX, int goalY, int startX, int startY) {

		this->grid->clearVisits();

		std::list<node> open_list;
		std::list<node> closed_list;

		int currentX = startX;
		int currentY = startY;

		node posA;
		int pathlength = 0;

		posA.x = currentX;
		posA.y = currentY;
		posA.parentX = currentX;
		posA.parentY = currentY;
		posA.length = pathlength;
		posA.eliminated = false;

		closed_list.push_back(posA);

		while (pathlength <= this->grid->getHeight() * this->grid->getWidth()) {

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
			if ((currentX < this->grid->getWidth() - 1) && (currentY > 0)
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
			if ((currentX < this->grid->getWidth() - 1)
					&& (this->grid->getBody(currentX + 1, currentY) == NULL)
					&& this->grid->getTerrain(currentX + 1, currentY)->stepOver()
					&& !this->grid->getTerrain(currentX + 1, currentY)->wasVisited()) {
				//meter a la lista abierta
				this->grid->getTerrain(currentX + 1, currentY)->visit();
				node pos;
				pos.x = currentX + 1;
				pos.y = currentY;
				pos.parentX = currentX;
				pos.parentY = currentY;
				pos.length = pathlength;
				pos.eliminated = false;
				open_list.push_back(pos);
			}

			//abajo derecha
			if ((currentX < this->grid->getWidth() - 1)
					&& (currentY < this->grid->getHeight() - 1)
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
			if ((currentY < this->grid->getHeight() - 1)
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
			if ((currentX > 0) && (currentY < this->grid->getHeight() - 1)
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
