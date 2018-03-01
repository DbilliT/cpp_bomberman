//
// CaseFactory.hpp for CaseFactory in /home/david_k/cpp_rendu/cpp_bomberman/project/core/game/CaseFactory
// 
// Made by paul david
// Login   <david_k@epitech.net>
// 
// Started on  Thu May 21 17:20:03 2015 paul david
// Last update Tue Jun  9 19:20:09 2015 paul david
//

#ifndef BONUSFACTORY_HPP_
#define BONUSFACTORY_HPP_

#include <map>
#include "BombUp.hpp"
#include "PowerUp.hpp"
#include "Boost.hpp"

class BonusFactory
{
public:
  BonusFactory();
  ~BonusFactory();
  IBonus *CreateBonus(BonusType Type, std::pair<unsigned int, unsigned int> const &pos) const;
  typedef IBonus *(BonusFactory::*fcreate)(std::pair<unsigned int, unsigned int> const &) const;
private:
  IBonus *CreateBoost(std::pair<unsigned int, unsigned int> const &) const;
  IBonus *CreateBombUp(std::pair<unsigned int, unsigned int> const &) const;
  IBonus *CreatePowerUp(std::pair<unsigned int, unsigned int> const &) const;

  std::map<BonusType, fcreate>create;
};

#endif
