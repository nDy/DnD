/*
 * DnD.h
 *
 *  Created on: Oct 12, 2012
 *      Author: nDy
 */

#ifndef DND_H_
#define DND_H_

#include "../common/Window.h"
#include "../window/Credits.h"
#include "../window/GameCreation.h"
#include "../window/InGame.h"
#include "../window/Intro.h"
#include "../window/Menu.h"
#include "../window/Options.h"
#include <SFML/Window.hpp>

class DnD {
private:

	int Current;
	bool Running;
	sf::Window* App;
	Window** windows;

public:

	enum {
		ERROR = -1, SUCCESS = 1
	};

	DnD() {
		App = new sf::Window();
		windows = new Window*[3];
		windows[Window::INTRO] = new Intro();
		windows[Window::MENU] = new Menu();
		windows[Window::OPTIONS] = new Options();
		this->Current = Window::INTRO;
	}

	bool Load() {
		App->Create(sf::VideoMode(800, 600, 32), "DnD");

		if (!App->IsOpened())
			return false;

		return true;
	}

	int Loop() {

		switch (this->Current) {
		case Window::INTRO:
			if (windows[Window::INTRO] == NULL) {
				windows[Window::INTRO] = new Intro();

				if (!windows[Window::INTRO]->Load()) {
					windows[Window::INTRO]->Clear();
					windows[Window::INTRO] = NULL;
					this->Clear();
					return Window::INTRO;
				}
			}

			if (this->Current == Window::ERROR)
				return DnD::ERROR;
			else
				return DnD::SUCCESS;

			break;

		case Window::MENU:
			if (windows[Window::MENU] == NULL) {
				windows[Window::MENU] = new Menu();

				if (!windows[Window::MENU]->Load()) {
					windows[Window::MENU]->Clear();
					windows[Window::MENU] = NULL;
					this->Clear();
					return Window::MENU;
				}
			}

			if (this->Current == Window::ERROR)
				return DnD::ERROR;
			else
				return DnD::SUCCESS;
			break;
		case Window::INGAME:
			if (windows[Window::INGAME] == NULL) {
				windows[Window::INGAME] = new InGame();

				if (!windows[Window::INGAME]->Load()) {
					windows[Window::INGAME]->Clear();
					windows[Window::INGAME] = NULL;
					this->Clear();
					return Window::INGAME;
				}
			}

			if (this->Current == Window::ERROR)
				return DnD::ERROR;
			else
				return DnD::SUCCESS;
			break;
		}
		return DnD::ERROR;
	}

	int Render() {
		switch (this->Current) {
		case Window::INTRO:
			windows[Window::INTRO]->Render(App);
			break;
		case Window::MENU:
			windows[Window::MENU]->Render(App);
			break;
		case Window::INGAME:
			windows[Window::INGAME]->Render(App);
			break;
		}
		App->Display();
		return 0;
	}

	void Event(sf::Event e) {

		switch (this->Current) {
		case Window::INTRO:
			windows[Window::INTRO]->Event(e);
			break;
		case Window::MENU:
			windows[Window::MENU]->Event(e);
			break;
		case Window::INGAME:
			windows[Window::INGAME]->Event(e);
			break;
		}

	}

	void Clear() {
		this->App->Close();
	}

	int Execute() {
		if (!this->Load())
			return EXIT_FAILURE;

		while (this->App->IsOpened()) {

			sf::Event Event;

			while (App->GetEvent(Event)) {

				this->Event(Event);

				if (this->Current != windows[this->Current]->getCurrent()) {
					this->Current = windows[this->Current]->getCurrent();
					windows[this->Current]->setCurrent(this->Current);
				}

				if (Event.Type == sf::Event::Closed) {
					this->Clear();
					return EXIT_SUCCESS;
				}

				if (this->Loop() == DnD::ERROR)
					return EXIT_FAILURE;
				if (this->Render() == DnD::ERROR)
					return EXIT_FAILURE;
			}

		}
		return EXIT_FAILURE;
	}
};

#endif /* DND_H_ */
