#include "Enemy.h"

Enemy::Enemy()
{
	health = 100;
	speed = 150;
	velocity.x = 0; //Goombas Movement

	if (!texture.loadFromFile("gfx/Goomba.png"))
	{
		std::cout << "File not found\n";
	}
	setTexture(&texture);
	setSize(sf::Vector2f(50, 50));
	setCollisionBox(getPosition(), getSize());
	setTag("Enemy");
	setMass(50.f);

}

void Enemy::update(float dt)
{
	move(velocity * speed * dt);
}
