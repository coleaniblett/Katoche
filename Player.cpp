#include "Player.h"

Player::Player()
{
	this->world = new World;
	this->continueGame = true;
}

Player::Player(World* worldToSet)
{
	this->world = worldToSet;
	this->continueGame = true;
}

void Player::enterRoom(Room* roomToEnter)
{
	this->world->setCurrentRoom(roomToEnter);
	roomToEnter->printDescription();
}

void Player::addToInventory(GameObject* objectToAdd)
{
	this->inventory.insert({ objectToAdd->getName(), objectToAdd });
}
