/*
 * Battle.cpp
 *
 *  Created on: Feb 5, 2015
 *      Author: Emmanuel
 */

#include "Battle.h"

Battle::Battle ()
{
	mAttacker = NULL;
	mDeffender = NULL;

	srand (time(NULL));
}

Battle::~Battle ()
{
	// TODO Auto-generated destructor stub
}

void
Battle::RunBattle (bool allIn, Player* player)
{
	bool keepAttacking = true;
	bool setupOK = SetupBattle(player);

	while(keepAttacking && setupOK)
	{

		mAttackersDice.clear();
		mDeffendersDice.clear();
		if(mAttacker->getAmountOfArmies() < min_armies_to_attack)
		{
			std::cout<<"You don't have enough armies to attack"<<std::endl;
			return;
		}

		if (typeid(player).name() == "AIPlayer*")
		{
			RollDices(true);
		}
		else
			RollDices(allIn);

		for(int i = 0; i < mDeffendersDice.size(); i++)
		{
			if(mAttackersDice.at(i) > mDeffendersDice.at(i))
			{
				int num = mDeffender->getAmountOfArmies() - 1;
			}
			else
			{
				int num = mAttacker->getAmountOfArmies() - 1;
				mAttacker->setAmountOfArmies(num);
			}
		}

		//PRINT CURRENT GAME

		if(mDeffender->getAmountOfArmies() == 0)
		{
			int newArmies;
			std::cout<<"Attackers Won! Distribute your armies!"<<std::endl<<"How many armies will you place in your new territory?"<<std::endl;
			if (typeid(player).name() == "AIPlayer*")
			{
				AIPlayer *AI = (AIPlayer*)player;

				newArmies = 1;
				std::cout<<newArmies<<std::endl;
			}
			else
				std::cin>>newArmies;
			if(newArmies > mAttackersDice.size())
			{
				newArmies = mAttackersDice.size();
			}
			if(newArmies > mAttacker->getAmountOfArmies() - 1)
			{
				newArmies = mAttacker->getAmountOfArmies() - 1;
			}
			mDeffender->setAmountOfArmies(newArmies);
			int num = mAttacker->getAmountOfArmies() - newArmies;
			mAttacker->setAmountOfArmies(num);
			mDeffender->setPlayerOwner(mAttacker->getPlayerOwner());
			std::cout<<mDeffender->getName()<<" is now owned by: "<<mDeffender->getPlayerOwner()->getName()<<std::endl;
			mDeffender->getPlayerOwner()->notify();

			// Set eligibility for fortification
			mAttacker->getPlayerOwner()->setHasNewTerritory(true);

			// If mDeffender is eliminated and has cards, then mAttacker receives them.
			if (mDeffender->getPlayerOwner()->getEliminated())
			{
				std::cout << "Defender is eliminated." << std::endl;
				if (mDeffender->getPlayerOwner()->getNCard() > 0)
				{
					std::cout << "Defender had cards." << std::endl;
					std::vector<Card*> cDeffender = mDeffender->getPlayerOwner()->getCards();
					std::cout << mAttacker->getPlayerOwner()->getName() << " has " << mAttacker->getPlayerOwner()->getNCard() << " cards." << std::endl;
					for (int i = 0; i < cDeffender.size(); i++)
					{
						mAttacker->getPlayerOwner()->addCard(cDeffender[i]);
					}
					std::cout << mAttacker->getPlayerOwner()->getName() << " has " << mAttacker->getPlayerOwner()->getNCard() << " cards." << std::endl;
				}
				else
					std::cout << "No card." << std::endl;
			}
			return;
		}
		else if(!allIn)
		{
			char choice;

			std::cout<<"Keep Attacking? (y/n)"<<std::endl;

			if(choice == 'n')
			{
				keepAttacking = false;
			}
			else
			{
				keepAttacking = true;
			}
		}

	}

}

void
Battle::setDeffender (Territory* deffender)
{
	mDeffender = deffender;
}

void
Battle::RollDices (bool allin)
{
	int atDice;
	if(!allin){
		std::cout<<"How many dice do you wish to roll?"<<std::endl;
		std::cin>>atDice;
	}
	else
	{
		atDice = 3;
	}
	if(atDice > max_attack_dices)
	{
		atDice = max_attack_dices;
	}
	if(atDice > mAttacker->getAmountOfArmies() - 1)
	{
		atDice = mAttacker->getAmountOfArmies() - 1;
	}
	int dfDice;
	dfDice = mDeffender->getAmountOfArmies();
	if(dfDice > max_defense_dices)
	{
		dfDice = max_defense_dices;
	}
	if(dfDice > atDice)
	{
		dfDice = atDice;
	}

	//rand

	for(int i = 0; i < atDice; i++)
	{
		mAttackersDice.push_back(rand() % 6 + 1);
	}
	for(int i = 0; i < dfDice; i++)
	{
		mDeffendersDice.push_back(rand() % 6 + 1);
	}

	std::sort(mAttackersDice.begin(), mAttackersDice.end(), std::greater<int>());
	std::sort(mDeffendersDice.begin(), mDeffendersDice.end(), std::greater<int>());

	std::cout<<std::endl<< "Attackers Dice: "<<std::endl;
	for(int i = 0; i < atDice; i++)
	{
		std::cout<<mAttackersDice.at(i)<<" ";
	}
	std::cout<<std::endl<< "Defenders Dice: "<<std::endl;
	for(int i = 0; i < dfDice; i++)
	{
		std::cout<<mDeffendersDice.at(i)<<" ";
	}
	std::cout<<std::endl;
}


bool
Battle::SetupBattle (Player* player)
{
	mMap = Map::getMapInstance();
	std::string at, dt;

	if(typeid(player).name() == "AIPlayer*")
	{
		AIPlayer *AI = (AIPlayer*)player;

		at = AI->decideAttackingTerritory();
		std::cout<<at<<std::endl;
	}
	else{
		std::cin.clear();
		std::cin.get();
		std::cout<<"Choose Attacking Territory:" <<std::endl;
		getline(std::cin, at);
	}
	if(mMap->getTerritoryByName(at)->getPlayerOwner() == player)
	{
		setAttacker(mMap->getTerritoryByName(at));
	}
	else
	{
		std::cout<<"This territory doesn't belong to you!"<<std::endl;
		return false;
	}


	if (typeid(player).name() == "AIPlayer*")
	{
		AIPlayer *AI = (AIPlayer*)player;

		dt = AI->decideDefendingTerritory();
		std::cout<<dt<<std::endl;
	}
	else{
		std::cout<<"Choose Defending Territory:" <<std::endl;
		getline(std::cin, dt);
	}
	if(mMap->getTerritoryByName(dt)->getPlayerOwner() != player)
	{
		setDeffender(mMap->getTerritoryByName(dt));
	}
	else
	{
		std::cout<<"You can't attack a territory owned by yourself!"<<std::endl;
		return false;
	}
	if(!mAttacker->isNeighbor(mDeffender))
	{
		std::cout<<"These territories are not neighbors!"<<std::endl;
		return false;
	}
	return true;
}

void
Battle::setAttacker (Territory* attacker)
{
	mAttacker = attacker;
}

void
Battle::run(Player* player)
{
  Map *map = Map::getMapInstance();
  map->getStatsNotifier()->setStatusMessage("Battle!");

  bool endTurn = false;
  char choice;

  while (!endTurn)
  {
  		std::cout  << "What would you like to do?" << std::endl

  		    << "1 - Normal Attack" << std::endl <<
		    "2 - AllOutAttack"<< std::endl <<
		    "3 - End Turn" << std::endl;

  if (player->getName() == "AI")
  {
  AIPlayer *AI = (AIPlayer*) player;

  choice = AI->decideAttack();
  std::cout << choice << std::endl;
  }
  else
  std::cin >> choice;
  switch (choice)
  {
  case '1':
  			// Notify Status
      map->getStatsNotifier()->setStatusMessage("Battle - Normal Attack");

      RunBattle(false, player);
      break;

  case '2':
  			// Notify Status
	map->getStatsNotifier()->setStatusMessage("Battle - All Out Attack");

  	RunBattle(true, player);
  	break;
  default:
  			// Notify Status
	map->getStatsNotifier()->setStatusMessage("Battle - End Turn");

	endTurn = true;

  }
  std::cin.get();

  	/*	for (unsigned int i = 0; i < map->getTerritories().size(); i++)
  {
  			std::cout  << map->getTerritories().at(i)->getName() << " "

  << map->getTerritories().at(i)->getPlayerOwner()->getName()
  << std::endl;
  }*/


  } // End of the Battle Loop

}






















