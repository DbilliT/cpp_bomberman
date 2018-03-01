//
// CaseAction.hpp for CaseAction in /home/david_k/cpp_rendu/cpp_bomberman/project/core/game/Bomb
// 
// Made by paul david
// Login   <david_k@epitech.net>
// 
// Started on  Wed Jun  3 15:19:13 2015 paul david
// Last update Thu Jun 11 15:20:38 2015 paul david
//

#ifndef CASEACTION_HPP_
#define CASEACTION_HPP_

#include <list>
#include <random>
#include <vector>
#include "BonusFactory.hpp"
#include "CaseFactory.hpp"

class CaseAction
{
public:
  CaseAction();
  ~CaseAction();
  void DestroyBox(std::vector<ICase **> &, std::pair<unsigned int, unsigned int> const &, std::list<IBonus *> &, std::list<std::pair<unsigned int, unsigned int> > &) const;
  void BonusSpawn(std::list<IBonus *> &, std::pair<unsigned int, unsigned int> const &) const;
private:
  CaseFactory CaseFacto;
  BonusFactory BonusFacto;
};

#endif
