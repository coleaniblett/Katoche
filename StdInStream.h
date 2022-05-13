#pragma once
#include <iostream>
#include <string>
#include "Player.h"
#include "InputParser.h"
class StdInStream
{
private:
	Player* player;
	InputParser* parser;
	std::string userInput;
public:
	StdInStream()
	{
		setPlayer(new Player);
		setParser(new InputParser);
	}
	StdInStream(Player* playerToSet, InputParser* parserToSet);
	void setPlayer(Player* playerToSet) { delete this->player; this->player = playerToSet; }
	void setParser(InputParser* parserToSet) { delete this->parser; this->parser = parserToSet; }
	void loopInputRequest();
	std::string takeInput();
	std::string cleanInput(std::string inputToClean);
	std::string removeArticles(std::string inputToClean);
};

