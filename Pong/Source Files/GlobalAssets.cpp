#include "../Headers/GlobalAssets.h"

Font gFont;
RenderWindow window(VideoMode(640, 480), "SFML Workspace");

const float PADDLE_W = 16.f;
const float PADDLE_H = 64.f;

const float WIN_H_CENTER = 320.f;
const float WIN_V_CENTER = 240.f;

Paddle p1;
Paddle p2;
Ball pong(&p1, &p2);

std::vector<Ball*> pongs;

Text title;
Text menu;
RectangleShape pointer;

float getRandFloat(float LO, float HI) {
	return LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));
}