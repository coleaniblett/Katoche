#include "Player.h"

// constructors
Player::Player()
{
	this->world = new World;
	this->continueGame = true;
	this->shadowState = 0;
}

Player::Player(World* worldToSet)
{
	this->world = worldToSet;
	this->continueGame = true;
	this->shadowState = 0;
}

// inventory methods
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

GameObject* Player::getObject(std::string objectToGet)
{
	return this->inventory.at(objectToGet);
}

// movement methods
void Player::enterRoom(Room* roomToEnter)
{
	this->world->setCurrentRoom(roomToEnter);
	std::cout << std::endl;
	std::cout << "Current Room: " << this->world->getCurrentRoom()->getName() << std::endl;
	roomToEnter->printDescription();
}

void Player::move(std::string direction)
{
	if (this->getWorld()->getCurrentRoom()->getRoom(direction))
		this->enterRoom(this->getWorld()->getCurrentRoom()->getRoom(direction));
	else
		std::cout << "You can't go that way." << std::endl;
}

// shadowState methods
void Player::printShadowDescription()
{
	if (this->shadowState == 0)
		std::cout << "Your shadow looks like it always has." << std::endl;
}

// other methods
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
