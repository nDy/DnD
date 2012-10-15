/*
 * EventHandler.h
 *
 *  Created on: Oct 13, 2012
 *      Author: ndy
 */

#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

#include <SFML/Window.hpp>
#include <iostream>
#include <string>

class EventHandler {
public:

	virtual ~EventHandler() {
	}
	;

	virtual void Closed() = 0;

	virtual void Resized(unsigned int Width, unsigned int Height) =0;

	virtual void LostFocus() = 0;

	virtual void GainedFocus() = 0;

	virtual void TextEntered(uint32_t UnicodeText) = 0;

	virtual void KeyPressed(sf::Key::Code Code, bool Alt, bool Ctrl,
			bool Shift) = 0;

	virtual void KeyReleased(sf::Key::Code Code, bool Alt, bool Ctrl,
			bool Shift) = 0;

	virtual void MouseWheelMoved(int Delta) = 0;

	virtual void MouseButtonPressed(sf::Mouse::Button Button, unsigned int X,
			unsigned int Y) = 0;

	virtual void MouseButtonReleased(sf::Mouse::Button Button, unsigned int X,
			unsigned int Y) = 0;

	virtual void MouseMoved(int X, int Y) = 0;

	virtual void MouseEntered() = 0;

	virtual void MouseLeft() = 0;

	virtual void Event(sf::Event e) {
		switch (e.Type) {
		case sf::Event::Closed:
			this->Closed();
			break;
		case sf::Event::Resized:
			this->Resized(e.Size.Width, e.Size.Height);
			break;
		case sf::Event::LostFocus:
			this->LostFocus();
			break;
		case sf::Event::GainedFocus:
			this->GainedFocus();
			break;
		case sf::Event::TextEntered:
			this->TextEntered(e.Text.Unicode);
			break;
		case sf::Event::KeyPressed:
			this->KeyPressed(e.Key.Code, e.Key.Alt, e.Key.Control, e.Key.Shift);
			break;
		case sf::Event::KeyReleased:
			this->KeyReleased(e.Key.Code, e.Key.Alt, e.Key.Control,
					e.Key.Shift);
			break;
		case sf::Event::MouseWheelMoved:
			this->MouseWheelMoved(e.MouseWheel.Delta);
			break;
		case sf::Event::MouseButtonPressed:
			this->MouseButtonPressed(e.MouseButton.Button, e.MouseButton.X,
					e.MouseButton.Y);
			break;
		case sf::Event::MouseButtonReleased:
			this->MouseButtonReleased(e.MouseButton.Button, e.MouseButton.X,
					e.MouseButton.Y);
			break;
		case sf::Event::MouseMoved:
			this->MouseMoved(e.MouseMove.X, e.MouseMove.Y);
			break;
		case sf::Event::MouseEntered:
			this->MouseEntered();
			break;
		case sf::Event::MouseLeft:
			this->MouseLeft();
			break;
		}
	}
};

#endif /* EVENTHANDLER_H_ */
