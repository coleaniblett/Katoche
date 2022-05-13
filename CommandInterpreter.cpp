#include "CommandInterpreter.h"

CommandInterpreter::CommandInterpreter()
{
    this->player = new Player;
    this->world = new World;
}

CommandInterpreter::CommandInterpreter(Player* playerToSet, World* worldToSet)
{
    this->player = playerToSet;
    this->world = worldToSet;
}

void CommandInterpreter::interpretSimpleCommand(std::string action)
{
    if (action == "quit")
        this->player->setContinueGame(false);
}

void CommandInterpreter::interpretSimpleCommand(std::string action, std::string identifier)
{

}

void CommandInterpreter::interpretCommand(std::string action, std::string dirObject)
{

}

void CommandInterpreter::interpretCommand(std::string action, std::string dirObject, std::string identifier)
{

}

void CommandInterpreter::interpretCommand(std::string action, std::string dirObject, std::string identifier, std::string secObject)
{

}
