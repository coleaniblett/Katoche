#include "Room.h"

Room::Room()
{
	this->name = "";
	this->description = "";
}

Room::Room(
	std::string nameToSet,
	std::string descriptionToSet
)
{
	this->name = nameToSet;
	this->description = descriptionToSet;
}

void Room::setExits(std::shared_ptr<Room> innerToSet, std::shared_ptr<Room> northToSet,
	std::shared_ptr<Room> westToSet, std::shared_ptr<Room> southToSet, std::shared_ptr<Room> eastToSet,
	std::shared_ptr<Room> upToSet, std::shared_ptr<Room> downToset)
{
	this->inner = innerToSet;
	this->north = northToSet;
	this->west = westToSet;
	this->south = southToSet;
	this->east = eastToSet;
	this->up = upToSet;
	this->down = downToset;
}

void Room::printExits()
{
	if (this->name == "Outside Entrance" || this->name == "Outside Exit")
		return;
	std::vector<std::string> exits;
	if (this->north != NULL)
		exits.push_back("north"); 
	if (this->west != NULL)
		exits.push_back("west"); 
	if (this->south != NULL)
		exits.push_back("south"); 
	if (this->east != NULL)
		exits.push_back("east");
	if (exits.size() == 0)
		return;
	else if (exits.size() == 1)
		std::cout << "There is one exit to the " << exits.at(0) << "\n";
	else
	{
		std::cout << "There are exits to the " << exits.at(0);
		exits.erase(exits.begin());
		while (exits.size() > 1)
		{
			std::cout << ", " << exits.at(0);
			exits.erase(exits.begin());
		}
		std::cout << " and " << exits.at(0) << ".\n";
	}
}

std::shared_ptr<Room> Room::getRoom(std::string roomToGet)
{
	if (roomToGet == "inner")
		return this->inner;
	else if (roomToGet == "north")
		return this->north;
	else if (roomToGet == "east")
		return this->east;
	else if (roomToGet == "south")
		return this->south;
	else if (roomToGet == "west")
		return this->west;
	else if (roomToGet == "up")
		return this->up;
	else if (roomToGet == "down")
		return this->down;
	else
	{
		std::cout << "Error in Room::getRoom function";
		return NULL;
	}
}

std::shared_ptr<GameObject> Room::getObject(std::string objectToGet)
{
	return this->contents.at(objectToGet);
}

void Room::addObject(std::shared_ptr<GameObject> objectToAdd)
{
	contents.insert({ objectToAdd->getName(), objectToAdd });
}

void Room::removeObject(std::string objectToRemove)
{
	contents.erase(objectToRemove);
}

bool Room::containsObject(std::string objectToCheck)
{
	if (this->contents.count(objectToCheck))
		return true;
	else
		return false;
}

void Room::printDescription()
{
	std::map<std::string, std::shared_ptr<GameObject>>::iterator it;
	std::cout << this->description;
	for (it = this->contents.begin(); it != this->contents.end(); it++)
	{
		std::cout << it->second->getLocationDescription();
	}
	this->printExits();
}
