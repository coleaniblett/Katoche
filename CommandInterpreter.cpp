// CommandInterpreter.cpp
// Implements the functionality of the CommandInterpreter class

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
    return synonymMap[dirObject];
}

void CommandInterpreter::interpretSimpleCommand(std::string action)
{
    // TODO: create map to hold actions as keys and their results as values
    /*if (action == "quit")
        this->player->setContinueGame(false);
    if (action == "help")
        this->player->getHelp();
    else if (action == "take")
        std::cout << "Take what?\n";
    else if (action == "get")
        std::cout << "Get what?\n";
    else if (action == "inventory")
        this->player->getInventory()->printInventory();
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
    else if (action == "lead")
        std::cout << "Lead what?\n";
    else if (action == "dig")
        this->player->dig();
    else if (action == "eat")
        std::cout << "Eat what?\n";
    else if (action == "stab")
        std::cout << "Stab what?\n";
    else if (action == "cut")
        std::cout << "Cut what?\n";
    else if (action == "sleep")
        this->player->sleep();
    else if (action == "leave")
        std::cout << "Leave what?\n";
    else if (action == "drop")
        std::cout << "Drop what?\n";
    else if (action == "pray")
        this->player->pray();
    else if (action == "stay")
        std::cout << "You decide to hang out for a second.\n";*/
    auto command = simpleCommandMap.find(action);
    if (command != simpleCommandMap.end()) 
    {
        command->second();
    }
    else 
    {
        std::cout << "Unknown command: " << action << "\n";
    }
    checkNeverTime();
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
    else if (action == "look")
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
    else if (action == "jump" || action == "drop")
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
    checkNeverTime();
}

void CommandInterpreter::interpretCommand(std::string action, std::string dirObject)
{
    std::string newDirObject = this->standardizeDirObject(dirObject);
    std::string curRoomName = this->world->getCurrentRoom()->getName();
    std::shared_ptr<Room> curRoom = this->world->getCurrentRoom();
    std::string itemContainer = curRoom->checkContainers(newDirObject);
    std::string searchedObject = curRoom->checkSearchedObjects(newDirObject);
    if (action == "take" || action == "get" || action == "grab")
    {
        if (this->world->getCurrentRoom()->containsObject(newDirObject))
        {
            if (this->world->getCurrentRoom()->getObject(newDirObject)->getCanBeTaken())
            {
                this->player->getInventory()->addToInventory(this->world->getCurrentRoom()->getObject(newDirObject));
                //this->player->addToInventory(this->world->getCurrentRoom()->getObject(newDirObject));
                this->world->getCurrentRoom()->removeObject(newDirObject);
                std::cout << "You take the " << dirObject << "." << std::endl;
            }
            else
                std::cout << "You can't take the " << dirObject << "." << std::endl;
        }
        else
        {
            itemContainer = curRoom->checkContainers(newDirObject);
            searchedObject = curRoom->checkSearchedObjects(newDirObject);
            if (itemContainer != "")
                this->player->getObjectFromContainer(newDirObject, itemContainer);
            else if (searchedObject != "")
            {
                this->player->getObjectFromSearchedObject(newDirObject, searchedObject);
            }
            else
                std::cout << "There is no " << dirObject << " to take." << std::endl;
        }
        if (this->player->getInventory()->getMagicRings()->getNumRings() >= 3)
        {
            this->world->setForeverRoom();
        }
    }
    else if (action == "examine")
    {
        if (dirObject == "room")
        {
            curRoom->printDescription();
        }
        else if (dirObject == "shadow")
        {
            this->player->printShadowDescription();
        }
        else if (curRoom->containsObject(newDirObject))
        {
            std::cout << curRoom->getObject(newDirObject)->getDescription() << std::endl;
        }
        else if (this->player->getInventory()->hasObject(newDirObject))
        {
            std::cout << this->player->getInventory()->getObject(newDirObject)->getDescription() << std::endl;
        }
        else if (itemContainer != "" &&
            std::dynamic_pointer_cast<ContainerObject>(curRoom->getObject(itemContainer))->hasObject(newDirObject))
        {
            std::cout << std::dynamic_pointer_cast<ContainerObject>(curRoom->getObject(itemContainer))->getObject(newDirObject)->getDescription() << "\n";
        }
        else if (searchedObject != "" &&
            std::dynamic_pointer_cast<SearchableObject>(curRoom->getObject(searchedObject))->hasObject(newDirObject))
        {
            std::cout << std::dynamic_pointer_cast<SearchableObject>(curRoom->getObject(searchedObject))->getObject(newDirObject)->getDescription() << "\n";
        }
        else
        {
            std::cout << "What " << dirObject << "?\n";
        }
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
        else if ((curRoom->containsObject("book") && dirObject == "book") || player->getInventory()->hasObject("book"))
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
    else if (action == "lead")
    {
        if (newDirObject == "horse")
            this->player->leadHorse();
        else
            std::cout << "You can't lead that.\n";
    }
    else if (action == "dig")
    {
        if (newDirObject == "ground" || newDirObject == "grave")
            this->player->dig();
    }
    else if (action == "eat")
    {
        player->eat(newDirObject);
    }
    else if (action == "climb")
    {
        player->climb(newDirObject);
    }
    else if (action == "cut" || action == "stab")
    {
        std::cout << "With what?\n";
    }
    else if (action == "leave" || action == "drop" || action == "place")
    {
        if (newDirObject == "horse")
        {
            this->player->leaveHorse();
        }
        else
            player->getInventory()->drop(newDirObject, curRoom);
    }
    checkNeverTime();
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
        else if (this->player->getInventory()->hasObject(newDirObject))
            std::cout << this->player->getInventory()->getObject(newDirObject)->getDescription() << std::endl;
        else
            std::cout << "What " << dirObject << "?" << std::endl;
    }
    else if (action == "dig")
    {
        if (identifier == "up" && (newDirObject == "ground" || newDirObject == "grave"))
            this->player->dig();
        else if (identifier == "with" && dirObject == "shovel")
            this->player->dig();
    }
    else if (action == "go")
    {
        if (newDirObject == "sleep" || newDirObject == "bed")
            this->player->sleep();
    }
    else if (action == "return" && identifier == "to" && dirObject == "entrance" &&
        this->player->getHasExited())
    {
        this->player->enterRoom(this->world->getRoom("Outside Entrance"));
    }
    checkNeverTime();
}

void CommandInterpreter::interpretCommand(std::string action, std::string dirObject, std::string identifier, std::string secObject)
{
    std::string newDirObject = this->standardizeDirObject(dirObject);
    std::string newSecObject = this->standardizeDirObject(secObject);
    if (action == "take" || action == "get" || action == "grab")
    {
        if (identifier == "from" || identifier == "in")
        {
            this->player->getObjectFromContainer(dirObject, secObject);
        }
    }
    else if ((action == "stab" || action == "cut" || action == "attack" || action == "shoot") && identifier == "with")
    {
        this->player->attack(newDirObject, newSecObject);
    }
    checkNeverTime();
}

bool CommandInterpreter::checkNeverTime()
{
    std::shared_ptr<Room> curRoom = this->world->getCurrentRoom();
    bool output = true;
    int curTime = this->world->getNeverTime();
    if (curRoom->getName() == "Never Room")
    {
        this->world->incNeverTime();
        switch (curTime)
        {
            case 1:
            {
                std::cout << "You are starting to get a worried feeling that something "
                    << "horrible is about to happen.\n";
                break;
            }
            case 2:
            {
                std::cout << "Something deep down in you, some kind of ancient instinct "
                    << "that you didn't know existed, is screaming at you: get out of this room.\n";
                    break;
            }
            case 3:
            {
                std::cout << "\nIf you were never born, would you have a problem with that?\n"
                    << "Because you never were. Maybe in some version of this reality, along some "
                    << "dimensional axis only comprehensible to the greatest superintelligences.\n"
                    << "But not here.\nYou were never here.\n";
                this->player->setContinueGame(false);
                break;
            }
        }
    }
    else if (curRoom->getName() == "Forever Room")
    {
        this->world->incNeverTime();
        switch (curTime)
        {
            case 1:
            {
                std::cout << "You become lost in the tranquility of the room - so deeply lost that "
                    << "a full aeon passes before you are able to regain your lucidity.\n"
                    << "You feel a new profund sense of time, as if there were almost no difference "
                    << "between a moment and an epoch.\n";
                this->player->incEsotericKnowledge();
                break;
            }
            case 2:
            {
                std::cout << "Another aeon passes before your mind finally recovers from the "
                    << "black hole that is this room, just barely capable of registering a thought.\n";
                break;
            }
            case 3:
            {
                std::cout << "It too late occurs to you that change is the currency of existence,"
                    << " and in the unchanging state you have found yourself in you're not longer "
                    << "quite sure you exist.\n"
                    << "Maybe you were always here, and everywhere, so completely present and "
                    << "ubiquitous that you escaped all of our notice. The canvas under the paint.\n"
                    << "But you're spread so thin against time that it's hard to say it matters.\n";
                break;
            }
        }
    }
    return output;
}
