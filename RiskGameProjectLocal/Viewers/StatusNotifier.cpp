/*
 * StatusNotifier.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: orpheus
 */

#include "StatusNotifier.h"

StatusNotifier::StatusNotifier(sf::RenderWindow& aWindow) : window (&aWindow)
{
	statusBar.create(window->getSize().x, 24);
}

StatusNotifier::~StatusNotifier()
{
}

void StatusNotifier::update()
{
	statusBar.clear();

	notifyStatus(getStatusMessage());
	statusBar.display();

	sf::Sprite statusSprite(statusBar.getTexture());
	statusSprite.setPosition(0,0);

	window->draw(statusSprite);
	window->display();
}

void StatusNotifier::setStatusMessage(std::string statusMessage)
{
	this->statusMessage = statusMessage;
	this->update();

}

std::string StatusNotifier::getStatusMessage()
{
	return this->statusMessage;
}

void StatusNotifier::notifyStatus(std::string message)
{

	// Draw the Bar
	sf::RectangleShape bar(sf::Vector2f(window->getSize().x, 24));
	bar.setFillColor(sf::Color(45,45,45, 210));
	bar.setPosition(sf::Vector2f(0, 0));

	statusBar.draw(bar);

	// SFML font settings
	sf::Font font;
	if (!font.loadFromFile("FreeSans.ttf"))
	{
		std::cerr << "Font could not be loaded!" << std::endl;
	}
	else
	{
		sf::Text messageText;

		// setting the text configurations for amount of Territories
		messageText.setString(message);
		messageText.setPosition(8, 1);
		messageText.setCharacterSize(15);		// set size in pixels
		messageText.setFont(font); 				// select the font
		messageText.setColor(sf::Color::White); // set the color
		messageText.setStyle(sf::Text::Bold);   // set the text style

		statusBar.draw(messageText);

	}

}
