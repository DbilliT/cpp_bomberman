//
// Boost.cpp for Boost in /home/david_k/cpp_rendu/cpp_bomberman/project/core/game/Boost
// 
// Made by paul david
// Login   <david_k@epitech.net>
// 
// Started on  Sun May 24 16:08:02 2015 paul david
// Last update Fri Jun 12 12:34:19 2015 paul david
//

#include "Boost.hpp"
#include "Player.hpp"

Boost::Boost(std::pair<unsigned int, unsigned int> const &pos) : Pos(pos), Type(BOOST)
{
}

Boost::~Boost()
{}

void Boost::pickedUp(character &player)
{
  player.setSpeed(player.getSpeed() + 0.2);
}

std::pair<unsigned int, unsigned int> const &Boost::getPos() const
{return this->Pos;}

BonusType Boost::getType() const
{return this->Type;}
