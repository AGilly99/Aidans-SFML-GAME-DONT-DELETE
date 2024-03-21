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
}

