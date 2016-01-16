#include "../Headers/Game.h"

float getHorizontalCenter(const Text& obj) {
	return WIN_H_CENTER - (obj.getLocalBounds().width / 2);
}

float getVerticalCenter(const Text& obj) {
	return WIN_V_CENTER - (obj.getLocalBounds().height / 2);
}

void initialize() {
	// Creating the text
	title.setFont(gFont);
	title.setString("PONG");
	title.setCharacterSize(70);
	title.setColor(Color::White);

	menu.setFont(gFont);
	menu.setString("One Player\nTwo Player");
	menu.setCharacterSize(40);
	menu.setColor(Color::White);

	pointer.setSize(Vector2f(16.f, 16.f));
	pointer.setFillColor(Color::White);

	// Positioning the text
	title.setPosition(Vector2f(getHorizontalCenter(title), getVerticalCenter(title) - 100));
	menu.setPosition(Vector2f(getHorizontalCenter(menu), getVerticalCenter(menu) + 50));
	pointer.setPosition(Vector2f(menu.getPosition().x - 30, menu.getPosition().y + 20));

	winner.setString("Nobody wins!");
	winner.setFont(gFont);
	winner.setColor(Color::White);
	winner.setPosition(Vector2f(getHorizontalCenter(winner), getVerticalCenter(winner)));
	restartPrompt.setString("Want a rematch? Press Q!");
	restartPrompt.setFont(gFont);
	restartPrompt.setColor(Color::White);
	restartPrompt.setPosition(Vector2f(getHorizontalCenter(restartPrompt), getVerticalCenter(restartPrompt) - 100));
}

int displayMenu() {
	static int selection = 1; // 1 for first option, decrease with down.

	// Create a cursor
	if (Keyboard::isKeyPressed(Keyboard::S) && selection != 0) {
		// Move cursor down
		pointer.move(Vector2f(0.f, 50.f));
		--selection;
	}
	if (Keyboard::isKeyPressed(Keyboard::W) && selection != 1) {
		// Move cursor up
		pointer.move(Vector2f(0.f, -50.f));
		++selection;
	}
	if (Keyboard::isKeyPressed(Keyboard::Return)) {
		pongs.push_back(new Ball(&p1, &p2));
		pongs.at(0)->resetClock();
		if (selection == 1) {
			// Start 1p game
			p1.setController(1); // set p1
			p2.setController(0); // set com
			p2.setTarget(pongs.at(0));
		}
		else if (selection == 0) {
			// Start 2p game
			p1.setController(1); // set p1
			p2.setController(2); // set p2
		}
		
		return 1;
	}

	window.draw(menu);
	window.draw(title);
	window.draw(pointer);

	return 0;
}

int playGame() {
	// std::cout << "Playing game!\n";

	p1.move();
	p2.move();
	
	for (unsigned i = 0; i < pongs.size(); ++i) {
		pongs.at(i)->move();
	}
	// std::cout << "Objects moved!\n";

	// Drawing portion
	p1.render();
	p2.render();
	for (unsigned i = 0; i < pongs.size(); ++i) {
		pongs.at(i)->render();
	}

	if (p1.score.score == 30) {
		// Player 1 wins
		winner.setString("Player 1 wins!");
		return 2;
	}
	else if (p2.score.score == 30) {
		// Player 2 wins
		winner.setString("Player 2 wins!");
		return 2;
	}


	// std::cout << "Objects drawn!\n";
	return 1;
}

int displayWinner() {
	window.draw(winner);
	window.draw(restartPrompt);
	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		p1.score.score = 0;
		p2.score.score = 0;
		while (!pongs.empty()) pongs.pop_back();
		pongs.push_back(new Ball(&p1, &p2));
		pongs.front()->resetClock();
		pongs.front()->resetPosition(true);
		std::cout << "Values reset!\n";
		return 1;
	}
	return 2;
}