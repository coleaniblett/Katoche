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

std::string CommandInterpreter::standardizeDirObject(std::string dirObject)
{
    if (dirObject == "opening")
        return "entrance";
    else
        return dirObject;
}

void CommandInterpreter::interpretSimpleCommand(std::string action)
{
    if (action == "quit")
        this->player->setContinueGame(false);
    if (action == "help")
        this->player->getHelp();
    else if (action == "take")
        std::cout << "Take what?" << std::endl;
    else if (action == "get")
        std::cout << "Get what?" << std::endl;
    else if (action == "inventory")
        this->player->printInventory();
    else if (action == "north" || action == "east" || action == "south" ||
        action == "west" || action == "up" || action == "down")
        this->player->move(action);
    else if (action == "examine")
        this->world->getCurrentRoom()->printDescription();
    else if (action == "enter")
        std::cout << "Enter what?" << std::endl;
}

void CommandInterpreter::interpretSimpleCommand(std::string action, std::string identifier)
{
    
}

void CommandInterpreter::interpretCommand(std::string action, std::string dirObject)
{
    dirObject = this->standardizeDirObject(dirObject);
    if (action == "take" || action == "get")
    {
        if (this->world->getCurrentRoom()->containsObject(dirObject))
        {
            if (this->world->getCurrentRoom()->getObject(dirObject)->getCanBeTaken())
            {
                this->player->addToInventory(this->world->getCurrentRoom()->getObject(dirObject));
                this->world->getCurrentRoom()->removeObject(dirObject);
                std::cout << "You take the " << dirObject << "." << std::endl;
            }
            else
                std::cout << "You can't take the " << dirObject << "." << std::endl;
        }
        else
            std::cout << "There is no " << dirObject << " to take." << std::endl;
    }
    else if (action == "examine")
    {
        if (dirObject == "room")
            this->world->getCurrentRoom()->printDescription();
        else if (this->world->getCurrentRoom()->containsObject(dirObject))
            std::cout << this->world->getCurrentRoom()->getObject(dirObject)->getDescription() << std::endl;
        else if (this->player->hasObject(dirObject))
            std::cout << this->player->getObject(dirObject)->getDescription() << std::endl;
        else
            std::cout << "What " << dirObject << "?" << std::endl;
    }
    else if (action == "enter")
    {

    }
}

void CommandInterpreter::interpretCommand(std::string action, std::string dirObject, std::string identifier)
{

}

void CommandInterpreter::interpretCommand(std::string action, std::string dirObject, std::string identifier, std::string secObject)
{

}
