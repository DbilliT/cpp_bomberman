//
// Skybox.hpp for  in /home/calatr_m/cpp_rendu/CPP/cpp_bomberman/project/UI
// 
// Made by Caltraba Mickael
// Login   <calatr_m@epitech.net>
// 
// Started on  Sun Jun  7 16:01:03 2015 Caltraba Mickael
// Last update Fri Jun 12 00:00:06 2015 Caltraba Mickael
//

#ifndef _SKYBOX_HPP
# define _SKYBOX_HPP

#include <Geometry.hh>
#include <Texture.hh>
#include <Clock.hh>
#include <map>
#include "AObject.hpp"

class Skybox : public AObject
{
public:
  Skybox(int, int, int, float);
  virtual ~Skybox();

  virtual bool          initialize() {return true;} 
  virtual void		checkKey(gdl::Clock const &, gdl::Input &);
  virtual void		update(gdl::Input&, float);
  virtual void		draw(gdl::AShader &, gdl::Clock const &);
  
  bool			initializeBox(int);
private:
  gdl::Texture		_texture;
  gdl::Geometry		*_geometry;
  std::map<int, std::string>	_resource;
};

#endif
