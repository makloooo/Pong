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

RenderWindow window(VideoMode(640, 480), "SFML Workspace");

void freeMove(Shape &shape, float v) {
	if (Keyboard::isKeyPressed(Keyboard::Left)) shape.move(-v, 0);
	if (Keyboard::isKeyPressed(Keyboard::Right)) shape.move(v, 0);
	if (Keyboard::isKeyPressed(Keyboard::Up)) shape.move(0, -v);
	if (Keyboard::isKeyPressed(Keyboard::Down)) shape.move(0, v);
	return;
}

int main() {
	window.setFramerateLimit(60);

	if (!gFont.loadFromFile("Resources/8bitOperatorPlus8-Regular.ttf")) {
		std::cout << "Could not load font!\n";
		return 1;
	}

	Paddle player(true, &window);
	Paddle com(false, &window);

	Ball pong(&window, &player, &com);

	com.setTarget(&pong);

	while (window.isOpen()) {
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed)
				window.close();
		}

		player.move();
		com.move();
		pong.move();

		// Drawing portion
		window.clear(Color::Black);
		player.render();
		com.render();
		pong.render();
		window.display(); // "RenderWindow" - Window has a renderer built into it.
	}

	return 0;
}