/*
 * Territory.h
 *
 *  Created on: Jan 28, 2015
 *      Author: mateus
 */

#ifndef TERRITORY_H_
#define TERRITORY_H_

#include "../Player/Player.h"
#include "../ObservablePattern/Observable.h"
#include <string>
#include <vector>

/* Added to fixe circular dependency problem */
class Player;

class Territory : public Observable
{

public:

	// Constructors and Destructor
	Territory();
	Territory(std::string name, std::vector<Territory*> neightbors, int posX, int PosY, Player* player, int armies);
	virtual ~Territory();
	// Copy Constructor
	Territory (const Territory& other);
	// Assignment Operator
	Territory& operator=(const Territory& other);

	// getters
	std::string getName();

	std::vector<Territory*> getNeighbors();

	int getPosX();

	int getPosY();

	Player* getPlayerOwner();

	int getAmountOfArmies();

	// setters
	void setName(std::string name);

	void setNeighbors(std::vector<Territory*> neighbors);

	void setPosX(int x);

	void setPosY(int y);

	void setPlayerOwner(Player* player);

	void setAmountOfArmies(int armies);

	// other methods
	void printMyNeighbors();

	Territory* getNeighborByName(std::string territory);

	void addNewNeighbor(Territory* territory);

	void removeNeighbor(Territory* territory); // don't delete, just remove from the list of neighbors

	bool isNeighbor(Territory* t);

private:

	std::string name;
	std::vector<Territory*> neighbors;
	int mPosX;
	int mPosY;
	Player* playerOwner;
	int amountOfArmies;

};


#endif /* TERRITORY_H_ */
