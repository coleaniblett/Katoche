#include "Player.h"

// constructors
Player::Player()
{
	this->world = new World;
	this->continueGame = true;
	this->shadowState = 0;
	this->leadingHorse = false;
}

Player::Player(World* worldToSet)
{
	this->world = worldToSet;
	this->continueGame = true;
	this->shadowState = 0;
	this->leadingHorse = false;
}

// inventory methods
void Player::addToInventory(std::shared_ptr<GameObject> objectToAdd)
{
	if (objectToAdd->getName() == "ring")
	{
		this->world->getMagicRings()->addRing();
		std::shared_ptr<GameObject> ring = this->world->getMagicRings()->getRings();
		if (this->hasObject("ring"))
			this->inventory.erase("ring");
		else if (this->hasObject("rings"))
			this->inventory.erase("rings");
		this->inventory.insert({ ring->getName(), ring });
	}
	else
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
	std::map<std::string, std::shared_ptr<GameObject>>::iterator it;
	for (it = this->inventory.begin(); it != this->inventory.end(); it++)
	{
		std::cout << it->first << std::endl;
	}
}

std::shared_ptr<GameObject> Player::getObject(std::string objectToGet)
{
	return this->inventory.at(objectToGet);
}

void Player::getObjectFromContainer(std::string objectToGet, std::string container)
{
	std::shared_ptr<Room> curRoom = this->world->getCurrentRoom();
	if (curRoom->containsObject(container))
	{
		if (typeid(*curRoom->getObject(container)) == typeid(class ContainerObject))
		{
			auto containerToUse = std::dynamic_pointer_cast<ContainerObject>(curRoom->getObject(container));
			if (containerToUse->checkIsOpen())
			{
				if (containerToUse->hasObject(objectToGet))
				{
					std::cout << "You take the " << objectToGet << " from the " << container << ".\n";
					this->addToInventory(containerToUse->getObject(objectToGet));
					containerToUse->removeObject(objectToGet);
				}
				else
					std::cout << "There is no " << objectToGet << " in the " << container << ".\n";
			}
			else
				std::cout << "The " << container << " is closed.\n";
		}
		else
			std::cout << "The " << container << " is not a container.\n";
	}
}

void Player::getObjectFromSearchedObject(std::string objectToGet, std::string searchedObject)
{
	std::shared_ptr<Room> curRoom = this->world->getCurrentRoom();
	if (curRoom->containsObject(searchedObject))
	{
		if (typeid(*curRoom->getObject(searchedObject)) == typeid(class SearchableObject))
		{
			auto objectToUse = std::dynamic_pointer_cast<SearchableObject>(curRoom->getObject(searchedObject));
			if (objectToUse->getHasBeenSearched())
			{
				if (objectToUse->hasObject(objectToGet))
				{
					std::cout << "You take the " << objectToGet << " from the " << searchedObject << ".\n";
					this->addToInventory(objectToUse->getObject(objectToGet));
					objectToUse->removeObject(objectToGet);
				}
				else
					std::cout << "The " << searchedObject << " doesn't have a " << objectToGet << ".\n";
			}
			else
				std::cout << "The " << searchedObject << " doesn't have a " << objectToGet << ".\n";
		}
		else
			std::cout << "You can't take anything from the " << searchedObject << ".\n";
	}
}

// movement methods
void Player::enterRoom(std::shared_ptr<Room> roomToEnter)
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
		std::cout << "Your feet touch the ground after a short drop, and the darkness disappears in an instant, seemingly out of nowhere.\n";
	roomToEnter->printDescription();
	if (this->leadingHorse == true && newRoomName == "Fountain Room")
	{
		std::cout << "Upon entering, the horse calmly walks up to the fountain and begins to drink from its water.\n"
			<< "It shows no sign of stopping.\n";
		std::shared_ptr<GameObject> horse(new GameObject(
			"horse",
			"It just keeps drinking. It looks transfixed and won't be budged.",
			"A horse stands next to the fountain, drinking incessantly.\n",
			false
		));
		roomToEnter->addObject(horse);
		this->leadingHorse = false;
	}
}

void Player::move(std::string direction)
{
	// special functionality for forest exploration
	if (this->world->getCurrentRoom()->getName() == "Forest"
		&& direction != "up" && direction != "down")
	{
		int roomCode = (rand() % 7);
		if (roomCode <= 3)
			this->enterRoom(this->world->getRoom("Forest"));
		else if (roomCode <= 5)
			this->enterRoom(this->world->getRoom("Outside Entrance"));
		else
			this->enterRoom(this->world->getRoom("Outside Exit"));
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
		<< "    - QUIT to exit the game\n\n";
}

void Player::read()
{
	// UNDER CONSTRUCTION
	std::cout << "Book reading functionality under construction\n";
}

void Player::openObject(std::string objectToOpen)
{
	std::shared_ptr<Room> curRoom = this->world->getCurrentRoom();
	if (curRoom->containsObject(objectToOpen))
	{
		if (typeid(*curRoom->getObject(objectToOpen)) == typeid(class ContainerObject))
		{
			auto containerToUse = std::dynamic_pointer_cast<ContainerObject>(curRoom->getObject(objectToOpen));
			if (!containerToUse->checkIsOpen())
			{
				std::cout << "You open the " << objectToOpen << ".\n";
				containerToUse->open();
				containerToUse->printContents();
			}
			else
				std::cout << "The " << objectToOpen << " is already open.\n";
		}
		else
			std::cout << "You can't open the " << objectToOpen << ".\n";
	}
	else
		std::cout << "There is no " << objectToOpen << ".\n";
}

void Player::closeObject(std::string objectToClose)
{
	std::shared_ptr<Room> curRoom = this->world->getCurrentRoom();
	if (curRoom->containsObject(objectToClose))
	{
		if (typeid(*curRoom->getObject(objectToClose)) == typeid(class ContainerObject))
		{
			auto containerToUse = std::dynamic_pointer_cast<ContainerObject>(curRoom->getObject(objectToClose));
			if (containerToUse->checkIsOpen())
			{
				std::cout << "You close the " << objectToClose << ".\n";
				containerToUse->close();
			}
			else
				std::cout << "The " << objectToClose << " is already closed.\n";
		}
		else
			std::cout << "You can't close the " << objectToClose << ".\n";
	}
	else
		std::cout << "There is no " << objectToClose << ".\n";
}

void Player::searchObject(std::string objectToSearch)
{
	std::shared_ptr<Room> curRoom = this->world->getCurrentRoom();
	if (curRoom->containsObject(objectToSearch))
	{
		if (objectToSearch == "grave" && curRoom->containsObject(objectToSearch))
		{
			if (this->inventory.count("shovel"))
			{
				auto objectToUse = std::dynamic_pointer_cast<SearchableObject>(curRoom->getObject(objectToSearch));
				objectToUse->setHasBeenSearched();
				std::cout << "Using your shovel, you dig up the grave.\n";
				objectToUse->printContents();
			}
			else
			{
				std::cout << "You can't dig up this ground with your bare hands.\n";
			}
			return;
		}
		if (typeid(*curRoom->getObject(objectToSearch)) == typeid(class SearchableObject))
		{
			auto objectToUse = std::dynamic_pointer_cast<SearchableObject>(curRoom->getObject(objectToSearch));
			objectToUse->setHasBeenSearched();
			objectToUse->printContents();
		}
		else
			std::cout << "You can't search the " << objectToSearch << ".\n";
	}
	else
		std::cout << "There is no " << objectToSearch << " to search.\n";
}

void Player::leadHorse()
{
	std::shared_ptr<Room> curRoom = this->world->getCurrentRoom();
	if (curRoom->containsObject("horse"))
	{
		this->leadingHorse = true;
		std::cout << "Although the horse has no harness, it seems willing to follow you.\n";
		curRoom->removeObject("horse");
	}
	else
		std::cout << "There is no horse here.\n";
}