//
// Box.hpp for Box in /home/david_k/cpp_rendu/cpp_bomberman/project/core/game/Box
// 
// Made by paul david
// Login   <david_k@epitech.net>
// 
// Started on  Thu May 21 15:19:52 2015 paul david
// Last update Thu May 21 16:06:21 2015 paul david
//

#ifndef BOX_HPP_
#define BOX_HPP_

#include "ICase.hpp"

class Box : public ICase
{
public:
  Box();
  virtual ~Box();
  virtual CaseType getType() const;
  virtual bool isFree() const;
private:
  CaseType type;
};

#endif
