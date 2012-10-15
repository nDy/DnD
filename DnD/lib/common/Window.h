/*
 * Window.h
 *
 *  Created on: Oct 12, 2012
 *      Author: ndy
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include "EventHandler.h"
#include <SFML/Window.hpp>

class Window : virtual public EventHandler{
public:

	enum {
		INTRO = 0, MENU = 1, INGAME = 2, OPTIONS = 3, GAMECREATION = 4, CREDITS = 5, ERROR, SUCCESS
	};

	virtual ~Window() {
	}

	virtual bool Load() = 0;

	virtual int Loop() = 0;

	virtual int Render(sf::Window*) = 0;

	virtual void Clear() = 0;

};

#endif /* WINDOW_H_ */
