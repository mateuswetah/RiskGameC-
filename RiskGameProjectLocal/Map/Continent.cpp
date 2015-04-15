/*
 * Continent.cpp
 *
 *  Created on: Jan 30, 2015
 *      Author: mateus
 */

#include "Continent.h"

// constructors and destructor ---------------------------------
Continent::Continent()
{
	name = "";
	color = "green"; // default
	//territories = NULL;
	notify();
}

Continent::Continent(std::string name, std::vector<Territory*> territories)
{
	this->name = name;
	this->territories = territories;
	notify();
}

Continent::~Continent()
{
	this->territories.clear();
}

// Copy Constructor
Continent::Continent (const Continent& other)
				: territories(other.territories.size()), name(other.name),
				  color(other.color), bonus(other.bonus)
{

	for (std::size_t i = 0; i < other.territories.size(); i++)
		territories[i] = new Territory(*other.territories[i]);

}

// Assignment Operator
Continent& Continent::operator=(const Continent& other)
{

	name = other.name;
	color = other.color;
	bonus = other.bonus;

	for (std::size_t i = 0; i < other.territories.size(); i++)
			territories[i] = new Territory(*other.territories[i]);

	return *this;
}

// getter ---------------------------------------------------------
std::vector<Territory*> Continent::getTerritories()
{
	return this->territories;
}

std::string Continent::getName()
{
	return this->name;
}

std::string Continent::getColor()
{
	return this->color;
}

int Continent::getBonus()
{
	return this->bonus;
}

// setter ---------------------------------------------------------
void Continent::setTerritories(std::vector<Territory*> territories)
{
	this->territories = territories;
	notify();
}

void Continent::setName(std::string name)
{
	this->name = name;
	notify();
}

void Continent::setColor(std::string color)
{
	this->color = color;
	notify();
}

void Continent::setBonus(int value)
{
	bonus = value;
}

// other methods --------------------------------------------------
// - displays a simple list of territories
void Continent::printMyTerritories()
{
	int nTerritories = this->territories.size();

	if (nTerritories == 0)
			std::cout << "No territories here." << std::endl;

	for (int i = 0; i < nTerritories; i++)
		std::cout << this->territories.at(i)->getName() << std:: endl;

}

// - find and return a territory object in the list by the given name
Territory* Continent::getTerritoryByName(std::string territory)
{
	int nTerritory = this->territories.size();
	int index = nTerritory;

	for (int i = 0; i < nTerritory; i++)
	{
		if (territory == this->getTerritories().at(i)->getName())
		{
			index = i;
			break;
		}
	}

	if (index == nTerritory)
	{
		Territory* limbo = new Territory();
		limbo->setName("Limbo");

		//std::cerr << "No territory found with this name!" << std::endl;
		return limbo;
	}
	else
		return this->getTerritories().at(index);

}

// - Add a territory to the list of territories
void Continent::addNewTerritory(Territory* territory)
{
	int nTerritories = this->territories.size();
	bool newTerritory = true;

	for (int i = 0; i < nTerritories; i++)
	{
		if (territory->getName() == this->territories.at(i)->getName())
		{
			std::cerr << "This territory is already part of this continent" << std::endl;
			newTerritory = false;
		}
	}

	if (newTerritory)
		this->territories.push_back(territory);

	notify();
}

// - Look for and remove a territory from the list of territories
void Continent::removeTerritory(Territory* territory) // removes from the continent, don't delete
{
	int nTerritories = this->territories.size();
	bool territoryExists = false;

	for (int i = 0; i < nTerritories; i++)
	{
		if (territory->getName() == this->territories.at(i)->getName())
		{
			this->territories.erase(this->territories.begin() + i);
			territoryExists = true;
			break;
		}
	}

	if (!territoryExists)
		std::cerr << "This territory isn't in this continent" << std::endl;

	notify();

}
