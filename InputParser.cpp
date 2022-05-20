#include "InputParser.h"

InputParser::InputParser()
{
    this->interpreter = new CommandInterpreter;
    this->identifierPosition = 0;
    this->spacePosition = 0;
}

InputParser::InputParser(CommandInterpreter* interpreterToSet)
{
    this->interpreter = interpreterToSet;
    this->identifierPosition = 0;
    this->spacePosition = 0;
}

void InputParser::parseInput(std::string inputToParse)
{
    this->setVariables(inputToParse);
    // command is one word
    if (spacePosition < 0)
    {
        this->interpreter->interpretSimpleCommand(input);
    }
    else
    {
        
        this->findAction();
        // command is too complex for parsing
        if (this->containsMultipleIdentifiers())
            return;
        this->findIdentifier();
        // if a command contains a identifier
        if (this->identifier.size() != 0)
        {
            identifierPosition = input.find(this->identifier, 0);
            this->identifier.erase(0, 1);
            // if identifier is at start of command
            if (identifierPosition == 0)
            {
                findPrimaryObject(1, 1);
                if (this->primaryObject.size() == 0)
                {
                    this->identifier.erase(this->identifier.size() - 1, 1);
                    this->interpreter->interpretSimpleCommand(this->action, this->identifier);
                }
                else
                    this->interpreter->interpretCommand(this->action, this->primaryObject, this->identifier);
            }
            // if identifier is at end of command
            else if (identifierPosition + this->identifier.size() + 1 == input.size())
            {
                this->findPrimaryObject(1, 0);
                this->interpreter->interpretCommand(action, primaryObject, this->identifier);
            }
            // if the identifier comes in the middle of the command
            else
            {
                findObjectsWithIdentifier();
                this->interpreter->interpretCommand(action, primaryObject, identifier, secondaryObject);
            }
        }
        // if a command contains no identifiers
        else
        {
            findPrimaryObject(0, 0);
            this->interpreter->interpretCommand(action, primaryObject);
        }
    }
}

void InputParser::setVariables(std::string inputToParse)
{
    this->action = "";
    this->primaryObject = "";
    this->secondaryObject = "";
    this->identifier = "";
    this->input = inputToParse;
    this->spacePosition = input.find(" ", 0);
    this->identifierPosition = 0;
}

void InputParser::findAction()
{
    this->action = this->input.substr(0, this->spacePosition);
    this->input.erase(0, this->spacePosition);
}

void InputParser::findIdentifier()
{
    int identifierPosition;
    // pad input in case identifier comes at end
    this->input.insert(this->input.size(), " ");
    for (std::string potentialIdentifier : this->identifiers)
    {
        identifierPosition = this->input.find(potentialIdentifier, 0);
        if (identifierPosition >= 0 && !(this->identifier.size() > 0))
        {
            this->identifier = potentialIdentifier;
        }
    }
}

void InputParser::findObjectsWithIdentifier()
{
    std::string temp = input;
    this->primaryObject = input.erase(this->identifierPosition, input.size() - this->identifier.size());
    this->primaryObject.erase(0, 1);
    this->secondaryObject = temp.erase(0, this->identifierPosition + this->identifier.size() + 1);
    secondaryObject.erase(this->secondaryObject.size() - 1, 1);
}

void InputParser::findPrimaryObject(int identifierFlag, int locationFlag)
{
    // identifier exists in command
    if (identifierFlag == 1)
    {
        // identifier is located at beginning
        if (locationFlag == 1)
        {
            this->primaryObject = this->input.erase(0, this->identifier.size() + 1);
            if (this->primaryObject.size() > 0)
                this->primaryObject.erase(this->primaryObject.size() - 1, 1);
        }
        // identifier is located at end
        else
        {
            this->primaryObject = this->input.erase(this->identifierPosition, this->identifier.size() + 1);
            this->primaryObject.erase(0, 1);
            this->identifier.erase(this->identifier.size() - 1, 1);
        }
    }
    // no identifier exists in command
    else
    {
        this->primaryObject = this->input;
        this->primaryObject.erase(0, 1);
        this->primaryObject.erase(this->primaryObject.size() - 1, 1);
    }
}

bool InputParser::containsMultipleIdentifiers()
{
    int count = 0,
        identifierPosition;
    for (std::string identifier : this->identifiers)
    {
        identifierPosition = input.find(identifier, 0);
        if (identifierPosition >= 0)
            count++;
    }
    if (count > 1)
    {
        std::cout << "I'm sorry, your sentence is too complex. Please limit "
            << "yourself to one prepositional phrase or adverb per command.\n";
        return true;
    }
    else
        return false;
}



