/*
 * Map.cpp
 *
 *  Created on: Feb 6, 2015
 *      Author: mateus
 */

#include "Map.h"
#include <iostream>

Map *Map::mapInstance = NULL;

// SingleTone Instance
Map* Map::getMapInstance()
{
	if (!mapInstance)
		mapInstance = new Map();
	return mapInstance;
}

// constructors and destructor ---------------------------------
Map::Map()
{

}

Map::Map(std::vector<Continent*> continents)
{
	this->continents = continents;
}

Map::~Map()
{
	this->continents.clear();
}

// Copy Constructor
Map::Map (const Map& other)
				: continents(other.continents.size()),
				  fileName(other.fileName)
{

	mapInstance = other.getMapInstance();

	for (std::size_t i = 0; i < other.continents.size(); i++)
		continents[i] = new Continent(*other.continents[i]);

}
// Assignment Operator
Map& Map::operator=(const Map& other)
{

	fileName = other.fileName;
	mapInstance = other.getMapInstance();

	for (std::size_t i = 0; i < other.continents.size(); i++)
			continents[i] = new Continent(*other.continents[i]);

	return *this;
}

// getter ---------------------------------------------------------
std::vector<Continent*> Map::getContinents()
{
	return this->continents;
}

std::vector<Territory*> Map::getTerritories()
{
	std::vector<Territory*> vt;
	int nContinents = this->continents.size();
	int nTerritories = 0;

	if (nContinents == 0)
		std::cout << "No continents here." << std::endl;
	// To remove in the final version ?
	// Replace by if (nContinent > 0) ??

	for (int i = 0; i < nContinents; i++)
	{
		nTerritories = this->continents.at(i)->getTerritories().size();

		for (int j = 0; j < nTerritories; j++)
			vt.push_back(this->continents.at(i)->getTerritories().at(j));
	}

	return vt;
}

std::string Map::getFileName()
{
	return this->fileName;
}

// setter ---------------------------------------------------------
void Map::setContinents(std::vector<Continent*> continents)
{
	this->continents = continents;

	notify();
}

void Map::setFileName(std::string fileName)
{
	this->fileName = fileName;

	notify();
}

void Map::printMyContinentsAndTerritory()
{
	int nContinents = this->continents.size();
	int nTerritories = 0;

	if (nContinents == 0)
		std::cout << "No continents here." << std::endl;

	for (int i = 0; i < nContinents; i++)
	{
		std::cout << this->continents.at(i)->getName() << std::endl;

		nTerritories = this->continents.at(i)->getTerritories().size();

		for (int j = 0; j < nTerritories; j++)
			std::cout << "  " << this->continents.at(i)->getTerritories().at(j)->getName() << std::endl;

	}

}

// other functions ----------------------------------------------
// - find and return a continent object in the list by the given name
Continent* Map::getContinentByName(std::string continent)
{
	int nContinents = this->continents.size();
	int index = nContinents;

	for (int i = 0; i < nContinents; i++)
	{
		if (continent == this->getContinents().at(i)->getName())
		{
			index = i;
			break;
		}
	}

	if (index == nContinents)
	{
		std::cout << "No Continent found with this name!" << std::endl;
		return NULL;
	}
	else
		return this->getContinents().at(index);

}

// - find and return a continent object in the list of continents by the given name
Territory* Map::getTerritoryByName(std::string territory)
{
	int nContinents = this->continents.size();
	int index = nContinents;

	if (nContinents == 0)
		std::cout << "No continents here, no territories to look for." << std::endl;

	for (int i = 0; i < nContinents; i++)
	{
		if (this->continents.at(i)->getTerritoryByName(territory)->getName() == territory)
		{
			index = i;
			break;
		}

	}

	if (index != nContinents)
		return this->continents.at(index)->getTerritoryByName(territory);
	else
	{
		Territory* limbo = new Territory();
		limbo->setName("Limbo");
		std::cerr << "There is no Territory with that name in any Continent of this Map!" << std::endl;

		return limbo;
	}
}

// - Add a continent to the list of continents
void Map::addNewContinent(Continent* continent)
{
	int nContinents = this->continents.size();
	bool newContinent = true;

	for (int i = 0; i < nContinents; i++)
	{
		if (continent->getName() == this->continents.at(i)->getName())
		{
			std::cerr << "This Continent is already part of this map" << std::endl;
			newContinent = false;
		}
	}

	if (newContinent)
		this->continents.push_back(continent);

}

// - Look for and remove a continent from the list of continents
void Map::removeContinent(Continent* continent)
{
	int nContinents = this->continents.size();
	bool continentExists = false;

	for (int i = 0; i < nContinents; i++)
	{
		if (continent->getName() == this->continents.at(i)->getName())
		{
			this->continents.erase(this->continents.begin() + i);
			continentExists = true;
			break;
		}
	}

	if (!continentExists)
		std::cerr << "This continent isn't in this map!" << std::endl;

	notify();

}

void Map::removeTerritory(Territory* territory)
{
	int nContinents = this->getContinents().size();
	bool territoryExists = false;

	for (int i = 0; i < nContinents; i++)
	{
		int nTerritories = this->getContinents().at(i)->getTerritories().size();

		for (int j = 0; j < nTerritories; j++)
		{
			if (territory->getName() == this->getContinents().at(i)->getTerritories().at(j)->getName())
			{
				(this->getContinents().at(i)->getTerritories()).erase((this->getContinents().at(i)->getTerritories()).begin() + j);

				territoryExists = true;
				break;
			}
		}
	}

	if (!territoryExists)
		std::cerr << "This territory isn't in this map!" << std::endl;

	notify();

}

// - Instantiate the continents


void
Map::loadMap (char* filename)
{

	MapIO mio;
	mio.loadMapInfo(filename);

}

std::vector<Territory*>
Map::getTerritoriesByPlayer (std::string player)
{
	std::vector<Territory*> vt;
	int nContinents = this->continents.size();
	int nTerritories = 0;

	if (nContinents == 0)
		std::cout << "No continents here." << std::endl;

	for (int i = 0; i < nContinents; i++)
	{
		nTerritories = this->continents.at(i)->getTerritories().size();

		for (int j = 0; j < nTerritories; j++)
		{
			if(this->continents.at(i)->getTerritories().at(j)->getPlayerOwner()->getName() == player)
				vt.push_back(this->continents.at(i)->getTerritories().at(j));
		}
	}
	return vt;
}

bool Map::checkIfContinentExists(std::string continent)
{
	int nContinents = this->continents.size();

	for (int i = 0; i < nContinents; i++)
	{
		if (continent == this->getContinents().at(i)->getName())
			return true;

	}

	return false;
}

bool Map::checkIfTerritoryExists(std::string territory)
{
	int nTerritories = this->getTerritories().size();

	for (int i = 0; i < nTerritories; i++)
	{
		if (territory == this->getTerritories().at(i)->getName())
			return true;
	}

	return false;
}
