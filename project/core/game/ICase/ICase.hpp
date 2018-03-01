//
// Case.hpp for Case in /home/david_k/cpp_rendu/cpp_bomberman/project/core/game/case
// 
// Made by paul david
// Login   <david_k@epitech.net>
// 
// Started on  Fri May 15 16:13:04 2015 paul david
// Last update Fri May 22 15:41:43 2015 Pierre Bechade
//

#ifndef ICASE_HPP_
# define ICASE_HPP_

#include <iostream>
#include <string>
#include <list>

enum CaseType
  {
    EMPTY = 0,
    WALL = 1,
    BOX = 2
  };

class ICase
{
public:
  virtual ~ICase() {}
  virtual CaseType getType() const = 0;
  virtual bool isFree() const = 0;
};

#endif
