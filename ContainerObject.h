#pragma once
#include <map>
#include <memory>
#include "GameObject.h"
class ContainerObject :
    public GameObject
{
private:
    std::map<std::string, std::shared_ptr<GameObject>> contents;
public:
    ContainerObject(std::string name, std::string description, std::string locationDescription, bool canBetaken) 
        : GameObject(name, description, locationDescription, canBetaken)
    {}
    void addObject(std::shared_ptr<GameObject> objectToAdd) { this->contents.insert({ objectToAdd->getName(), objectToAdd }); }
    void removeObject(std::string objectToRemove) { this->contents.erase(objectToRemove); }
    bool hasObject(std::string objectToCheck) { return this->contents.count(objectToCheck); }
};

