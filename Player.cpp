#include "Player.h"

// constructors
Player::Player()
{
	this->world = new World;
	this->continueGame = true;
	this->shadowState = 0;
	this->leadingHorse = false;
	this->esotericKnowledge = 0;
}

Player::Player(World* worldToSet)
{
	this->world = worldToSet;
	this->continueGame = true;
	this->shadowState = 0;
	this->leadingHorse = false;
	this->esotericKnowledge = 0;
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
	std::shared_ptr<Room> curRoom = this->world->getCurrentRoom();
	std::string currentRoomName = curRoom->getName();
	std::string newRoomName = roomToEnter->getName();
	bool droppingDown = false;
	if (currentRoomName == "Event Horizon" && newRoomName == "First Room")
		droppingDown = true;
	if (newRoomName != "Graveyard Room" || !this->world->getShadowSelfAlive())
	{
		this->world->setCurrentRoom(roomToEnter);
		std::cout << std::endl;
		std::cout << "Current Room: " << this->world->getCurrentRoom()->getName() << std::endl;
		if (droppingDown == true)
			std::cout << "Your feet touch the ground after a short drop, and the darkness disappears in an instant, seemingly out of nowhere.\n";
		roomToEnter->printDescription();
	}
	else
	{
		std::cout << "As you walk to the north side of the room, the figure of you walks forward "
			<< "in an identical manner. Upon reaching the north exit, you find yourself standing "
			<< "in the doorway of an identical room, seeing the same image of your duplicate "
			<< "facing away from you that you witnessed upon stepping into the last room.\n";
	}
	// special functionality for leading horse
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
	// special functionality for climbing horse in Fountain Room
	if (currentRoomName == "Fountain Room" && curRoom->containsObject("bow and quiver"))
		curRoom->getObject("bow and quiver")->setCanbeTaken(false);
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

void Player::dig()
{
	if (this->world->getCurrentRoom()->getName() == "Graveyard Room")
		this->searchObject("grave");
	else
		std::cout << "You can't dig here.\n";
}

void Player::eat(std::string objectToEat)
{
	if (objectToEat == "red mushroom" || objectToEat == "purple mushroom" ||
		objectToEat == "brown mushroom")
	{
		if (this->hasObject(objectToEat) || this->world->getCurrentRoom()->containsObject(objectToEat))
		{
			if (objectToEat == "red mushroom")
			{
				this->esotericKnowledge += 1;
				std::cout << "You eat the mushroom. You feel some new profound understanding of reality itself, "
					<< "as if you can see the hidden stitches of this dimension.\n";
			}
			else if (objectToEat == "purple mushroom")
			{
				std::cout << "You eat the purple mushroom and a powerful nausea quickly overtakes you. "
					<< "You fall to your knees and the room seems to spin around you.\n"
					<< "You have died.\n";
				this->continueGame = false;
			}
			else if (objectToEat == "brown mushroom")
			{
				std::cout << "You eat the mushroom. Nothing seems to happen.\n";
			}
		}
		else
			std::cout << "There is no " << objectToEat << ".\n";
	}
	else
		std::cout << "You cant' eat that.\n";
}

void Player::climb(std::string objectToClimb)
{
	std::shared_ptr<Room> curRoom = this->world->getCurrentRoom();
	if (!curRoom->containsObject(objectToClimb))
	{
		std::cout << "What " << objectToClimb << "?\n";
		return;
	}
	if (objectToClimb == "rope")
	{
		if (curRoom->getName() == "Antechamber")
		{
			this->move("down");
		}
		else if (curRoom->getName() == "First Room")
		{
			this->move("up");
		}
	}
	else if (objectToClimb == "horse")
	{
		std::cout << "You climb onto the back of the horse.\n";
		if (curRoom->getName() == "Fountain Room")
		{
			curRoom->getObject("bow and quiver")->setCanbeTaken(true);
		}
	}
	else
	{
		std::cout << "You can't climb that.\n";
	}
}

void Player::attack(std::string target, std::string weapon)
{
	if (weapon == "knife" || weapon == "bow and quiver" || weapon == "sword" || weapon == "shovel")
	{
		if (this->hasObject(weapon))
		{
			if (target == "shadow self")
			{
				if (weapon == "bow and quiver")
				{
					std::cout << "You place an arrow in your bow and pull the string back. With "
						<< "careful aim, you point the arrow at the being ahead of you and "
						<< "let go. The arrow lands in his back and he shrieks, twisting and falling "
						<< "to the ground. It's the first movement you've seen from him that wasn't a "
						<< "perfect mimickry of your own movements. He now lies in the floor in a "
						<< "puddle of his own blood.\n";
					this->world->setShadowSelfAlive(false);
					this->getWorld()->getCurrentRoom()->getObject("shadow self")->setDescription(
						"He's a complete duplicate of you, only deader."
					);
					this->getWorld()->getCurrentRoom()->getObject("shadow self")->setLocationDescription(
						""
					);
					this->getWorld()->getCurrentRoom()->setDescription(
						"The corpse of your double lies on the floor of this room.\n"
					);
				}
				else
				{
					std::cout << "As you move forward to attack with your " << weapon
						<< " the figure ahead of you also moves head with the exact same "
						<< "movements as you. Stepping after it, you find yourself in a "
						<< "doorway identical to the one you started in, staring at "
						<< "an identical room, the other figure just as far away from you "
						<< "as before.\n";
				}
			}
			else if (target == "yourself")
			{
				std::cout << "Why would you want to hurt yourself?\n";
			}
			else
			{
				std::cout << "Why would you want to hurt a " << target << "?\n";
			}
		}
		else
		{
			std::cout << "You don't have one of those.\n";
		}
	}
	else
	{
		std::cout << "That's not a weapon.\n";
	}
}

void Player::sleep()
{
	if (this->world->getCurrentRoom()->getName() == "Your Bedroom")
	{
		std::cout << "You lie down on your old bed and quickly nod off.\n\n"
			<< "Current Room: ???\n"
			<< "You find yourself in a new room - or is it a room? The walls and ceiling "
			<< "seem to retreat in the distance. You're in a white robe, kneeling "
			<< "before a set of stairs that lead up to a throne. An old bearded man sits "
			<< "there.\n";
		int numRings = this->world->getMagicRings()->getNumRings();
		if (numRings == 0)
		{
			std::cout << "He frowns at you.\n \"It seems that you are only at the start "
				<< "of your journey,\" he says to you. \"No matter.\"\n";
		}
		else if (numRings == 1)
		{
			std::cout << "He looks at you.\n\ \"It seems you've found one of my rings.\", "
				<< "he says to you. \"Have you noticed its power? How it changes the "
				<< "world around you?\" He runs his hand through his beard. \"But you "
				<< "still have much to learn.\"\n";
		}
		else
		{
			std::cout << "He smiles at you. \"Already, you've found " << numRings << " of my rings. "
				<< "You are doing well.\"\n";
		}
		std::cout << "The old man closes his eyes and raises his hands. As he speaks, his "
			<< "voice seems to come from within your own mind.\n"
			<< "BE\nEVERYWHERE\nFOREVER\n";
		std::cout << "?od uoy od tahW ";
		std::string userInput;
		std::getline(std::cin, userInput);
		std::cout << "\nCurrent Room: Your Bedroom\n"
			<< "You wake up in your bed.\n";
	}
	else
	{
		std::cout << "You can't sleep here.\n";
	}
}

void Player::drop(std::string objectToDrop)
{
	std::shared_ptr<Room> curRoom = this->world->getCurrentRoom();
	if (objectToDrop == "horse")
	{
		if (this->leadingHorse)
		{
			std::shared_ptr<GameObject> horse(new GameObject(
				"horse",
				"The horse appears calm, but when you look into its eyes you see what looks like remarkable awareness. But then again, you've never spent much time around horses. Have you?",
				"In the room stands a tall bay horse.\n",
				false
			));
			curRoom->addObject(horse);
			std::cout << "You slowly wave your hands at the floor in a gesture to the horse to stay. "
				<< "It seems to understand.\n";
			this->leadingHorse = false;
		}
		else
		{
			std::cout << "You're not leading a horse.\n";
		}
	}
}