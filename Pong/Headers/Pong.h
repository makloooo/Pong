#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>

using namespace sf;

#include "GlobalAssets.h"

class Paddle;
class Ball;

class Controller {
protected:
	Ball* pong;
	Paddle* player;
public:
	Controller();
	virtual void move() = 0;
	void setTarget(Ball*);
};

class PlayerOne : public Controller {
public:
	PlayerOne(Paddle*);
	void move();
};

class PlayerTwo : public Controller {
public:
	PlayerTwo(Paddle*);
	void move();
};

class AI : public Controller {
public:
	AI(Paddle*);
	void move();
};

class GameObject {
protected:
	void updateCollider();
public:
	Rect<float> collider;
	RectangleShape graphic;

	GameObject();
	virtual void move() = 0;
	virtual void render() = 0;
};

class ScoreModule {
public:
	Paddle* PlayerOne;
	int score;
	Text text;

	ScoreModule();
	void addScore();
	void loadScoreText();
};

class Paddle : public GameObject {
private:
	float moveSpeed;
	Controller* control;

	void setSide(bool);
public:
	ScoreModule score;

	using GameObject::collider;
	using GameObject::render;
	Paddle();
	Paddle(bool);
	~Paddle();

	Vector2f getPosition();
	RectangleShape getGraphic();
	float getSpeed();

	void setTarget(Ball*);
	void setController(int);

	void move();
	void render();
};

class Ball : public GameObject {
private:
	Paddle* p1;
	Paddle* p2;

	Clock clock;

	Vector2f velocity;
public:
	using GameObject::collider;

	Ball(Paddle*, Paddle*);
	void move();
	void render();

	Vector2f getPosition();
	RectangleShape getGraphic();
};