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
#include <SFML/Graphics.hpp>

class DnD {
private:

	int Current;
	bool Running;
	sf::RenderWindow* App;
	Window** windows;

public:

	enum {
		ERROR = -1, SUCCESS = 1
	};

	DnD() {
		App = new sf::RenderWindow();
		windows = new Window*[6];
		windows[Window::INTRO] = new Intro();
		windows[Window::MENU] = new Menu();
		windows[Window::OPTIONS] = new Options();
		windows[Window::GAMECREATION] = new GameCreation();
		windows[Window::INGAME] = new InGame();
		windows[Window::CREDITS] = new Credits();
		this->Current = Window::INGAME;
	}

	bool Load() {

		App->Create(sf::VideoMode(800, 600, 32), "DnD");

		if (!App->IsOpened())
			return false;

		App->SetFramerateLimit(60);

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
			break;

		case Window::OPTIONS:
			if (windows[Window::OPTIONS] == NULL) {
				windows[Window::OPTIONS] = new Intro();

				if (!windows[Window::OPTIONS]->Load()) {
					windows[Window::OPTIONS]->Clear();
					windows[Window::OPTIONS] = NULL;
					this->Clear();
					return Window::OPTIONS;
				}
			}
			break;

		case Window::GAMECREATION:
			if (windows[Window::GAMECREATION] == NULL) {
				windows[Window::GAMECREATION] = new Intro();

				if (!windows[Window::GAMECREATION]->Load()) {
					windows[Window::GAMECREATION]->Clear();
					windows[Window::GAMECREATION] = NULL;
					this->Clear();
					return Window::GAMECREATION;
				}
			}
			break;

		case Window::CREDITS:
			if (windows[Window::CREDITS] == NULL) {
				windows[Window::CREDITS] = new Intro();

				if (!windows[Window::CREDITS]->Load()) {
					windows[Window::CREDITS]->Clear();
					windows[Window::CREDITS] = NULL;
					this->Clear();
					return Window::CREDITS;
				}
			}
			break;

		}

		if (this->Current == Window::ERROR)
			return DnD::ERROR;
		else
			return DnD::SUCCESS;
	}

	int Render() {
		this->App->Clear();
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
		case Window::OPTIONS:
			windows[Window::INGAME]->Render(App);
			break;
		case Window::GAMECREATION:
			windows[Window::INGAME]->Render(App);
			break;
		case Window::CREDITS:
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
		case Window::OPTIONS:
			windows[Window::INGAME]->Event(e);
			break;
		case Window::GAMECREATION:
			windows[Window::INGAME]->Event(e);
			break;
		case Window::CREDITS:
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
					int oldCurrent = this->Current;
					this->Current = windows[oldCurrent]->getCurrent();
					windows[this->Current]->setCurrent(this->Current);
					//Liberar memoria de windows[oldCurrent]
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
