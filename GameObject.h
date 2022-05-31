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
	virtual std::string getName() { return this->name; }
	virtual std::string getDescription() { return this->description; }
	virtual std::string getLocationDescription() { return this->locationDescription; }
	virtual bool getCanBeTaken() { return this->canBeTaken; }
};

