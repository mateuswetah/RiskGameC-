/*
 * StatusNotifier.h
 *
 *  Created on: Apr 14, 2015
 *      Author: orpheus
 */

#ifndef DRIVER_STATUSNOTIFIER_H_
#define DRIVER_STATUSNOTIFIER_H_

#include "SFML/Graphics.hpp"
#include <sstream>
#include <iostream>


class StatusNotifier
{
public:
	StatusNotifier( sf::RenderWindow& aWindow);
	virtual ~StatusNotifier();

	// Status Message
	void setStatusMessage(std::string statusMessage);
	std::string getStatusMessage();

	void update();

	void notifyStatus(std::string message);

private:
	sf::RenderWindow* window;
	sf::RenderTexture statusBar;
	std::string statusMessage;
};

#endif /* DRIVER_STATUSNOTIFIER_H_ */
