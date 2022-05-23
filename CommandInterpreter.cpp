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
    if (dirObject == "opening" || dirObject == "building" || dirObject == "structure")
        return "entrance";
    else if (dirObject == "body" || dirObject == "dead body" || dirObject == "dead person")
        return "corpse";
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
        std::cout << "Take what?\n";
    else if (action == "get")
        std::cout << "Get what?\n";
    else if (action == "inventory")
        this->player->printInventory();
    else if (action == "north" || action == "east" || action == "south" ||
        action == "west" || action == "up" || action == "down")
        this->player->move(action);
    else if (action == "examine")
        this->world->getCurrentRoom()->printDescription();
    else if (action == "enter")
        std::cout << "Enter what?\n";
    else if (action == "go")
        std::cout << "Go where?\n";
}

void CommandInterpreter::interpretSimpleCommand(std::string action, std::string identifier)
{
    if (action == "climb" || action == "go")
    {
        if (identifier == "up" || identifier == "down")
        {
            this->player->move(identifier);
        }
    }
}

void CommandInterpreter::interpretCommand(std::string action, std::string dirObject)
{
    std::string newDirObject = this->standardizeDirObject(dirObject);
    if (action == "take" || action == "get")
    {
        if (this->world->getCurrentRoom()->containsObject(newDirObject))
        {
            if (this->world->getCurrentRoom()->getObject(newDirObject)->getCanBeTaken())
            {
                this->player->addToInventory(this->world->getCurrentRoom()->getObject(newDirObject));
                this->world->getCurrentRoom()->removeObject(newDirObject);
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
        else if (dirObject == "shadow")
            this->player->printShadowDescription();
        else if (this->world->getCurrentRoom()->containsObject(newDirObject))
            std::cout << this->world->getCurrentRoom()->getObject(newDirObject)->getDescription() << std::endl;
        else if (this->player->hasObject(newDirObject))
            std::cout << this->player->getObject(newDirObject)->getDescription() << std::endl;
        else
            std::cout << "What " << dirObject << "?" << std::endl;
    }
    else if (action == "enter")
    {
        if (this->world->getCurrentRoom()->getRoom("inner"))
            this->player->move("inner");
    }
    else if (action == "go")
    {
        if (dirObject == "inside")
        {
            this->player->move("inner");
        }
        else if (dirObject == "north" || dirObject == "west" || dirObject == "south"
            || dirObject == "east")
            this->player->move(dirObject);
    }
}

void CommandInterpreter::interpretCommand(std::string action, std::string dirObject, std::string identifier)
{
    std::string newDirObject = this->standardizeDirObject(dirObject);
    if (action == "look" && identifier == "at")
    {
        if (newDirObject == "room")
            this->world->getCurrentRoom()->printDescription();
        else if (dirObject == "shadow")
            this->player->printShadowDescription();
        else if (this->world->getCurrentRoom()->containsObject(newDirObject))
            std::cout << this->world->getCurrentRoom()->getObject(newDirObject)->getDescription() << std::endl;
        else if (this->player->hasObject(newDirObject))
            std::cout << this->player->getObject(newDirObject)->getDescription() << std::endl;
        else
            std::cout << "What " << dirObject << "?" << std::endl;
    }
}

void CommandInterpreter::interpretCommand(std::string action, std::string dirObject, std::string identifier, std::string secObject)
{

}
