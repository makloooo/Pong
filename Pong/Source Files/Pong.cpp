#include "../Headers/Pong.h"

const float MAX_BOT = 400.f;
const float MAX_TOP = 140.f;

/* Controller methods */
Controller::Controller() {};

void Controller::setTarget(Ball* tracking) {
	pong = tracking;
}

PlayerOne::PlayerOne(Paddle* attached) {
	player = attached;
	pong = NULL;
}

void PlayerOne::move() {
	Vector2f currPosition = player->getPosition();
	if (Keyboard::isKeyPressed(Keyboard::W) && currPosition.y >= MAX_TOP) player->graphic.move(0, -player->getSpeed());
	if (Keyboard::isKeyPressed(Keyboard::S) && currPosition.y <= MAX_BOT) player->graphic.move(0, player->getSpeed());
}

PlayerTwo::PlayerTwo(Paddle* attached) {
	player = attached;
	pong = NULL;
}

void PlayerTwo::move() {
	Vector2f currPosition = player->getPosition();
	if (Keyboard::isKeyPressed(Keyboard::Up) && currPosition.y >= MAX_TOP) player->graphic.move(0, -player->getSpeed());
	if (Keyboard::isKeyPressed(Keyboard::Down) && currPosition.y <= MAX_BOT) player->graphic.move(0, player->getSpeed());
}

AI::AI(Paddle* attached) {
	player = attached;
	this->pong = pong;
}

void AI::move() {
	Vector2f padPos = player->getPosition();
	Vector2f ballPos = pong->getPosition();
	if (ballPos.y + 8 < padPos.y + 32 && padPos.y >= MAX_TOP) player->graphic.move(0, -player->getSpeed());
	else if (ballPos.y + 8 > padPos.y + 32 && padPos.y <= MAX_BOT) player->graphic.move(0, player->getSpeed());
}
/* End Controller methods */

/* Game Object methods */
GameObject::GameObject() {};

void GameObject::render() {
	window.draw(graphic);
}

void GameObject::updateCollider() {
	collider.top = graphic.getPosition().y;
	collider.left = graphic.getPosition().x;
	collider.height = graphic.getSize().y;
	collider.width = graphic.getSize().x;
}
/* End Game Object methods */

/* Score Module functions*/
ScoreModule::ScoreModule() {
	score = 0;
}

void ScoreModule::addScore() {
	++score;
	text.setString(std::to_string(score));
}

void ScoreModule::loadScoreText() {
	text.setFont(gFont);
	text.setString("0");
	text.setCharacterSize(100);
	text.setColor(Color::White);
}
/* End Score Module Functions */

/* Paddle Methods */
Paddle::Paddle() {
	moveSpeed = 5.f;
	control = NULL;

	score.loadScoreText();

	graphic.setSize(Vector2f(PADDLE_W, PADDLE_H));
	graphic.setFillColor(Color::White);

	updateCollider();
}

Paddle::Paddle(bool left) {
	moveSpeed = 5.f;

	score.loadScoreText();

	graphic.setSize(Vector2f(PADDLE_W, PADDLE_H));
	graphic.setFillColor(Color::White);
	if (left) {
		graphic.setPosition(40, WIN_V_CENTER - 32);
		score.text.setPosition(100, 0);
		control = new PlayerOne(this);
	}
	else {
		graphic.setPosition(600, WIN_V_CENTER - 32);
		score.text.setPosition(520, 0);
		control = new AI(this);
	}

	updateCollider();
}

Paddle::~Paddle() {
	if (control != NULL) delete control;
}

Vector2f Paddle::getPosition() {
	return graphic.getPosition();
}

RectangleShape Paddle::getGraphic() {
	return graphic;
}

float Paddle::getSpeed() {
	return moveSpeed;
}

void Paddle::setController(int type) {
	if (control != NULL) delete control;
	if (type == 0) {
		control = new AI(this);
		setSide(false);
	}
	else if (type == 1) {
		control = new PlayerOne(this);
		setSide(true);
	}
	else if (type == 2) {
		control = new PlayerTwo(this);
		setSide(false);
	}
	// std::cout << "Controller set!\n";
}

void Paddle::setSide(bool left) {
	if (left) {
		graphic.setPosition(40, WIN_V_CENTER - 32);
		score.text.setPosition(100, 0);
	}
	else {
		graphic.setPosition(600, WIN_V_CENTER - 32);
		score.text.setPosition(520, 0);
	}
	updateCollider();
	// std::cout << "Side set!\n";
}

void Paddle::setTarget(Ball* tracking) {
	// Use this for AI only!!
	control->setTarget(tracking);
}

void Paddle::move() {
	control->move();
	updateCollider();
}

void Paddle::render() {
	window.draw(graphic);
	window.draw(score.text);
}
/* End Paddle Methods*/

/* Ball Methods */
Ball::Ball(Paddle* p1, Paddle* p2) {
	this->p1 = p1;
	this->p2 = p2;

	graphic.setFillColor(Color::White);
	graphic.setSize(Vector2f(16, 16));
	graphic.setPosition(WIN_H_CENTER - 8, WIN_V_CENTER - 8);
	
	velocity.x = -4;
	velocity.y = 7;
}

void Ball::move() {
	if (clock.getElapsedTime().asSeconds() > 1) graphic.move(velocity.x, velocity.y);
	updateCollider();

	// If the ball reaches the top or bottom boundary, it will reverse its y-direction
	if (collider.top <= MAX_TOP || collider.top + collider.height >= MAX_BOT) velocity.y *= -1;

	// If the ball collides with the any of the paddles, it will reverse its x-direction
	if (this->collider.intersects(p1->collider)) velocity.x *= -1;
	if (this->collider.intersects(p2->collider)) velocity.x *= -1;

	// When the ball moves into a scoring zone
	if (collider.left <= 0) {
		p2->score.addScore();
		graphic.setPosition(WIN_H_CENTER - 16, WIN_V_CENTER - 16);
		velocity.x = -4;
		clock.restart();
	}
	if (collider.left + collider.width >= 640) {
		p1->score.addScore();
		graphic.setPosition(WIN_H_CENTER - 16, WIN_V_CENTER - 16);
		velocity.x = 4;
		clock.restart();
	}
}

void Ball::render() {
	window.draw(graphic);
}

RectangleShape Ball::getGraphic() {
	return graphic;
}

Vector2f Ball::getPosition() {
	return graphic.getPosition();
}
/* End Ball Methods*/