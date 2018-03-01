//
// Cube.hpp for Graphic in /home/calatr_m/test
// 
// Made by Caltraba Mickael
// Login   <calatr_m@epitech.net>
// 
// Started on  Tue May 19 13:34:49 2015 Caltraba Mickael
// Last update Fri Jun 12 23:42:11 2015 Caltraba Mickael
//

#ifndef _CUBE_HPP_
# define _CUBE_HPP_

#include <Geometry.hh>
#include <Texture.hh>
#include <Clock.hh>

#include "AObject.hpp"

class Player;
class IBonus;

class Cube : public AObject
{
public:
  Cube(int, int, float, float, float, float, bool, gdl::Texture&);
  virtual ~Cube();

  virtual bool		initialize();
  virtual void		checkKey(gdl::Clock const &, gdl::Input &);
  virtual void		update(gdl::Input&, float);
  virtual void		draw(gdl::AShader &, gdl::Clock const &);

  int			getX() const;
  int			getY() const;

private:
  gdl::Texture		_texture;
  static gdl::Geometry	*_geometry;
  bool			_destroy;
};

#endif
