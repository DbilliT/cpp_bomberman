//
// TextureManager.hpp for  in /home/calatr_m/cpp_rendu/CPP/cpp_bomberman/project/UI
// 
// Made by Caltraba Mickael
// Login   <calatr_m@epitech.net>
// 
// Started on  Wed Jun  3 16:39:30 2015 Caltraba Mickael
// Last update Sat Jun 13 11:21:34 2015 Caltraba Mickael
//

#ifndef _TEXTUREMANAGER_HPP_
# define _TEXTUREMANAGER_HPP_

#include <string>
#include <vector>
#include <unordered_map>
#include <Texture.hh>
#include <iostream>

class TextureManager
{
public:
  TextureManager();
  ~TextureManager();

  bool		init();
  gdl::Texture		&getTexture(std::string const &);

private:
  gdl::Texture	_wall;
  gdl::Texture	_ground;
  gdl::Texture	_box;
  gdl::Texture	_fire;

  gdl::Texture	_bomb;
  gdl::Texture	_power;
  gdl::Texture	_bombUp;
  gdl::Texture	_boost;

  gdl::Texture	_quit;
  gdl::Texture	_continue;
};

#endif
