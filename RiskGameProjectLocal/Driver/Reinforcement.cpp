#include "Reinforcement.h"

/*Reinforcement::Reinforcement()
{
	std::cout << "Reinforcement Phase.\n";
	map = Map::getMapInstance();
	numOfR = 0;
}*/

Reinforcement::Reinforcement(Player* p, int* c)
{
	std::cout << "Reinforcement Phase.\n";
	mCurrent = p;
	cardBonusCt = c;
	toExchange = false;
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
	std::cout << "Inside count card." << std::endl;
	//this->mCurrent->getPDeck()->printCards();
	//PlayerDeck *deck = mCurrent->getPDeck();
	std::vector<Card*> cards = mCurrent->getPDeck()->getCards();
	int numOfCard = mCurrent->getNCard();
	std::cout << "NumOfCards = " << numOfCard << std::endl;
	bool meetConditions = checkMinCondition();
	if (numOfCard >= 5)
	{
		std::cout << "Player must exchange its cards.\n\n";
		exchangeCards(cards);
	}
	else if (meetConditions)
	{	
		std::cout << "Player may exchange its cards.\n\n";
		std::string ans;
		std::cin.ignore();
		std::cout << "Do you want to exchange? true or false.\n\n";
		std::cin >> ans;
		if (ans == "true")
			exchangeCards(cards);
	}
	else
	{
		std::cout << "Cannot exchange." << std::endl;
	}
}



void Reinforcement::exchangeCards(std::vector<Card*> cards)
{
	//this->mCurrent->getPDeck()->printCards();
	//std::vector<Card*> *cards = &(mCurrent->getPDeck()->getCards());
	Card* exchangeSet[3];

	// Listing the cards
	std::cout << "List of Cards (Select a set of 3 unique types or a set of 3 cards of the same type)\n\n";
//	deck->printCards();
	//std::vector<Card*> *set = &(deck->getCards());

	if (cards.size() <= 0)
		std::cout << "No card.\n";
	else
	{
		for (int i = 0; i < cards.size(); i++)
		{
			std::cout << i << ") " << cards.at(i)->getTerritoryName() << ", ";
			std::cout << cards.at(i)->getTypeOfArmyStr() << std::endl;
		}
	}

	//mCurrent->notify();
	/*PlayerDeck *pDeck = mCurrent->getPDeck();
	std::vector<Card*> cards = pDeck->getCards();*/
	std::cout << "SUCEED" << std::endl;
	// Asking the player to pick 3 cards
	do {
		int choice;

		for (int i = 0; i < 3; i++)
		{
			std::cout << "Select card #:" << (i + 1) << std::endl;
			std::cin.ignore();
			std::cin >> choice;
			exchangeSet[i] = cards.at(choice);
			std::cout << exchangeSet[i]->getTypeOfArmy() << std::endl;
		}
		
	} while ( !sameType(exchangeSet) && !uniqueType(exchangeSet) );																			
	
	std::cout << "Out!" << std::endl;
	

	// Look for card territory extra bonus
	checkCardName(exchangeSet);
	std::cout << "No error" << std::endl;
	// Update the player's & the game's number of reinforcements
	std::cout << "carBonus = " << cardBonusCt << std::endl;
	numOfR += (int)cardBonusCt;
	cardBonusCt += 5;

	std::cout << "Reinforcement = " << numOfR << std::endl;

//	useCard = true;

}

bool Reinforcement::sameType(Card* exchangeSet[3])
{
	return ((exchangeSet[0]->getTypeOfArmy() == exchangeSet[1]->getTypeOfArmy()) && (exchangeSet[1]->getTypeOfArmy() == exchangeSet[2]->getTypeOfArmy()));
}

bool Reinforcement::uniqueType(Card* exchangeSet[3])
{
	return ((exchangeSet[0]->getTypeOfArmy() != exchangeSet[1]->getTypeOfArmy()) && (exchangeSet[1]->getTypeOfArmy() != exchangeSet[2]->getTypeOfArmy())		// Case: unique type 
		&& (exchangeSet[0]->getTypeOfArmy() != exchangeSet[2]->getTypeOfArmy()) );

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
/*	delete map;
	allTerritories.clear();*/
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
	std::cout << "End REiNFORCEMENT\n";
}

/*int* Reinforcement::updateCardBonus()
{
	if (useCard)
		cardBonusCt += 5;
	return cardBonusCt;
} */
