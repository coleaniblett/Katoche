#pragma once
#include <map>
#include <memory>
#include <iostream>
#include "GameObject.h"
class ContainerObject :
    public GameObject
{
private:
    std::map<std::string, std::shared_ptr<GameObject>> contents;
    bool isOpen;
public:
    ContainerObject(std::string name, std::string description, std::string locationDescription, bool canBetaken) 
        : GameObject(name, description, locationDescription, canBetaken)
    {
        this->isOpen = false;
    }
    void addObject(std::shared_ptr<GameObject> objectToAdd) { this->contents.insert({ objectToAdd->getName(), objectToAdd }); }
    void removeObject(std::string objectToRemove) { this->contents.erase(objectToRemove); }
    std::shared_ptr<GameObject> getObject(std::string objectToGet) { return this->contents.at(objectToGet); }
    bool hasObject(std::string objectToCheck) { return this->contents.count(objectToCheck); }
    void open() { this->isOpen = true; }
    void close() { this->isOpen = false; }
    bool checkIsOpen() { return this->isOpen; }
    void printContents();
};

