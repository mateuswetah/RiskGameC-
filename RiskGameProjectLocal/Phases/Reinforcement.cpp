#include "Reinforcement.h"

Reinforcement::Reinforcement(int ct)
{
	std::cout << "Reinforcement Phase.\n";
	//mCurrent = p;
	cardBonusCt = ct;
	exchange = false;
	numOfR = 0;
}

Reinforcement::~Reinforcement()
{
	delete mCurrent;
}

void Reinforcement::countTerritories()
{
	std::cout << "Counting the number of territories..\n";
	int count = mCurrent->getNTerritory();
	//std::cout << "Num = " << count << std::endl;
	count = (int)floor(count / 3);
	if (count >= 3)
		numOfR += count;
	else
		numOfR += 3;
	std::cout << "Reinforcement = " << numOfR << std::endl;
}


void Reinforcement::countContinents()
{
	std::cout << "Counting the number of continents...\n";
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
		numOfR += bonus;
		
	}

	std::cout << "Reinforcement = " << numOfR << std::endl;
	std::cout << "End of Continent Bonus\n";
}

bool Reinforcement::checkMinCondition()
{
	int type1 = 0;
	int type2 = 0;
	int type3 = 0;

	// Counting card per type
	for (int i = 0; i < mCurrent->getNCard(); i++)
	{
		int type = mCurrent->getCards().at(i)->getTypeOfArmy();
		if (type == 1)
			type1++;
		else if (type == 2)
			type2++;
		else
			type3++;
	}

	// Check condition
	if (type1 >= 3 || type2 >= 3 || type3 >= 3 || (type1 > 0 && type2 > 0 && type3 > 0))
		return true;
	else
	{
		return false;
	}
}

void Reinforcement::countCards()
{
	std::cout << "Counting the number of cards..\n";
	std::vector<Card*> cards = mCurrent->getCards();
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
		if(ans == "true")
			exchangeCards(cards);
	}
	else
	{
		std::cout << "Cannot exchange." << std::endl;
	}
}



void Reinforcement::exchangeCards(std::vector<Card*> cards)
{
	exchange = true;
	Card* exchangeSet[3];

	// Listing the cards
	std::cout << "List of Cards (Select a set of 3 unique types or a set of 3 cards of the same type)\n\n";
	
	for (int i = 0; i < cards.size(); i++)
		{
			std::cout << i << ") " << cards.at(i)->getTerritoryName() << ", ";
			std::cout << cards.at(i)->getTypeOfArmyStr() << std::endl;
		}
	
	do {
		int choice;

		for (int i = 0; i < 3; i++)
		{
			std::cout << "Select card #:" << (i + 1) << std::endl;
			std::cin.ignore();
			std::cin >> choice;
			exchangeSet[i] = cards.at(choice);
		}
		
	} while (!sameType(exchangeSet) && !uniqueType(exchangeSet));
	
	// Look for card territory extra bonus
	checkCardName(exchangeSet);

	// Update info
	updatePDeck(exchangeSet, cards);
	numOfR += cardBonusCt;

	std::cout << "Reinforcement = " << numOfR << std::endl;

}

void Reinforcement::updatePDeck(Card* exchangeSet[3], std::vector<Card*> cards)
{
	// Delete the cards from the player's deck
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < cards.size(); j++)
		{
			if (cards.at(j)->getTerritoryName() == exchangeSet[i]->getTerritoryName())
			{
				cards.erase(cards.begin() + j);
				break;
			}
		}
	}

	// Update info
	mCurrent->setNCard(cards.size());
	mCurrent->setCards(cards);
	mCurrent->notify();
}


bool Reinforcement::sameType(Card* exchangeSet[3])
{
	return ((exchangeSet[0]->getTypeOfArmy() == exchangeSet[1]->getTypeOfArmy()) && (exchangeSet[1]->getTypeOfArmy() == exchangeSet[2]->getTypeOfArmy()));
}

bool Reinforcement::uniqueType(Card* exchangeSet[3])
{
	return ((exchangeSet[0]->getTypeOfArmy() != exchangeSet[1]->getTypeOfArmy()) && (exchangeSet[1]->getTypeOfArmy() != exchangeSet[2]->getTypeOfArmy())		// Case: unique type 
		&& (exchangeSet[0]->getTypeOfArmy() != exchangeSet[2]->getTypeOfArmy()));

}

void Reinforcement::checkCardName(Card* exchangeSet[3])
{
	// Looking for all the territories that the player owns
	Map *map = Map::getMapInstance();
	std::vector<Territory*> allTerritories = map->getTerritories();
	std::vector<Territory*>::iterator it;
	bool eligible = false; // To control outer loop
	
	for (it = allTerritories.begin(); it != allTerritories.end(); it++)
	{
		if (!eligible)
		{
			if (((*it)->getPlayerOwner() == mCurrent) && !eligible)
			{
				// Looking for card with the player's territory
				for (int i = 0; i < 3; i++)
				{
					if (exchangeSet[i]->getTerritoryName() == (*it)->getName())
					{
						// Assign 2 extra armies for this territory
						(*it)->setAmountOfArmies((*it)->getAmountOfArmies() + 2);
						eligible = true;
						break; // Break innerloop
					}
				}
			}
		}
		else
			break; // Break outerloop
	}

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

	/* Distribute army */
	placeReinforcement();

	std::cout << "End of Reinforcement" << std::endl;
}

int Reinforcement::updateCardBonus()
{
	if (exchange)
		cardBonusCt += 5;
	return cardBonusCt;
}

void Reinforcement::placeReinforcement()
{
	std::cout << "Place Reinforcements" << std::endl;

	Map *map = Map::getMapInstance();

	while (mCurrent->getNReinforcement() > 0)
	{

		std::cout << mCurrent->getName() << ", "	<< mCurrent->getNReinforcement()
		<< " reinforcements remaining, select a country.\n";
		std::string territory;
		getline(std::cin, territory);

		if (map->getTerritoryByName(territory)->getPlayerOwner() == mCurrent)
		{
			map->getTerritoryByName(territory)->setAmountOfArmies(
				map->getTerritoryByName(territory)->getAmountOfArmies()	+ 1);
			mCurrent->setNReinforcement(mCurrent->getNReinforcement() - 1);
			std::cout << territory << " has now " << map->getTerritoryByName(territory)->getAmountOfArmies() << " armies.\n";
		}
		
	}

	if (mCurrent->getName() == "AI")
	{


	}
}

void
Reinforcement::run(Player* player)
{
    Map::getMapInstance()->getStatsNotifier()->setStatusMessage("Reinforcement");
    reinforce();
}

















