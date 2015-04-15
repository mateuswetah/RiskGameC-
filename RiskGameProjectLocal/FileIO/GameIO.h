/*
 * GameIO.h
 *
 *  Created on: Apr 8, 2015
 *      Author: Emmanuel
 */

#ifndef MAP_MAPIO_GAMEIO_H_
#define MAP_MAPIO_GAMEIO_H_
#include "../Map/Map.h"
#include <string>
#include <vector>

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

class Map;

class GameIO
{
public:
  GameIO ();
  virtual
  ~GameIO ();

  //To be Substituted by the Builder pattern by the other member of the group.

  void loadGameInfo(std::string filename);
  void saveGameInfo(std::string filename);

private:
  Map *mMap;
};

#endif /* MAP_MAPIO_GAMEIO_H_ */
