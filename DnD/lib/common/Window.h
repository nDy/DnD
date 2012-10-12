/*
 * Window.h
 *
 *  Created on: Oct 12, 2012
 *      Author: ndy
 */

#ifndef WINDOW_H_
#define WINDOW_H_

class Window {
public:

	enum {
		INTRO, MENU, INGAME, OPTIONS, GAMECREATION, CREDITS
	};

	virtual ~Window() {
	}

	virtual bool Load() = 0;

	virtual void Loop() = 0;

	virtual void Render() = 0;

	virtual void Clear() = 0;

};

#endif /* WINDOW_H_ */
