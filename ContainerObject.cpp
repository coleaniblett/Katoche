// ContainerObject.cpp
// implements the functionality of the ContainerObject class

#include "ContainerObject.h"

void ContainerObject::printContents()
{
	std::cout << "The " << this->getName();
	if (this->contents.size() == 0)
		std::cout << " is empty.\n";
	else
	{
		std::cout << " contains";
		auto it = contents.begin();
		if (this->contents.size() == 1)
			std::cout << " a " << it->second->getName() << ".\n";
		else if (this->contents.size() == 2)
		{
			std::cout << " a " << it->second->getName();
			it++;
			std::cout << " and a " << it->second->getName() << ".\n";
		}
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
