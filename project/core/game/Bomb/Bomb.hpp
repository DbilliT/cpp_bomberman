#ifndef BOMB_HPP_
#define BOMB_HPP_

#include "CaseAction.hpp"

class Player;
class Bot;

class Bomb
{
public:
  Bomb(int, int, int);
  ~Bomb();
private:
  CaseAction		BoxInteract;
  std::pair <unsigned int, unsigned int>	_xy;
  int			_timeRest;
  int			_power;
  clock_t		TimePlant;
  clock_t		TimeElapsed;
  bool			Alive;
  void			destroy(std::vector<ICase **> &, int, int, int, int, std::list<IBonus *> &, std::list<std::pair<unsigned int, unsigned int> > &BoxDestroyed);
  int			kill(std::list <Player> &, std::list<Bot> &, int, int, int, int);
public:
  bool						isAlive() const;
  std::pair <unsigned int, unsigned int>	getYX() const;
  unsigned int					getY() const;
  unsigned int					getX() const;
  
  int			getTimeRest() const;
  int			getPower() const;  
  std::list<std::pair<unsigned int, unsigned int> >			countdown(std::vector<ICase **> &, std::list <Player> &player, std::pair<unsigned int, unsigned int> const & size_map, std::list<IBonus *> &Bonus, std::list<Bot> &bot, std::list<Bomb *> &bombs);
  void			explode(std::vector<ICase **> &, std::list<Player> & player, std::pair<unsigned int, unsigned int> const & size_map, std::list<IBonus *> &Bonus, std::list<Bot> & bot, std::list<Bomb *> &bombs, std::list<std::pair<unsigned int, unsigned int> > &BoxDestroyed);
  void			chainExplosion(std::vector<ICase **> &Map, std::list <Player> & player, std::pair<unsigned int, unsigned int> const &size_map, std::list<IBonus *> &Bonus, std::list<Bot> &bot, std::list<Bomb *> &bombs, std::list<std::pair<unsigned int, unsigned int> > &BoxDestroyed, int H, int B, int G, int D);

};

#endif
