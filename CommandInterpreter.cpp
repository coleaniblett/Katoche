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
    else if (action == "take")
        std::cout << "Take what?" << std::endl;
}

void CommandInterpreter::interpretSimpleCommand(std::string action, std::string identifier)
{

}

void CommandInterpreter::interpretCommand(std::string action, std::string dirObject)
{
    std::cout << "Test" << std::endl;
    if (action == "take")
    {
        if (this->world->getCurrentRoom()->containsObject(dirObject))
        {
            this->player->addToInventory(this->world->getCurrentRoom()->getObject(dirObject));
            this->world->getCurrentRoom()->removeObject(dirObject);
            std::cout << "You take the " << dirObject << std::endl;
        }
    }
}

void CommandInterpreter::interpretCommand(std::string action, std::string dirObject, std::string identifier)
{

}

void CommandInterpreter::interpretCommand(std::string action, std::string dirObject, std::string identifier, std::string secObject)
{

}
