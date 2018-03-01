#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "character.hpp"

class Player : public character
{
public:
  Player(std::pair<unsigned int, unsigned int> const &pos, unsigned int color, std::string const &name);
  Player(std::pair<unsigned int, unsigned int> const &pos, unsigned int color, std::string const &name, unsigned int speed, unsigned int power, unsigned int bomb);
  ~Player();
  std::string const &getName() const;
  bool isPlayerBomb(Bomb const *bomb) const;
  void	setScore(int);
  int	getScore() const;
private:
  std::string _name;
  int	Score;
};

#endif
