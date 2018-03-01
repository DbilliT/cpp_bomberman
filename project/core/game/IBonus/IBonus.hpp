//
// IBonus.hpp for IBonus in /home/david_k/cpp_rendu/cpp_bomberman/project/core/game/IBonus
// 
// Made by paul david
// Login   <david_k@epitech.net>
// 
// Started on  Fri May 22 17:50:57 2015 paul david
// Last update Thu Jun 11 16:14:56 2015 paul david
//

#ifndef IBONUS_HPP_
#define IBONUS_HPP_

#include <utility>

class character;

enum BonusType
  {
    BOOST = 0,
    POWERUP = 1,
    BOMBUP = 2
  };

class IBonus
{
public:
  virtual ~IBonus() {}
  virtual void	pickedUp(character &player) = 0;
  virtual std::pair<unsigned int, unsigned int> const &getPos() const = 0;
  virtual BonusType getType() const = 0;
};

#endif
