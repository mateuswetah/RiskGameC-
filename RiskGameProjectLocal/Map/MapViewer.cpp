/*
 * MapViewer.cpp
 *
 *  Created on: Mar 2, 2015
 *      Author: mateus
 */

#include "MapViewer.h"

MapViewer::MapViewer(Map* aMap, sf::RenderWindow &aWindow) : observedMap (aMap), window (&aWindow)
{
	observedMap->attach(this);

	for(unsigned int i = 0; i < this->observedMap->getContinents().size();i++)
	{
	    this->observedMap->getContinents()[i]->attach(this);
	}

	for(unsigned int i = 0; i < this->observedMap->getTerritories().size();i++)
	{
	    this->observedMap->getTerritories()[i]->attach(this);
	}

	loaded = false;

}

MapViewer::~MapViewer()
{
	(this->observedMap)->detach(this);
}

void MapViewer::update()
{

	loadMapImage(this->observedMap->getFileName());
	drawAllNeighborsLines();
	drawContinentInfoBar();
	drawAllContinentOwners();
	//window->display();

}

void MapViewer::drawNeighborLine(int x1, int y1, int x2, int y2, sf::Color color)
{
	 sf::VertexArray lines(sf::Lines, 2);

	 lines[0].position = sf::Vector2f(x1, y1);
	 lines[0].color = color;
	 lines[1].position = sf::Vector2f(x2, y2);
	 lines[1].color = color;

	 window->draw(lines);
}

void MapViewer::drawAllNeighborsLines()
{
	int nTerritories = observedMap->getTerritories().size();

	for (int i = 0; i < nTerritories; i++)
	{
		observedMap->getTerritories().at(i);

		int nNeighbors = observedMap->getTerritories().at(i)->getNeighbors().size();
		int tx = observedMap->getTerritories().at(i)->getPosX();
		int ty = observedMap->getTerritories().at(i)->getPosY();

		for(int j = 0; j < nNeighbors; j++)
		{
			int nx = observedMap->getTerritories().at(i)->getNeighbors().at(j)->getPosX();
			int ny = observedMap->getTerritories().at(i)->getNeighbors().at(j)->getPosY();

			if (tx != 0 && ty != 0 && nx != 0 && ny != 0)
				this->drawNeighborLine(tx, ty, nx, ny, sf::Color(255, 0, 0));
		}
	}
}

void MapViewer::drawContinentOwner(int xPos, int yPos, std::string continentColor)
{
	int circleSize = 21;
	xPos -= circleSize/2 + 5; // Adjusting the reference
	yPos -= circleSize;		// Adjusting the reference

	sf::CircleShape continentOwnerInTerritory(circleSize, 6);

	// Color of the Continent
	sf::Color color = convertContinentColor(continentColor);

	continentOwnerInTerritory.setFillColor(color);
	continentOwnerInTerritory.setPosition(xPos, yPos);

	// Draw the Continent hexagon
	window->draw(continentOwnerInTerritory);

}

void MapViewer::drawAllContinentOwners()
{
	int nContinents = this->observedMap->getContinents().size();

	for(int i = 0; i < nContinents; i++)
	{
		int nTerritories = this->observedMap->getContinents().at(i)->getTerritories().size();

		for (int j = 0; j < nTerritories; j++)
			drawContinentOwner( this->observedMap->getContinents().at(i)->getTerritories().at(j)->getPosX(),
								this->observedMap->getContinents().at(i)->getTerritories().at(j)->getPosY(),
								this->observedMap->getContinents().at(i)->getColor()
							  );
	}
}

void MapViewer::drawContinentInfoBar()
{

	// Draw the Bar
	sf::RectangleShape territoryBar(sf::Vector2f(window->getSize().x, 30));
	territoryBar.setFillColor(sf::Color(45,45,45, 210));
	territoryBar.setPosition(sf::Vector2f(0, window->getSize().y - 130));

	window->draw(territoryBar);

	// Draw the continent information
	int nContinents = this->observedMap->getContinents().size();

	for(int i = 0; i < nContinents; i++)
	{
		drawContinentLabel(this->observedMap->getContinents().at(i)->getName(),
							this->observedMap->getContinents().at(i)->getColor(),
							this->observedMap->getContinents().at(i)->getTerritories().size(),
							i);
	}


}

void MapViewer::drawContinentLabel(std::string continentName,
									std::string continentColor,
									int nTerritories,
									int posX)
{
	int refPosX = (window->getSize().x/observedMap->getContinents().size())*posX + 8 ;
	int refPosY = window->getSize().y - 124;

	sf::Font font;
	if (!font.loadFromFile("FreeSans.ttf"))
	{
		std::cerr << "Font could not be loaded!" << std::endl;
	}
	else
	{
		sf::Text text;

		// Elipsing
		if (continentName.size() > (8/observedMap->getContinents().size()) + 8)
		{
			continentName = continentName.substr(0, 8/observedMap->getContinents().size() + 8);
			continentName += "...";
		}

		std::stringstream ssInfo;
		ssInfo << continentName << "(" << nTerritories << ")";

		// setting the text configurations
		text.setString(ssInfo.str());
		text.setPosition(refPosX, refPosY ); // put in center of the circle
		text.setCharacterSize(16);		 		// set size in pixels
		text.setFont(font); 			 		// select the font
		text.setColor(convertContinentColor(continentColor)); // set the color
		text.setStyle(sf::Text::Bold);   		// set the text style

		// Draw the Amount of Armies
		window->draw(text);
	}
}

sf::Color MapViewer::convertContinentColor(std::string continentColor)
{
	sf::Color color;

	if (continentColor == "blue")
		color = sf::Color(0, 0, 150, 185);
	else if (continentColor == "red")
		color = sf::Color(150, 0, 0, 185);
	else if (continentColor == "green")
		color = sf::Color(0, 150, 0, 185);
	else if (continentColor == "black")
		color = sf::Color(0, 0, 0, 187);
	else if (continentColor == "cyan")
		color = sf::Color(0, 150, 150, 185);
	else if (continentColor == "magenta")
		color = sf::Color(150, 0, 150, 185);
	else if (continentColor == "yellow")
		color = sf::Color(150, 150, 0, 185);
	else if (continentColor == "gray")
			color = sf::Color(60, 60, 60, 180);

	return color;
}

bool MapViewer::loadMapImage(std::string nameOfImage)
{

  if(!loaded){
	if (!mapBackground.loadFromFile(nameOfImage))
	{
		std::cerr << "Error trying to load the " << nameOfImage << " picture!" << std::endl;
		return false;
	}
	else
	{
		//std::cout << "Background map picture loaded successfully!" << std::endl;

		sf::Vector2u dimensions = mapBackground.getSize();

	  	if (dimensions.x >= 900)
	  		this->window->setSize(sf::Vector2u(dimensions.x, dimensions.y + 100));
	  	else
	  		this->window->setSize(sf::Vector2u(dimensions.x + (900 - dimensions.x), dimensions.y + 100));

		mapTexture.loadFromImage(mapBackground);
		spriteBackground.setTexture(mapTexture);

		this->window->draw(spriteBackground);

		loaded = true;

		return true;
	}
  }
  else
  {

      this->window->draw(spriteBackground);
      return true;
  }

}


