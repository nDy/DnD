/*
 * Window.h
 *
 *  Created on: Oct 12, 2012
 *      Author: ndy
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include "EventHandler.h"
#include <SFML/Graphics.hpp>

class Window: virtual public EventHandler {
private:
	int Current;
public:

	enum {
		INTRO = 0,
		MENU = 1,
		INGAME = 2,
		OPTIONS = 3,
		GAMECREATION = 4,
		CREDITS = 5,
		ERROR,
		SUCCESS
	};

	virtual ~Window() {
	}

	virtual bool Load() = 0;

	virtual int Loop() = 0;

	virtual int Render(sf::RenderWindow*) = 0;

	virtual void Clear() = 0;

	virtual int getCurrent() {
		return this->Current;
	}

	virtual void setCurrent(int c) {
		this->Current = c;
	}

};

#endif /* WINDOW_H_ */
