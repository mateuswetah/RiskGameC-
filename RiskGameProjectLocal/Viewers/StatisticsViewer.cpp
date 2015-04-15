/*
 * StatistcsViewer.cpp
 *
 *  Created on: Apr 7, 2015
 *      Author: orpheus
 */

#include "StatisticsViewer.h"

StatisticsViewer::StatisticsViewer()
{
}

StatisticsViewer::StatisticsViewer(Player* aPlayer,
		sf::RenderTexture& aBottomBar, sf::RenderWindow& aWindow) :
		observedPlayer(aPlayer), bottomBar(&aBottomBar), window(&aWindow)
{

	this->refPosX = 0;
	this->refPosY = bottomBar->getSize().y - 100;
	this->color = getSFMLColor(this->observedPlayer->getColor());

	(this->observedPlayer)->attach(this);

}

StatisticsViewer::~StatisticsViewer()
{
	(this->observedPlayer)->detach(this);
}

void StatisticsViewer::update()
{
	// Update Player Stats
	this->observedPlayer->defineNTerritory();
	this->observedPlayer->defineNCard();
	this->observedPlayer->defineNArmy();
	this->observedPlayer->defineNReinforcement();

	// Update viewer
	bottomBar->clear(sf::Color(45, 45, 45)); /// Background Color
	drawPlayerBlock();
	drawPlayerStatistics();
	bottomBar->display();
	sf::Sprite bottomSprite(bottomBar->getTexture());
	bottomSprite.setPosition(
			(window->getSize().x / 6) * (this->observedPlayer->getNumber()), // Distributes the players info in the available space
			window->getSize().y - 100 // Put the statistics in the black bottom bar;
					);
	window->draw(bottomSprite);

}

sf::Color StatisticsViewer::getSFMLColor(std::string sPlayerColor)
{

	// Color of the player
	sf::Color color;

	if (sPlayerColor == "blue")
		color = sf::Color(0, 0, 255);
	else if (sPlayerColor == "red")
		color = sf::Color(255, 0, 0);
	else if (sPlayerColor == "green")
		color = sf::Color(0, 255, 0);
	else if (sPlayerColor == "cyan")
		color = sf::Color(0, 255, 255);
	else if (sPlayerColor == "magenta")
		color = sf::Color(255, 0, 255);
	else if (sPlayerColor == "yellow")
		color = sf::Color(255, 255, 0);

	return color;
}

void StatisticsViewer::drawPlayerBlock()
{
	// Draw Borders for the individual player
	sf::VertexArray lines(sf::Lines, 2);

	lines[0].position = sf::Vector2f(refPosX + bottomBar->getSize().x,
			(bottomBar->getSize().y - 100));
	lines[0].color = color;
	lines[1].position = sf::Vector2f(refPosX + bottomBar->getSize().x,
			(bottomBar->getSize().y));
	lines[1].color = color;

	bottomBar->draw(lines);

// Not implemented as the method getTurnState is not fully implemented.

	if (this->observedPlayer->getTurnState())
	{
		// Draw the PLAY box for the player that is as the current turn
		sf::RectangleShape playRect(sf::Vector2f(28, 100));
		playRect.setFillColor(color);
		playRect.setPosition(refPosX + (bottomBar->getSize().x) - 28, refPosY);

		bottomBar->draw(playRect);

		// SFML font settings
		sf::Font font;
		if (!font.loadFromFile("FreeSans.ttf"))
		{
			std::cerr << "Font could not be loaded!" << std::endl;
		}
		else
		{
			sf::Text playText;
			std::string playString = "T\nU\nR\nN";

			// setting the text configurations for amount of Territories
			playText.setString(playString);
			playText.setPosition(refPosX + (bottomBar->getSize().x) - 20,
					refPosY + 7);
			playText.setCharacterSize(18);		// set size in pixels
			playText.setFont(font); 			// select the font
			playText.setColor(sf::Color::White); 			// set the color
			playText.setStyle(sf::Text::Bold);  // set the text style

			bottomBar->draw(playText);
		}
	}

}

void StatisticsViewer::drawPlayerStatistics()
{

	// Paragraph formating
	int topPadding = 12;
	int rightPadding = 12;
	int lineSpacing = 4;
	int fontSize = 16;

	// SFML font settings
	sf::Font font;
	if (!font.loadFromFile("FreeSans.ttf"))
	{
		std::cerr << "Font could not be loaded!" << std::endl;
	}
	else
	{
		sf::Text nameOfPlayer, nTerritories, nArmies, nCards;

		// set the strings to display
		std::string sNameOfPlayer = this->observedPlayer->getName();

		std::stringstream sStreamTerritories;
		std::string sTerritories;
		sStreamTerritories << "Territories: "
				<< this->observedPlayer->getNTerritory();
		sTerritories = sStreamTerritories.str();

		std::stringstream sStreamArmies;
		std::string sArmies;
		sStreamArmies << "Armies: "
				<< this->observedPlayer->getNReinforcement();
		sArmies = sStreamArmies.str();

		std::stringstream sStreamCards;
		std::string sCards;
		sStreamCards << "Cards: " << this->observedPlayer->getNCard();
		sCards = sStreamCards.str();

		// setting the text configurations for User Name
		nameOfPlayer.setString(sNameOfPlayer);
		nameOfPlayer.setPosition(refPosX + rightPadding - 3,
				refPosY + topPadding - 6);
		nameOfPlayer.setCharacterSize(fontSize + 4);	// set size in pixels
		nameOfPlayer.setFont(font); 			 		// select the font
		nameOfPlayer.setColor(color); 					// set the color
		nameOfPlayer.setStyle(sf::Text::Regular);   	// set the text style

		// setting the text configurations for amount of Territories
		nTerritories.setString(sTerritories);
		nTerritories.setPosition(refPosX + rightPadding,
				refPosY + topPadding + (lineSpacing + fontSize) * 1);
		nTerritories.setCharacterSize(fontSize);		// set size in pixels
		nTerritories.setFont(font); 			 		// select the font
		nTerritories.setColor(sf::Color::White); 				// set the color
		nTerritories.setStyle(sf::Text::Regular);   	// set the text style

		// setting the text configurations for amount of Armies
		nArmies.setString(sArmies);
		nArmies.setPosition(refPosX + rightPadding,
				refPosY + topPadding + (lineSpacing + fontSize) * 2);
		nArmies.setCharacterSize(fontSize);			// set size in pixels
		nArmies.setFont(font); 			 			// select the font
		nArmies.setColor(sf::Color::White); 					// set the color
		nArmies.setStyle(sf::Text::Regular);   		// set the text style

		// setting the text configurations for amount of Cards
		nCards.setString(sCards);
		nCards.setPosition(refPosX + rightPadding,
				refPosY + topPadding + (lineSpacing + fontSize) * 3);
		nCards.setCharacterSize(fontSize);			// set size in pixels
		nCards.setFont(font); 			 			// select the font
		nCards.setColor(sf::Color::White); 					// set the color
		nCards.setStyle(sf::Text::Regular);   		// set the text style

		// Draw the informations
		bottomBar->draw(nameOfPlayer);
		bottomBar->draw(nTerritories);
		bottomBar->draw(nArmies);
		bottomBar->draw(nCards);

	}

}

