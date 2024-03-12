#include "Tiles.h"

Tiles::Tiles()
{
	setSize(sf::Vector2f(50, 50));
	setStatic(true);
	setTrigger(true);
	//setMass(50.f);
	editing = true;
}

void Tiles::update(float dt)
{
	// Set the collision box to be the same as the sprite
	updateCollisionBox(dt);
}

void Tiles::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Return) && editing) {
		editing = false;
		std::cout << "Editing: " << editing << std::endl;

	}


	if (editing)
	{
		// Move the tile
		float moveSpeed = 100.0f; // Speed of movement

		if (input->isKeyDown(sf::Keyboard::Left)) {
			setPosition(getPosition().x - moveSpeed * dt, getPosition().y);
		}
		if (input->isKeyDown(sf::Keyboard::Right)) {
			setPosition(getPosition().x + moveSpeed * dt, getPosition().y);
		}
		if (input->isKeyDown(sf::Keyboard::Up)) {
			setPosition(getPosition().x, getPosition().y - moveSpeed * dt);
		}
		if (input->isKeyDown(sf::Keyboard::Down)) {
			setPosition(getPosition().x, getPosition().y + moveSpeed * dt);
		}


		//Resize the tile
		if (input->isKeyDown(sf::Keyboard::J))
		{
			setSize(sf::Vector2f(getSize().x - 0.2, getSize().y));
		}


		if (input->isKeyDown(sf::Keyboard::L))
		{
			setSize(sf::Vector2f(getSize().x + 0.2, getSize().y));
		}

		if (input->isKeyDown(sf::Keyboard::I))
		{
			setSize(sf::Vector2f(getSize().x, getSize().y - 0.2));
		}

		if (input->isKeyDown(sf::Keyboard::K))
		{
			setSize(sf::Vector2f(getSize().x, getSize().y + 0.2));
		}
	}

}
