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
#include <limits>

class Dragon: public Character {

private:
	int EnemyAproxLife;
	int DamageDealt;
	Character* Enemy;

public:

	std::list<Action> AtackActions;

	enum {
		FUERADERANGO = 50,
		BLOODIED = 70,
		ATAQUE = 100,
		MAXMOVPORTURNO = 1,
		MAXATKPORTURNO = 1
	};

	Dragon(int X, int Y, SquareGrid* Grid, Character* enemy) :
			Character(X, Y, Grid) {
		//Conocimiento, Velocidad del agente
		this->setSpeed(6);
		this->setLife(200);
		this->EnemyAproxLife = std::numeric_limits<int>::max();
		this->DamageDealt = 0;
		this->Enemy = enemy;

		Action Bite;
		Bite.actionType = ATTACK;
		Bite.type = NONE;
		Bite.Vstype = AC;
		Bite.MAXvalue = 18;
		Bite.name = BITE;
		this->AtackActions.push_back(Bite);

		Action Fury;
		Fury.actionType = ATTACK;
		Fury.type = NONE;
		Fury.Vstype = AC;
		Fury.MAXvalue = 42;
		Fury.name = FURY;
		this->AtackActions.push_back(Fury);

		Action Claw;
		Claw.actionType = ATTACK;
		Claw.type = NONE;
		Claw.Vstype = AC;
		Claw.MAXvalue = 12;
		Claw.name = CLAW;
		this->AtackActions.push_back(Claw);

	}

	int Utility(std::list<Action> Acciones) {
		int result = 0;
		if (Enemy->Dead()) {
			result = std::numeric_limits<int>::max();
			return result;
		}

		if (Enemy->Bloodied()) {
			result += BLOODIED;
		} else {
			result -= BLOODIED;
		}

		if (this->Bloodied()) {
			result -= BLOODIED;
		} else {
			result += BLOODIED;
		}

		Action null;
		null.actionType = -1;
		for (std::list<Action>::iterator i = Acciones.begin();
				i != Acciones.end(); ++i) {
			switch ((*i).actionType) {
			case MOVEMENT:
				null = (*i);
				if (Adjacent((*i).goalX, (*i).goalY, this->Enemy->getPosX(),
						this->Enemy->getPosY())) {
					result += FUERADERANGO;
				} else {
					result -= FUERADERANGO;
				}
				break;
			case ATTACK:
				if (null.actionType == -1) {
					if (this->isAdjacentTo(this->Enemy->getPosX(),
							this->Enemy->getPosY())) {
						result += ATAQUE;
						result += (*i).MAXvalue;
					} else {
						result -= ATAQUE;
					}

				} else {
					if (Adjacent((*i).goalX, (*i).goalY, this->Enemy->getPosX(),
							this->Enemy->getPosY())) {
						result += ATAQUE;
						result += (*i).MAXvalue;
					} else {
						result -= ATAQUE;
					}

				}
				break;
			default:
				break;
			}
		}

		return result;
	}

	std::list<Action> turn() {

		//Actualizar las probabilidades de las acciones del enemigo
		//armar listas
		std::list<std::list<Action> > ListadeListas;

		//Atk
		if (this->isAdjacentTo(Enemy->getPosX(), Enemy->getPosY())) {
			for (std::list<Action>::iterator i = AtackActions.begin();
					i != AtackActions.end(); ++i) {

				if ((*i).actionType == ATTACK) {
					std::list<Action> tempList;
					tempList.push_front(*i);
					ListadeListas.push_back(tempList);
				}
			}
		}

		//Atk+mov
		if (this->isAdjacentTo(Enemy->getPosX(), Enemy->getPosY())) {
			for (std::list<Action>::iterator i = AtackActions.begin();
					i != AtackActions.end(); ++i) {
				//insertar movimiento
				for (int x = this->getPosX() - this->getSpeed();
						x <= this->getPosX() + this->getSpeed(); x++) {
					if (x >= 0 && x < this->getGrid()->getWidth()) {
						for (int y = this->getPosY() - this->getSpeed();
								y <= this->getPosY() + this->getSpeed(); y++) {
							if (y >= 0 && y < this->getGrid()->getHeight()) {
								if (this->validMove(x, y)) {
									std::list<Action> tempList;
									tempList.push_back(*i);
									Action movimiento;
									movimiento.actionType = MOVEMENT;
									movimiento.goalX = x;
									movimiento.goalY = y;
									tempList.push_front(movimiento);
									ListadeListas.push_back(tempList);
								}
							}
						}
					}
				}
			}
		}

		//Mov
		//insertar movimiento
		for (int x = this->getPosX() - this->getSpeed();
				x <= this->getPosX() + this->getSpeed(); x++) {
			if (x >= 0) {
				for (int y = this->getPosY() - this->getSpeed();
						y <= this->getPosY() + this->getSpeed(); y++) {
					if (y >= 0) {
						if (this->validMove(x, y)) {
							std::list<Action> tempList;
							Action movimiento;
							movimiento.actionType = MOVEMENT;
							movimiento.goalX = x;
							movimiento.goalY = y;
							tempList.push_back(movimiento);
							ListadeListas.push_back(tempList);
						}
					}
				}
			}
		}

		//Mov+atk
		for (int x = this->getPosX() - this->getSpeed();
				x <= this->getPosX() + this->getSpeed(); x++) {
			if (x >= 0) {
				for (int y = this->getPosY() - this->getSpeed();
						y <= this->getPosY() + this->getSpeed(); y++) {
					if (y >= 0) {
						if (this->validMove(x, y)) {
							if (Adjacent(x, y, Enemy->getPosX(),
									Enemy->getPosY())) {
								for (std::list<Action>::iterator i =
										AtackActions.begin();
										i != AtackActions.end(); ++i) {
									if ((*i).actionType == ATTACK) {
										std::list<Action> tempList;
										Action movimiento;
										movimiento.actionType = MOVEMENT;
										movimiento.goalX = x;
										movimiento.goalY = y;
										tempList.push_back(movimiento);
										tempList.push_back(*i);
										ListadeListas.push_back(tempList);
									}
								}
							}
						}
					}
				}
			}
		}

		//evaluar utilidad
		std::list<Action> aux;
		int current;
		std::cout << "El agente calcula " << ListadeListas.size()
				<< " posibles jugadas." << std::endl;

		for (std::list<std::list<Action> >::iterator i = ListadeListas.begin();
				i != ListadeListas.end(); ++i) {
			if (i == ListadeListas.begin()) {
				aux = (*i);
				current = Utility(aux);
			} else {
				if (Utility((*i)) >= current) {
					aux = (*i);
					current = Utility((*i));
				}
			}
		}
		//ejecutar ataques para accion de mayor utilidad
		for (std::list<Action>::iterator i = aux.begin(); i != aux.end(); ++i) {
			switch ((*i).name) {
			case CLAW:
				(*i).value = 0;
				(*i).value += (4 + (rand() % 8 + 1));
				this->DamageDealt = (*i).value;
				break;
			case BITE:
				(*i).value = 0;
				(*i).value += (4 + (rand() % 8 + 1) + (rand() % 6 + 1));
				this->DamageDealt = (*i).value;
				break;
			case FURY:
				(*i).value = 0;
				(*i).value += ((4 + (rand() % 8 + 1)) + (4 + (rand() % 8 + 1))
						+ 4 + (rand() % 8 + 1) + (rand() % 6 + 1));
				this->DamageDealt = (*i).value;
				break;
			default:
				break;
			}
		}
		//retorno
		return aux;
	}

private:
};

#endif /* DRAGON_H_ */
