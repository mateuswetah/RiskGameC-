#include "Reinforcement.h"

/*Reinforcement::Reinforcement()
{
	std::cout << "Reinforcement Phase.\n";
	map = Map::getMapInstance();
	numOfR = 0;
}*/

Reinforcement::Reinforcement(Player *p, int *c)
{
	std::cout << "Reinforcement Phase.\n";
	mCurrent = p;
	cardBonusCt = c;
	useCard = false;
	numOfR = 0;
}

void Reinforcement::countTerritories()
{
	std::cout << "Counting the number of territories.\n";
	int count = mCurrent->getNTerritory();
	std::cout << "Num = " << count << std::endl;
	count = (int)floor(count / 3);
	if (count >= 3)
		numOfR += count;
	else
		numOfR += 3;
	std::cout << "Reinforcement = " << numOfR << std::endl;
}


void Reinforcement::countContinents()
{
	std::cout << "Counting the number of continents.\n";

	// Entire territory info
	Map *map = Map::getMapInstance();
	std::vector<Continent*> continents = map->getContinents();
	std::vector<Territory*> territories;

	// Check if the current player owns the continent
	std::vector<Continent*>::iterator it;
	for (it = continents.begin(); it != continents.end(); it++)
	{
		// Set the value of continent bonus 
		int bonus = (*it)->getBonus();

		territories = (*it)->getTerritories();
		std::vector<Territory*>::iterator it2;
		for (it2 = territories.begin(); it2 != territories.end(); it2++)
		{
			if ((*it2)->getPlayerOwner()->getName() != mCurrent->getName())
			{
				// Player is not the owner of the continent: no bonus -> set to 0
				bonus = 0;
				break;
			}
		}
		// Assign appropriate bonus value according to ownership status
		numOfR = bonus;
		
	}

	std::cout << "Reinforcement = " << numOfR << std::endl;
	std::cout << "End of Continent Bonus\n";
}

bool Reinforcement::checkMinCondition()
{
	int type1 = 0;
	int type2 = 0;
	int type3 = 0;

	PlayerDeck *pdeck = this->mCurrent->getPDeck();
	pdeck->printCards();

	// Counting card per type
	for (int i = 0; i < pdeck->getNumOfCards(); i++)
	{
	/*	int type = pdeck->getCards().at(i)->getTypeOfArmy();
		if (type == 1)
			type1++;
		else if (type == 2)
			type2++;
		else
			type3++;*/
	}

	// Delete pointer
	delete pdeck;
	pdeck = NULL;

	// Check condition
	if (type1 >= 3 || type2 >= 3 || type3 >= 3 || (type1 > 0 && type2 > 0 && type3 > 0))
		return true;
	else
	{
		//std::cout << "Do not meet mininal condition." << std::endl;
		return false;
	}
}

void Reinforcement::countCards()
{
	int numOfCard = mCurrent->getNCard();
	std::cout << "NumOfCards = " << numOfCard << std::endl;
	bool meetConditions = checkMinCondition();
	if (numOfCard >= 5)
	{
		std::cout << "Player must exchange its cards.\n\n";
		exchangeCards();
	}
	else if (meetConditions)
	{	
		std::cout << "Player may exchange its cards.\n\n";
		std::string ans;
		std::cin.ignore();
		std::cout << "Do you want to exchange? true or false.\n\n";
		std::cin >> ans;
		if (ans == "true")
			exchangeCards();
	}
	else
	{
		std::cout << "Cannot exchange." << std::endl;
	}
}



void Reinforcement::exchangeCards()
{
	std::vector<Card*> deck = mCurrent->getPDeck()->getCards();
	Card* exchangeSet[3];

	// Listing the cards
	std::cout << "List of Cards (Select a set of 3 unique types or a set of 3 cards of the same type)\n\n";
	mCurrent->getPDeck()->printCards();

	// Asking the player to pick 3 cards
	do {
		int choice;

		for (int i = 1; i <= 3; i++)
		{
			std::cout << "Select card #:" << i - 1 << std::endl;
			std::cin.ignore();
			std::cin >> choice;
			exchangeSet[i-1] = deck.at(choice);
		}

	} while (!(exchangeSet[1]->getTypeOfArmy() == exchangeSet[2]->getTypeOfArmy() && exchangeSet[2]->getTypeOfArmy() == exchangeSet[3]->getTypeOfArmy()) ||		// Case: same type
		((exchangeSet[1]->getTypeOfArmy() == exchangeSet[2]->getTypeOfArmy()) || (exchangeSet[2]->getTypeOfArmy() == exchangeSet[3]->getTypeOfArmy()) ||		// Case: unique type 
		(exchangeSet[1]->getTypeOfArmy() == exchangeSet[3]->getTypeOfArmy())));																					

	// Look for card territory extra bonus
	checkCardName(exchangeSet);
	
	// Update the player's & the game's number of reinforcements
	numOfR += (*cardBonusCt);
	cardBonusCt += 5;

	std::cout << "Reinforcement = " << numOfR << std::endl;

//	useCard = true;

	// Delete pointers
	deck.clear();
	delete exchangeSet;
}


void Reinforcement::checkCardName(Card* exchangeSet[3])
{
	// Looking for all the territories that the player owns
	Map *map = Map::getMapInstance();
	std::vector<Territory*> allTerritories = map->getTerritories();
	std::vector<Territory*>::iterator it;

	for (it = allTerritories.begin(); it != allTerritories.end(); it++)
	{
		bool eligible = false; // To control outer loop

		if (((*it)->getPlayerOwner()->getName() == mCurrent->getName()) && !eligible)
		{
			// Looking for card with the player's territory
			for (int i = 0; i < 3; i++)
			{
				// Check if eligible for extra 2 armies territory name bonus per turn
				if (exchangeSet[i]->getTerritoryName() == (*it)->getName())
				{
					// Assign 2 extra armies for this territory
					(*it)->setAmountOfArmies((*it)->getAmountOfArmies() + 2);
					eligible = true;
					break; // Break innerloop
				}
			}
		}
		else
			break; // Break outerloop
	}

	// Deleting pointers
	delete map;
	allTerritories.clear();
}

void Reinforcement::reinforce()
{
	/* Execute the counts */
	countTerritories();
	countContinents();
	countCards();

	/* Assign the number of reinforcements to the current player */
	mCurrent->setNReinforcement(numOfR);
	mCurrent->notify();
}

/*int* Reinforcement::updateCardBonus()
{
	if (useCard)
		cardBonusCt += 5;
	return cardBonusCt;
} */
