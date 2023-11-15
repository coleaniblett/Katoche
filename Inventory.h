// Inventory.h
// Defines the Inventory class, responsible for managing the player's items and belongings in the game

#pragma once
#include <map>
#include <memory>
#include "GameObject.h"
#include "MagicRings.h"
#include "Room.h"

class Inventory
{
private:
	std::map <std::string, std::shared_ptr<GameObject>> inventory;
	std::shared_ptr<MagicRings> magicRings;
public:
	Inventory() { this->magicRings.reset(new MagicRings()); }
	void addToInventory(std::shared_ptr<GameObject> objectToAdd);
	bool hasObject(std::string objectToCheck);
	void printInventory();
	std::shared_ptr<GameObject> getObject(std::string objectToGet);
	void drop(std::string objectToDrop, std::shared_ptr<Room> curRoom);
	std::shared_ptr<MagicRings> getMagicRings() { return this->magicRings; }
};

