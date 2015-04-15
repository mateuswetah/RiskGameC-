#include "Fortification.h"

Fortification::Fortification()
{
	std::cout << "Fortification phase!\n\n";
	//mCurrent = aPlayer;
	tOriginStr = "";
	tDestinationStr = "";
}


Fortification::~Fortification()
{
	delete mCurrent;
	delete tOrigin;
	delete tDestination;
}


void Fortification::move(std::string origin, std::string destination)
{
	Map *map = Map::getMapInstance();
	int num;
	int maxNum = map->getTerritoryByName(origin)->getAmountOfArmies() - 1;

	// Ask for input
	do {
		std::cout << "Select a number of territories to migrate: 1";
		if (maxNum == 1)
			std::cout << std::endl;
		else
			std::cout << "-" << maxNum << std::endl;
		std::cin >> num;
	} while (num < 1 || num > maxNum);

	// Set new amount of armies
	tOrigin->setAmountOfArmies(tOrigin->getAmountOfArmies() - num);
	tDestination->setAmountOfArmies(tDestination->getAmountOfArmies() + num);
	 
	// Display update
	std::cout << tOrigin->getName() << " : " << tOrigin->getAmountOfArmies() << std::endl;
	std::cout << tDestination->getName() << " : " << tDestination->getAmountOfArmies() << std::endl;
}

void Fortification::selectDestination(std::string origin)
{
	Map *map = Map::getMapInstance();
	std::cout << "Army can be migrated.\n\n";

	// Get the list of neighbors for a territory
	std::cout << "Destination." << std::endl;
	std::vector <std::string> neighbor = createNeighborsStr(tOriginStr);

	for (int i = 0; i < neighbor.size(); i++)
	{
		int nArmy = map->getTerritoryByName(neighbor[i])->getAmountOfArmies();
		std::cout << "- " << neighbor[i] << ", " << nArmy;
		if (nArmy == 1)
			std::cout << " army" << std::endl;
		else
			std::cout << " armies" << std::endl;
	}

	bool validOrigin = false;
	std::string destinationAns;
	do {
		std::cout << "Please choose an destination.\n\n";
		std::cin >> destinationAns;
		for (int i = 0; i < neighbor.size(); i++)
		{
			if (neighbor[i] == destinationAns)
			{
				validOrigin = true;
				break;
			}
		}

	} while (!validOrigin);

	tDestinationStr = destinationAns;
	setTDestination(tDestinationStr);
}

void Fortification::selectOrigin()
{
	Map *map = Map::getMapInstance();

	// List the valid origin
	std::vector<std::string>::iterator itS;
	std::cout << "Origin: " << std::endl;
	for (itS = originStr.begin(); itS != originStr.end(); itS++)
	{
		int nArmy = map->getTerritoryByName(*itS)->getAmountOfArmies();
		std::cout << "- " << (*itS) << ", " << nArmy;
		if (nArmy == 1)
			std::cout << " army" << std::endl;
		else
			std::cout << " armies" << std::endl;
	}

	bool validOrigin = false;
	std::string originAns;
	do {
		std::cout << "Please choose an origin.\n\n";
		std::cin >> originAns;
		for (int i = 0; i < originStr.size(); i++)
		{
			if (originStr[i] == originAns)
			{
				validOrigin = true;
				break;
			}
		}

	} while (!validOrigin);

	tOriginStr = originAns;
	setTOrigin(tOriginStr);
}

void Fortification::fortify()
{
	Map *map = Map::getMapInstance();

	// List the territories that migrate 
	std::vector<Territory*> allTerritories = map->getTerritories();		// Map's territories
	std::vector<Territory*> pTerritories = map->getTerritoriesByPlayer(mCurrent->getName());								// Player's territories

	std::vector <std::string> tempOriginStr1;
	std::vector <std::string> tempDestinationStr1;
	std::vector <std::string> tempOriginStr2;
	std::vector <std::string> tempDestinationStr2;

	std::cout << "Current player: " << mCurrent->getName() << std::endl;

	
	// Get preliminary origin and destination list
	std::vector<Territory*>::iterator it;
	
	for (it = allTerritories.begin(); it != allTerritories.end(); it++)
	{
		// Look for all owned territories (= min 1 army)
		if ((*it)->getPlayerOwner() == mCurrent)
		{
			tempDestinationStr1.push_back((*it)->getName());

			// Look for all owned territories with at least 2 armies
			if ((*it)->getAmountOfArmies() >= 2)
{
				tempOriginStr1.push_back((*it)->getName());

				pTerritories.push_back(*it);	
			}
		}
}

	// Sort the list of origins
	for (int i = 0; i < tempOriginStr1.size(); i++)
{
		// Get the list of neighbors for a territory
		std::vector <std::string> neighbor = createNeighborsStr(tempOriginStr1[i]);

		// Add the one that has valid neighbors
		if (neighbor.size() > 0)
	{
			originStr.push_back(tempOriginStr1[i]);
		}
	}

	// Select Origin
	selectOrigin();
	
	// Select Designation
	selectDestination(tOriginStr);

	// Move Armies
	move(tOriginStr, tDestinationStr);
	}

std::vector<std::string> Fortification::createNeighborsStr(std::string name)
{
	//std::cout << "CREATE " << std::endl;
	Map *map = Map::getMapInstance();
	std::vector<Territory*> nTerritory = map->getTerritoryByName(name)->getNeighbors();
	std::vector<std::string> nTerritoryStr0;
	std::vector<std::string> nTerritoryStr;

	// Get the name of all neighbors
	for (int i = 0; i < nTerritory.size(); i++)
	{
		nTerritoryStr0.push_back(nTerritory.at(i)->getName());
}

	// Get the name of the owned neighbors
	for (int j = 0; j < nTerritoryStr0.size(); j++)
{
		for (int k = 0; k < map->getTerritories().size(); k++)
	{
			if (nTerritoryStr0[j] == map->getTerritories().at(k)->getName())
				if (map->getTerritories().at(k)->getPlayerOwner() == mCurrent)
					nTerritoryStr.push_back(nTerritoryStr0[j]);
		}
	}
	
	return nTerritoryStr;
}

void Fortification::setTOrigin(std::string aTerritory)
{
	Map *map = Map::getMapInstance();
	tOrigin = map->getTerritoryByName(aTerritory);
}

void Fortification::setTDestination(std::string aTerritory)
{
	Map *map = Map::getMapInstance();
	tDestination = map->getTerritoryByName(aTerritory);
}

void
Fortification::run(Player* player)
{
  mCurrent = player;
  if (mCurrent->getHasNewTerritory())
  {
	  fortify();
	  // New risk card
	  std::cout << "Player receives a new Risk card!" << std::endl;
	  mCurrent->addCard(GameDeck::getGameDeckInstance()->drawCard());
  }
}
