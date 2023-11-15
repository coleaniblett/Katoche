
/*******************************************************************************
 *  CommandInterpreter.cpp                                                     *
 *                                                                             *
 *  Defines the World class, representing the game world with rooms and        *
 *	objects                                                                    *
 *                                                                             *
 ******************************************************************************/

#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "Room.h"
#include "ContainerObject.h"
#include "SearchableObject.h"
#include "MagicRings.h"

class World
{
private:
	std::map<std::string, std::shared_ptr<Room>> rooms;
	std::shared_ptr<Room> currentRoom;
	//std::shared_ptr<MagicRings> magicRings;
	bool shadowSelfAlive;
	int neverRoomTime;
	std::shared_ptr<Room> getOutsideEntrance();
	std::shared_ptr<Room> getAntechamber();
	std::shared_ptr<Room> getEventHorizon();
	std::shared_ptr<Room> getFirstRoom();
	std::shared_ptr<Room> getFountainRoom();
	std::shared_ptr<Room> getStableRoom();
	std::shared_ptr<Room> getTempleRoom();
	std::shared_ptr<Room> getShroomRoom();
	std::shared_ptr<Room> getLibrary();
	std::shared_ptr<Room> getYourBedroom();
	std::shared_ptr<Room> getInfinityRoom();
	std::shared_ptr<Room> getArmory();
	std::shared_ptr<Room> getGraveyardRoom();
	std::shared_ptr<Room> getNeverRoom();
	std::shared_ptr<Room> getForeverRoom();
	std::shared_ptr<Room> getFinalRoom();
	std::shared_ptr<Room> getForest();
	std::shared_ptr<Room> getOutsideExit();
public:
	World();
	std::shared_ptr<Room> getRoom(std::string roomToGet) { return this->rooms.at(roomToGet); }
	void setCurrentRoom(std::shared_ptr<Room> roomToSet);
	void setShadowSelfAlive(bool valueToSet) { this->shadowSelfAlive = valueToSet; }
	bool getShadowSelfAlive() { return this->shadowSelfAlive; }
	std::shared_ptr<Room> getCurrentRoom() { return this->currentRoom; }	
	//std::shared_ptr<MagicRings> getMagicRings() { return this->magicRings; }
	int getNeverTime() { return this->neverRoomTime; }
	void incNeverTime() { this->neverRoomTime += 1; }
	void setForeverRoom();
	void resetNeverTime() { this->neverRoomTime = 0; }
};

