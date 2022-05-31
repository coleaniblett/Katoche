#pragma once
#include <string>
#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "GameObject.h"
class Room
{
private:
	std::string name;
	std::string description;
	std::map<std::string, GameObject*> contents;
	bool containsRoom;
	std::shared_ptr<Room> inner;
	std::shared_ptr<Room> north;
	std::shared_ptr<Room> west;
	std::shared_ptr<Room> south;
	std::shared_ptr<Room> east;
	std::shared_ptr<Room> up;
	std::shared_ptr<Room> down;
public:
	Room();
	Room(
		std::string nameToSet,
		std::string descriptionToSet
	);
	std::string getDescription() { return this->description; }
	std::string getName() { return this->name; }
	void setExits(std::shared_ptr<Room> innerToSet, std::shared_ptr<Room> northToSet, 
		std::shared_ptr<Room> westToSet, std::shared_ptr<Room> southToSet, std::shared_ptr<Room> eastToSet, 
		std::shared_ptr<Room> upToSet, std::shared_ptr<Room> downToset);
	void printExits();
	std::shared_ptr<Room> getRoom(std::string roomToGet);
	GameObject* getObject(std::string objectToGet);
	void addObject(GameObject* objectToAdd);
	void removeObject(std::string objectToRemove);
	bool containsObject(std::string objectToCheck);
	void printDescription();
};
