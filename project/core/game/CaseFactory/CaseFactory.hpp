//
// CaseFactory.hpp for CaseFactory in /home/david_k/cpp_rendu/cpp_bomberman/project/core/game/CaseFactory
// 
// Made by paul david
// Login   <david_k@epitech.net>
// 
// Started on  Thu May 21 17:20:03 2015 paul david
// Last update Tue Jun  9 19:15:38 2015 paul david
//

#ifndef CASEFACTORY_HPP_
#define CASEFACTORY_HPP_

#include <map>
#include "Case.hpp"
#include "Wall.hpp"
#include "Box.hpp"

class CaseFactory
{
public:
  CaseFactory();
  ~CaseFactory();
  ICase *CreateCase(CaseType Type) const;
  typedef ICase *(CaseFactory::*fcreate)() const;
private:
  ICase *CreateWall() const;
  ICase *CreateBox() const;
  ICase *CreateEmpty() const;

  std::map<CaseType, fcreate>create;
};

#endif
