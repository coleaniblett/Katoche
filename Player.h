// Player.h
// Defines the Player class, representing a player in the game

#pragma once
#include <typeinfo>
#include "Inventory.h"
#include "Room.h"
#include "World.h"
class Player
{
private:
	World* world;
	bool continueGame;
	//std::map <std::string, std::shared_ptr<GameObject>> inventory;
	Inventory* inventory;
	int shadowState;
	bool leadingHorse;
	int esotericKnowledge;
	bool prayed;
	bool visitedWiseOldMan;
	bool hasExited;
	bool hasRead;
public:
	// constructors
	Player();
	Player(World* worldToSet, Inventory* inventory);
	// world methods
	World* getWorld() { return this->world; }
	void setWorld(World* worldToSet) { delete this->world; this->world = worldToSet; }
	// continueGame methods
	bool getContinueGame() { return this->continueGame; }
	void setContinueGame(bool valueToSet) { this->continueGame = valueToSet; }
	// inventory methods
	Inventory* getInventory() { return this->inventory; }
	//std::shared_ptr<GameObject> getObject(std::string objectToGet);
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
	void leadHorse();
	void leaveHorse();
	void dig();
	void eat(std::string objectToEat);
	void climb(std::string objectToClimb);
	void attack(std::string target, std::string weapon);
	void sleep();
	void pray();
	bool getHasExited() { return this->hasExited; }
	void incEsotericKnowledge() { this->esotericKnowledge += 1; }
};
