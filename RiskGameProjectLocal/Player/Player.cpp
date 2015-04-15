#include "Player.h"

Player::Player()
{
	//order = 0;
	mNumber = 0;
	name = "";
	turnState = false;
	nCard = 0;
	nTerritory = 0;
	nContinent = 0;
	nArmy = 0;
	nReinforcement = 0;
	nWin = 0;
	this->color = "gray"; // default
	hasNewTerritory = false;
	eliminated = false;
}

Player::Player(std::string color)
{
	this->color = color;
}
Player::Player(int n)
{
	hasNewTerritory = false;
	mNumber = n;
	name = "";
	turnState = false;
	nCard = 0;
	nTerritory = 0;
	nContinent = 0;
	nArmy = 0;
	nReinforcement = 0;
	nWin = 0;
	this->color = "green"; // default
	eliminated = false;
}


std::string Player::getColor()
{
	return this->color;
}

void Player::setName(std::string n)
{
	name = n;

	notify();
}

void Player::setTurnState(bool state)
{
	this->turnState = state;

	notify();
}

void Player::setColor(std::string color)
{
	this->color = color;

	notify();
}
std::string Player::getName()
{
	return name;
}

int
Player::getNumber()
{
	return mNumber;
}

bool Player::getTurnState()
{
	return this->turnState;
}

void Player::setNArmy(int a)
{
	nArmy = a;
	notify();
}

void Player::defineNArmy()
{
	// Local variables
	int num = 0;
	Map *map = Map::getMapInstance();
	std::vector<Territory*> allTerritories = map->getTerritories();
	std::vector<Territory*>::iterator it;

	// Looking for all the territories that the player owns 
	for (it = allTerritories.begin(); it != allTerritories.end(); it++)
	{
		if ((*it)->getPlayerOwner()->getName() == name)
		{
			// Count the number of armies in this territory
			num += (*it)->getAmountOfArmies();
		}
	}

	nArmy = num;
}

int Player::getNArmy()
{
	return nArmy;
}

/*
void Player::incArmy()
{
nArmy++;

notify();
}

void Player::decArmyToPlace()
{
nArmy--;

notify();
}*/

void Player::winTerritory()
{
	nTerritory++;

	notify();
}
/*
void Player::loseTerritory()
{
nTerritory--;

notify();
}*/

void Player::defineNTerritory()
{
	// Local variables
	Map *map = Map::getMapInstance();
	std::vector<Territory*> allTerritories = map->getTerritories();
	int num = 0;
	std::vector<Territory*>::iterator it;

	// Looking for all the territories that the player owns
	for (it = allTerritories.begin(); it != allTerritories.end(); it++)
	{
		if ((*it)->getPlayerOwner() == this)
			num++;
	}

	// Assign to nTerritory
	nTerritory = num;

	if (num == 0)
		eliminated = true;
}

int Player::getNTerritory()
{
	return nTerritory;
}

int Player::getNCard()
{
	return nCard;
}

void Player::setNCard(int i)
{
	nCard = i;

	notify();
}

void Player::setNReinforcement(int n)
{
	nReinforcement = n; 

	notify();
}

bool Player::getHasNewTerritory()
{
	return hasNewTerritory;
}

void Player::setHasNewTerritory(bool b)
{
	hasNewTerritory = b;

	//notify();
}

int Player::getNReinforcement()
{
	return nReinforcement;
}

void Player::defineNCard()
{
	nCard = cards.size();
}

void Player::defineNReinforcement()
{
	nReinforcement = getNReinforcement();
}

// Getters
std::vector<Card*> Player::getCards()
{
	return cards;
}


void Player::setCards(std::vector<Card*> set)
{
	cards = set;
	notify();
}

// Others
void Player::addCard(Card* aCard)		// aCard should be define with GameDeck::drawCard() function
{
	this->cards.push_back(aCard);
	//defineNCard();
	notify();
}

void Player::removeCard(Card* aCard)
{
	for (int i = 0; i < cards.size(); i++)
	{
		if (cards.at(i)->getTerritoryName() == aCard->getTerritoryName())
		{
			cards.erase(cards.begin() + i);
			break;
		}
	}
	//defineNCard();
	notify();
}

void Player::printCards()
{
	if (cards.size() <= 0)
		std::cout << "No card.\n";
	else
	{
		for (int i = 0; i < cards.size(); i++)
		{
			std::cout << cards.at(i)->getTerritoryName() << ", ";
			std::cout << cards.at(i)->getTypeOfArmyStr() << std::endl;
		}
	}
}

bool Player::getEliminated()
{
	return eliminated;
}