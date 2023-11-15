
/*******************************************************************************
*	GameObject.cpp                                                             *
*                                                                              *
*	Implements the functionality for the GameObject class                      *
*                                                                              *
*******************************************************************************/

#include "GameObject.h"

// No-argument constructor
GameObject::GameObject()
{
	this->name = "";
	this->description = "";
	this->locationDescription = "";
	this->canBeTaken = false;
}

// Standard constructor
GameObject::GameObject(
	std::string nameToSet,
	std::string descriptionToSet,
	std::string locationDescriptionToSet,
	bool canBeTakenSetting
)
{
	this->name = nameToSet;
	this->description = descriptionToSet;
	this->locationDescription = locationDescriptionToSet;
	this->canBeTaken = canBeTakenSetting;
}
