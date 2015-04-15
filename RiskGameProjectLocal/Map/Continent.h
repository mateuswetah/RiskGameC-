/*
 * Continent.h
 *
 *  Created on: Jan 30, 2015
 *      Author: mateus
 */

#ifndef CONTINENT_H_
#define CONTINENT_H_

#include <vector>
#include "Territory.h"
#include "Observable.h" // ALREADY IN TERRITORY.H 

/* Added to fixe circular dependency problem */
class Territory;

class Continent : public Observable
{

public:
	// constructors
	Continent();

	Continent(std::string name, std::vector<Territory*> territories);

	// destructor
	virtual ~Continent();

	// Copy Constructor
	Continent (const Continent& other);

	// Assignment Operator
	Continent& operator=(const Continent& other);

	// getter
	std::vector<Territory*> getTerritories();

	std::string getName();

	std::string getColor();

	int getBonus();

	// setter
	void setTerritories(std::vector<Territory*> territories);

	void setName(std::string name);

	void setColor(std::string color);

	void setBonus(int value);

	// other methods
	void printMyTerritories();

	Territory* getTerritoryByName(std::string territory);

	void addNewTerritory(Territory* territory);

	void removeTerritory(Territory* territory); // removes from the continent, don't delete


private:

	std::vector<Territory*> territories;
	std::string name;
	std::string color;
	int bonus; // Reinforcement bonus

};

#endif /* CONTINENT_H_ */
