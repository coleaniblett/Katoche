#include "Room.h"

Room::Room()
{
	this->name = "";
	this->description = "";
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

void Room::setExits(Room* northToSet, Room* westToSet, Room* southToSet,
	Room* eastToSet, Room* upToSet, Room* downToset)
{
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

void Room::printDescription()
{
	std::cout << this->description << std::endl;
}
