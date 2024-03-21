#include "Level.h"
#include "Framework/utilities.h"


//set stuff 
Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, World* w)
{
	window = hwnd;
	input = in;
	gameState = gs;
	world = w;

	if (!font.loadFromFile("font/arial.ttf")) {
		std::cout << "error loading font" << std::endl;
	};

	TileEditorText.setFont(font);
	TileEditorText.setCharacterSize(24);
	TileEditorText.setFillColor(sf::Color::Red);

	TileEditorText.setString(" Press E to edit tiles");
	TileEditorText.setPosition(0, 0);

	//Collectables Collected Text
	CollectablesCollectedText.setFont(font);
	CollectablesCollectedText.setCharacterSize(24);
	CollectablesCollectedText.setFillColor(sf::Color::Black);
	CollectablesCollectedText.setPosition(window->getSize().x, 0);
	CollectablesCollectedText.setString("Collected: ");

	// initialise game objects
	p1.setPosition(100, 100);
	p1.setInput(input);

	e1[0].setPosition(500,  636);
	e1[1].setPosition(1000, 636);
	e1[2].setPosition(1500, 636);
	e1[3].setPosition(2000, 636);
	e1[4].setPosition(2500, 636);
	e1[5].setPosition(3000, 636);
	e1[6].setPosition(4000, 636);
	e1[7].setPosition(4600, 636);
	e1[8].setPosition(7000, 636);
	e1[9].setPosition(7100, 636);
	for (int i = 0; i < NumberOfEnemies; i++)
	{
		world->AddGameObject(e1[i]);
	}

	BackgroundMap.setWindow(window);
	BackgroundMap.setInput(input);
	world->AddGameObject(p1);

	// Set up tile manager
	tileManager.setCollectableTexture("gfx/Collectable.png");
	tileManager.setPlatformTexture("gfx/Platform.png");
	tileManager.setInput(input);
	tileManager.setWindow(window);
	tileManager.setWorld(world);
	tileManager.ShowDebugCollisionBox(true);

	if (!tileManager.loadTiles())
	{
		std::cout << "Tiles not found\n";
	}
	else
	{
		std::cout << "Tiles loaded\n";
	}
	sf::Vector2f viewSize = sf::Vector2f(window->getSize().x, window->getSize().y);
	view.setSize(viewSize.x, viewSize.y);
	view.setCenter(viewSize.x / 2, viewSize.y / 2);
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

	// Check if 'E' is pressed to toggle editing mode
	if (input->isKeyDown(sf::Keyboard::E))
	{
		// First, if we're in edit mode, we save the tiles
		if (editMode)
		{
			std::cout << "Exiting edit mode. Saving tiles...\n";
			tileManager.saveTiles(tileManager.getTiles(), tileManager.getFilePath());
		}
		// Then toggle the edit mode
		editMode = !editMode;
		input->setKeyUp(sf::Keyboard::E); // Acknowledge the key press
	}

	if (editMode)
	{
		// Handle moving the view or other edit-mode-specific logic
		moveView(dt);
		//tileManager.handleInput(dt); // tileManager might have its own logic for when editing is true
	}
	else
	{
		// Handle game logic when not in edit mode
		p1.handleInput(dt);
	}
}

// Update game objects
void Level::update(float dt)
{
	sf::Vector2f viewSize = sf::Vector2f(window->getSize().x, window->getSize().y);

	CollectablesCollectedText.setPosition(view.getCenter().x - viewSize.x / 14, view.getCenter().y - viewSize.y / 2);

	std::cout << p1.getPosition().x << std::endl;



	for (int i = 0; i < NumberOfEnemies; i++)
	{
		if (e1[i].CollisionWithTag("Player"))
		{
			//std::cout << e1[i].getCollisionDirection() << std::endl;
			if (e1[i].getCollisionDirection() == "Up")
			{
				e1[i].setAlive(false);
				world->RemoveGameObject(e1[i]);
			}
			else
			{
				std::cout << "Player hit enemy from the side\n";
				p1.setPosition(100, 100);
			}
		}
	}

	if (p1.CollisionWithTag("Collectable"))
	{
		// Player is Colliding with Collectable
		p1.addColelctablesCollected(1); // Increment Collectable count
		tileManager.RemoveCollectable(); // Remove the collectable

		// Update the CollectablesCollectedText to display the new number of rings collected
		int collectableCount = p1.getCollectablesCollected(); // Assume p1 is the player object and has the getCollectablesCount method
		CollectablesCollectedText.setString("Collected: " + std::to_string(collectableCount));
	}

	for (size_t i = 0; i < NumberOfEnemies; i++)
	{
		if (e1[i].CollisionWithTag("Wall"))
		{
			e1[i].setVelocity(-e1[i].getVelocity().x, e1[i].getVelocity().y);
		}
	}
	
	if (p1.getPosition().y > 900)
	{
		p1.setPosition(100, 100);
		gameState->setCurrentState(State::MENU);
	}

	if (p1.getPosition().x > 7888.19)
	{
		std::cout << "You Win MOFO" << std::endl;
		p1.setPosition(sf::Vector2f(100, 100));
		gameState->setCurrentState(State::CREDITS);
	}
	if (editMode)
	{
		TileEditorText.setPosition(view.getCenter().x - viewSize.x / 2, view.getCenter().y - viewSize.y / 2);
		TileEditorText.setString("Editing mode\nLeft Mouse Button to place tile\nPress B to set collider as a wall (allows bouncing)\nPress C to make it a collectable\nPress P to make it a Platform\nPress E to exit and Save");
		tileManager.handleInput(dt);
		tileManager.update(dt);
	}
	else
	{
		TileEditorText.setString("Press E to edit tiles");

		//Move the view to follow the player
		view.setCenter(view.getCenter().x, 360);

		sf::Vector2f playerPosition = p1.getPosition();
		float newX = std::max(playerPosition.x, view.getSize().x / 2.0f);
		view.setCenter(newX, view.getCenter().y);
		window->setView(view);
	}
}

// Render level
void Level::render()
{
	beginDraw();
	
	window->draw(BackgroundMap);
	//window->draw(TileEditorText);

	
	window->draw(p1);
	//window->draw(p1.getDebugCollisionBox());

	for (int i = 0; i < NumberOfEnemies; i++)
	{
		if (e1[i].isAlive())
		{
			window->draw(e1[i]);
			//window->draw(e1[i].getDebugCollisionBox());
		}
	}

	tileManager.render(editMode);
	if (editMode) window->draw(TileEditorText);
	window->draw(CollectablesCollectedText);

	endDraw();
}
void Level::moveView(float dt)
{

	if (input->isKeyDown(sf::Keyboard::W))
	{
		view.move(0, -100 * dt);
	}
	if (input->isKeyDown(sf::Keyboard::S))
	{
		view.move(0, 100 * dt);
	}
	if (input->isKeyDown(sf::Keyboard::A))
	{
		view.move(-100 * dt, 0);
	}
	if (input->isKeyDown(sf::Keyboard::D))
	{
		view.move(100 * dt, 0);
	}

	window->setView(view);

}

void Level::adjustViewToWindowSize(unsigned int width, unsigned int height)
{
	sf::FloatRect visibleArea(0, 0, static_cast<float>(width), static_cast<float>(height));
	view.setSize(static_cast<float>(width), static_cast<float>(height));
	view.setCenter(static_cast<float>(width) / 2, static_cast<float>(height) / 2);
}