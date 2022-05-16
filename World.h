#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Room.h"
//#include "Player.h"

class World
{
private:
	//std::vector<Room*> rooms = { &sampleRoom1, &sampleRoom2 };
	std::map<std::string, Room> rooms;
	Room* currentRoom;
	//Room sampleRoom1 = getSampleRoom1();
	//Room sampleRoom2 = getSampleRoom2();
	GameObject sampleObject1;
	GameObject sampleObject2;
public:
	World()
	{
		this->rooms.insert({ getSampleRoom1().getName(), getSampleRoom1() });
		this->rooms.insert({ getSampleRoom2().getName(), getSampleRoom2() });
		this->rooms.at("Sample Room 1").setExits(&(this->rooms.at("Sample Room 2")), NULL,
			NULL, NULL, NULL, NULL);
		this->rooms.at("Sample Room 2").setExits(NULL, NULL, &(this->rooms.at("Sample Room 1")),
			NULL, NULL, NULL);
		this->currentRoom = &(this->rooms.at("Sample Room 1"));
	};
	void testRooms();
	void setRooms();
	void setCurrentRoom(Room* roomToSet);
	Room* getCurrentRoom() { return this->currentRoom; }
	Room getSampleRoom1();
	Room getSampleRoom2();
};

