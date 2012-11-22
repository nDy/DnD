/*
 * InGame.h
 *
 *  Created on: Oct 12, 2012
 *      Author: ndy
 */

#ifndef INGAME_H_
#define INGAME_H_

#include "../common/Window.h"
#include "../common/ImageHandler.h"
#include "../bodies/Player.h"
#include "../bodies/Dragon.h"
#include "../grid/SquareGrid.H"

class InGame: public Window {
private:
	SquareGrid* grid;
	Dragon* dragon;
public:

	InGame() :
			Window() {
		this->grid = new SquareGrid();
		this->dragon = new Dragon(7, 7, grid);
		this->setCurrent(Window::INGAME);
	}

	bool Load() {
		return true;
	}

	int Loop() {
		return 0;
	}

	int Render(sf::RenderWindow* App) {
		//renderizado

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

#endif /* INGAME_H_ */
