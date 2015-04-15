/*
 * MapCreator.h
 *
 *  Created on: Apr 13, 2015
 *      Author: orpheus
 */

#ifndef MAP_MAPCREATOR_MAPCREATOR_H_
#define MAP_MAPCREATOR_MAPCREATOR_H_

#include "../Map.h"
#include "../Continent.h"
#include "../Territory.h"

#include "../../Viewers/MapViewer.h"

#include "../../FileIO/MapIO.h"

#include <SFML/Graphics.hpp>
#include <string>

class MapCreator
{
public:
	MapCreator();
	virtual ~MapCreator();

	std::string getFileName();
	Map* getMap();

	void mapCreatorMenu();
	void territoryEditorMenu(std::string territory);

	void createAMap();
	void mapCreatorGraphics();
	void createContinents();
	void createTerritories();
	void editTerritories();
	void removeContinents();
	void removeTerritories();

private:
	std::string fileName;
	Map* newMap;

	MapCreator* mapCreator;
	MapViewer* MapObserver;

	sf::RenderWindow window;
};

#endif /* MAP_MAPCREATOR_MAPCREATOR_H_ */
