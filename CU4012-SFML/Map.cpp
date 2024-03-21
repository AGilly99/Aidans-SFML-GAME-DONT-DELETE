#include "Map.h"
#include <iostream>
#include "Framework/utilities.h"
Map::Map()
{
	if (!mapTexture.loadFromFile("gfx/background.png")) //Loading map texture
	{
		std::cout << "Texture not found\n"; 
	}

	setTexture(&mapTexture);
	setSize(sf::Vector2f(3376*2.5, 1450));

	view.setSize(WINDOWWIDTH, WINDOWHEIGHT);
	view.setCenter(WINDOWWIDTH / 2, WINDOWHEIGHT / 2);
}

void Map::update(float dt, sf::Vector2f playerPos)
{
    float movementSpeed = 200.0f; // Adjust this value as needed for desired movement speed

    if (input->isKeyDown(sf::Keyboard::A))
    {
        view.move(-movementSpeed * dt, 0);
    }
    if (input->isKeyDown(sf::Keyboard::D))
    {
        view.move(movementSpeed * dt, 0);
    }

    window->setView(view);
}