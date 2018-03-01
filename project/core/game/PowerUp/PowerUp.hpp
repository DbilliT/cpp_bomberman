//
// PowerUp.hpp for PowerUp in /home/david_k/cpp_rendu/cpp_bomberman/project/core/game/PowerUp
// 
// Made by paul david
// Login   <david_k@epitech.net>
// 
// Started on  Tue May 26 13:50:38 2015 paul david
// Last update Thu Jun 11 16:10:33 2015 paul david
//

#ifndef POWERUP_HPP_
#define POWERUP_HPP_

#include "IBonus.hpp"

class PowerUp : public IBonus
{
public:
  PowerUp(std::pair<unsigned int, unsigned int> const &pos);
  virtual ~PowerUp();
  virtual void pickedUp(character &player);
  virtual std::pair <unsigned int, unsigned int> const &getPos() const;
  virtual BonusType getType() const;
private:
  const std::pair <unsigned int, unsigned int> Pos;
  const BonusType Type;
};

#endif
