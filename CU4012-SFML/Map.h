#pragma once
#include "Framework/GameObject.h"
class Map : public GameObject
{
	sf::View view;
	sf::Texture mapTexture;

public:
	Map();
	void update(float dt,sf::Vector2f playerPos);
};

