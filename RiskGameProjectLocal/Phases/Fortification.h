#pragma once

#include "../Map/Map.h"
#include "../Player/Player.h"
#include "Phase.h"

class Fortification :public Phase
{
public:
	// Constructor
	Fortification();
	virtual ~Fortification();

	// Setters
	void setTOrigin(std::string aTerritory);
	void setTDestination(std::string aTerritory);

	// Others
	void selectOrigin();
	void selectDestination(std::string origin);
	void move(std::string origin, std::string destination);
	std::vector<std::string> createNeighborsStr(std::string name);
	void fortify();
	void run(Player* player);

private:
	Player *mCurrent;
	std::string tOriginStr;
	std::string tDestinationStr;
	Territory *tOrigin;
	Territory *tDestination;
	std::vector<std::string> originStr;
	std::vector<std::string> destinationStr;
};
