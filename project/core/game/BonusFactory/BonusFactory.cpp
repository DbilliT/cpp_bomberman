//
// CaseFactory.cpp for CaseFactory in /home/david_k/cpp_rendu/cpp_bomberman/project/core/game/CaseFactory
// 
// Made by paul david
// Login   <david_k@epitech.net>
// 
// Started on  Thu May 21 17:41:55 2015 paul david
// Last update Tue Jun  9 19:18:16 2015 paul david
//

#include "BonusFactory.hpp"

BonusFactory::BonusFactory()
{
  this->create[BOOST] = &BonusFactory::CreateBoost;
  this->create[BOMBUP] = &BonusFactory::CreateBombUp;
  this->create[POWERUP] = &BonusFactory::CreatePowerUp;
}

BonusFactory::~BonusFactory()
{
}

IBonus *BonusFactory::CreateBonus(BonusType Type, std::pair<unsigned int, unsigned int> const &pos) const
{
  return ((this->*(*create.find(Type)).second)(pos));
}

IBonus *BonusFactory::CreateBoost(std::pair<unsigned int, unsigned int> const &pos) const
{
  return (new Boost(pos));
}

IBonus *BonusFactory::CreateBombUp(std::pair<unsigned int, unsigned int> const &pos) const
{
  return (new BombUp(pos));
}

IBonus *BonusFactory::CreatePowerUp(std::pair<unsigned int, unsigned int> const &pos) const
{
  return (new PowerUp(pos));
}
