#include "Level.h"
#include "Framework/utilities.h"


//set stuff 
Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, World* w)
{
	window = hwnd;
	input = in;
	gameState = gs;
	world = w;
	// initialise game objects
	p1.setPosition(100, 100);
	p1.setInput(input);

	e1[0].setPosition(500,  636);
	e1[1].setPosition(1000, 636);
	e1[2].setPosition(1500, 636);
	e1[3].setPosition(2000, 636);
	e1[4].setPosition(2500, 636);
	e1[5].setPosition(3000, 636);
	for (int i = 0; i < 6; i++)
	{
		world->AddGameObject(e1[i]);
	}

	BackgroundMap.setWindow(window);
	BackgroundMap.setInput(input);
	world->AddGameObject(p1);


	tileManager.setInput(input);
	tileManager.setWindow(window);
	tileManager.setWorld(world);

	if (!tileManager.loadTiles())
	{
		std::cout << "Tiles not found\n";
	}
	else
	{
		std::cout << "Tiles loaded\n";
	}
}

//remove stuff
Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		exit(0);
	}
	p1.handleInput(dt);
	tileManager.handleInput(dt);
}

// Update game objects
void Level::update(float dt)
{

	BackgroundMap.update(dt,p1.getPosition());
	if(p1.CollisionWithTag("Enemy"))
	{ 
		std::cout << "Player is colliding with the enemy\n";
	}

	std::cout << "Player Position" << p1.getPosition().y<<std::endl; //getting my position so its easier to set my collider

	tileManager.update(dt);
}

// Render level
void Level::render()
{
	beginDraw();
	
	window->draw(BackgroundMap);
	
	window->draw(p1);
	window->draw(p1.getDebugCollisionBox());

	for (int i = 0; i < 6; i++)
	{
		window->draw(e1[i]);
		window->draw(e1[i].getDebugCollisionBox());
	}



	tileManager.render(); //comment this if you dont want to see the tiles 

	endDraw();
}
