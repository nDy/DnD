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
	Fighter(int X, int Y, SquareGrid* Grid, Character* enemy) :
			Character(X, Y, Grid) {
		this->setLife(50);
		this->setSpeed(5);
		this->Enemy = enemy;

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
	std::list<Action> turn() {
		int x, y, menu, moveCheck, atkCheck, attackAction;
		std::list<Action> turno;
		std::cout << "Que desea hacer?" << std::endl;
		std::cout << "1.-Realizar accion de movimiento." << std::endl;
		std::cout << "2.-Realizar accion de ataque." << std::endl;
		std::cin >> menu;
		switch (menu) {
		case 1:
			std::cout << "Introduzca coordenada X del movimiento" << std::endl;
			std::cin >> x;
			std::cout << "Introduzca coordenada Y del movimiento" << std::endl;
			std::cin >> y;
			Action movimiento;
			movimiento.actionType = MOVEMENT;
			movimiento.goalX = x;
			movimiento.goalY = y;
			turno.push_back(movimiento);
			break;
		case 2:
			std::cout << "Que ataque desea realizar?" << std::endl;
			std::cout << "1.-Cleave." << std::endl;
			std::cout << "2.-Sure Strike." << std::endl;
			std::cout << "3.-Reaping Strike." << std::endl;
			break;
		default:
			break;
		}

		return turno;

		//moverse
		//ataque
	}
};

#endif /* FIGHTER_H_ */
