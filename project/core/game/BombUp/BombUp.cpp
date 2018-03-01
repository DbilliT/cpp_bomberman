//
// BombUp.cpp for BombUp in /home/david_k/cpp_rendu/cpp_bomberman/project/core/game/BombUp
// 
// Made by paul david
// Login   <david_k@epitech.net>
// 
// Started on  Sun May 24 16:08:02 2015 paul david
// Last update Thu Jun 11 19:26:28 2015 paul david
//

#include "BombUp.hpp"
#include "Player.hpp"

BombUp::BombUp(std::pair<unsigned int, unsigned int> const &pos) : Pos(pos), Type(BOMBUP)
{
}

BombUp::~BombUp()
{}

void BombUp::pickedUp(character &player)
{
  player.setNbBomb(player.getNbBomb() + 1);
}

std::pair<unsigned int, unsigned int> const &BombUp::getPos() const
{return this->Pos;}

BonusType BombUp::getType() const
{return this->Type;}
