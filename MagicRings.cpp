
/*******************************************************************************
*	MagicRings.cpp                                                             *
*                                                                              *
*	Implements the functionality of the MagicRings class                       *
*                                                                              *
*******************************************************************************/

#include "MagicRings.h"

void MagicRings::addRing()
{
	this->numRings += 1;
	std::cout << "You put the ring on one of your fingers. You feel a sense of increased power that is difficult to describe.\n";
	
}

std::shared_ptr<GameObject> MagicRings::getRings()
{
	if (this->numRings == 1)
	{
		std::shared_ptr<GameObject> ring(new GameObject(
			"ring",
			"It's made of silver. It looks... precious.",
			"",
			true
		));
		return ring;
	}
	else if (this->numRings == 2)
	{
		std::shared_ptr<GameObject> ring(new GameObject(
			"rings",
			"You've picked up two of these strange rings.",
			"",
			true
		));
		return ring;
	}
	else if (this->numRings == 3)
	{
		std::shared_ptr<GameObject> ring(new GameObject(
			"rings",
			"You've picked up three of these strange rings.",
			"",
			true
		));
		return ring;
	}
	else if (this->numRings == 4)
	{
		std::shared_ptr<GameObject> ring(new GameObject(
			"rings",
			"You've picked up four of these strange rings.",
			"",
			true
		));
		return ring;
	}
	else if (this->numRings == 5)
	{
		std::shared_ptr<GameObject> ring(new GameObject(
			"rings",
			"You've picked up five of these strange rings.",
			"",
			true
		));
		return ring;
	}
	else if (this->numRings == 6)
	{
		std::shared_ptr<GameObject> ring(new GameObject(
			"rings",
			"You've picked up six of these strang rings.",
			"",
			true
		));
		return ring;
	}
	else
		return nullptr;
}
