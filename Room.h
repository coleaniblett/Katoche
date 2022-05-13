#pragma once
#include <string>
#include <iostream>
class Room
{
private:
	std::string name;
	std::string description;
	Room* north;
	Room* west;
	Room* south;
	Room* east;
	Room* up;
	Room* down;
public:
	Room();
	Room(
		std::string nameToSet,
		std::string descriptionToSet
	);
	std::string getDescription() { return this->description; }
	void setExits(Room* northToSet, Room* westToSet, Room* southToSet,
		Room* eastToSet, Room* upToSet, Room* downToset);
	void printDescription();
};
