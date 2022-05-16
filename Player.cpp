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

void Player::printInventory()
{
	std::cout << "You currently have:" << std::endl;
	std::map<std::string, GameObject*>::iterator it;
	for (it = this->inventory.begin(); it != this->inventory.end(); it++)
	{
		std::cout << it->first << std::endl;
	}
}

void Player::move(std::string direction)
{
	if (this->getWorld()->getCurrentRoom()->getRoom(direction))
		this->enterRoom(this->getWorld()->getCurrentRoom()->getRoom(direction));
	else
		std::cout << "You can't go that way." << std::endl;
}
