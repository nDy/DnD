/*
 * DnD.h
 *
 *  Created on: Oct 12, 2012
 *      Author: nDy
 */

#ifndef DND_H_
#define DND_H_

#include "../common/Window.h"
#include <SFML/Window.hpp>

class DnD: public Window {
private:

	int Current;
	bool Running;
	sf::Window* App;

public:

	DnD() {
		App = new sf::Window();
	}

	bool Load() {
		App->Create(sf::VideoMode(800, 600, 32), "DnD");

		if (!App->IsOpened())
			return false;

		return true;
	}

	void Loop() {
		App->Display();
	}

	void Render() {

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
				if (Event.Type == sf::Event::Closed) {
					this->Clear();
					return EXIT_SUCCESS;
				}
			}

			this->Loop();

			this->Render();

		}

		return EXIT_FAILURE;
	}
};

#endif /* DND_H_ */
