/*
 * Phase.h
 *
 *  Created on: Apr 14, 2015
 *      Author: Emmanuel
 */

#ifndef PHASES_PHASE_H_
#define PHASES_PHASE_H_

#include "../Player/Player.h"

class Phase
{
public:
  Phase ();
  virtual
  ~Phase ();
  virtual void run(Player* player) = 0;
};

#endif /* PHASES_PHASE_H_ */
