/*
 * Map.h
 *
 *  Created on: Feb 6, 2015
 *      Author: mateus
 */

#ifndef MAP_H_
#define MAP_H_

#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <vector>	/*ALREADY IN TERRITORY.H, CONTINENT.H */

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

#include "Continent.h"
#include "../ObservablePattern/Observable.h" // ALREADY IN TERRITORY.H, CONTINENT.H
#include "../FileIO/MapIO.h"
#include "../Viewers/StatusNotifier.h"
#include "../Cards/GameDeck.h"

/* Added to fixe circular dependency problem */
class Continent;
class Territory;

class Map : public Observable
{

public:
	// SingleTone Instance
	static Map* getMapInstance();

	// constructor
	Map();

	Map(std::vector<Continent*> continents);

	// Copy Constructor
	Map (const Map& other);

	// Assignment Operator
	Map& operator=(const Map& other);

	// destructor
	virtual ~Map();

	// getter
	std::string 		getFileName();
	std::vector<Continent*> getContinents();
	std::vector<Territory*> getTerritories();
	std::vector<Territory*> getTerritoriesByPlayer(std::string player);

	// setter
	void setContinents(std::vector<Continent*> continents);
	void setFileName(std::string fileName);

	// other methods
	void printMyContinentsAndTerritory();

	Continent* getContinentByName(std::string continent);

	Territory* getTerritoryByName(std::string territory);

	void addNewContinent(Continent* continent);

	void removeContinent(Continent* continent); // removes from the continent, don't delete

	void removeTerritory(Territory* territory); // removes from the territories, don't delete

	bool checkIfContinentExists(std::string continent);

	bool checkIfTerritoryExists(std::string territory);

	void loadMap(char* filename);

	void 		setStatsNotifier(StatusNotifier* sn){statusNotifier = sn;};
	StatusNotifier* getStatsNotifier(){return statusNotifier;};

private:

	// SingleTone Instance
	static Map *mapInstance;

	// Vector that holds the continents
	std::vector<Continent*> continents;

	StatusNotifier* statusNotifier;
	// Name for the picture to be loaded by SMFL
	std::string fileName;
};

#endif /* MAP_H_ */
