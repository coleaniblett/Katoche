// Katoche.cpp
// Entry point for the "Katoche" text-based adventure game
// This file houses the main function where the game execution begins
// Created by Cole Niblett

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "StdInStream.h"
#include "Player.h"
#include "World.h"
#include "InputParser.h"
#include "Inventory.h"

int main()
{
	World world;
	Inventory inventory;
	Player player(&world, &inventory);
	CommandInterpreter interpreter(&player, &world);
	InputParser parser(&interpreter);
	StdInStream input(&player, &parser);

	input.loopInputRequest();
}


