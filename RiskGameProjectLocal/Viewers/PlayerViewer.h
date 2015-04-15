/*
 * PlayerViewer.h
 *
 *  Created on: Mar 7, 2015
 *      Author: mateus
 */

#ifndef PLAYERVIEWER_H_
#define PLAYERVIEWER_H_

#include "../ObservablePattern/Observer.h"
#include "SFML/Graphics.hpp"
#include "../Map/Map.h"
#include <iostream>
#include <vector>

class PlayerViewer : public Observer
{

	public:
		PlayerViewer(Map* aMap, sf::RenderWindow &aWindow);
		~PlayerViewer();
		void update();
		void drawOnePlayerInfo(int xPos, int yPos, std::string playerColor, int amountOfArmies);
		void drawAllPlayersInfo();

	private:
		Map* observedMap;
		sf::RenderWindow *window;

};

#endif /* PLAYERVIEWER_H_ */
