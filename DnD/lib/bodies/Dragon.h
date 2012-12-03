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
#include <fstream>
#include<string>

class Dragon: public Character {

private:
	int EnemyAproxLife;
	int DamageDealt;
	Character* Enemy;
	int FUERADERANGO;
	int BLOODIED;
	int ATAQUE;
	int PROBABILIDADDEC;
	int PROBABILIDADDESS;
	int PROBABILIDADDERS;

public:

	std::list<Action> AtackActions;

	enum {
		MAXMOVPORTURNO = 1, MAXATKPORTURNO = 1
	};

	void actualizarvalores() {
		//Normalizar las probabilidades
		//Cargarlas en el archivo
		std::ofstream myfile;
		myfile.open("Info.txt");
		myfile << FUERADERANGO << "\n";
		myfile << BLOODIED << "\n";
		myfile << ATAQUE << "\n";
		myfile << PROBABILIDADDEC << "\n";
		myfile << PROBABILIDADDESS << "\n";
		myfile << PROBABILIDADDERS << "\n";
		myfile.close();
	}

	void cargarvalores() {
		std::string line;
		std::ifstream myfile("Info.txt");
		if (myfile.is_open()) {
			getline(myfile, line);
			FUERADERANGO = atoi(line.c_str());
			std::cout << "Se ha cargado FUERADERANGO con un valor de: "
					<< FUERADERANGO << std::endl;
			getline(myfile, line);
			BLOODIED = atoi(line.c_str());
			std::cout << "Se ha cargado BLOODIED con un valor de: " << BLOODIED
					<< std::endl;
			getline(myfile, line);
			ATAQUE = atoi(line.c_str());
			std::cout << "Se ha cargado ATAQUE con un valor de: " << ATAQUE
					<< std::endl;
			getline(myfile, line);
			PROBABILIDADDEC = atoi(line.c_str());
			std::cout
					<< "Se ha cargado PROBABILIDADDEC, que se asigna a la probabilidad que se le asigna al ataque Cleave con un valor de: "
					<< PROBABILIDADDEC << std::endl;
			getline(myfile, line);
			PROBABILIDADDESS = atoi(line.c_str());
			std::cout
					<< "Se ha cargado PROBABILIDADDESS, que se asigna a la probabilidad que se le asigna al ataque Sure Strike con un valor de: "
					<< PROBABILIDADDESS << std::endl;
			getline(myfile, line);
			PROBABILIDADDERS = atoi(line.c_str());
			std::cout
					<< "Se ha cargado PROBABILIDADDERS, que se asigna a la probabilidad que se le asigna al ataque Reaping Strike con un valor de: "
					<< PROBABILIDADDERS << std::endl;
			myfile.close();
		} else {
			//Valores cuando no tiene conocimiento previo
			FUERADERANGO = 50;
			BLOODIED = 70;
			ATAQUE = 100;
			PROBABILIDADDEC = 375;
			PROBABILIDADDESS = 250;
			PROBABILIDADDERS = 375;
		}

	}

	void alimentarConocimiento(std::list<Action> AccionesHechasPorEnemigo){

	}

	Dragon(int X, int Y, SquareGrid* Grid, Character* enemy) :
			Character(X, Y, Grid) {
		//Inicializacion de constantes de valores aprendidos por el agente desde el archivo
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

	float distance(int startX, int startY, int goalX, int goalY) {
		return sqrt(
				(startX - goalX) * (startX - goalX)
						+ (startY - goalY) * (startY - goalY));
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
		Action nullatk;
		null.actionType = -1;
		nullatk.actionType = -1;
		for (std::list<Action>::iterator i = Acciones.begin();
				i != Acciones.end(); ++i) {
			switch ((*i).actionType) {
			case MOVEMENT:
				null = (*i);
				result -= distance((*i).goalX, (*i).goalY,
						this->Enemy->getPosX(), this->Enemy->getPosY());
				if (Adjacent((*i).goalX, (*i).goalY, this->Enemy->getPosX(),
						this->Enemy->getPosY())) {
					result += FUERADERANGO;
				} else {
					result -= FUERADERANGO;
				}
				break;
			case ATTACK:
				nullatk = (*i);
				break;
			default:
				break;
			}
		}

		if (nullatk.actionType == -1) {
			result -= ATAQUE;
		} else {
			result += ATAQUE;
			result += nullatk.MAXvalue; //prob

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
			if (x >= 0 && x < this->getGrid()->getWidth()) {
				for (int y = this->getPosY() - this->getSpeed();
						y <= this->getPosY() + this->getSpeed(); y++) {
					if (y >= 0 && y < this->getGrid()->getHeight()) {
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
			if (x >= 0 && x < this->getGrid()->getWidth()) {
				for (int y = this->getPosY() - this->getSpeed();
						y <= this->getPosY() + this->getSpeed(); y++) {
					if (y >= 0 && y < this->getGrid()->getHeight()) {
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
