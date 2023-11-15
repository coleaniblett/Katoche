// CommandInterpreter.h
// Defines the command interpreter class, responsible for interpreting user commands

#pragma once
#include <string>
#include <iostream>
#include "Inventory.h"
#include "Player.h"
#include "World.h"
class CommandInterpreter
{
private:
	Player* player;
	World* world;
public:
	CommandInterpreter();
	CommandInterpreter(Player* playerToSet, World* worldToSet);
	World* getWorld() { return this->world; }
	Player* getPlayer() { return this->player; }
	std::string standardizeDirObject(std::string dirObject);
	void interpretSimpleCommand(std::string action);
	void interpretSimpleCommand(std::string action, std::string identifier);
	void interpretCommand(std::string action, std::string dirObject);
	void interpretCommand(std::string action, std::string dirObject, std::string identifier);
	void interpretCommand(std::string action, std::string dirObject, std::string identifier, std::string secObject);
	bool checkNeverTime();
};
