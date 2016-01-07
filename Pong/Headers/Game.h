#pragma once
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

float getHorizontalCenter(const Text& obj);
float getVerticalCenter(const Text& obj);

void initialize();

int playGame();

int displayMenu();

void spawnPong();