/*
 * Menu.h
 *
 *  Created on: Oct 12, 2012
 *      Author: ndy
 */

#ifndef MENU_H_
#define MENU_H_

#include "../common/Window.h"
#include "../common/EventHandler.h"

class Menu: public Window {
private:
public:

	bool Load() {
		this->setCurrent(Window::MENU);
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
		if (Code == sf::Key::Space) {
			this->setCurrent(Window::INTRO);
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

#endif /* MENU_H_ */
