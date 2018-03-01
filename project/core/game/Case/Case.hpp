//
// Case.hpp for Case in /home/david_k/cpp_rendu/cpp_bomberman/project/core/game/Case
// 
// Made by paul david
// Login   <david_k@epitech.net>
// 
// Started on  Thu May 21 16:26:20 2015 paul david
// Last update Fri May 22 15:50:39 2015 Pierre Bechade
//

#ifndef CASE_HPP_
#define CASE_HPP_

#include "ICase.hpp"

class Case : public ICase
{
public:
  Case();
  virtual ~Case();
  virtual bool isFree() const;
  virtual CaseType getType() const;
private:
  CaseType type;
};

#endif
