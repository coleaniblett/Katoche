// SearchableObject.h
// Defines the SearchableObject class, representing an object that can be searched

#pragma once
#include <map>
#include <memory>
#include <iostream>
#include "GameObject.h"
class SearchableObject :
    public GameObject
{
private:
    std::map<std::string, std::shared_ptr<GameObject>> contents;
    bool hasBeenSearched;
public:
    SearchableObject(std::string name, std::string description, std::string locationDescription, bool canBeTaken)
        : GameObject(name, description, locationDescription, canBeTaken)
    {
        this->hasBeenSearched = false;
    }
    void addObject(std::shared_ptr<GameObject> objectToAdd) { this->contents.insert({ objectToAdd->getName(), objectToAdd }); }
    void setHasBeenSearched() { this->hasBeenSearched = true; }
    bool getHasBeenSearched() { return this->hasBeenSearched; }
    bool hasObject(std::string objectToCheck) { return this->contents.count(objectToCheck); }
    std::map<std::string, std::shared_ptr<GameObject>> getContents() { return this->contents; }
    void printContents();
    std::shared_ptr<GameObject> getObject(std::string objectToGet) { return this->contents.at(objectToGet); }
    void removeObject(std::string objectToGet) { this->contents.erase(objectToGet); }
};

