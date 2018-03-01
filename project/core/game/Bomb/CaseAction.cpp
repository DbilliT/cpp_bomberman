//
// CaseAction.cpp for CaseAction in /home/david_k/cpp_rendu/cpp_bomberman/project/core/game/Bomb
// 
// Made by paul david
// Login   <david_k@epitech.net>
// 
// Started on  Wed Jun  3 15:32:42 2015 paul david
// Last update Thu Jun 11 23:30:23 2015 paul david
//

#include "CaseAction.hpp"

CaseAction::CaseAction()
{
}

CaseAction::~CaseAction()
{
}

void CaseAction::DestroyBox(std::vector<ICase **> &Map, std::pair<unsigned int, unsigned int> const &pos, std::list<IBonus *> &Bonus, std::list<std::pair<unsigned int, unsigned int> > &BoxDestroyed) const
{
  if (Map[pos.first][pos.second]->getType() == BOX)
    {
      BoxDestroyed.push_back(pos);
      delete Map[pos.first][pos.second];
      Map[pos.first][pos.second] = CaseFacto.CreateCase(EMPTY);
      BonusSpawn(Bonus, pos);
    }
}

void CaseAction::BonusSpawn(std::list<IBonus *> &Bonus, std::pair<unsigned int, unsigned int> const &pos) const
{
  std::random_device	rand;
  int			res;

  res = rand() % 4;
  if (res != 3)
    Bonus.push_back(BonusFacto.CreateBonus(static_cast<BonusType>(res), pos));
}
