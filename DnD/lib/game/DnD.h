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
	bool Running;
	sf::Window* App;

public:

	DnD() {
		Running = true;
		App = new sf::Window();
	}

	bool Load() {
		App->Create(sf::VideoMode(800, 600, 32), "DnD Game Module");
		return true;
	}

	void Loop() {

	}

	void Render() {

	}

	void Clear() {

	}

	int Execute() {
		this->Load();

		bool Running = true;
		while (Running) {
			App->Display();
		}

		return EXIT_SUCCESS;
	}
};

#endif /* DND_H_ */
