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

const float PADDLE_W = 16.f;
const float PADDLE_H = 64.f;

const float MAX_BOT = 400.f;
const float MAX_TOP = 140.f;

const float WIN_H_CENTER = 320.f;
const float WIN_V_CENTER = 240.f;

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

class Player : public Controller {
public:
	Player(Paddle*);
	void move();
};

class AI : public Controller {
public:
	AI(Paddle*);
	void move();
};

class GameObject {
protected:
	RenderWindow* window;

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
	Paddle* player;
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

public:
	ScoreModule score;

	using GameObject::collider;
	using GameObject::render;
	Paddle(bool, RenderWindow*);

	Vector2f getPosition();
	RectangleShape getGraphic();
	float getSpeed();

	void setTarget(Ball*);

	void move();
	void render();
};

class Ball : public GameObject {
private:
	Paddle* player;
	Paddle* com;

	Clock clock;

	Vector2f velocity;
public:
	using GameObject::collider;

	Ball(RenderWindow*, Paddle*, Paddle*);
	void move();
	void render();

	Vector2f getPosition();
	RectangleShape getGraphic();
};