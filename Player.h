#pragma once
#include "Room.h"
#include "World.h"
class Player
{
private:
	World* world;
	bool continueGame;
	std::map <std::string, GameObject*> inventory;
	int shadowState;
public:
	// constructors
	Player();
	Player(World* worldToSet);
	// world methods
	World* getWorld() { return this->world; }
	void setWorld(World* worldToSet) { delete this->world; this->world = worldToSet; }
	// continueGame methods
	bool getContinueGame() { return this->continueGame; }
	void setContinueGame(bool valueToSet) { this->continueGame = valueToSet; }
	// inventory methods
	void addToInventory(GameObject* objectToAdd);
	bool hasObject(std::string objectToCheck);
	void printInventory();
	GameObject* getObject(std::string objectToGet);
	// shadowState methods
	int getShadowState() { return this->shadowState; }
	void setShadowState(int stateToSet) { this->shadowState = stateToSet; }
	void printShadowDescription();
	// movement methods
	void enterRoom(Room* roomToEnter);
	void move(std::string direction);
	void jump();
	// other methods
	void getHelp();
};
