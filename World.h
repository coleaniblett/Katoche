#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Room.h"
//#include "Player.h"

class World
{
private:
	std::vector<Room*> rooms = { &sampleRoom1, &sampleRoom2 };
	Room* currentRoom;
	Room sampleRoom1 = getSampleRoom1();
	Room sampleRoom2 = getSampleRoom2();
public:
	World()
	{
		this->currentRoom = rooms.at(0);
	};
	void testRooms();
	void setRooms();
	void setCurrentRoom(Room* roomToSet);
	Room* getCurrentRoom() { return this->currentRoom; }
	Room getSampleRoom1();
	Room getSampleRoom2();
};

