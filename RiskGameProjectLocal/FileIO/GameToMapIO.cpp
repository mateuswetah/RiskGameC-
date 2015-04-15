/*
 * GameToMapIO.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: Emmanuel
 */

#include "../FileIO/GameToMapIO.h"

GameToMapIO::GameToMapIO (MapIO mio)
{
  // TODO Auto-generated constructor stub
  mMapIO = mio;
}

GameToMapIO::~GameToMapIO ()
{
  // TODO Auto-generated destructor stub
}

void
GameToMapIO::loadGameInfo (std::string filename)
{
  mMapIO.loadMapInfo(filename);
}

void
GameToMapIO::saveGameInfo (std::string filename)
{
  mMapIO.saveMapInfo(filename);
}
