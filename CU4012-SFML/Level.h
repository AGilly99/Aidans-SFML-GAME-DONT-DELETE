#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/BaseLevel.h"
#include "Framework/Input.h"
#include "Framework/GameState.h"
#include "Framework/World.h"
#include <string>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Ground.h"
#include "Map.h"
#include "Walls.h"
class Level : public BaseLevel{
public:
	Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, World* w);
	~Level();

	void handleInput(float dt) override;
	void update(float dt) override;
	void render();

private:
	// Default variables for level class.
	Player p1;
	Enemy e1;

	Ground ground[3];
	Map BackgroundMap;

	sf::View view;

	Walls walls[2];
};