/*
 * ConsoleDnD.h
 *
 *  Created on: Nov 25, 2012
 *      Author: ndy
 */

#ifndef CONSOLEDND_H_
#define CONSOLEDND_H_

#include"../bodies/Fighter.h"
#include"../bodies/Dragon.h"
#include"../grid/SquareGrid.H"
#include <cstdlib>

class ConsoleDnD {
private:
	bool running;
	Fighter* player;
	Dragon* dragon;
	SquareGrid* grid;
public:
	ConsoleDnD() {
		this->running = true;
		this->grid = new SquareGrid();
		this->player = new Fighter(1, 2, grid,this->dragon);
		//meter el cuerpo al grid
		this->dragon = new Dragon(1, 5, grid,this->player);
	}

	void Run() {
		while (running) {
			//player->turn;
			//dragon->turn;
			this->render();
			sleep(2);
		}
	}

	void render() {
		if(this->player == NULL){
			std::cout<<"NO instancia el player"<<std::endl;
		}
		for (int varH = 0; varH < this->grid->getHeight(); ++varH) {
			for (int varL = 0; varL < this->grid->getWidth(); ++varL) {
				if (!this->grid->getTerrain(varL, varH)->stepOver()) {
					std::cout << "W ";
				} else {
					if (this->grid->getBody(varL, varH) == NULL) {
						std::cout << "X ";
					} else {
						std::cout << "O ";
					}
				}

			}
			std::cout << std::endl;
		}
	}

};

#endif /* CONSOLEDND_H_ */
