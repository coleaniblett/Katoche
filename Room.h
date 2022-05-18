#pragma once
#include <string>
#include <iostream>
#include <map>
#include "GameObject.h"
class Room
{
private:
	std::string name;
	std::string description;
	std::map<std::string, GameObject*> contents;
	bool containsRoom;
	Room* roomContained;
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
		std::string descriptionToSet,
		bool containsRoomToSet
	);
	std::string getDescription() { return this->description; }
	std::string getName() { return this->name; }
	void setExits(Room* northToSet, Room* westToSet, Room* southToSet,
		Room* eastToSet, Room* upToSet, Room* downToset);
	void setRoomContained(Room* roomToSet) { this->roomContained = roomToSet; }
	bool getContainsRoom() { return this->containsRoom; }
	Room* getRoomContained() { return this->roomContained; }
	Room* getRoom(std::string roomToGet);
	GameObject* getObject(std::string objectToGet);
	void addObject(GameObject* objectToAdd);
	void removeObject(std::string objectToRemove);
	bool containsObject(std::string objectToCheck);
	void printDescription();
};
