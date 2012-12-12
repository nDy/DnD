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
#include <string>
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"

class Dragon: public Character {

private:
	int EnemyAproxLife;
	int DamageDealt;
	Character* Enemy;
	std::list<std::list<Action> > AccionesDePartida;
	int FUERADERANGO;
	int BLOODIED;
	int ATAQUE;
	int PROBABILIDADDEC;
	int PROBABILIDADDEB;
	int PROBABILIDADDEF;

public:

	std::list<Action> AtackActions;

	enum {
		MAXMOVPORTURNO = 1, MAXATKPORTURNO = 1
	};

	void actualizarvalores() {
		//Actualizar las probabilidades
		int BitePGame = 0;
		int BiteTotal = 0;
		int ClawPGame = 0;
		int ClawTotal = 0;
		int FuryPGame = 0;
		int FuryTotal = 0;
		for (std::list<std::list<Action> >::iterator i =
				AccionesDePartida.begin(); i != AccionesDePartida.end(); ++i) {
			for (std::list<Action>::iterator j = (*i).begin(); j != (*i).end();
					++j) {
				if ((*j).actionType == ATTACK) {

					switch ((*j).name) {
					case CLAW:
						++ClawPGame;
						ClawTotal += (*j).value;
						break;
					case BITE:
						++BitePGame;
						BiteTotal += (*j).value;
						break;
					case FURY:
						++FuryPGame;
						FuryTotal += (*j).value;
						break;
					default:
						break;
					}
				}
			}

		}

		std::cout << "Se hicieron " << FuryPGame << "Fury" << std::endl;
		std::cout << "Se hicieron " << ClawPGame << "Claw" << std::endl;
		std::cout << "Se hicieron " << BitePGame << "Bite" << std::endl;

		int FC; //Factor de correccion

		std::cout
				<< "La probabilidad de que ocurra Fury antes de aprender de los eventos ocurridos durante la partida es de "
				<< (float) PROBABILIDADDEF / 100 << "%" << std::endl;
		std::cout
				<< "La probabilidad de que ocurra Claw antes de aprender de los eventos ocurridos durante la partida es de "
				<< (float) PROBABILIDADDEC / 100 << "%" << std::endl;
		std::cout
				<< "La probabilidad de que ocurra Bite antes de aprender de los eventos ocurridos durante la partida es de "
				<< (float) PROBABILIDADDEB / 100 << "%" << std::endl;

		if (BitePGame != 0 && ClawPGame != 0 && FuryPGame != 0) {
			//se ejecutan las 3 acciones de ataque en la partida
			if (PROBABILIDADDEB > 500 && PROBABILIDADDEC > 500
					&& PROBABILIDADDEF > 500) {
				FC = 500;
			} else if (PROBABILIDADDEB > PROBABILIDADDEC
					&& PROBABILIDADDEB > PROBABILIDADDEF) {
				if (PROBABILIDADDEC > PROBABILIDADDEF) {
					FC = PROBABILIDADDEF;
				} else {
					FC = PROBABILIDADDEC;
				}
			} else {
				FC = PROBABILIDADDEB;
			}

			int PremioBite;
			PremioBite = ((float) (BiteTotal / BitePGame)
					/ ((BiteTotal / BitePGame) + (ClawTotal / ClawPGame)
							+ (FuryTotal / FuryPGame))) * (3 * FC);
			int PremioClaw;
			PremioClaw = ((float) (ClawTotal / ClawPGame)
					/ ((BiteTotal / BitePGame) + (ClawTotal / ClawPGame)
							+ (FuryTotal / FuryPGame))) * (3 * FC);
			int PremioFury;
			PremioFury = ((float) (FuryTotal / FuryPGame)
					/ ((BiteTotal / BitePGame) + (ClawTotal / ClawPGame)
							+ (FuryTotal / FuryPGame))) * (3 * FC);

			//Normalizacion
			while (PremioBite + PremioClaw + PremioFury != 3 * FC) {
				if (PremioBite + PremioClaw + PremioFury > 3 * FC) {
					PremioBite--;
				}

				if (PremioBite + PremioClaw + PremioFury > 3 * FC) {
					PremioClaw--;
				}
				if (PremioBite + PremioClaw + PremioFury > 3 * FC) {
					PremioFury--;
				}

				if (PremioBite + PremioClaw + PremioFury < 3 * FC) {
					PremioBite++;
				}
				if (PremioBite + PremioClaw + PremioFury < 3 * FC) {
					PremioClaw++;
				}
				if (PremioBite + PremioClaw + PremioFury < 3 * FC) {
					PremioFury++;
				}
			}

			PROBABILIDADDEB = PROBABILIDADDEB + PremioBite - FC;

			PROBABILIDADDEC = PROBABILIDADDEC + PremioClaw - FC;

			PROBABILIDADDEF = PROBABILIDADDEF + PremioFury - FC;

		} else if (BitePGame != 0 && ClawPGame != 0) {
			if (PROBABILIDADDEB > 500 && PROBABILIDADDEC > 500) {
				FC = 500;

			} else if (PROBABILIDADDEB > PROBABILIDADDEC) {
				FC = PROBABILIDADDEC;
			} else {
				FC = PROBABILIDADDEB;
			}

			int PremioBite;
			PremioBite = ((float) (BiteTotal / BitePGame)
					/ ((BiteTotal / BitePGame) + (ClawTotal / ClawPGame)))
					* (2 * FC);
			int PremioClaw;
			PremioClaw = ((float) (ClawTotal / ClawPGame)
					/ ((BiteTotal / BitePGame) + (ClawTotal / ClawPGame)))
					* (2 * FC);

			//Normalizacion
			while (PremioBite + PremioClaw != 2 * FC) {
				if (PremioBite + PremioClaw > 2 * FC) {
					PremioBite--;
				}

				if (PremioBite + PremioClaw > 2 * FC) {
					PremioClaw--;
				}

				if (PremioBite + PremioClaw < 2 * FC) {
					PremioBite++;
				}
				if (PremioBite + PremioClaw < 2 * FC) {
					PremioClaw++;
				}

			}

			PROBABILIDADDEB = PROBABILIDADDEB + PremioBite - FC;

			PROBABILIDADDEC = PROBABILIDADDEC + PremioClaw - FC;

		} else if (ClawPGame != 0 && FuryPGame != 0) {
			if (PROBABILIDADDEF > 500 && PROBABILIDADDEC > 500) {
				FC = 500;
			} else if (PROBABILIDADDEF > PROBABILIDADDEC) {
				FC = PROBABILIDADDEC;
			} else {
				FC = PROBABILIDADDEF;
			}

			int PremioClaw;
			PremioClaw = ((float) (ClawTotal / ClawPGame)
					/ ((FuryTotal / FuryPGame) + (ClawTotal / ClawPGame)))
					* (2 * FC);
			int PremioFury;
			PremioFury = ((float) (FuryTotal / FuryPGame)
					/ ((FuryTotal / FuryPGame) + (ClawTotal / ClawPGame)))
					* (2 * FC);

			//Normalizacion
			while (PremioClaw + PremioFury != 2 * FC) {

				if (PremioClaw + PremioFury > 2 * FC) {
					PremioClaw--;
				}
				if (PremioClaw + PremioFury > 2 * FC) {
					PremioFury--;
				}

				if (PremioClaw + PremioFury < 2 * FC) {
					PremioClaw++;
				}
				if (PremioClaw + PremioFury < 2 * FC) {
					PremioFury++;
				}
			}

			PROBABILIDADDEC = PROBABILIDADDEC + PremioClaw - FC;

			PROBABILIDADDEF = PROBABILIDADDEF + PremioFury - FC;

		} else if (BitePGame != 0 && FuryPGame != 0) {
			if (PROBABILIDADDEB > 500 && PROBABILIDADDEF > 500) {
				FC = 500;
			} else if (PROBABILIDADDEB > PROBABILIDADDEF) {
				FC = PROBABILIDADDEF;
			} else {
				FC = PROBABILIDADDEB;
			}

			int PremioBite;
			PremioBite = ((float) (BiteTotal / BitePGame)
					/ ((FuryTotal / FuryPGame) + (BiteTotal / BitePGame)))
					* (2 * FC);
			int PremioFury;
			PremioFury = ((float) (FuryTotal / FuryPGame)
					/ ((FuryTotal / FuryPGame) + (BiteTotal / BitePGame)))
					* (2 * FC);

			//Normalizacion
			while (PremioBite + PremioFury != 2 * FC) {
				if (PremioBite + PremioFury > 2 * FC) {
					PremioBite--;
				}

				if (PremioBite + PremioFury > 2 * FC) {
					PremioFury--;
				}

				if (PremioBite + PremioFury < 2 * FC) {
					PremioBite++;
				}
				if (PremioBite + PremioFury < 2 * FC) {
					PremioFury++;
				}
			}

			PROBABILIDADDEB = PROBABILIDADDEB + PremioBite - FC;

			PROBABILIDADDEF = PROBABILIDADDEF + PremioFury - FC;

		} else {
			FC = 0;
		}

		std::cout << "Se usa un factor de correccion de " << FC << std::endl;

		std::cout
				<< "La probabilidad de que ocurra Fury despues de aprender de los eventos ocurridos durante la partida es de "
				<< (float) PROBABILIDADDEF / 100 << "%" << std::endl;
		std::cout
				<< "La probabilidad de que ocurra Claw despues de aprender de los eventos ocurridos durante la partida es de "
				<< (float) PROBABILIDADDEC / 100 << "%" << std::endl;
		std::cout
				<< "La probabilidad de que ocurra Bite despues de aprender de los eventos ocurridos durante la partida es de "
				<< (float) PROBABILIDADDEB / 100 << "%" << std::endl;

		//Cargarlas en el archivo
		std::ofstream myfile;
		myfile.open("Info.txt");
		myfile << FUERADERANGO << "\n";
		myfile << BLOODIED << "\n";
		myfile << ATAQUE << "\n";
		myfile << PROBABILIDADDEC << "\n";
		myfile << PROBABILIDADDEB << "\n";
		myfile << PROBABILIDADDEF << "\n";
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
			PROBABILIDADDEB = atoi(line.c_str());
			std::cout
					<< "Se ha cargado PROBABILIDADDEB, que se asigna a la probabilidad que se le asigna al ataque Sure Strike con un valor de: "
					<< PROBABILIDADDEB << std::endl;
			getline(myfile, line);
			PROBABILIDADDEF = atoi(line.c_str());
			std::cout
					<< "Se ha cargado PROBABILIDADDEF, que se asigna a la probabilidad que se le asigna al ataque Reaping Strike con un valor de: "
					<< PROBABILIDADDEF << std::endl;
			myfile.close();
		} else {
			//Valores cuando no tiene conocimiento previo
			FUERADERANGO = 50;
			BLOODIED = 70;
			ATAQUE = 100;
			PROBABILIDADDEC = 3333;
			PROBABILIDADDEB = 3333;
			PROBABILIDADDEF = 3334;
		}

	}

	void alimentarConocimiento(std::list<Action> AccionesHechasPorEnemigo) {
		this->AccionesDePartida.push_back(AccionesHechasPorEnemigo);
		std::cout
				<< "Se alimenta la base de conocimiento con las acciones realizadas en el turno"
				<< std::endl;
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

	Action atk() {
		Action atk;
		atk.actionType = ATTACK;
		boost::mt19937 rng(time(0));
		boost::uniform_int<> one_to_tenthousand(0, 10000);
		boost::variate_generator<boost::mt19937, boost::uniform_int<> > dice(
				rng, one_to_tenthousand);
		int value = dice();

		if ((0 <= value) && (value < PROBABILIDADDEB)) {
			//El ataque es Bite
			atk.name = BITE;
		}
		if ((PROBABILIDADDEB <= value)
				&& (value < PROBABILIDADDEB + PROBABILIDADDEC)) {
			//El ataque es Claw
			atk.name = CLAW;
		}
		if ((PROBABILIDADDEB + PROBABILIDADDEC <= value)
				&& value
						< (PROBABILIDADDEB + PROBABILIDADDEC + PROBABILIDADDEF)) {
			//El ataque es Fury
			atk.name = FURY;
		}

		return atk;
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
		}

		return result;
	}

	std::list<Action> turn() {

		//Actualizar las probabilidades de las acciones del enemigo
		//armar listas
		std::list<std::list<Action> > ListadeListas;

		//Atk
		if (this->isAdjacentTo(Enemy->getPosX(), Enemy->getPosY())) {
			Action atk;
			atk.actionType = ATTACK;
			std::list<Action> tempList;
			tempList.push_front(atk);
			ListadeListas.push_back(tempList);
		}

		//Atk+mov
		if (this->isAdjacentTo(Enemy->getPosX(), Enemy->getPosY())) {
			Action atk;
			atk.actionType = ATTACK;
			//insertar movimiento
			for (int x = this->getPosX() - this->getSpeed();
					x <= this->getPosX() + this->getSpeed(); x++) {
				if (x >= 0 && x < this->getGrid()->getWidth()) {
					for (int y = this->getPosY() - this->getSpeed();
							y <= this->getPosY() + this->getSpeed(); y++) {
						if (y >= 0 && y < this->getGrid()->getHeight()) {
							if (this->validMove(x, y)) {
								std::list<Action> tempList;
								tempList.push_back(atk);
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
								Action atk;
								atk.actionType = ATTACK;
								atk.value = 0;
								std::list<Action> tempList;
								Action movimiento;
								movimiento.actionType = MOVEMENT;
								movimiento.goalX = x;
								movimiento.goalY = y;
								tempList.push_back(movimiento);
								tempList.push_back(atk);
								ListadeListas.push_back(tempList);
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

		//Decision de ataque

		for (std::list<Action>::iterator i = aux.begin(); i != aux.end(); ++i) {
			if ((*i).actionType == ATTACK) {
				(*i) = atk();
			}
		}

		this->DamageDealt = 0;

		if (this->Bloodied()) {
			std::cout << "El agente nota que se encuentra Bloodied"
					<< std::endl;
		}

		if (this->Enemy->Bloodied()) {
			std::cout << "El agente nota que el enemigo se encuentra Bloodied"
					<< std::endl;
		}

		//ejecutar ataques para accion de mayor utilidad
		for (std::list<Action>::iterator i = aux.begin(); i != aux.end(); ++i) {
			switch ((*i).name) {
			case CLAW:
				(*i).value = 0;
				(*i).value += (4 + (rand() % 8 + 1));
				this->DamageDealt = (*i).value;
				std::cout
						<< "El hagente decidio realizar un ataque \"Claw\" haciendo un total de "
						<< this->DamageDealt << " puntos de dano." << std::endl;
				break;
			case BITE:
				(*i).value = 0;
				(*i).value += (4 + (rand() % 8 + 1) + (rand() % 6 + 1));
				this->DamageDealt = (*i).value;
				std::cout
						<< "El hagente decidio realizar un ataque \"Bite\" haciendo un total de "
						<< this->DamageDealt << " puntos de dano." << std::endl;
				break;
			case FURY:
				(*i).value = 0;
				(*i).value += ((4 + (rand() % 8 + 1)) + (4 + (rand() % 8 + 1))
						+ 4 + (rand() % 8 + 1) + (rand() % 6 + 1));
				this->DamageDealt = (*i).value;
				std::cout
						<< "El hagente decidio realizar un ataque \"Dragons Fury\" haciendo un total de "
						<< this->DamageDealt << " puntos de dano." << std::endl;
				break;
			default:
				break;
			}
		}

		//Alimentar acciones hechas a la base de conocimiento para actualizacion en tiempo real
		this->alimentarConocimiento(aux);
		//retorno

		return aux;
	}

private:
};

#endif /* DRAGON_H_ */
