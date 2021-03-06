#include "Game.h"

//////// Constructor ////////
Game::Game()
{
	menu();

}

Game::~Game()
{
}

//////// Menu ////////
void Game::menu()
{
	bool exit = false;

	while (!exit)
	{
		std::cout << ">>#>>#>>#>>#>>#>>#>>-- RISK! --<<#<<#<<#<<#<<#<<#<<"	<< std::endl;
		std::cout << "--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--"	<< std::endl;
		std::cout << "                                                  "	<< std::endl;
		std::cout << "       Welcome to RISK!, a game made with C++     "	<< std::endl;
		std::cout << std::endl;

		int option = 0;

		while (option < 1 || option > 4)
		{
			std::cout << "Please type the number of your option:" 		<< std::endl;
			std::cout << " 1 - Start a new RISK! with an existing map."	<< std::endl;
			std::cout << " 2 - Load a previously started RISK! game."	<< std::endl;
			std::cout << " 3 - Create a new map with RISK! Map Creator"	<< std::endl;
			std::cout << " 4 - Exit."									<< std::endl;

			std::cin >> option;
		}

		std::string mapFileName;

		switch (option)
		{
		case 1: // Opening new Game with .map file
			std::cout << "Type the name of the map you want to load. Ex: 'World.map' " << std::endl;
			std::cin.get();
			std::getline(std::cin, mapFileName);

			std::cout << "Loading map..." << std::endl;
			map = Map::getMapInstance();

			graphics(mapFileName);
			std::cout << "Map has been created!"  << std::endl;

			startUp();
			std::cout << "End of Start-up! Let's play!"  << std::endl;

			mainPlay();

			break;
		case 2: // Loading existing game
			std::cout << "Type the name of the game you want to load. Ex: 'Game3.gsv' " << std::endl;
			std::cin.get();
			std::getline(std::cin, mapFileName);

			std::cout << "Loading map..."  << std::endl;
			map = Map::getMapInstance();
			graphics(mapFileName);
			std::cout << "Game has been loaded! Let's Play!"  << std::endl;
			mainPlay();

			break;
		case 3: // Map Creator
			mapCreator = new MapCreator();
			mapCreator->createAMap();

			break;
		case 4:
			exit = true;
			return;
		}
	}

}


//////// Start-Up ////////
void Game::startUp()
{
	cardReinforcement = 5;
	endGame = false;

	createPlayer();
	turnOrder();
	pickRandom();
	placeArmy();

	GameDeck gDeck;
	gDeck.createDeck();
	/*std::cout << "Listing all Risk cards:\n";
	gDeck.printCards();*/


}


void Game::graphics(std::string mapFileName)
{
	MapIO mio;
	GameToMapIO gtmio(mio);
	gtmio.loadGameInfo(mapFileName);
	//mio.loadMapInfo("World.map");
	mio.saveMapInfo("WorldSave.map");

	// Loads the Background Image
	sf::Image mapBackground;
	mapBackground.loadFromFile(map->getFileName());

	// Creates the main render window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	if (mapBackground.getSize().x >= 900)
		window.create(
				sf::VideoMode(mapBackground.getSize().x,
						mapBackground.getSize().y + 100), "RISK! - " + mapFileName ,
						sf::Style::Titlebar, settings);
	else
		window.create(
				sf::VideoMode(
						mapBackground.getSize().x
						+ (900 - mapBackground.getSize().x),
						mapBackground.getSize().y + 100), "RISK! - " + mapFileName,
						sf::Style::Titlebar, settings);

	window.clear(sf::Color(45, 45, 45));

	// Attach Map and Player Viewers:
	MapObserver = new MapViewer(map, window); // Responsible for displaying the Map itself, continent colors and neighborhoods
	PlayerObserver = new PlayerViewer(map, window); // Responsible for displaying the User in it's territories and it's armies

	// Coloring the continents (max 8 colors)
	std::string c[] =
	{ "blue", "red", "green", "black", "cyan", "magenta", "yellow", "gray" };

	for (unsigned int i = 0; i < map->getContinents().size(); i++)
	{
		map->getContinents().at(i)->setColor(c[i % 8]);
	}

	// Creates the Status Bar for notifying each stage of the game.
	map->setStatsNotifier(new StatusNotifier(window));
	map->getStatsNotifier()->setStatusMessage("Map Loaded Successfully");

	window.display();
}

void Game::createPlayer()
{
	// Notify Status
	map->getStatsNotifier()->setStatusMessage("Creating Players");

	// Coloring the players (max 6)
	std::string c[] = { "blue", "red", "green", "cyan", "magenta", "yellow" };

	do
	{
		std::cout << "Please enter the number of players: (2-6).\n\n";
		std::cin >> nPlayer;
	}
	while (nPlayer < 2 || nPlayer > 6);

	std::cout << "\nCreating players...\n\n";
	players = new Player*[nPlayer];

	// Create the Statistics Observers, that will monitor individually each player
	StatisticsObserver = new StatisticsViewer*[nPlayer];
	bottomBar = new sf::RenderTexture[nPlayer];

	for (int i = 0; i < nPlayer; i++)
	{
		if (i == 0)
		{
			players[i] = new AIPlayer("AI", 0);
			players[i]->setName("AI");
			std::cout << "Creating AI PLayer..." << std::endl;
			AIPlayer *AI = (AIPlayer*)players[0];
			AI->setStrategy(new Defensive());
		}
		else
		{
			players[i] = new Player(i);
			std::cout << "Please enter your name, player " << i << ":" << std::endl;
			std::string name;
			std::cin >> name;
			players[i]->setName(name);
			players[i]->setColor(c[i]);
		}

		bottomBar[i].create(window.getSize().x/6, 100); // Creates a RenderTexture for the player in the bottomBar
		StatisticsObserver[i] = new StatisticsViewer(players[i], bottomBar[i],
				window); // Creates the Observer for this player, for displaying in the bottom bar

		players[i]->setNArmy(assignArmy());
		players[i]->setNReinforcement(assignArmy());
		totArmy += assignArmy() * nPlayer;

		std::cout << players[i]->getName()
					<< " is now the player of color " << players[i]->getColor() << " and will receive an army of "
					<< assignArmy() << " infantries.\n\n";

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

void Game::placeArmy()
{
	// Notify Status
	map->getStatsNotifier()->setStatusMessage("Distributing armies");

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
			std::cout << players[ct]->getName() << ", "
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

	updateTurnStatus();

}

void Game::pickRandom()
{
	// Notify Status
	map->getStatsNotifier()->setStatusMessage("Pick Random");

	std::cout << "Pick Random.\n\n";

	ct = first;
	std::vector<Territory*> vt = map->getTerritories();

	updateTurnStatus();

	srand(time(NULL));

	int numTerri = vt.size();

	while (numTerri > 0)
	{
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

		updateTurnStatus();
	}
}

void Game::turnOrder()
{
	/* The player with the highest score is the one that plays first.
	To apply the clockwise principle, the next player is the next one
	in the circular array.*/

	srand(time(NULL));

	int max = 0;
	int playerInd = 0;

	for (int i = 0; i < nPlayer; i++)
	{
		std::cout << players[i]->getName() << " rolls the dice...\n";
		int dice = rollDice();
		std::cout << dice << std::endl;
		if (dice > max)
		{
			max = dice;
			playerInd = i;
		}
	}

	//Player *temp = new Player[nPlayer];

	std::cout << players[playerInd]->getName() << " plays first." << std::endl;
	ct = playerInd;
	first = playerInd;

	ct = (first) % nPlayer;

	updateTurnStatus();

}

///////// Main Play ////////

void Game::mainPlay()
{
	std::cout << "Let's start the game...\n\n";

	// Notify Status
	map->getStatsNotifier()->setStatusMessage("Let's Start the Game!");

	int test = 5;
	ct = first;

	updateTurnStatus();

	//Round-Robin
	while (!endGame && test > 0)
	{
		players[ct]->setHasNewTerritory(false); // Reset to false

		std::cout << players[ct]->getName() << "'s turn!\n\n";

		// Reinforcement
		reinforcement();

		// Battle
		battle();

		// Fortification
		fortification();

		// Update
		ct = (ct + 1) % nPlayer;
		updateTurnStatus();
		test--;

	}
}

////////  Reinforcement  //////// 
void Game::reinforcement()
{
  mPhase = new Reinforcement(cardReinforcement);
  mPhase->run(players[ct]);
  cardReinforcement = ((Reinforcement*)mPhase)->updateCardBonus();
}


////////  Battle  ////////
void Game::battle()
{
  mPhase = new Battle();
  mPhase->run(players[ct]);

  if (monitorWins())
  {
	  std::cout << players[ct]->getName() << " is the winner!" << std::endl;
	  players[ct]->setHasNewTerritory(false);	// Ignore Fortification
	  endGame = true; // Exit MainPlay
	  return; // Exit Battle
  }
  else
  {
	  std::cout << "No winner yet." << std::endl;
  }

}

////////  Fortification  ////////
void Game::fortification()
{
	mPhase = new Fortification();
	mPhase->run(players[ct]);
}

////////  Other  ////////
int Game::rollDice()
{
	int val = rand() % 5 + 1;
	return val;
}

void Game::updateTurnStatus()
{
	for (int i = 0; i < nPlayer; i++)
	{
		if (i == ct)
			players[i]->setTurnState(true);
		else
			players[i]->setTurnState(false);
	}
}



bool Game::monitorWins()
{
	bool winner = true;
	std::vector<Territory*> territory = map->getTerritories();
	for (int i = 0; i < territory.size(); i++)
	{
		if (territory[i]->getPlayerOwner() == players[ct])
		{
			winner = false;
			break;
		}
	}
	return winner;
}

void Game::monitorDefeat()
{
	int num = nPlayer;

	for (int i = 0; i < nPlayer; i++)
	{
		if (players[i]->getEliminated())
		{
			players[i] = NULL;
			num--;
		}
	}

	Player **temp = new Player*[num];

	for (int j = 0; j < nPlayer; j++)
	{
		int index = 0;
		if (players[j] != NULL)
		{
			temp[index] = players[j];
			if (players[j]->getTurnState() == true)
				ct = index;
			delete [] players[j];
		}
	}

	setNPlayer(num);
}

void Game::setNPlayer(int num)
{
	nPlayer = num;
}

void Game::setPlayers(Player** aPlayers)
{
	players = aPlayers;
}

