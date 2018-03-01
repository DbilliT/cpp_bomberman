//
// player.cpp for player in /home/david_k/cpp_rendu/cpp_bomberman/project/core/game/players
// 
// Made by paul david
// Login   <david_k@epitech.net>
// 
// Started on  Sun May 24 15:05:03 2015 paul david
// Last update Sun Jun 14 17:23:38 2015 Pierre Bechade
//

#include "Player.hpp"

Player::Player(std::pair<unsigned int, unsigned int> const &pos, unsigned int color, std::string const &name) : character(pos, color)
{
  this->_name = name;
  this->Score = 0;
}

Player::Player(std::pair<unsigned int, unsigned int> const &pos, unsigned int color, std::string const &name, unsigned int speed, unsigned int power, unsigned int bomb) : character(pos, color, speed, power, bomb)
{
  this->_name = name;
  this->Score = 0;
}

Player::~Player()
{
}

std::string const &Player::getName() const
{return this->_name;}

bool	Player::isPlayerBomb(Bomb const *bomb) const
{
  std::list<Bomb *>::const_iterator it;

  for (it = this->BombPlanted.begin(); it != this->BombPlanted.end(); ++it)
    {
      if ((*it) == bomb)
	return true;
    }
  return false;
}

void	Player::setScore(int a)
{
  this->Score = a;
}

int	Player::getScore() const
{
  return this->Score;
}
