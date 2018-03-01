//
// Case.cpp for Case in /home/david_k/cpp_rendu/cpp_bomberman/project/core/game/Case
// 
// Made by paul david
// Login   <david_k@epitech.net>
// 
// Started on  Thu May 21 16:41:36 2015 paul david
// Last update Fri May 22 16:16:04 2015 Pierre Bechade
//

#include "Case.hpp"

Case::Case() : type(EMPTY)
{
}

Case::~Case()
{
}

bool Case::isFree() const
{
  return (true);
}

CaseType Case::getType() const
{
  return this->type;
}
