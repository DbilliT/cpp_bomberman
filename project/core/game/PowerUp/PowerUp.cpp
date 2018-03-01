//
// PowerUp.cpp for PowerUp in /home/david_k/cpp_rendu/cpp_bomberman/project/core/game/PowerUp
// 
// Made by paul david
// Login   <david_k@epitech.net>
// 
// Started on  Tue May 26 13:55:16 2015 paul david
// Last update Thu Jun 11 22:55:50 2015 paul david
//

#include "PowerUp.hpp"
#include "Player.hpp"

PowerUp::PowerUp(std::pair<unsigned int, unsigned int> const &pos) : Pos(pos), Type(POWERUP)
{}

PowerUp::~PowerUp()
{}

void PowerUp::pickedUp(character &player)
{player.setBombPower(player.getBombPower() + 1);}

std::pair<unsigned int, unsigned int> const &PowerUp::getPos() const
{return this->Pos;}

BonusType PowerUp::getType() const
{return this->Type;}
