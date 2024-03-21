#pragma once
#include "Framework/GameObject.h"
#include <iostream>
class Player : public GameObject
{
	int health;
	float speed;
	sf::Texture texture;

	int CollectablesCollected;
public:
	Player();

	void handleInput(float dt);
	void update(float dt);

	void addColelctablesCollected(int collectables){ CollectablesCollected += collectables; }
	int getCollectablesCollected(){ return CollectablesCollected; }
};

