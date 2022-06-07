#pragma once
#include <typeinfo>
#include "Room.h"
#include "World.h"
class Player
{
private:
	World* world;
	bool continueGame;
	std::map <std::string, std::shared_ptr<GameObject>> inventory;
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
	void addToInventory(std::shared_ptr<GameObject> objectToAdd);
	bool hasObject(std::string objectToCheck);
	void printInventory();
	std::shared_ptr<GameObject> getObject(std::string objectToGet);
	void getObjectFromContainer(std::string objectToGet, std::string container);
	void getObjectFromSearchedObject(std::string objectToGet, std::string searchedObject);
	// shadowState methods
	int getShadowState() { return this->shadowState; }
	void setShadowState(int stateToSet) { this->shadowState = stateToSet; }
	void printShadowDescription();
	// movement methods
	void enterRoom(std::shared_ptr<Room> roomToEnter);
	void move(std::string direction);
	void jump();
	// other methods
	void getHelp();
	void read();
	void openObject(std::string objectToOpen);
	void closeObject(std::string objectToClose);
	void searchObject(std::string objectToSearch);
};
