/*
 * AIPlayer.cpp
 *
 *  Created on: Mar 8, 2015
 *      Author: Emmanuel
 */

#include "AIPlayer.h"

AIPlayer::AIPlayer (std::string name, int n)
{
  mStrategy = new Random();
  mStrategy->setPlayer(name);
  setName(name);
  setNumber(n);
  setColor("blue");
  // TODO Auto-generated constructor stub

}

AIPlayer::~AIPlayer ()
{
  // TODO Auto-generated destructor stub
}

void
AIPlayer::setStrategy (Strategy* newStrategy)
{
  this->mStrategy = newStrategy;
  mStrategy->setPlayer(this->getName());
}

char
AIPlayer::decideAttack ()
{
  return mStrategy->decideAttack();
}

std::string
AIPlayer::decideAttackingTerritory ()
{
  return mStrategy->decideAttackingTerritory();
}

std::string
AIPlayer::decideDefendingTerritory ()
{
  return mStrategy->decideDefendingTerritory();
}

char
AIPlayer::decideKeepAttacking ()
{
  return mStrategy->decideKeepAttacking();
}
