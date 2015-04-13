#include "Game.h"

//////// Constructor ////////
Game::Game()
{
	std::cout << "Risk!\n\n";
	std::cout << "Loading map...\n\n";
	map = Map::getMapInstance();
	graphics();
	std::cout << "Map has been created!\n\n";
	startUp();
	std::cout << "End of Start-up!\n\n";
	//mainPlay(); !! To put back on after reinforcement testing
	cardReinforcement = new int(5);
	totArmy = 0;
}

//////// Start-Up ////////
void Game::startUp()
{
	endGame = false;
	createPlayer();
	/*turnOrder();
	pickRandom();
	placeArmy();	!! To put back on after reinforcement testing */
	GameDeck gDeck;
	gDeck.createDeck();
	std::cout << "Listing all Risk cards:\n";
	gDeck.printCards();
	
	/* Reinforcement Test		  */
//	Reinforcement rPhase(players[0], cardReinforcement);
//	rPhase.reinforce();
	/* _End of Reinforcement Test */
}


void Game::graphics()
{
	// Requires the Singletone instance of Map

	std::string c[] =
	{ "blue", "red", "green", "black", "gray", "cyan", "magenta", "yellow" };

	window.clear(sf::Color(45, 45, 45));
	MapIO mio;
	GameToMapIO gtmio(mio);
	gtmio.loadGameInfo("World.map");
	//mio.loadMapInfo("World.map");
	mio.saveMapInfo("WorldSave.map");
	window.display();

	map->getFileName();
	sf::Image mapBackground;
	mapBackground.loadFromFile(map->getFileName());

	// Creates the main render window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 6;
	//settings.depthBits = 0;
	//settings.stencilBits = 0;
	//settings.majorVersion = 3;
	//settings.minorVersion = 3;

	if (mapBackground.getSize().x >= 900)
		window.create(
		sf::VideoMode(mapBackground.getSize().x,
		mapBackground.getSize().y + 100), "Map Assignment 2!",
		sf::Style::Default, settings);
	else
		window.create(
		sf::VideoMode(
		mapBackground.getSize().x
		+ (900 - mapBackground.getSize().x),
		mapBackground.getSize().y + 100), "Map Assignment 2!",
		sf::Style::Default, settings);

	// Create and Attach Map and Player Viewers:
	MapObserver = new MapViewer(map, window); // Responsible for displaying the Map itself, continent colors and neighborhoods
	PlayerObserver = new PlayerViewer(map, window); // Responsible for displaying the User in it's territories and it's armies

	for (int i = 0; i < map->getContinents().size(); i++)
	{
		map->getContinents().at(i)->setColor(c[i % 8]);
	}

	map->notify();
	window.display();
}

void Game::createPlayer()
{

	std::cout << "Please enter the number of player 2-6.\n\n";
	//std::cin >> nPlayer;
	std::cout << "2" << std::endl; // !! To change back to 3 after reinforcement testing
	nPlayer = 2;

	players = new Player*[nPlayer];

	std::cout << "\nCreating players...\n\n";

	players[0] = new Player(0);
	std::cout << "Please enter your name\n";
	std::string name;
	std::cin >> name;
	players[0]->setName(name);
	players[0]->setColor("red");
	
	players[1] = new AIPlayer("AI", 1);
	players[1]->setName("AI");
	std::cout << "Please enter your name\n";
	std::cout << "AI\n";
	AIPlayer *AI = (AIPlayer*)players[1];
	AI->setStrategy(new Defensive());
	
	// !! To put back on after reinforcement testing
	/*players[2] = new Player(2);
	std::cout << "Please enter your name\n";
	std::cin >> name;
	players[2]->setName(name);
	players[2]->setColor("green");*/ 

	// Create the Statistics Observers, that will monitor individually each player
	StatisticsObserver = new StatisticsViewer*[nPlayer];
	bottomBar = new sf::RenderTexture[nPlayer];

	for (int i = 0; i < nPlayer; i++)
	{
		bottomBar[i].create(window.getSize().x / 6, 100);
		StatisticsObserver[i] = new StatisticsViewer(players[i], bottomBar[i],
			window);
		players[i]->setNArmy(assignArmy());
		players[i]->setNReinforcement(assignArmy());
		totArmy += assignArmy() * nPlayer;
		std::cout << players[i]->getName()
			<< " is now a player and will receive an army of "
			<< assignArmy() << " infantries.\n\n";
		players[i]->notify();
	}

	std::cout << std::endl;

}

int Game::assignArmy()
{
	switch (nPlayer)
	{
	case 2:
		return 23;
	case 3:
		return 35;
	case 4:
		return 30;
	case 5:
		return 25;
	case 6:
		return 20;
	default:
		return 0;
	}
}

// To remove
/*void Game::ownCountry(Country c, Player p)
{
if (!c.getIsOwned())
c.setIsOwned(true);
else
cout << "Country is occupied, please chose again.\n\n";
}*/

void Game::placeArmy()
{
	std::cout << "Now it's the distributing armies phase." << std::endl;
	//ct = first;
	int turn = ct;

	for (int i = 0; i < nPlayer; i++)
	{

		if (i == ct)
			players[i]->setTurnState(true);
		else
			players[i]->setTurnState(false);

		while (players[ct]->getNReinforcement() > 0)
		{
			std::cout << players[ct]->getName() << ",  "
				<< players[ct]->getNReinforcement()
				<< " reinforcements remaining, select a country.\n";
			std::string territory;
			getline(std::cin, territory);

			if (map->getTerritoryByName(territory)->getPlayerOwner()->getName()
				== players[ct]->getName())
			{
				map->getTerritoryByName(territory)->setAmountOfArmies(
					map->getTerritoryByName(territory)->getAmountOfArmies()
					+ 1);
				players[ct]->setNReinforcement(
					players[ct]->getNReinforcement() - 1);
				std::cout << territory << " has now "
					<< map->getTerritoryByName(territory)->getAmountOfArmies()
					<< " armies.\n";
			}
		}
		ct = (ct + 1) % nPlayer;

	}

	ct = turn;

	for (int i = 0; i < nPlayer; i++)
	{
		if (i == ct)
			players[i]->setTurnState(true);
		else
			players[i]->setTurnState(false);
	}

}
void Game::pickRandom()
{
	std::cout << "Pick Random.\n\n";

	ct = first;
	std::vector<Territory*> vt = map->getTerritories();

	for (int i = 0; i < nPlayer; i++)
	{
		if (i == ct)
			players[i]->setTurnState(true);
		else
			players[i]->setTurnState(false);
	}

	srand(time(NULL));

	int numTerri = vt.size();

	while (numTerri > 0)
	{
		// To remvove ?
		/*std::cout << "Inside num > 0\n\n";
		int rd;
		do {
		std::cout << "Inside rd > 0\n\n";
		rd = rand() % (numTerri);
		} while (map->getTerritories().at(rd)->getPlayerOwner()->getName() == "");
		std::cout << players[ct].getName() << " is assigned a country.\n\n";
		map->getTerritories().at(rd)->setPlayerOwner(&players[ct]);
		players[ct].setNReinforcement(players[].getNReinforcement() - 1);
		totArmy--;*/

		int rd;
		rd = rand() % (numTerri);

		vt.at(rd)->setPlayerOwner(players[ct]);
		vt.at(rd)->setAmountOfArmies(1);
		players[ct]->setNReinforcement(players[ct]->getNReinforcement() - 1);
		players[ct]->winTerritory();

		std::cout << vt.at(rd)->getName() << " belongs to: "
			<< players[ct]->getName() << std::endl;

		vt.erase(vt.begin() + rd);

		numTerri--;
		totArmy--;

		//Incrementing the turn order counter
		ct = (ct + 1) % nPlayer;

		for (int i = 0; i < nPlayer; i++)
		{
			if (i == ct)
				players[i]->setTurnState(true);
			else
				players[i]->setTurnState(false);
		}
	}

	GameIO gio;
	gio.saveGameInfo("gameSave.gsv");
	std::cout
		<< "If you desire to change any information from the current game state, edit the gameSave.gsv file and press enter.";
	std::cin.get();
	std::cin.get();
	gio.loadGameInfo("gameSave.gsv");
}

// To remove
/* OLD
void Game::placeArmy()
{
int army = assignArmy() * nPlayer;
int numOfCountries = 5; // Reality: 68, 5 for test
//bool unavailChoice = false;

while (numOfCountries > 0) //&& players[ct].getNumOfArmy > 0
{
//do {
std::cout << "Here Order: " << ct << std::endl;
std::cout << players[ct].getName() << ", select a country.\n";
std::string territory;
std::cin >> territory;
map->getTerritoryByName(territory)->setPlayerOwner(&players[ct]);
players[ct].winTerritory();
//	players[ct].decArmyToPlace();
std::cout << territory << " is now occupied by " << players[ct].getName() << std::endl;
/*	}
} while (!unavailChoice);*//* To add: real control over occupied and unoccupied country, with final countries */

/*		numOfCountries--;
ct = (ct + 1) % nPlayer; */ //Goes to next player
/*	}

}*/

void Game::turnOrder()
{
	/* The player with the highest score is the one that plays first.
	To apply the clockwise principle, the next player is the next one
	in the circular array.*/

	srand(time(NULL));

	int max = 0;
	int p = 0;

	for (int i = 0; i < nPlayer; i++)
	{
		std::cout << players[i]->getName() << " rolls the dice...\n";
		int dice = rollDice();
		std::cout << dice << std::endl;
		if (dice > max)
		{
			max = dice;
			p = i;
		}
	}
	Player *temp = new Player[nPlayer];
	std::cout << players[p]->getName() << " plays first." << std::endl;
	ct = p;
	first = p;
	/*for (int i = 0; i < nPlayer; i++)
	{
	temp[i] = *players[ct%nPlayer];
	//	std::cout << "Temp " << i << " is " << players[ct%nPlayer].getName() << std::endl;
	ct++;
	}
	players = &temp;*/
	ct = (first) % nPlayer;

	for (int i = 0; i < nPlayer; i++)
	{
		if (i == ct)
			players[i]->setTurnState(true);
		else
			players[i]->setTurnState(false);
	}

}

///////// Main Play ////////

void Game::mainPlay()
{
	std::cout << "Let's start the game...\n\n";

	int test = 5;
	ct = first;

	for (int i = 0; i < nPlayer; i++)
	{
		if (i == ct)
			players[i]->setTurnState(true);
		else
			players[i]->setTurnState(false);
	}

	//Round-Robin
	while (!endGame && test > 0)
	{

		std::cout << players[ct]->getName() << "'s turn!\n\n";

		//Reinforcement
		//std::cout << "Before Reinforcement, Test" << players[ct].getListCards(0) << " " << players[ct].getListCards(1) << " " << players[ct].getListCards(2) << std::endl;
		//reinforcement();

		//Battle
		//	battle();

		ct = (ct + 1) % nPlayer;

		for (int i = 0; i < nPlayer; i++)
		{
			if (i == ct)
				players[i]->setTurnState(true);
			else
				players[i]->setTurnState(false);
		}

		test--;
	}
}

////////  Reinforcement  //////// 
void Game::reinforcement()
{
	Reinforcement rPhase(players[ct], cardReinforcement);
	rPhase.reinforce();
	placeArmy();
}

// !! To put back on after reinforcement testing
////////  Battle  ////////
/*
void Game::battle()
{
bool endTurn = false;
char choice;
Battle b;
while (!endTurn)
{
std::cout << "What would you like to do?" << std::endl
<< "1 - Normal Attack" << std::endl << "2 - AllOutAttack"
<< std::endl << "3 - End Turn" << std::endl;

if (players[ct]->getName() == "AI")
{
AIPlayer *AI = (AIPlayer*) players[ct];

choice = AI->decideAttack();
std::cout << choice << std::endl;
}
else
std::cin >> choice;
switch (choice)
{
case '1':
b.RunBattle(false, players[ct]);
break;
case '2':
b.RunBattle(true, players[ct]);
break;
default:
endTurn = true;
}
std::cin.get();

for (int i = 0; i < map->getTerritories().size(); i++)
{
std::cout << map->getTerritories().at(i)->getName() << " "
<< map->getTerritories().at(i)->getPlayerOwner()->getName()
<< std::endl;
}

}
}*/


// !! To put back on after reinforcement testing
////////  Fortification  ////////
/*void Game::fortification()
{
Fortification f(map, players[ct]);
cout << "Please choose an origin." << endl;
string origin;
cin >> origin;
f.selectOrigin("evendim", ct);
/*cout << "Please choose a destination.";
string d;
cin >> d;
cout << "Destination is: " << d << endl;*/
//f.selectDestination(o, d, ct);
//}
////////  Other  ////////
int Game::rollDice()
{
	int val = rand() % 5 + 1;
	return val;
}
// !! To put back on after reinforcement testing
/*
void Game::drawCard()
{
if (players[ct]->getHasNewTerritory())
{
std::cout << "Player has conquered a new territory and will receive a Risk card\n\n";
players[ct]->setHasNewTerritory(false);
int card = rand() * 3;
if (card == 0)
players[ct]->setListCards(players[ct]->getListCards(0) + 1, 0, 0);
if (card == 1)
players[ct]->setListCards(0, players[ct]->getListCards(1) + 1, 0);
if (card == 2)
players[ct]->setListCards(0, 0, players[ct]->getListCards(2 + 1));
players[ct]->setNCard(players[ct]->getNCard() + 1);
if (players[ct]->getNCard() > 5)
std::cout << "Player has 5 cards and must exchange them in the next round.\n\n";
else
std::cout << "No risk card.\n\n";
}

}
*/
