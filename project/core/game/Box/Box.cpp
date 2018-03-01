//
// Box.cpp for Box in /home/david_k/cpp_rendu/cpp_bomberman/project/core/game/Box
// 
// Made by paul david
// Login   <david_k@epitech.net>
// 
// Started on  Thu May 21 15:23:09 2015 paul david
// Last update Fri May 22 16:16:40 2015 Pierre Bechade
//

#include "Box.hpp"

Box::Box()
{
  this->type = BOX;
}

Box::~Box()
{
}

CaseType Box::getType() const
{
  return this->type;
}

bool	Box::isFree() const
{
  return false;
}
