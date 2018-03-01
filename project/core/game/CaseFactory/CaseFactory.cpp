//
// CaseFactory.cpp for CaseFactory in /home/david_k/cpp_rendu/cpp_bomberman/project/core/game/CaseFactory
// 
// Made by paul david
// Login   <david_k@epitech.net>
// 
// Started on  Thu May 21 17:41:55 2015 paul david
// Last update Tue Jun  9 19:14:44 2015 paul david
//

#include "CaseFactory.hpp"

CaseFactory::CaseFactory()
{
  this->create[WALL] = &CaseFactory::CreateWall;
  this->create[BOX] = &CaseFactory::CreateBox;
  this->create[EMPTY] = &CaseFactory::CreateEmpty;
}

CaseFactory::~CaseFactory()
{
}

ICase *CaseFactory::CreateCase(CaseType Type) const
{
  return ((this->*(*create.find(Type)).second))();
}

ICase *CaseFactory::CreateWall() const
{
  return (new Wall);
}

ICase *CaseFactory::CreateBox() const
{
  return (new Box);
}

ICase *CaseFactory::CreateEmpty() const
{
  return (new Case);
}
