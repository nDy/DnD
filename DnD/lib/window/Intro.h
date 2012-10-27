/*
 * Intro.h
 *
 *  Created on: Oct 12, 2012
 *      Author: ndy
 */

#ifndef INTRO_H_
#define INTRO_H_

#include "../common/Window.h"
#include "../common/EventHandler.h"
#include <iostream>

class Intro: public Window {
private:

public:

	bool Load() {
		this->setCurrent(Window::INTRO);
		return true;
	}

	int Loop() {
		return Window::INTRO;
	}

	int Render(sf::RenderWindow* App) {
		return 0;
	}

	void Clear() {

	}

	void Closed() {
	}

	void Resized(unsigned int Width, unsigned int Height) {

	}

	void LostFocus() {
	}

	void GainedFocus() {
	}

	void TextEntered(uint32_t UnicodeText) {
	}

	void KeyPressed(sf::Key::Code Code, bool Alt, bool Ctrl, bool Shift) {
		if (Code == sf::Key::Space) {
			this->setCurrent(Window::MENU);
		}
	}

	void KeyReleased(sf::Key::Code Code, bool Alt, bool Ctrl, bool Shift) {
	}

	void MouseWheelMoved(int Delta) {
	}

	void MouseButtonPressed(sf::Mouse::Button Button, unsigned int X,
			unsigned int Y) {
	}

	void MouseButtonReleased(sf::Mouse::Button Button, unsigned int X,
			unsigned int Y) {
	}

	void MouseMoved(int X, int Y) {
	}

	void MouseEntered() {
	}

	void MouseLeft() {
	}

};

#endif /* INTRO_H_ */
