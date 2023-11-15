
/*******************************************************************************
*	Inventory.cpp                                                              *
*                                                                              *
*	Implements the functionality of the Inventory class                        *
*                                                                              *
*******************************************************************************/

#include "Inventory.h"

void Inventory::addToInventory(std::shared_ptr<GameObject> objectToAdd)
{
	if (objectToAdd->getName() == "ring")
	{
		this->magicRings->addRing();
		std::shared_ptr<GameObject> ring = this->magicRings->getRings();
		if (this->hasObject("ring"))
			this->inventory.erase("ring");
		else if (this->hasObject("rings"))
			this->inventory.erase("rings");
		this->inventory.insert({ ring->getName(), ring });
		int numRings = this->magicRings->getNumRings();
	}
	else
		this->inventory.insert({ objectToAdd->getName(), objectToAdd });
}

bool Inventory::hasObject(std::string objectToCheck)
{
	if (this->inventory.count(objectToCheck))
		return true;
	else
		return false;
}

void Inventory::printInventory()
{
	std::cout << "You currently have:" << std::endl;
	std::map<std::string, std::shared_ptr<GameObject>>::iterator it;
	for (it = this->inventory.begin(); it != this->inventory.end(); it++)
	{
		std::cout << it->first << std::endl;
	}
}

std::shared_ptr<GameObject> Inventory::getObject(std::string objectToGet)
{
	return this->inventory.at(objectToGet);
}

void Inventory::drop(std::string objectToDrop, std::shared_ptr<Room> curRoom)
{
	// special functionality for rings
	if (objectToDrop == "ring" || objectToDrop == "rings")
	{
		std::cout << "Something tells you it wouldn't be a good idea to lose these rings.\n";
		return;
	}
	// standard functionality
	else if (this->hasObject(objectToDrop))
	{
		std::string newLocationDescription = "A " + objectToDrop + " lies on the floor.\n";
		this->getObject(objectToDrop)->setLocationDescription(newLocationDescription);
		curRoom->addObject(this->getObject(objectToDrop));
		this->inventory.erase(objectToDrop);
		std::cout << "You place the " << objectToDrop << " on the ground.\n";
		if (objectToDrop == "candle" && curRoom->getName() == "Temple Room")
		{
			std::cout << "After setting the candle bown before the statue, it suddenly lights up.\n";
		}
	}
	else
	{
		std::cout << "You don't have a " << objectToDrop << ".\n";
	}
}