//
// TextureManager.cpp for  in /home/calatr_m/cpp_rendu/CPP/cpp_bomberman/project/UI
// 
// Made by Caltraba Mickael
// Login   <calatr_m@epitech.net>
// 
// Started on  Wed Jun  3 16:39:03 2015 Caltraba Mickael
// Last update Sun Jun 14 21:13:10 2015 Caltraba Mickael
//

#include "TextureManager.hpp"

TextureManager::TextureManager()
{
}
TextureManager::~TextureManager()
{
}

bool	TextureManager::init()
{
  if (!this->_wall.load("./project/UI/GDL/Ressources/Wall.tga"))
    return (false);
  if (!this->_box.load("./project/UI/GDL/Ressources/Box.tga"))
    return (false);
  if (!this->_ground.load("./project/UI/GDL/Ressources/Ground.tga"))
    return (false);
  if (!this->_fire.load("./project/UI/GDL/Ressources/Fire.tga"))
    return (false);
  if (!this->_quit.load("./project/UI/GDL/Ressources/Quit.tga"))
    return (false);
  if (!this->_continue.load("./project/UI/GDL/Ressources/Continue.tga"))
    return (false);
  if (!this->_bomb.load("./project/UI/GDL/Ressources/Bomb.tga"))
    return (false);
  if (!this->_power.load("./project/UI/GDL/Ressources/Power.tga"))
    return (false);
  if (!this->_bombUp.load("./project/UI/GDL/Ressources/BombUp.tga"))
    return (false);
  if (!this->_boost.load("./project/UI/GDL/Ressources/Boost.tga"))
    return (false);
  return true;
}

gdl::Texture	&TextureManager::getTexture(std::string const &name)
{
  if (name == "Wall")
    return (this->_wall);
  if (name == "Box")
    return (this->_box);
  if (name == "Ground")
    return (this->_ground);
  if (name == "Fire")
    return (this->_fire);
  if (name == "Quit")
    return (this->_quit);
  if (name == "Continue")
    return (this->_continue);
  if (name == "Bomb")
    return (this->_bomb);
  if (name == "BombUp")
    return (this->_bombUp);
  if (name == "Boost")
    return (this->_boost);
  if (name == "Power")
    return (this->_power);
  return (this->_continue);
}
