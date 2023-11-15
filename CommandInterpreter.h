
/*******************************************************************************
*	CommandInterpreter.h                                                       *
*                                                                              *
*	Defines the command interpreter class, responsible for interpreting user   *
*	commands.                                                                  *
*                                                                              *
*******************************************************************************/

#pragma once
#include <string>
#include <iostream>
#include <functional>
#include "Inventory.h"
#include "Player.h"
#include "World.h"

using CommandFunction = std::function<void()>;

class CommandInterpreter
{
private:
	Player* player;
	World* world;
	std::map<std::string, std::string> synonymMap = {
		{"opening", "entrance"},
		{"building", "entrance"},
		{"structure", "entrance"},
		{"body", "corpse"},
		{"dead body", "corpse"},
		{"dead person", "corpse"},
		{"person", "shadow self"},
		{"figure", "shadow self"},
		{"bow", "bow and quiver"},
		{"quiver", "bow and quiver"}
	};
	std::map<std::string, CommandFunction> simpleCommandMap = {
		// Meta commands
		{"quit", [this]() { this->player->setContinueGame(false); }},
		{"help", [this]() { this->player->getHelp(); }},
		// Inventory commands
		{"take", []() { std::cout << "Take what?\n"; }},
		{"get", []() { std::cout << "Get what?\n"; }},
		{"inventory", [this]() { this->player->getInventory()->printInventory(); }},
		// Movement commands
		// TODO: write "exit" command
		{"north", [this]() { this->player->move("north"); }},
		{"east", [this]() { this->player->move("east"); }},
		{"south", [this]() { this->player->move("south"); }},
		{"west", [this]() { this->player->move("west"); }},
		{"up", [this]() { this->player->move("up"); }},
		{"down", [this]() { this->player->move("down"); }},
		{"enter", []() { std::cout << "Enter what?\n"; }},
		{"go", []() { std::cout << "Go where?\n"; }},
		// Examination commands
		{"examine", [this](){ this->world->getCurrentRoom()->printDescription(); }},
		{"look", [this](){ this->world->getCurrentRoom()->printDescription(); }},
		// Interactive commands
		{"read", [](){ std::cout << "Read what?\n"; }},
		{"drop", [](){ std::cout << "Drop what?\n"; }},
		{"open", [](){ std::cout << "Open what?\n"; }},
		{"close", [](){ std::cout << "Close what?\n"; }},
		{"search", [](){ std::cout << "Search what?\n"; }},
		{"lead", [](){ std::cout << "Lead what?\n"; }},
		{"eat", [](){ std::cout << "Eat what?\n"; }},
		{"stab", [](){ std::cout << "Stab what?\n"; }},
		{"cut", [](){ std::cout << "Cut what?\n"; }},
		{"leave", [](){ std::cout << "Leave what?\n"; }},
		{"drop", [](){ std::cout << "Drop what?\n"; }},
		// Solo commands
		{"sleep", [this]() { this->player->sleep(); }},
		{"jump", [this](){ this->player->jump(); }},
		{"pray", [this]() { this->player->pray(); }},
		{"stay", [](){ std::cout << "You decide to hang out for a second.\n"; }}
	};
public:
	CommandInterpreter();
	CommandInterpreter(Player* playerToSet, World* worldToSet);
	// TODO: check if these getter methods are ever used
	World* getWorld() { return this->world; }
	Player* getPlayer() { return this->player; }
	void interpretSimpleCommand(std::string action);
	void interpretSimpleCommand(std::string action, std::string identifier);
	void interpretCommand(std::string action, std::string dirObject);
	void interpretCommand(std::string action, std::string dirObject, std::string identifier);
	void interpretCommand(std::string action, std::string dirObject, std::string identifier, std::string secObject);
	bool checkNeverTime();
};
