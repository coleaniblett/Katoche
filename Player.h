#pragma once
#include "Room.h"
#include "World.h"
class Player
{
private:
	bool continueGame;
	World* world;
	std::map <std::string, GameObject*> inventory;
public:
	Player();
	Player(World* worldToSet);
	World* getWorld() { return this->world; }
	void setWorld(World* worldToSet) { delete this->world; this->world = worldToSet; }
	bool getContinueGame() { return this->continueGame; }
	void setContinueGame(bool valueToSet) { this->continueGame = valueToSet; }
	void enterRoom(Room* roomToEnter);
	void addToInventory(GameObject* objectToAdd);
	void printInventory();
	void move(std::string direction);
};
