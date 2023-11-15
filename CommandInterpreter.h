// CommandInterpreter.h
// Defines the command interpreter class, responsible for interpreting user commands

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
		// meta commands
		{"quit", [this]() { this->player->setContinueGame(false); }},
		// inventory commands
		{"help", [this]() { this->player->getHelp(); }},
		{"take", []() { std::cout << "Take what?\n"; }},
		{"get", []() { std::cout << "Get what?\n"; }},
		{"inventory", [this]() { this->player->getInventory()->printInventory(); }},
		// movement commands
		{"north", [this]() { this->player->move("north"); }},
		{"east", [this]() { this->player->move("east"); }},
		{"south", [this]() { this->player->move("south"); }},
		{"west", [this]() { this->player->move("west"); }},
		{"up", [this]() { this->player->move("up"); }},
		{"down", [this]() { this->player->move("down"); }},
		{"enter", []() { std::cout << "Enter what?\n"; }},
		{"go", []() { std::cout << "Go where?\n"; }},
		// examination commands
		{"examine", [this](){ this->world->getCurrentRoom()->printDescription(); }},
		{"look", [this](){ this->world->getCurrentRoom()->printDescription(); }},
		{"jump", [this](){ this->player->jump(); }},
		// interactive commands
		{"read", [this](){ std::cout << "Read what?\n"; }},
		{"drop", [](){ std::cout << "Drop what?\n"; }},
		{"open", [](){ std::cout << "Open what?\n"; }},
		{"close", [](){ std::cout << "Close what?\n"; }},
		{"search", [](){ std::cout << "Search what?\n"; }},
		{"lead", [](){ std::cout << "Lead what?\n"; }},
		{"dig", [this]() { this->player->dig(); }},
		{"eat", [](){ std::cout << "Eat what?\n"; }},
		{"stab", [](){ std::cout << "Stab what?\n"; }},
		{"cut", [](){ std::cout << "Cut what?\n"; }},
		{"sleep", [this]() { this->player->sleep(); }},
		{"leave", [](){ std::cout << "Leave what?\n"; }},
		{"drop", [](){ std::cout << "Drop what?\n"; }},
		{"pray", [this]() { this->player->pray(); }},
		{"stay", [](){ std::cout << "You decide to hang out for a second.\n"; }}
	};
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
