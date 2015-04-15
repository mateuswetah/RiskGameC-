/*
 * MapIO.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: Emmanuel
 */

#include "../FileIO/MapIO.h"

MapIO::MapIO ()
{
  // TODO Auto-generated constructor stub

}

MapIO::~MapIO ()
{
  // TODO Auto-generated destructor stub
}

void MapIO::loadMapInfo (std::string filename)
{
	mMap = Map::getMapInstance();

	// Reading lines
    char lineBuffer[302];
    char lineStream[302];
    std::string lineString;

    // Auxiliary for finding character position
    size_t posC;

    // Info for the viewMap
    std::string imageFileName;

    // Vector for the name of the continents
    std::vector<std::string> continents;

    // Vector for the info of the territories
    std::vector<std::string> continentsNames;

    // Flags for switching between the modes of parsing
    bool map = false;
    bool continent = false;
    bool territory = false;

    // File to be read
    FILE *fptr;

    if ((fptr = fopen(filename.c_str(),"r")) == NULL)
      printf("Error! opening file");
    else
    {
		while (!feof(fptr))
		{
		  // Processing the line
		  fgets(lineBuffer, 300, fptr);
		  sscanf(lineBuffer, "%[^\n]s", lineStream);
		  lineString = std::string(lineStream);

		  // Looks for the map tag:
		  if(lineString.find("[Map]") == 0)
			{
			  map = true;
			  continent = false;
			  territory = false;
			}
		  // Looks for the continents tag:
		  else if(lineString.find("[Continents]") == 0)
			{
			  map = false;
			  continent = true;
			  territory = false;
			}
		  // Looks for the territories tag:
		  else if(lineString.find("[Territories]") == 0)
			{
			  map = false;
			  continent = false;
			  territory = true;
			}


		  if (map)
			{
			  // Looks for the Image File name (image.bmp, image.png, etc)
			  if(lineString.find("image") == 0)
			{
				imageFileName = lineString.substr(6);
				#ifdef linux
					imageFileName = imageFileName.substr(0, imageFileName.size() - 1); // removes the break line character
				#endif

				mMap->setFileName(imageFileName);
			}
			}
		  else if (continent)
			{
			  if (lineString.find("=") != -1)
			{
			  posC = lineString.find("=");

			  // Takes the continent name
			  std::string aContinent = lineString.substr(0, posC);
			  continentsNames.push_back(aContinent);

			  // Takes the continent reinforcement bonus
			  std::string aContinentBonusStr = lineString.substr(posC + 1);
			  std::stringstream convert(aContinentBonusStr);
			  int aContinentBonusInt;
			  if (!(convert >> aContinentBonusInt))
				  aContinentBonusInt = 0;

			  Continent* continentObject = new Continent();
			  continentObject->setName(aContinent);
			  continentObject->setBonus(aContinentBonusInt); // Define the continent bonus value for reinforcement
			  mMap->addNewContinent(continentObject);
			}

			}
		  else if (territory)
			{
			  if (lineString.find(",") != -1)
			{
			  Territory* territoryObject = new Territory();

			  // Takes the territory name
			  posC = lineString.find(","); // first comma
			  std::string aTerritoryName = lineString.substr(0, posC);

			  // Takes the xPosition
			  size_t posC1 = lineString.find(",", posC + 1); // second comma
			  std::string aTerritoryPosX = lineString.substr(posC+1, posC1 - posC - 1);

			  // Takes the yPosition
			  size_t posC2 = lineString.find(",", posC1 + 1); // third comma
			  std::string aTerritoryPosY = lineString.substr(posC1+1, posC2 - posC1 - posC - 1);

			  // Takes the Continent that the territory belong to
			  size_t posC3 = lineString.find(",", posC2 + 1); // fourth comma
			  std::string aTerritoryContinent = lineString.substr(posC2+1, posC3 - posC2 - 1);

			  // Takes the vector of Neighbors
			  size_t posC4 = lineString.find(",", posC3 ); // fifth comma
			  std::string aTerritoryListNeighbors = lineString.substr(posC4 + 1);

			  // Passes the whole info string to the vector of territories
			  std::stringstream territoryInfo;
			  territoryInfo << aTerritoryListNeighbors;

			  std::vector<std::string> aTerritoryNeighbors;
			  std::string aTerritoryNeighbor;

			  while (getline(territoryInfo, aTerritoryNeighbor, ','))
				aTerritoryNeighbors.push_back(aTerritoryNeighbor);


			  for (int i = 0; i < aTerritoryNeighbors.size(); i++)
				{

				  if (mMap->getTerritoryByName(aTerritoryNeighbors.at(i))->getName() == "Limbo" )
				{
				  Territory* territoryNeighborObject = new Territory();
				  territoryNeighborObject->setName(aTerritoryNeighbors.at(i));

				  territoryObject->addNewNeighbor(territoryNeighborObject);
				}
				  else
				{
				  territoryObject->addNewNeighbor(mMap->getTerritoryByName(aTerritoryNeighbors.at(i)));
				}
				}

			  territoryObject->setName(aTerritoryName);
			  territoryObject->setPosX(atoi(aTerritoryPosX.c_str()));
			  territoryObject->setPosY(atoi(aTerritoryPosY.c_str()));

			  Continent* c;
			  c = mMap->getContinentByName(aTerritoryContinent);

			  (c->addNewTerritory(territoryObject));

			  std::cout << territoryObject->getName()
								 << ", posX = " << territoryObject->getPosX()
								 << ", posY = " << territoryObject->getPosY()
								 << ", continent = " << aTerritoryContinent
								 << ", neighbors: ";



			  for (int i = 0; i < territoryObject->getNeighbors().size(); i++)
				{
				  std::cout << (territoryObject->getNeighbors().at(i))->getName() << ", ";
				}
			  std::cout<<std::endl;
			  //std::cout<<this->getTerritoryByName(territoryObject->getName())->getName()<<std::endl;

			}

			}

		}

        fclose(fptr);

        mMap->printMyContinentsAndTerritory();


        //cout << imageFileName;
      }
    mMap->notify();

}

void
MapIO
::saveMapInfo (std::string filename)
{
  mMap = Map::getMapInstance();

   // File to be read
   FILE *fptr;

   if ((fptr = fopen(filename.c_str(),"w")) == NULL)
     printf("Error! opening file");
   else
   {
       fputs("[Map]\n", fptr);
       fputs("author=Emmanuel, Mateus, Sylvie, Sarah\n", fptr);
       fputs("image=", fptr);
       fputs(mMap->getFileName().c_str(), fptr);
       fputs("\n\n", fptr);

       fputs("[Continents]\n", fptr);
       for(int i = 0; i < mMap->getContinents().size(); i++)
       {
	   fputs(mMap->getContinents().at(i)->getName().c_str(), fptr);
	   fputs("=", fptr);
	   std::stringstream ss;
	   ss<<mMap->getContinents().at(i)->getBonus();
	   fputs(ss.str().c_str(), fptr);
	   fputs("\n",fptr);
       }
       fputs("\n", fptr);

       fputs("[Territories]\n", fptr);
       for(int i = 0; i < mMap->getContinents().size(); i++)
      {
	   for(int j = 0; j < mMap->getContinents().at(i)->getTerritories().size(); j++)
	   {
	       Territory* t = mMap->getContinents().at(i)->getTerritories().at(j);
	       std::stringstream px, py;
	       fputs(t->getName().c_str(), fptr);
	       fputs(",", fptr);
	       px<< t->getPosX();
	       py<< t->getPosY();
	       fputs(px.str().c_str(), fptr);
	       fputs(",", fptr);
	       fputs(py.str().c_str(), fptr);
	       fputs(",", fptr);
	       fputs(mMap->getContinents().at(i)->getName().c_str(), fptr);
	       for(int k = 0; k < t->getNeighbors().size(); k++)
	       {
		   fputs(",", fptr);
		   fputs(t->getNeighbors().at(k)->getName().c_str(), fptr);
	       }
	       fputs("\n", fptr);
	   }
	   fputs("\n", fptr);
      }
     fclose(fptr);
   }
}
