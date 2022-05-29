#pragma once
#include <string>
#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>
#include "GameObject.h"
class Room
{
private:
	std::string name;
	std::string description;
	std::map<std::string, GameObject*> contents;
	bool containsRoom;
	Room* inner;
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
	std::string getName() { return this->name; }
	void setExits(Room* innerToSet, Room* northToSet, Room* westToSet, Room* southToSet,
		Room* eastToSet, Room* upToSet, Room* downToset);
	Room* getRoom(std::string roomToGet);
	GameObject* getObject(std::string objectToGet);
	void addObject(GameObject* objectToAdd);
	void removeObject(std::string objectToRemove);
	bool containsObject(std::string objectToCheck);
	void printDescription();
};
