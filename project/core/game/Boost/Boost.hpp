//
// Boost.hpp for Boost in /home/david_k/cpp_rendu/cpp_bomberman/project/core/game/Boost
// 
// Made by paul david
// Login   <david_k@epitech.net>
// 
// Started on  Fri May 22 20:38:13 2015 paul david
// Last update Thu Jun 11 16:06:11 2015 paul david
//

#ifndef BOOST_HPP_
#define BOOST_HPP_

#include "IBonus.hpp"

class Boost : public IBonus
{
public:
  Boost(std::pair<unsigned int, unsigned int> const &pos);
  virtual ~Boost();
  virtual void pickedUp(character &player);
  virtual std::pair <unsigned int, unsigned int> const &getPos() const;
  virtual BonusType getType() const;
private:
  const std::pair <unsigned int, unsigned int> Pos;
  const BonusType Type;
};

#endif
