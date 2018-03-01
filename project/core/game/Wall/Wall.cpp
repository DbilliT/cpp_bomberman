//
// Wall.cpp for Wall in /home/david_k/cpp_rendu/cpp_bomberman/project/core/game/Wall
// 
// Made by paul david
// Login   <david_k@epitech.net>
// 
// Started on  Thu May 21 15:07:13 2015 paul david
// Last update Thu May 21 16:24:05 2015 paul david
//

#include "Wall.hpp"

Wall::Wall()
{
  this->type = WALL;
}

Wall::~Wall()
{
}

CaseType Wall::getType() const
{
  return (this->type);
}

bool Wall::isFree() const
{
  return false;
}
