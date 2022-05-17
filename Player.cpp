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

GameObject* Player::getObject(std::string objectToGet)
{
	return this->inventory.at(objectToGet);
}

void Player::addToInventory(GameObject* objectToAdd)
{
	this->inventory.insert({ objectToAdd->getName(), objectToAdd });
}

bool Player::hasObject(std::string objectToCheck)
{
	if (this->inventory.count(objectToCheck))
		return true;
	else
		return false;
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

void Player::getHelp()
{
	std::cout << "Experiment with different commands to solve puzzles and progress. "
		<< "Example commands include:\n"
		<< "    - NORTH, EAST, SOUTH, WEST, UP, and DOWN to travel\n"
		<< "    - TAKE or GET to pick up objects\n"
		<< "    - INVENTORY to check your current items\n"
		<< "    - EXAMINE to look at something more closely\n"
		<< "    - HELP to print this message again\n" 
		<< "    - QUIT to exit the game\n" << std::endl;
}
