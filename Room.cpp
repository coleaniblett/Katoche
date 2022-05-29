#include "Room.h"

Room::Room()
{
	this->name = "";
	this->description = "";
	this->inner = new Room;
	this->north = new Room;
	this->west = new Room;
	this->south = new Room;
	this->east = new Room;
	this->up = new Room;
	this->down = new Room;
}

Room::Room(
	std::string nameToSet,
	std::string descriptionToSet
)
{
	this->name = nameToSet;
	this->description = descriptionToSet;
}

void Room::setExits(Room* innerToSet, Room* northToSet, Room* westToSet, Room* southToSet,
	Room* eastToSet, Room* upToSet, Room* downToset)
{
	delete this->inner;
	this->inner = innerToSet;
	delete this->north;
	this->north = northToSet;
	delete this->west;
	this->west = westToSet;
	delete this->south;
	this->south = southToSet;
	delete this->east;
	this->east = eastToSet;
	delete this->up;
	this->up = upToSet;
	delete this->down;
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

Room* Room::getRoom(std::string roomToGet)
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

GameObject* Room::getObject(std::string objectToGet)
{
	return this->contents.at(objectToGet);
}

void Room::addObject(GameObject* objectToAdd)
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
	std::map<std::string, GameObject*>::iterator it;
	std::cout << this->description;
	for (it = this->contents.begin(); it != this->contents.end(); it++)
	{
		std::cout << it->second->getLocationDescription();
	}
	this->printExits();
}
