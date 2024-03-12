#include "TileManager.h"


TileManager::TileManager()
{
    filePath = "TilesData.txt";

}


void TileManager::handleInput(float dt)
{
    // Add a new tile only if no tile is currently being edited
    if (activeTileIndex == -1 && input->isLeftMouseDown()) {
        input->setLeftMouse(Input::MouseState::UP);
        sf::Vector2i mousePos = sf::Vector2i(input->getMouseX(), input->getMouseY());

        auto newTile = std::make_unique<Tiles>();
        newTile->setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        world->AddGameObject(*newTile);
        tiles.push_back(std::move(newTile));
        activeTileIndex = tiles.size() - 1;
    }

    // Forward input handling only to the active (editing) tile
    if (activeTileIndex != -1)
    {
        tiles[activeTileIndex]->setInput(input);
        tiles[activeTileIndex]->handleInput(dt);
        // If editing is finished, reset activeTileIndex
        if (!tiles[activeTileIndex]->isEditing())
        {
            activeTileIndex = -1;
        }
    }

    // Saving logic remains unchanged
    if (input->isKeyDown(sf::Keyboard::LControl) && input->isKeyDown(sf::Keyboard::S)) {
        input->setKeyUp(sf::Keyboard::LControl);
        input->setKeyUp(sf::Keyboard::S);
        std::cout << "Saving tiles\n";
        saveTiles(tiles, filePath);
    }
}

void TileManager::update(float dt)
{
    for (auto& tilePtr : tiles) {
        if (tilePtr) { // Check if the pointer is not null
            tilePtr->update(dt); // Dereference the pointer to get the Tiles object
        }
    }
}


void TileManager::render()
{
    for (auto& tilePtr : tiles) {
        if (tilePtr) { // Check if the pointer is not null
            //window->draw(*tilePtr); // Dereference the pointer to get the Tiles object
            window->draw(tilePtr->getDebugCollisionBox());
        }
    }
}



void TileManager::saveTiles(const std::vector<std::unique_ptr<Tiles>>& tiles, const std::string& filePath)
{
     std::ofstream file(filePath);
    for (const auto& tile : tiles) {
        file << tile->getPosition().x << ","
             << tile->getPosition().y << ","
            << tile->getSize().x << ","
            << tile->getSize().y << "\n";
    }
}

bool TileManager::loadTiles()
{
    if (tiles.empty())
    {
        std::ifstream file(filePath);
        
        if (!file.is_open()) {
			return false;
		}
        std::string line;

        while (std::getline(file, line)) {
            std::stringstream linestream(line);
            std::string segment;
            std::vector<std::string> seglist;

            while (std::getline(linestream, segment, ',')) {
                //std::cout << segment << std::endl;
                seglist.push_back(segment);
            }

            if (seglist.size() >= 4) {
                // Assuming segment order is type, posX, posY, sizeX, sizeY
                auto newTile = std::make_unique<Tiles>();
                //tile.setTag(std::stoi(seglist[0])); // Ensure this matches your type representation
                newTile->setPosition(sf::Vector2f(std::stof(seglist[0]), std::stof(seglist[1])));
                newTile->setSize(sf::Vector2f(std::stof(seglist[2]), std::stof(seglist[3])));
                world->AddGameObject(*newTile);
                tiles.push_back(std::move(newTile));
                //std::cout<<"Tiles: "<<tiles.size()<<std::endl;  
            }
            
        }
        
        return true;

    }

    return false;
}

std::vector<std::unique_ptr<Tiles>>& TileManager::getTiles() {
    return tiles;
}

