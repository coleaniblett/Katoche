#pragma once
#include "Room.h"
#include "World.h"
class Player
{
private:
	bool continueGame;
	World* world;
public:
	Player();
	Player(World* worldToSet);
	World* getWorld() { return this->world; }
	void setWorld(World* worldToSet) { delete this->world; this->world = worldToSet; }
	bool getContinueGame() { return this->continueGame; }
	void setContinueGame(bool valueToSet) { this->continueGame = valueToSet; }
	void enterRoom(Room* roomToEnter);
};
