#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Room.h"
//#include "Player.h"

class World
{
private:
	std::map<std::string, Room> rooms;
	Room* currentRoom;
	GameObject sampleObject1;
	GameObject sampleObject2;
public:
	World();
	void setCurrentRoom(Room* roomToSet);
	Room* getCurrentRoom() { return this->currentRoom; }
	Room getSampleRoom1();
	Room getSampleRoom2();
};

