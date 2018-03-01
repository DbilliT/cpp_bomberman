//
// Ground.hpp for  in /home/calatr_m/cpp_rendu/CPP/cpp_bomberman/project/UI
// 
// Made by Caltraba Mickael
// Login   <calatr_m@epitech.net>
// 
// Started on  Fri May 29 16:32:57 2015 Caltraba Mickael
// Last update Thu Jun 11 23:57:42 2015 Caltraba Mickael
//

#ifndef _GROUND_HPP_
# define _GROUND_HPP_

#include <Geometry.hh>
#include <Texture.hh>
#include <Clock.hh>

#include "AObject.hpp"

class Player;
class IBonus;

class Ground : public AObject
{
public:
  Ground(float, float, float, float, float);
  virtual ~Ground();

  virtual bool          initialize();
  virtual void          update(gdl::Clock const &, gdl::Input&,
                               std::list<AObject *> const &);
  virtual void          draw(gdl::AShader &, gdl::Clock const &);

private:
  gdl::Texture          _texture;
  static gdl::Geometry  *_geometry;
};

#endif
