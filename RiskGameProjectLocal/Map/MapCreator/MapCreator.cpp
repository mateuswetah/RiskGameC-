/*
 * MapCreator.cpp
 *
 *  Created on: Apr 13, 2015
 *      Author: orpheus
 */

#include "MapCreator.h"

MapCreator::MapCreator()
{
	this->newMap = Map::getMapInstance();
}

MapCreator::~MapCreator()
{
	// TODO Auto-generated destructor stub
}

std::string MapCreator::getFileName()
{
	return fileName;
}

Map* MapCreator::getMap()
{
	return this->newMap;
}

void MapCreator::createAMap()
{

	std::cout << ">>#>>#>>#>>#>-- RISK! - MAP CREATOR --<#<<#<<#<<#<<"	<< std::endl;
	std::cout << "--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--"	<< std::endl;
	std::cout << "                                   			    "	<< std::endl;

	std::string pictureFileName;
	std::cout << "Type the name of the image file for the map background: (Ex.: 'world.bmp')" << std::endl;
	std::cin.clear();
	std::cin.get();
	std::getline(std::cin, pictureFileName);
	this->newMap->setFileName(pictureFileName);

	mapCreatorGraphics();
	mapCreatorMenu();

	return;

}

void MapCreator::mapCreatorGraphics()
{
	// Loads the Background Image
	sf::Image mapBackground;
	mapBackground.loadFromFile(newMap->getFileName());

	// Creates the main render window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 6;

	if (mapBackground.getSize().x >= 900)
		window.create(
		sf::VideoMode(mapBackground.getSize().x,
		mapBackground.getSize().y + 100), "RISK! - MAP CREATOR ",
		sf::Style::Titlebar, settings);
	else
		window.create(
		sf::VideoMode(
		mapBackground.getSize().x
		+ (900 - mapBackground.getSize().x),
		mapBackground.getSize().y + 100), "RISK! - MAP CREATOR",
		sf::Style::Titlebar, settings);

	window.clear(sf::Color(45, 45, 45));

	// Attach Map and Player Viewers:
	MapObserver = new MapViewer(newMap, window); // Responsible for displaying the Map itself, continent colors and neighborhoods

	newMap->notify();

	window.display();
}

void MapCreator::mapCreatorMenu()
{

	bool exit = false;

	while (!exit)
	{
		window.display();

		int option = 0;

		while (option < 1 || option > 7)
		{
			std::cout << "---------------------------------------" 		<< std::endl;
			std::cout << "Please type the number of your option:" 		<< std::endl;
			std::cout << " 1 - Create Continents					"	<< std::endl;
			std::cout << " 2 - Create Territories					"	<< std::endl;
			std::cout << " 3 - Edit Territories Info				"	<< std::endl;
			std::cout << " 4 - Remove Continents					"	<< std::endl;
			std::cout << " 5 - Remove Territories					"	<< std::endl;
			std::cout << " 6 - Print map Continents and Territories "	<< std::endl;
			std::cout << " 7 - Exit and Save .map					"	<< std::endl;

			std::cin >> option;
		}

		switch (option)
		{
		case 1:
			createContinents();
			break;
		case 2:
			createTerritories();
			break;
		case 3:
			editTerritories();
			break;
		case 4:
			removeContinents();
			break;
		case 5:
			removeTerritories();
			break;

		case 6:
			std::cout << "These are the current Continents and Territories of this map: " << std::endl;
			newMap->printMyContinentsAndTerritory();
			break;

		case 7:
			std::cout << "Map Created! Give a name for your .map file: (Ex.: 'World.map')" 	<< std::endl;
			std::cin.clear();
			std::cin.get();
			std::getline(std::cin, this->fileName);

			MapIO* mio = new MapIO();
			mio->loadMapInfo(this->fileName);

			exit = true;

			window.close();

			break;

		}
	}

	return;
}

void MapCreator::territoryEditorMenu(std::string territory)
{
	bool exit = false;
	Territory* tmp = newMap->getTerritoryByName(territory);

	while (!exit)
	{
		window.display();

		int option = 0;

		while (option < 1 || option > 6)
		{
			std::cout << "-------------------------------------------"	<< std::endl;
			std::cout << "Editing the territory " << territory << ":"	<< std::endl;
			std::cout << "Please type the number of your option:" 		<< std::endl;
			std::cout << " 1 - Set coordinates X and Y on the map	"	<< std::endl;
			std::cout << " 2 - Set a list of neighbors				"	<< std::endl;
			std::cout << " 3 - Remove a neighbor					"	<< std::endl;
			std::cout << " 4 - View informations of the Territory	"	<< std::endl;
			std::cout << " 5 - Change the continent owner			"	<< std::endl;
			std::cout << " 6 - Return to the Map Creator Menu		"	<< std::endl;

			std::cin >> option;
		}

		switch (option)
		{
		case 1:
		{
			int posX, posY;

//			if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
//			{
//				posX = sf::Mouse::getPosition(window).x;
//
//				std::cout << "Position X of the Territory " << territory << " on the map: ";
//				posY = sf::Mouse::getPosition(window).y;
//
//				std::cout << "Position Y of the Territory " << territory << " on the map: ";
//
//				window.display();
//			}

			std::cout << "Position X of the Territory " << territory << " on the map: ";
			std::cin.clear();
			std::cin >> posX;
			tmp->setPosX(posX);

			std::cout << "Position Y of the Territory " << territory << " on the map: ";
			std::cin.clear();
			std::cin >> posY;
			tmp->setPosY(posY);

		}
		break;

		case 2:
		{
			int nNeighbors;
			std::string oneNeighbor;

			std::cout << "How many neighbors do you want to add to " << territory << " now?" << std::endl;
			std::cin >> nNeighbors;

			std::cin.ignore();

			for (int i = 0; i < nNeighbors; i++)
			{
				std::cout << "Name of the neighbor " << i + 1 << ": " << std::endl;
				std::getline(std::cin, oneNeighbor);

				while (!newMap->checkIfTerritoryExists(oneNeighbor))
				{
					std::cerr << "There is no Territory named " << oneNeighbor << " in the map! "	<< std::endl;
					std::cout << "Please type the name of an existing one:		   " 	<< std::endl;
					std::cin.ignore();
					std::getline(std::cin, oneNeighbor);
				}

				tmp->addNewNeighbor(newMap->getTerritoryByName(oneNeighbor));

			}

			std::cout << "The actual list of Neighbors of " << territory << " is: " << std::endl;
			tmp->printMyNeighbors();
		}
		break;

		case 3:
		{
			std::cout << "The actual list of Neighbors of " << territory << " is: " << std::endl;
			tmp->printMyNeighbors();

			std::string aNeighbor;
			std::cout << "Which neighbor do you want to remove from this list?" << std::endl;
			std::cin.clear();
			std::cin.get();
			std::getline(std::cin, aNeighbor);
			tmp->removeNeighbor(newMap->getTerritoryByName(aNeighbor));

			std::cout << "Updated list of Neighbors of " << territory << ": " << std::endl;
			tmp->printMyNeighbors();

		}
		break;

		case 4:
			std::cout << "You are editing " << territory << std::endl;
			std::cout << "Which is in the coordinates (" << tmp->getPosX() << ", " << tmp->getPosY() << ")" << std::endl;
			std::cout << "These are it's current Neighbors" << std::endl;
			tmp->printMyNeighbors();

		break;

		case 5:
		{
			std::string newContinentName;

			std::cout << "Name of the new Continent that " << territory << " will belong to: ";
			std::cin.clear();
			std::cin.get();
			std::getline(std::cin, newContinentName);

			while (!newMap->checkIfContinentExists(newContinentName))
			{
				std::cerr << "There is no Continent with this name in the map! 		  "	<< std::endl;
				std::cout << "Please type a name of an existing one:				  " << std::endl;
				std::cin.clear();
				std::cin.get();
				std::getline(std::cin, newContinentName);
			}

			// Look for which continent territory currently belongs too
			for (int i = 0; i < newMap->getContinents().size(); i++)
			{
				if (newMap->getContinents().at(i)->getTerritoryByName(territory)->getName() != "Limbo")
					newMap->getContinents().at(i)->removeTerritory(newMap->getContinents().at(i)->getTerritoryByName(territory));

			}

			newMap->getContinentByName(newContinentName)->addNewTerritory(tmp);

		}
		break;

		case 6:
			exit = true;
		break;

		}

	}

}

void MapCreator::createContinents()
{
	int nContinents;

	std::cout << "How many new Continents you want to add to " << newMap->getFileName() << "?" << std::endl;
	std::cin >> nContinents;

	std::cin.ignore();

	for (int i = 0; i < nContinents; i++)
	{
		std::string continentName;

		std::cout << " Name for Continent " << i + 1 << ": ";

		std::getline(std::cin, continentName);

		while (newMap->checkIfContinentExists(continentName))
		{
			std::cerr << "There is already a continent named " << continentName << " in the map! "	<< std::endl;
			std::cout << "Please type a new name:								  ";
			std::getline(std::cin, continentName);
		}

		Continent* newContinent = new Continent();
		newContinent->setName(continentName);
		newMap->addNewContinent(newContinent);

		std::cout << std::endl;
	}

	MapObserver = new MapViewer(newMap, window);

	// Coloring the continents (max 8 colors)
	std::string c[] =
		{ "blue", "red", "green", "black", "gray", "cyan", "magenta", "yellow" };

	for (unsigned int i = 0; i < newMap->getContinents().size(); i++)
	{
		newMap->getContinents().at(i)->setColor(c[i % 8]);
	}


}

void MapCreator::createTerritories()
{
	int nTerritories;

	std::cout << "How many new Territories you want to add to " << newMap->getFileName() << "?" << std::endl;
	std::cin >> nTerritories;

	std::cin.ignore();

	for (int i = 0; i < nTerritories; i++)
	{
		std::string territoryName, continentName;

		std::cout << " Name for Territory " << i + 1 << ": ";
		std::getline(std::cin, territoryName);

		while (newMap->checkIfTerritoryExists(territoryName))
		{
			std::cerr << "There is already a Territory named " << territoryName << " in the map! "	<< std::endl;
			std::cout << "Please type a new name:								  " << std::endl;
			std::getline(std::cin, territoryName);
		}

		std::cout << "Continent which " << territoryName << " will belongs to: ";
		std::getline(std::cin, continentName);

		while (!newMap->checkIfContinentExists(continentName))
		{
			std::cerr << "There is no continent named " << continentName << " in the map! "	<< std::endl;
			std::cout << "Please type a new name:						   "	<< std::endl;
			std::getline(std::cin, continentName);
		}

		Territory* newTerritory = new Territory();
		newTerritory->setName(territoryName);
		newMap->getContinentByName(continentName)->addNewTerritory(newTerritory);

		std::cout << std::endl;
	}

	MapObserver = new MapViewer(newMap, window);

}

void MapCreator::editTerritories()
{
	std::string territoryName;

	std::cout << "Which territory of " << newMap->getFileName() << " do you want to edit?" << std::endl;
	std::cin.ignore();
	std::getline(std::cin, territoryName);

	while (!newMap->checkIfTerritoryExists(territoryName))
	{
		std::cerr << "There is no territory with this name in the map! "	<< std::endl;
		std::cout << "Please type a another name:						"   << std::endl;
		std::cin.ignore();
		std::getline(std::cin, territoryName);
	}

	territoryEditorMenu(territoryName);
}

void MapCreator::removeContinents()
{
	std::string continentName;

	std::cout << "Name of the continent to be removed from the map: (remember, this will remove it's territories too) " ;
	std::cin.clear();
	std::cin.get();
	std::getline(std::cin, continentName);

	while (!newMap->checkIfContinentExists(continentName))
	{
		std::cerr << "There is no continent named " << continentName << " in the map! " << std::endl;
		std::cout << "Please type a new name:								" << std::endl;
		std::cin.clear();
		std::cin.get();
		std::getline(std::cin, continentName);
	}

	newMap->removeContinent(newMap->getContinentByName(continentName));

	MapObserver = new MapViewer(newMap, window);

}

void MapCreator::removeTerritories()
{
	std::string territoryName;

	std::cout << "Name of the Territory to be removed from the map: " ;
	std::cin.clear();
	std::cin.get();
	std::getline(std::cin, territoryName);

	while (!newMap->checkIfTerritoryExists(territoryName))
	{
		std::cerr << "There is no territory named" << territoryName << " in the map!" << std::endl;
		std::cout << "Please type a new name:	" << std::endl;
		std::cin.clear();
		std::cin.get();
		std::getline(std::cin, territoryName);
	}

	// Look for which continent territory currently belongs too
	for (unsigned int i = 0; i < newMap->getContinents().size(); i++)
	{
		if (newMap->getContinents().at(i)->getTerritoryByName(territoryName)->getName() != "Limbo")
			newMap->getContinents().at(i)->removeTerritory(newMap->getContinents().at(i)->getTerritoryByName(territoryName));

	}

	MapObserver = new MapViewer(newMap, window);

}
