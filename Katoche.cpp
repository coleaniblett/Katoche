#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "StdInStream.h"
#include "Player.h"
#include "World.h"
#include "InputParser.h"

int main()
{
	World world;
	Player player(&world);
	CommandInterpreter interpreter(&player, &world);
	InputParser parser(&interpreter);
	StdInStream input(&player, &parser);

	input.loopInputRequest();
}


