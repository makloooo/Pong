#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>

#include "../Headers/Pong.h"

using namespace sf;

class Paddle;
class Ball;

extern Font gFont;
extern RenderWindow window;

extern const float PADDLE_W;
extern const float PADDLE_H;

extern const float WIN_H_CENTER;
extern const float WIN_V_CENTER;

extern Paddle p1;
extern Paddle p2;
extern Ball pong;

extern std::vector<Ball*> pongs;

extern Text title;
extern Text menu;
extern RectangleShape pointer;

extern Text winner;
extern Text restartPrompt;

extern float getRandFloat(float LO, float HI);