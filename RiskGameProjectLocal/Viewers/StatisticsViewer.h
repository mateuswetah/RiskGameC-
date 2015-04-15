/*
 * StatistcsViewer.h
 *
 *  Created on: Apr 7, 2015
 *      Author: orpheus
 */

#ifndef PLAYER_STATISTICSVIEWER_H_
#define PLAYER_STATISTICSVIEWER_H_

#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>
#include "../ObservablePattern/Observer.h"
#include "../Player/Player.h"
#include <sstream>
#include "../Map/Map.h"

class StatisticsViewer : public Observer
{

	public:

		StatisticsViewer();
		StatisticsViewer(Player* aPlayer, sf::RenderTexture& aBottomBar, sf::RenderWindow& aWindow);
		virtual ~StatisticsViewer();

		void update();

		sf::Color getSFMLColor(std::string sPlayerColor);

		void drawPlayerBlock();
		void drawPlayerStatistics();

	private:
		Player* observedPlayer;
		sf::RenderTexture *bottomBar;
		sf::RenderWindow *window;
		int refPosX; 		// Position X in the statistics bottom bar
		int refPosY; 		// Position Y in the statistics bottom bar
		sf::Color color;			// Color of the observed player

};

#endif /* PLAYER_STATISTICSVIEWER_H_ */
