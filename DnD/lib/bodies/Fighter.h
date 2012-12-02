/*
 * Player.h
 *
 *  Created on: Nov 22, 2012
 *      Author: ndy
 */

#ifndef FIGHTER_H_
#define FIGHTER_H_

#include "Character.h"
#include <list>

class Fighter: public Character {
private:
	std::list<Action> AtackActions;
	Character* Enemy;
public:
	Fighter(int X, int Y, SquareGrid* Grid) :
			Character(X, Y, Grid) {
		this->setLife(50);
		this->setSpeed(5);

		Action Cleave;
		Cleave.actionType = ATTACK;
		Cleave.type = STR;
		Cleave.Vstype = AC;
		Cleave.MAXvalue = 15;
		Cleave.name = CLEAVE;
		this->AtackActions.push_back(Cleave);

		Action SureStrike;
		SureStrike.actionType = ATTACK;
		SureStrike.type = STR;
		SureStrike.Vstype = AC;
		SureStrike.MAXvalue = 10;
		SureStrike.name = SURESTRIKE;
		this->AtackActions.push_back(SureStrike);

		Action ReapingStrike;
		ReapingStrike.actionType = ATTACK;
		ReapingStrike.type = STR;
		ReapingStrike.Vstype = AC;
		ReapingStrike.MAXvalue = 15;
		ReapingStrike.name = REAPINGSTRIKE;
		this->AtackActions.push_back(ReapingStrike);

	}

	void setEnemy(Character* enemy) {
		this->Enemy = enemy;
	}

	std::list<Action> turn() {
		int x, y, menu;
		bool attacked = false;
		bool moved = false;
		bool endturn = false;
		std::list<Action> turno;
		while (!endturn) {
			std::cout << "Que desea hacer?" << std::endl;
			std::cout << "1.-Realizar accion de movimiento." << std::endl;
			std::cout << "2.-Realizar accion de ataque." << std::endl;
			std::cout << "2.-Terminar turno." << std::endl;
			std::cin >> menu;
			switch (menu) {
			case 1:
				if (!moved) {
					std::cout << "Introduzca coordenada X del movimiento"
							<< std::endl;
					std::cin >> x;
					std::cout << "Introduzca coordenada Y del movimiento"
							<< std::endl;
					std::cin >> y;
					Action movimiento;
					movimiento.actionType = MOVEMENT;
					movimiento.goalX = x;
					movimiento.goalY = y;
					turno.push_back(movimiento);
					moved = true;
					if (attacked && moved)
						endturn = true;
				} else {
					std::cout
							<< "Solo esta permitido realizar una accion de movimiento por turno"
							<< std::endl;
				}
				break;
			case 2:
				if (!attacked) {
					int auxx, auxy;
					bool moved = false;

					for (std::list<Action>::iterator i = turno.begin();
							i != turno.end(); ++i) {
						if ((*i).actionType == Fighter::MOVEMENT) {
							moved = true;
						}
					}

					if (moved) {
						auxx = x;
						auxy = y;
					} else {
						auxx = this->getPosX();
						auxy = this->getPosY();
					}

					if (this->Adjacent(auxx, auxy, Enemy->getPosX(),
							Enemy->getPosY())) {
						std::cout << "Que ataque desea realizar?" << std::endl;
						std::cout << "1.-Cleave." << std::endl;
						std::cout << "2.-Sure Strike." << std::endl;
						std::cout << "3.-Reaping Strike." << std::endl;
						int atk;
						std::cin >> atk;
						switch (atk) {
						case 1:
							for (std::list<Action>::iterator i =
									AtackActions.begin();
									i != AtackActions.end(); ++i) {
								if ((*i).name == Fighter::CLEAVE) {
									turno.push_front(*i);
								}
							}

							break;
						case 2:
							for (std::list<Action>::iterator i =
									AtackActions.begin();
									i != AtackActions.end(); ++i) {
								if ((*i).name == Fighter::SURESTRIKE) {
									turno.push_front(*i);
								}
							}
							break;
						case 3:
							for (std::list<Action>::iterator i =
									AtackActions.begin();
									i != AtackActions.end(); ++i) {
								if ((*i).name == Fighter::REAPINGSTRIKE) {
									turno.push_front(*i);
								}
							}
							break;
						default:
							break;
						}
					} else {
						std::cout
								<< "El enemigo no esta dentro del rango de ataque."
								<< std::endl;
					}
					attacked = true;
					if (attacked && moved)
						endturn = true;
				} else {
					std::cout
							<< "Solo esta permitido realizar una accion de ataque por turno"
							<< std::endl;
				}
				break;
			case 3:
				endturn = true;
				break;
			default:
				break;
			}
		}
//calcular los ataques del turno
		for (std::list<Action>::iterator i = turno.begin(); i != turno.end();
				++i) {
			switch ((*i).name) {
			case CLEAVE:
				(*i).value = 0;
				(*i).value += (5 + (rand() % 10 + 1));
				break;
			case SURESTRIKE:
				(*i).value = 0;
				(*i).value += (rand() % 10 + 1);
				break;
			case REAPINGSTRIKE:
				(*i).value = 0;
				(*i).value += (5 + (rand() % 10 + 1));
				break;
			default:
				break;
			}
		}
		return turno;
	}
}
;

#endif /* FIGHTER_H_ */
