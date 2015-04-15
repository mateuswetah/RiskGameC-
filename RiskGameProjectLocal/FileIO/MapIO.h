/*
 * MapIO.h
 *
 *  Created on: Apr 8, 2015
 *      Author: Emmanuel
 */

#ifndef MAP_MAPIO_MAPIO_H_
#define MAP_MAPIO_MAPIO_H_

#include "../Map/Map.h"
#include <string>
#include <vector>

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

class Map;

class MapIO	//Adaptee
{
public:
  MapIO ();
  virtual
  ~MapIO ();

  void loadMapInfo(std::string filename);
  void saveMapInfo(std::string filename);

private:
  Map* mMap;
};

#endif /* MAP_MAPIO_MAPIO_H_ */
