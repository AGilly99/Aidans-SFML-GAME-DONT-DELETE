#pragma once
#include "GameObject.h"
class Tiles :
    public GameObject
{
    bool editing; // To track editing mode
    bool addedToWorld = false;
public:
    Tiles();

    void handleInput(float dt) override;
    void update(float dt) override;
    void markAddedToWorld() { addedToWorld = true; }

    bool isAddedToWorld() const {
        return addedToWorld;
    }

    bool isEditing() {
		return editing;
	}
};

