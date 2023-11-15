// MagicRings.h
// Defines the MagicRings class, representing a collection of magic rings in the game

#pragma once
#include <iostream>
#include <map>
#include <memory>
#include "GameObject.h"

class MagicRings
{
private:
	int numRings;
public:
	MagicRings() { numRings = 0; }
	int getNumRings() { return this->numRings; }
	void addRing();
	std::shared_ptr<GameObject> getRings();
};

