#include "Player.h"
#include "Enemy.h"

Player::Player()
{
	health = 100;
	speed = 200;

	if (!texture.loadFromFile("gfx/Mario.png")) //loading Players Texture
	{
		std::cout << "File not found\n";
	}
	setTexture(&texture);
	setSize(sf::Vector2f(50, 50)); //marios size
	setCollisionBox(getPosition(), getSize());
	setMass(100.f);
	setTag("Player");
}

void Player::handleInput(float dt)
{
	velocity.x = 0.f;

	// Update velocity based on input
	if (input->isKeyDown(sf::Keyboard::A))
	{
		// Update only the horizontal component, preserving vertical velocity
		velocity.x = -speed;
	}
	if (input->isKeyDown(sf::Keyboard::D))
	{
		// Update only the horizontal component, preserving vertical velocity
		velocity.x = speed;
	}

	if (input->isKeyDown(sf::Keyboard::Space) && canJump)
	{
		Jump(200.f);
	}
}

void Player::update(float dt)
{

}
