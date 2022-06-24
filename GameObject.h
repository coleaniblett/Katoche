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
	void setCanbeTaken(bool valueToSet) { this->canBeTaken = valueToSet; }
	void setDescription(std::string descriptionToSet) { this->description = descriptionToSet; }
	void setLocationDescription(std::string descriptionToSet) { this->locationDescription = descriptionToSet; }
};

