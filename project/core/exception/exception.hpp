//
// exception.hpp for exception in /home/bechad_p/rendu/cpp_bomberman/project/core/exception
// 
// Made by Pierre Bechade
// Login   <bechad_p@epitech.net>
// 
// Started on  Fri May 15 09:21:27 2015 Pierre Bechade
// Last update Sat Jun  6 17:13:23 2015 Pierre Bechade
//

#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

#include <exception>
#include <new>

class Exception : public std::exception
{
public:
  Exception(std::string const &error) throw() : _error(error) {}
  virtual ~Exception() throw() {}
  virtual const char *what() const throw()
  {
    return _error.c_str();
  }
protected:
  std::string const _error;
};

class Wrong_file : public Exception
{
public:
  Wrong_file(std::string const &error) throw() : Exception(error) {}
  virtual ~Wrong_file() throw() {}
  virtual const char *what() const throw()
  {
    return _error.c_str();
  }
private:
  std::string const _error;
};

class SoundManagerIssue : public Exception
{
public:
  SoundManagerIssue(std::string const &error) throw() : Exception(error) {}
  virtual ~SoundManagerIssue() throw() {}
  virtual const char *whatFmod() const throw()
  {
    return _errorFmod.c_str();
  }
private:
  std::string const _errorFmod;
};

#endif /* EXCEPTION_HPP */
