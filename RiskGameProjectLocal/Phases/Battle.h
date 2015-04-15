/*
 * Battle.h
 *
 *  Created on: Feb 5, 2015
 *      Author: Emmanuel
 */

#ifndef BATTLE_H_
#define BATTLE_H_

#define max_attack_dices 3
#define max_defense_dices 2

#define min_armies_to_attack 2

#include "../Map/Map.h"
#include "../Player/Player.h"
#include "../Player/AIPlayer.h"

#include "time.h"
#include <algorithm>
#include <stdlib.h>
#include <functional>
#include <typeinfo>
#include <cctype>

class Battle
{
public:
  Battle ();
  virtual
  ~Battle ();

  void RunBattle(bool allIn, Player* player);
  bool SetupBattle(Player* player);
  void RollDices(bool allin);
  void setDeffender (Territory* deffender);
  void setAttacker (Territory* attacker);

private:
  Map*	mMap;
  Territory* mAttacker;
  Territory* mDeffender;
  std::vector<int> mAttackersDice;
  std::vector<int> mDeffendersDice;
};

#endif /* BATTLE_H_ */
