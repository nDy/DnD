/*
 * Credits.h
 *
 *  Created on: Oct 12, 2012
 *      Author: ndy
 */

#ifndef CREDITS_H_
#define CREDITS_H_

#include "../common/Window.h"
#include "../common/EventHandler.h"

class Credits: public Window {
private:
public:

	bool Load() {
		return true;
	}

	int Loop() {
		return 0;
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

#endif /* CREDITS_H_ */
