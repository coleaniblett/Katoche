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
    else if (dirObject == "person" || dirObject == "figure")
        return "shadow self";
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
    else if (action == "examine" || action == "look")
        this->world->getCurrentRoom()->printDescription();
    else if (action == "enter")
        std::cout << "Enter what?\n";
    else if (action == "go")
        std::cout << "Go where?\n";
    else if (action == "jump")
        this->player->jump();
    else if (action == "read")
        std::cout << "Read what?\n";
    else if (action == "drop")
        std::cout << "Drop what?\n";
    else if (action == "open")
        std::cout << "Open what?\n";
    else if (action == "close")
        std::cout << "Close what?\n";
    else if (action == "search")
        std::cout << "Search what?\n";
}

void CommandInterpreter::interpretSimpleCommand(std::string action, std::string identifier)
{
    std::string curRoomName = this->world->getCurrentRoom()->getName();
    if (action == "climb" || action == "go")
    {
        if (curRoomName == "Outside Exit")
            std::cout << "The door is locked.\n";
        else if (identifier == "up" || identifier == "down")
        {
            this->player->move(identifier);
        }
    }
    if (action == "look")
    {
        if (identifier == "around")
            this->world->getCurrentRoom()->printDescription();
        else if (identifier == "down")
        {
            if (curRoomName == "Antechamber")
                std::cout << "The rope disappears into the darkness below. You can't tell how far the hole goes, but it looks like it is a minimum of 40 feet.\n";
            else
                std::cout << "There is nothing notable about the ground here.\n";
        }
    }
    if (action == "jump" || action == "drop")
    {
        if (identifier == "down")
        {
            if (curRoomName == "Event Horizon")
                player->move("down");
            else if (curRoomName == "Antechamber")
            {
                std::cout << "You jump down the hole. After falling some distance, you hit the ground with a hard thump.\nYou have died.\n";
                this->player->setContinueGame(false);
            }
            else
            {
                std::cout << "There is no place for you to jump down to.\n";
            }
        }
	}
}

void CommandInterpreter::interpretCommand(std::string action, std::string dirObject)
{
    std::string newDirObject = this->standardizeDirObject(dirObject);
    std::string curRoomName = this->world->getCurrentRoom()->getName();
    std::string itemContainer;
    std::string searchedObject;
    std::shared_ptr<Room> curRoom = this->world->getCurrentRoom();
    if (action == "take" || action == "get" || action == "grab")
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
        {
            itemContainer = curRoom->checkContainers(dirObject);
            searchedObject = curRoom->checkSearchedObjects(dirObject);
            if (itemContainer != "")
                this->player->getObjectFromContainer(dirObject, itemContainer);
            else if (searchedObject != "")
            {
                this->player->getObjectFromSearchedObject(dirObject, searchedObject);
            }
            else
                std::cout << "There is no " << dirObject << " to take." << std::endl;
        }
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
            if (this->world->getCurrentRoom()->getName() == "Outside Exit")
                std::cout << "The door is locked.\n";
            else
                this->player->move("inner");
        }
        else if (dirObject == "north" || dirObject == "west" || dirObject == "south"
            || dirObject == "east")
            this->player->move(dirObject);
    }
    else if (action == "read")
    {
        if (curRoomName == "First Room" && dirObject == "writing")
            std::cout << this->world->getCurrentRoom()->getObject("writing")->getDescription() << "\n";
        else if ((curRoom->containsObject("book") && dirObject == "book") || player->hasObject("book"))
            this->player->read();
    }
    else if (action == "open")
    {
        this->player->openObject(dirObject);
    }
    else if (action == "close")
    {
        this->player->closeObject(dirObject);
    }
    else if (action == "search")
    {
        this->player->searchObject(newDirObject);
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
    std::string newDirObject = this->standardizeDirObject(dirObject);
    if (action == "take" || action == "get" || action == "grab")
    {
        if (identifier == "from" || identifier == "in")
        {
            this->player->getObjectFromContainer(dirObject, secObject);
        }
    }
}
