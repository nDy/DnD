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
	int EnemyAproxLife;
	int DamageDealt;

	enum {
		FUERADERANGO = 50,
		BLOODIED = 70,
		ATAQUE = 100,
		MAXMOVPORTURNO = 1,
		MAXATKPORTURNO = 1
	};

	Dragon(int X, int Y, SquareGrid* Grid) :
			Character(X, Y, Grid) {
		//Conocimiento, Velocidad del agente
		this->setSpeed(6);
		this->EnemyAproxLife = std::numeric_limits<int>::max();
		this->DamageDealt = 0;
	}

	int Utility(Character* Enemy, std::list<Action> Acciones) {
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
			switch ((*i).getType()) {
			case Action::MOVEMENT:
				if (getAstarPath((*i).getGoalX(), (*i).getGoalY()) == 2) {
					result += FUERADERANGO;
				} else {
					result -= FUERADERANGO;
				}
				break;
			case Action::ATTACK:
				if (getAstarPath((*i).getGoalX(), (*i).getGoalY()) == 2) {
					result += ATAQUE;
					result += (*i).getMaxValue();
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

	void turn() {
		//Actualizar las probabilidades de las acciones del enemigo
		//armar listas
		//evaluar utilidad
		//ejecutar mayor utilidad
	}

private:
};

#endif /* DRAGON_H_ */
