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
public:
	struct Action {
		int actionType;
		int type;
		int Vstype;
		int value;
		int MAXvalue;
		int goalX, goalY;
	};
private:
	std::list<Action> AtackActions;
	int EnemyAproxLife;
	int DamageDealt;
	Character* Enemy;

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
		NONE
	};

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
		this->EnemyAproxLife = std::numeric_limits<int>::max();
		this->DamageDealt = 0;
		this->Enemy = enemy;
		/*Action Claw(this, this->Enemy, ATTACK, NONE, AC,
		 12);
		 this->addAttackAction(Claw);

		 this->addAttackAction(
		 Action(this, this->Enemy, ATTACK, NONE,
		 AC, 18));
		 */
		Action Bite;
		Bite.actionType = ATTACK;
		Bite.type = NONE;
		Bite.Vstype = AC;
		Bite.MAXvalue = 22;
		this->AtackActions.push_back(Bite);

		Action Fury;
		Fury.actionType = ATTACK;
		Fury.type = NONE;
		Fury.Vstype = AC;
		Fury.MAXvalue = 42;
		this->AtackActions.push_back(Fury);

		Action Claw;
		Claw.actionType = ATTACK;
		Claw.type = NONE;
		Claw.Vstype = AC;
		Claw.MAXvalue = 12;
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

		for (std::list<Action>::iterator i = Acciones.begin();
				i != Acciones.end(); ++i) {
			switch ((*i).actionType) {
			case MOVEMENT:
				if (getAstarPath((*i).goalX, (*i).goalY, this->getPosX(),
						this->getPosY()).size() == 2) {
					result += FUERADERANGO;
				} else {
					result -= FUERADERANGO;
				}
				break;
			case ATTACK:
				if (getAstarPath((*i).goalX, (*i).goalY, this->getPosX(),
						this->getPosY()).size() == 2) {
					result += ATAQUE;
					result += (*i).MAXvalue;
				} else {
					result -= ATAQUE;
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
		std::cout << "Arma la lista" << std::endl;
		//Atk
		std::cout << "Arma la lista" << this->AtackActions.size() << std::endl;

		for (std::list<Action>::iterator i = this->AtackActions.begin();
				i != AtackActions.end(); ++i) {
			std::cout << " Tipo " << (*i).actionType << " Max " << (*i).MAXvalue
					<< std::endl;
		}

		std::cout << "pasa el chequeo" << std::endl;

		if (getAstarPath(Enemy->getPosX(), Enemy->getPosY(), this->getPosX(),
				this->getPosY()).size() == 2) {
			for (std::list<Action>::iterator i = AtackActions.begin();
					i != AtackActions.end(); ++i) {
				/*
				 std::cout << "entra a la lista" << std::endl;

				 if ((*i).getActionType() == ATTACK) {
				 Action flag((*i));
				 std::list<Action> tempList;
				 tempList.push_front(*i);
				 ListadeListas.push_front(tempList);
				 }*/
			}
		}
		std::cout << "inserta posibles acciones de atk" << std::endl;
		//Atk+mov
		if (getAstarPath(Enemy->getPosX(), Enemy->getPosY(), this->getPosX(),
				this->getPosY()).size() == 2) {
			for (std::list<Action>::iterator i = AtackActions.begin();
					i != AtackActions.end(); ++i) {
				//insertar movimiento
				for (int x = this->getPosX() - this->getSpeed();
						x <= this->getPosX() + this->getSpeed(); x++) {
					if (x >= 0) {
						for (int y = this->getPosY() - this->getSpeed();
								y <= this->getPosY() + this->getSpeed(); y++) {
							if (y >= 0) {
								if (this->validMove(x, y)) {
									std::list<Action> tempList;
									tempList.push_front(*i);
									Action movimiento;
									//(this, MOVEMENT, x,y);
									tempList.push_front(movimiento);
									ListadeListas.push_front(tempList);
								}
							}
						}
					}
				}
			}
		}
		std::cout << "inserta posibles acciones de atk + mov" << std::endl;

		//Mov
		for (int x = this->getPosX() - this->getSpeed();
				x <= this->getPosX() + this->getSpeed(); x++) {
			if (x >= 0) {
				for (int y = this->getPosY() - this->getSpeed();
						y <= this->getPosY() + this->getSpeed(); y++) {
					if (y >= 0) {
						if (this->validMove(x, y)) {
							if (getAstarPath(Enemy->getPosX(), Enemy->getPosY(),
									x, y).size() == 2) {
								std::list<Action> tempList;
								Action movimiento;
								//(this, MOVEMENT, x, y);
								tempList.push_front(movimiento);
								ListadeListas.push_front(tempList);

							}
						}
					}
				}
			}
		}
		std::cout << "inserta posibles acciones de mov" << std::endl;

		//Mov+atk
		for (int x = this->getPosX() - this->getSpeed();
				x <= this->getPosX() + this->getSpeed(); x++) {
			if (x >= 0) {
				for (int y = this->getPosY() - this->getSpeed();
						y <= this->getPosY() + this->getSpeed(); y++) {
					if (y >= 0) {
						if (this->validMove(x, y)) {
							if (getAstarPath(Enemy->getPosX(), Enemy->getPosY(),
									x, y).size() == 2) {
								for (std::list<Action>::iterator i =
										AtackActions.begin();
										i != AtackActions.end(); ++i) {
									std::list<Action> tempList;
									tempList.push_front(*i);
									Action movimiento;
									//(this, MOVEMENT, x,y);
									tempList.push_front(movimiento);
									ListadeListas.push_front(tempList);
								}
							}
						}
					}
				}
			}
		}
		std::cout << "inserta posibles acciones de mov +atk" << std::endl;

		//evaluar utilidad
		std::list<Action> aux;
		//ejecutar mayor utilidad
	}

private:
};

#endif /* DRAGON_H_ */
