/*
 * MapViewer.h
 *
 *  Created on: Mar 2, 2015
 *      Author: mateus
 */

#ifndef MAPVIEWER_H_
#define MAPVIEWER_H_

#include "../ObservablePattern/Observer.h"
#include "../Map/Map.h"

#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>


class MapViewer : public Observer
{

	public:
		// Constructor and Destructor
		MapViewer(Map* aMap, sf::RenderWindow &aWindow);
		~MapViewer();

		// Called by the Notify of Observable
		void update();

		// SFML display functions
		void drawNeighborLine(int x1, int y1, int x2, int y2, sf::Color color);
		void drawAllNeighborsLines();

		void drawContinentOwner(int xPos, int yPos, std::string continentColor);
		void drawAllContinentOwners();

		void drawContinentInfoBar();
		void drawContinentLabel(std::string continentName, std::string continentColor, int nTerritories, int posX);
		sf::Color convertContinentColor(std::string continentColor);

		bool loadMapImage(std::string nameOfImage);

	private:
		Map* observedMap;
		sf::RenderWindow *window;

		bool loaded;

		sf::Image mapBackground;
		sf::Texture mapTexture;
		sf::Sprite spriteBackground;
};


#endif /* MAPVIEWER_H_ */
