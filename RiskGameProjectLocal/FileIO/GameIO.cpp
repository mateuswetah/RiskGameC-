/*
 * GameIO.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: Emmanuel
 */

#include "../FileIO/GameIO.h"

GameIO::GameIO ()
{
  // TODO Auto-generated constructor stub

}

GameIO::~GameIO ()
{
  // TODO Auto-generated destructor stub
}

void
GameIO::loadGameInfo (std::string filename)
{
  mMap = Map::getMapInstance();

  char lineBuffer[302];
  char lineStream[302];
  std::string lineString;
  size_t posC;
   // File to be read
   FILE *fptr;

   if ((fptr = fopen(filename.c_str(),"r")) == NULL)
     printf("Error! opening file");
   else
   {
       while (!feof(fptr))
       {
	   fgets(lineBuffer, 300, fptr);
	   sscanf(lineBuffer, "%[^\n]s", lineStream);
	   lineString = std::string(lineStream);
	   if (lineString.find(",") != -1)
	   {
	       Territory* t;
	       posC = lineString.find(",");
	       std::string aTerritoryName = lineString.substr(0, posC);
	       t = mMap->getTerritoryByName(aTerritoryName);
	       size_t posC1 = lineString.find(",", posC + 1); // second comma
	       std::string aTerritoryOwner = lineString.substr(posC+1, posC1 - posC - 1);
	       t->setPlayerOwner(mMap->getTerritoriesByPlayer(aTerritoryOwner).at(0)->getPlayerOwner());
	       std::string aTerritoryArmies = lineString.substr(posC1+1);
	       std::cout<<"Amount: "<<atoi(aTerritoryArmies.c_str())<<std::endl;
	       t->setAmountOfArmies(atoi(aTerritoryArmies.c_str()));
	   }

       }
       fclose(fptr);
   }
}

void
GameIO::saveGameInfo (std::string filename)
{
  mMap = Map::getMapInstance();

   // File to be read
   FILE *fptr;

   if ((fptr = fopen(filename.c_str(),"w")) == NULL)
     printf("Error! opening file");
   else
   {
       for(int i = 0; i < mMap->getTerritories().size(); i++)
       {
	   Territory* t = mMap->getTerritories().at(i);
	   fputs(t->getName().c_str(), fptr);
	   fputs(",", fptr);
	   fputs(t->getPlayerOwner()->getName().c_str(), fptr);
	   fputs(",", fptr);
	   std::stringstream	ss;
	   ss<<t->getAmountOfArmies();
	   fputs(ss.str().c_str(), fptr);
	   fputs("\n", fptr);
       }
   }
   fclose(fptr);

}
