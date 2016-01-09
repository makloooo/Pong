#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>

using namespace sf;

#include "../Headers/Pong.h"
#include "../Headers/GlobalAssets.h"
#include "../Headers/Game.h"

/*
void freeMove(Shape &shape, float v) {
	if (Keyboard::isKeyPressed(Keyboard::Left)) shape.move(-v, 0);
	if (Keyboard::isKeyPressed(Keyboard::Right)) shape.move(v, 0);
	if (Keyboard::isKeyPressed(Keyboard::Up)) shape.move(0, -v);
	if (Keyboard::isKeyPressed(Keyboard::Down)) shape.move(0, v);
	return;
}
*/

int main() {
	window.setFramerateLimit(60);

	if (!gFont.loadFromFile("Resources/8bitOperatorPlus8-Regular.ttf")) {
		std::cout << "Could not load font!\n";
		return 1;
	}

	int state = 0;
	srand((unsigned)(time(0)));

	initialize();

	while (window.isOpen()) {
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
				window.close();
		}
		
		window.clear(Color::Black);

		if (state == 0) state = displayMenu(); // State 0

		if (state == 1) state = playGame(); // State 1

		if (state == 2) state = displayWinner(); // State 2

		window.display();
	}

	return 0;
}