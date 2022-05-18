#pragma once
#include <string>
class GameObject
{
private:
	std::string name,
		description,
		locationDescription;
	bool canBeTaken;
public:
	GameObject();
	GameObject(
		std::string nameToSet,
		std::string descriptionToSet,
		std::string locationDescriptionToSet,
		bool canBeTakenSetting
	);
	std::string getName() { return this->name; }
	std::string getDescription() { return this->description; }
	std::string getLocationDescription() { return this->locationDescription; }
	bool getCanBeTaken() { return this->canBeTaken; }
};

