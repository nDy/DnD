/*
 * Body.h
 *
 *  Created on: Oct 27, 2012
 *      Author: ndy
 */

#ifndef BODY_H_
#define BODY_H_

class Body {
	/*
	 Clase de cuerpo basico, se pueden crear a partir de esta,
	 clases que se pueden instanciar en el mapa. Para rcaracteres
	 que tienen uso de velocidad de movimiento y tienen una
	 cantidad de hp, revisar Character.
	 */

private:
	int x;
	int y;
	bool active;
	bool step;
	bool lookOver; // para ver sobre , a traves de ellos
	short int bodyType;
	//imagen.

public:
	Body(int X, int Y) { //agregar puntero al grid
		this->x = X;
		this->y = Y;
		this->active = true;
		this->step = true;
	}

	void setActive(bool Active) {
		this->active = Active;
	}

	int getPosX() {
		return this->x;
	}

	int getPosY() {
		return this->y;
	}
	void setPosX(int X) {
		this->x = X;
	}
	void setPosY(int Y) {
		this->y = Y;
	}

	bool stepOver() {
		return this->step;
	}

	void stepOver(bool stepOver) {
		this->step = stepOver;
	}

};

#endif /* BODY_H_ */
