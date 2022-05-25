#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Room.h"

class World
{
private:
	std::map<std::string, Room> rooms;
	Room* currentRoom;
	std::map<std::string, GameObject> objects;
	Room getOutsideEntrance();
	Room getAntechamber();
	Room getEventHorizon();
	Room getFirstRoom();
	Room getFountainRoom();
	Room getStableRoom();
	Room getTempleRoom();
	Room getShroomRoom();
	Room getLibrary();
public:
	World();
	void setCurrentRoom(Room* roomToSet);
	Room* getCurrentRoom() { return this->currentRoom; }	
};

