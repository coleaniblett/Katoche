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
	std::string currentRoomName = this->world->getCurrentRoom()->getName();
	std::string newRoomName = roomToEnter->getName();
	bool droppingDown = false;
	if (currentRoomName == "Event Horizon" && newRoomName == "First Room")
		droppingDown = true;
	this->world->setCurrentRoom(roomToEnter);
	std::cout << std::endl;
	std::cout << "Current Room: " << this->world->getCurrentRoom()->getName() << std::endl;
	if (droppingDown == true)
		std::cout << "Your feet touch the ground after a short drop, and the darkness disappears in an instant, seemingly out of nowhere.";
	roomToEnter->printDescription();
}

void Player::move(std::string direction)
{
	// special functionality for forest exploration
	if (this->world->getCurrentRoom()->getName() == "Forest"
		&& direction != "up" && direction != "down")
	{
		int roomCode = (rand() % 7);
		if (roomCode <= 3)
			this->enterRoom(this->getWorld()->getRoom("Forest"));
		else if (roomCode <= 5)
			this->enterRoom(this->getWorld()->getRoom("Outside Entrance"));
		else
			this->enterRoom(this->getWorld()->getRoom("Outside Exit"));
	}
	// standard functionality
	else
	{
		if (this->getWorld()->getCurrentRoom()->getRoom(direction))
			this->enterRoom(this->getWorld()->getCurrentRoom()->getRoom(direction));
		else
			std::cout << "You can't go that way." << std::endl;
	}
}

void Player::jump()
{
	std::string currentRoomName = this->world->getCurrentRoom()->getName();
	if (currentRoomName == "Event Horizon")
	{
		this->move("down");
	}
	else
	{
		std::cout << "You jump. It's not particularly impressive.\n";
		if (currentRoomName == "First Room")
		{
			std::cout << "You can't jump high enough to reach the rope.\n";
		}
		else if (currentRoomName == "Fountain Room")
		{
			std::cout << "You can't jump high enough to reach the bow.\n";
		}
	}
}

// shadowState methods
void Player::printShadowDescription()
{
	if (this->shadowState == 0)
		std::cout << "Your shadow moves as you rotate, so you cannot turn and face it completely, but it otherwise looks normal from what you can see over your shoulder." << std::endl;
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
