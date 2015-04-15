/*
 * PlayerViewer.cpp
 *
 *  Created on: Mar 7, 2015
 *      Author: mateus
 */

#include "PlayerViewer.h"

PlayerViewer::PlayerViewer(Map* aMap, sf::RenderWindow& aWindow) : observedMap (aMap), window (&aWindow)
{
	(this->observedMap)->attach(this);

	for(int i = 0; i < this->observedMap->getContinents().size();i++)
	{
	    this->observedMap->getContinents()[i]->attach(this);
	}

	for(int i = 0; i < this->observedMap->getTerritories().size();i++)
	{
	    this->observedMap->getTerritories()[i]->attach(this);
	}

}

PlayerViewer::~PlayerViewer()
{
	(this->observedMap)->detach(this);
}

void PlayerViewer::update()
{
	//loadMapImage(this->observedMap->getFileName());
	drawAllPlayersInfo();
	window->display();

}


void PlayerViewer::drawOnePlayerInfo(int xPos, int yPos, std::string playerColor, int amountOfArmies)
{

	int circleSize = 12;
	xPos -= circleSize/2;   // Adjusting the reference
	yPos -= circleSize;		// Adjusting the reference

	sf::CircleShape playerInTerritory(circleSize);

	// Color of the player
	sf::Color color;

	if (playerColor == "blue")
		color = sf::Color(0, 0, 255);
	else if (playerColor == "red")
		color = sf::Color(255, 0, 0);
	else if (playerColor == "green")
		color = sf::Color(0, 255, 0);
	else if (playerColor == "cyan")
		color = sf::Color(0, 250, 250);
	else if (playerColor == "magenta")
		color = sf::Color(255, 0, 255);
	else if (playerColor == "yellow")
		color = sf::Color(255, 245, 0);

	playerInTerritory.setFillColor(color);
	playerInTerritory.setPosition(xPos, yPos);

	// Draw the Player circle
	window->draw(playerInTerritory);

	// Number of Armies
	sf::Font font;
	if (!font.loadFromFile("FreeSans.ttf"))
	{
		std::cerr << "Font could not be loaded!" << std::endl;
	}
	else
	{
		sf::Text text;

		// set the string to display
		std::stringstream strStream;
		std::string str;
		if (amountOfArmies < 10)
			strStream << "0" << amountOfArmies ;
		else
			strStream << amountOfArmies;
		str = strStream.str();

		// setting the text configurations
		text.setString(str);
		text.setPosition(xPos + circleSize/2 - 3, yPos + circleSize/4); // put in center of the circle
		text.setCharacterSize(14);		 		// set size in pixels
		text.setFont(font); 			 		// select the font
		text.setColor(sf::Color::White); 		// set the color
		text.setStyle(sf::Text::Bold);   		// set the text style

		// Draw the Amount of Armies
		window->draw(text);
	}

}

void PlayerViewer::drawAllPlayersInfo()
{
	int nTerritories = this->observedMap->getTerritories().size();

	for(int i = 0; i < nTerritories; i++)
		drawOnePlayerInfo(	this->observedMap->getTerritories().at(i)->getPosX(),
					  this->observedMap->getTerritories().at(i)->getPosY(),
					  this->observedMap->getTerritories().at(i)->getPlayerOwner()->getColor(),
					  this->observedMap->getTerritories().at(i)->getAmountOfArmies()
				   );

}




