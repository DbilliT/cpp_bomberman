//
// Wall.hpp for Wall in /home/david_k/cpp_rendu/cpp_bomberman/project/core/game/Wall
// 
// Made by paul david
// Login   <david_k@epitech.net>
// 
// Started on  Thu May 21 14:55:04 2015 paul david
// Last update Thu May 21 16:22:20 2015 paul david
//

#ifndef WALL_HPP_
#define WALL_HPP_

#include "ICase.hpp"

class Wall : public ICase
{
public:
  Wall();
  virtual ~Wall();
  virtual CaseType getType() const;
  virtual bool isFree() const;
private:
  CaseType	type;
};

#endif
