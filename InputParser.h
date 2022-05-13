#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Player.h"
#include "World.h"
#include "CommandInterpreter.h"
class InputParser
{
private:
	CommandInterpreter* interpreter;
	std::vector<std::string> identifiers = { " under ", " around ", " at ", " above ",
		" next to ", " with ", " on ", " to ", " in ", " into ", " out ", " up ", " from " };
	std::string input;
	std::string action;
	std::string identifier;
	std::string primaryObject;
	std::string secondaryObject;
	int spacePosition;
	int identifierPosition;
public:
	InputParser();
	InputParser(CommandInterpreter* interpreterToSet);
	CommandInterpreter* getInterpreter() { return this->interpreter; }
	void setVariables(std::string inputToParse);
	void setInterpreter(CommandInterpreter* interpreterToSet)
	{
		delete this->interpreter;
		this->interpreter = interpreterToSet;
	}
	void parseInput(std::string inputToParse);
	void findAction();
	void findIdentifier();
	void findPrimaryObject(int identifierFlag, int locationFlag);
	bool containsMultipleIdentifiers();
	void findObjectsWithIdentifier();
};

