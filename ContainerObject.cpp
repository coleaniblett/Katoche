
/*******************************************************************************
*	ContainerObject.cpp                                                        *
*                                                                              *
*	Implements the functionality of the ContainerObject class                  *
*                                                                              *
*******************************************************************************/

#include "ContainerObject.h"

// TODO: test all four conditions
void ContainerObject::printContents()
{
	// container object is empty
	if (this->contents.size() == 0)
		std::cout << "The " << this->getName() << " is empty.\n";
	// container object is not empty
	else
	{
		std::cout << "The " << this->getName() << " contains";
		auto it = contents.begin();
		// container object contains one item
		if (this->contents.size() == 1)
			std::cout << " a " << it->second->getName() << ".\n";
		// container object contains two items
		else if (this->contents.size() == 2)
		{
			std::cout << " a " << it->second->getName();
			it++;
			std::cout << " and a " << it->second->getName() << ".\n";
		}
		// container object contains three or more items
		else
		{
			int contentsSize = this->contents.size();
			int count = 1;
			while (count < contentsSize)
			{
				std::cout << " a ";
				std::cout << it->second->getName() << ",";
				it++;
				count++;
			}
			std::cout << " and a " << it->second->getName() << ".\n";
		}
	}
}
