/*
 * Territory.cpp
 *
 *  Created on: Jan 28, 2015
 *      Author: mateus
 */

#include "Territory.h"

// constructors and destructor ------------------------------------
Territory::Territory()
{
	name = "";
	//neighbors = NULL;
	mPosX = 0;
	mPosY = 0;
	playerOwner = new Player;
	amountOfArmies = 0;

	notify();

}

Territory::Territory(std::string name, std::vector<Territory*> neighbors, int posX, int posY, Player* player, int armies)
{
	this->name = name;
	this->neighbors = neighbors;
	mPosX = posX;
	mPosY = posY;
	playerOwner = player;
	amountOfArmies = armies;

	notify();
}

Territory::~Territory()
{
	this->neighbors.clear();
	delete playerOwner;

}

// Copy Constructor
Territory::Territory (const Territory& other)
				: neighbors(other.neighbors.size()),
				  name(other.name), mPosX(other.mPosX),
				  mPosY(other.mPosY), amountOfArmies(other.amountOfArmies),
				  playerOwner(NULL)
{

	if (playerOwner)
		playerOwner = new Player(*other.playerOwner);

	for (std::size_t i = 0; i < other.neighbors.size(); i++)
		neighbors[i] = new Territory(*other.neighbors[i]);

}
// Assignment Operator
Territory& Territory::operator=(const Territory& other)
{

	name = other.name;
	mPosX = other.mPosX;
	mPosY = other.mPosY;
	amountOfArmies = other.amountOfArmies;
	playerOwner = new Player(*other.playerOwner);

	for (std::size_t i = 0; i < other.neighbors.size(); i++)
			neighbors[i] = new Territory(*other.neighbors[i]);

	return *this;
}

// getters --------------------------------------------------------
std::string Territory::getName()
{
	return this->name;
}

std::vector<Territory*> Territory::getNeighbors()
{
	return this->neighbors;
}

int Territory::getPosX()
{
	return this->mPosX;
}

int Territory::getPosY()
{
	return this->mPosY;
}

Player* Territory::getPlayerOwner()
{
	return this->playerOwner;
}

int Territory::getAmountOfArmies()
{
	return this->amountOfArmies;
}

// setters ------------------------------- ------------------------
void Territory::setName(std::string name)
{
	this->name = name;

	notify();
}

void Territory::setNeighbors(std::vector<Territory*> neighbors)
{
	this->neighbors = neighbors;

	notify();
}

void Territory::setPosX(int x)
{
	mPosX = x;

	notify();
}

void Territory::setPosY(int y)
{
	mPosY = y;

	notify();
}

void Territory::setPlayerOwner(Player* player)
{
	playerOwner = player;

	notify();
}

void Territory::setAmountOfArmies(int armies)
{
	amountOfArmies = armies;

	notify();
}

// other methods --------------------------------------------------
// - displays a simple list of neighbors
void Territory::printMyNeighbors()
{
	int nNeighbors = this->neighbors.size();

	if (nNeighbors == 0)
		std::cerr << "No neighbors here." << std::endl;

	for (int i = 0; i < nNeighbors; i++)
	{
		std::cout << neighbors.at(i)->getName() << ", "
			<< neighbors.at(i)->getPlayerOwner()->getName() << std::endl;
	}

}

// - find and return a neighbor object in the list by the given name
Territory* Territory::getNeighborByName(std::string territory)
{
	int nNeighbors = this->getNeighbors().size();
	int index = nNeighbors;
	int i;

	for (i = 0; i < nNeighbors; i++)
	{
		if (territory == this->getNeighbors().at(i)->getName())
		{
			index = i;
			break;
		}
	}

	if (index == nNeighbors)
	{
		Territory* limbo = new Territory();
		limbo->setName("Limbo");

		std::cerr << "No neighbor found with this name!" << std::endl;
		return limbo;
	}
	else
		return this->getNeighbors().at(index);

}

// - Add a neighbor to the list of neighbors
void Territory::addNewNeighbor(Territory* territory)
{
	int nNeighbors = this->neighbors.size();
	bool newNeighbor = true;

	for (int i = 0; i < nNeighbors; i++)
	{
		if (territory->getName() == this->neighbors.at(i)->getName())
		{
			std::cerr << "This territory is already neighbor of this territory" << std::endl;
			newNeighbor = false;
		}
	}

	if (newNeighbor)
		this->neighbors.push_back(territory);

	notify();

}

// - Look for and remove a neighbor from the list of neighbors
void Territory::removeNeighbor(Territory* territory) // don't delete, just remove from the list of neighbors
{
	int nNeighbor = this->neighbors.size();
	bool neighborExists = false;

	for (int i = 0; i < nNeighbor; i++)
	{
		if (territory->getName() == this->neighbors.at(i)->getName())
		{

			this->neighbors.erase(this->neighbors.begin() + i);
			neighborExists = true;

			break;
		}
	}

	if (!neighborExists)
		std::cerr << "This territory isn't a neighbor" << std::endl;

	notify();

}

bool
Territory::isNeighbor (Territory* t)
{
  int nNeighbor = this->neighbors.size();
  bool neighborExists = false;

  for (int i = 0; i < nNeighbor; i++)
  {
      if(this->neighbors.at(i)->getName() == t->getName())
	return true;
  }
  return false;
}
