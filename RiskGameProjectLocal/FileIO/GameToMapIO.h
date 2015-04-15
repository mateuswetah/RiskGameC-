/*
 * GameToMapIO.h
 *
 *  Created on: Apr 8, 2015
 *      Author: Emmanuel
 */

#ifndef MAP_MAPIO_GAMETOMAPIO_H_
#define MAP_MAPIO_GAMETOMAPIO_H_

#include "../Map/Map.h"
#include <string>
#include <vector>

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

class Map;

class GameToMapIO
{
public:
  GameToMapIO (MapIO mio);
  virtual
  ~GameToMapIO ();

  void loadGameInfo(std::string filename);
  void saveGameInfo(std::string filename);

private:
  MapIO mMapIO;
};

#endif /* MAP_MAPIO_GAMETOMAPIO_H_ */
