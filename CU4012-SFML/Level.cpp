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

	e1.setPosition(500, 100);



	BackgroundMap.setWindow(window);
	BackgroundMap.setInput(input);
	world->AddGameObject(p1);
	world->AddGameObject(e1);


	walls[0].setPosition(1, 0);
	walls[0].setSize(sf::Vector2f(15, 675));
	walls[0].setCollisionBox(walls[0].getPosition(), walls[0].getSize());

	world->AddGameObject(walls[0]);

	ground[0].setPosition(0, WINDOWHEIGHT - 50); //setting first floor collider
	ground[0].setSize(sf::Vector2f(2759, 50));
	ground[0].setCollisionBox(ground[0].getPosition(), ground[0].getSize());
	world->AddGameObject(ground[0]);

	ground[1].setPosition(2839, WINDOWHEIGHT - 50);  //second floor collider
	ground[1].setCollisionBox(ground[1].getPosition(), ground[1].getSize());
	ground[1].setSize(sf::Vector2f(50, 50));
	world->AddGameObject(ground[1]);

	world->AddGameObject(p1);
	world->AddGameObject(e1);

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

	//std::cout << "Player Position" << p1.getPosition().x<<std::endl; //getting my position so its easier to set my collider

	tileManager.update(dt);
}

// Render level
void Level::render()
{
	beginDraw();
	
	window->draw(BackgroundMap);
	
	window->draw(p1);
	window->draw(p1.getDebugCollisionBox());


	window->draw(e1);
	window->draw(e1.getDebugCollisionBox());

	//window->draw(walls[0].getDebugCollisionBox());

	//window->draw(ground[0].getDebugCollisionBox());
	window->draw(ground[1].getDebugCollisionBox());

	tileManager.render(); //comment this if you dont want to see the tiles 

	endDraw();
}
