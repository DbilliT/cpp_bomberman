#ifndef BOT_HPP_
#define BOT_HPP_

#include "character.hpp"

class Bot : public character
{
public:
  Bot(std::pair<unsigned int, unsigned int> const &pos, unsigned int color);
  Bot(std::pair<unsigned int, unsigned int> const &pos, unsigned int color,  unsigned int speed, unsigned int power, unsigned int bomb);
  ~Bot();
};

#endif
