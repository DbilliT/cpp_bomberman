#include "bomberman.hpp"

Bomb::Bomb(int x, int y, int power)
{
  this->TimeElapsed = 0;
  this->_xy.first = y;
  this->_xy.second = x;
  this->_power = power;
  this->TimePlant = clock();
  this->Alive = true;
}

Bomb::~Bomb()
{
}

bool	Bomb::isAlive() const
{
  return this->Alive;
}

std::pair <unsigned int, unsigned int>	Bomb::getYX() const
{return this->_xy;}

unsigned int	Bomb::getY() const
{return this->_xy.first;}

unsigned int	Bomb::getX() const
{return this->_xy.second;}

int			Bomb::getTimeRest() const
{return this->_timeRest;}

int			Bomb::getPower() const
{return this->_power;}

std::list<std::pair<unsigned int, unsigned int> >	Bomb::countdown(std::vector<ICase **> &Map, std::list <Player> & player, std::pair<unsigned int, unsigned int> const & size_map, std::list<IBonus *> &Bonus, std::list<Bot> &bot, std::list<Bomb *> &bombs)
{
  (void)Map; (void)player;(void)size_map; (void)Bonus;
  std::list<std::pair<unsigned int, unsigned int> > BoxDestroyed;
  TimeElapsed += clock() - this->TimePlant;
  if (static_cast<float>(TimeElapsed)/CLOCKS_PER_SEC >= 15.0)
    {
      this->explode(Map, player, size_map, Bonus, bot, bombs, BoxDestroyed);
      return BoxDestroyed;
    }
  return BoxDestroyed;
}

void	Bomb::explode(std::vector<ICase **> &Map, std::list <Player> & player, std::pair<unsigned int, unsigned int> const &size_map, std::list<IBonus *> &Bonus, std::list<Bot> &bot, std::list<Bomb *> &bombs, std::list<std::pair<unsigned int, unsigned int> > &BoxDestroyed)
{
  int	H;
  int	B;
  int	G;
  int	D;
  int	score = 0;
  std::list<Player>::iterator it;
  std::list<Bomb *>::iterator ite;

  for (it = player.begin(); it != player.end(); ++it)
    if ((*it).isPlayerBomb(this))
      break;
  this->Alive = false;
  B = (this->_xy.first == 0) ? 0 : 1;
  H = (this->_xy.first == size_map.first - 1) ? 0 : 1;
  G = (this->_xy.second == 0) ? 0 : 1;
  D = (this->_xy.second == size_map.second - 1) ? 0 : 1;
  while (static_cast<unsigned int>(this->_xy.first + H) < (size_map.first - 1) && H < (_power - 1) && Map[this->_xy.first + H][this->_xy.second]->isFree())
    {
      for (ite = bombs.begin(); ite != bombs.end(); ++ite)
	{
	  if ((*ite)->getY() == this->_xy.first + H)
	    break;
	}
      if (ite != bombs.end())
	  break;
      ++H;
    }
  while ((this->_xy.first - B) > 0 && B <(_power - 1) && Map[this->_xy.first - B][this->_xy.second]->isFree())
    {
      for (ite = bombs.begin(); ite != bombs.end(); ++ite)
	{
	  if ((*ite)->getY() == this->_xy.first - B)
	    break;
	}
      if (ite != bombs.end())
	  break;
      ++B;   
    }
  while ((this->_xy.second - G) > 0 && G < (_power - 1) && Map[this->_xy.first][this->_xy.second - G]->isFree())
    {
      for (ite = bombs.begin(); ite != bombs.end(); ++ite)
	{
	  if ((*ite)->getX() == this->_xy.second - G)
	    break;
	}
      if (ite != bombs.end())
	  break;
      ++G;
    }
  while (static_cast<unsigned int>(this->_xy.second + D) < (size_map.second - 1) && D < (_power - 1) && Map[this->_xy.first][this->_xy.second + D]->isFree())
    {
      for (ite = bombs.begin(); ite != bombs.end(); ++ite)
	{
	  if ((*ite)->getX() == this->_xy.second + D)
	    break;
	}
      if (ite != bombs.end())
	  break;
      ++D;
    }
  this->destroy(Map, H, B, G, D, Bonus, BoxDestroyed);
  score += this->kill(player, bot, H, B, G, D);
  score += BoxDestroyed.size();
  if (it != player.end())
    (*it).setScore((*it).getScore() + score);
  this->chainExplosion(Map, player, size_map, Bonus, bot, bombs, BoxDestroyed, H, B, G, D);
}

int	Bomb::kill(std::list <Player> & player, std::list <Bot> &bot, int H, int B, int G, int D)
{
  std::list<Player>::iterator it;
  int	score;
  
  for (it = player.begin(); it != player.end(); ++it)
    {
      if (floor((*it).getX()) == this->_xy.second && (floor((*it).getY()) >= this->_xy.first - B && floor((*it).getY()) <= this->_xy.first + H))
	{
	  (*it).setAlive(false);
	  score += 10;
	}
      else if (floor((*it).getY()) == this->_xy.first && (floor((*it).getX()) >=_xy.second - G && floor((*it).getX()) <= this->_xy.second + D))
	{
	  (*it).setAlive(false);
	  score += 10;
	}
    }
  std::list<Bot>::iterator ite;
  
  for (ite = bot.begin(); ite != bot.end(); ++ite)
    {
      if (floor((*ite).getX()) == this->_xy.second && (floor((*ite).getY()) >= this->_xy.first - B && floor((*ite).getY()) <= this->_xy.first + H))
	{
	  (*ite).setAlive(false);
	  score += 10;
	}
      else if (floor((*ite).getY()) == this->_xy.first && (floor((*ite).getX()) >=_xy.second - G && floor((*ite).getX()) <= this->_xy.second + D))
	{
	  (*ite).setAlive(false);
	  score += 10;
	}
    }
  return score;
}

void	Bomb::destroy(std::vector<ICase **> &Map, int H, int B, int G, int D, std::list<IBonus *> &Bonus, std::list<std::pair<unsigned int, unsigned int> > &BoxDestroyed)
{
  std::list<IBonus *>::iterator it;
  
  for (it = Bonus.begin(); it != Bonus.end(); ++it)
    {
      if (floor((*it)->getPos().second) == this->_xy.second && (floor((*it)->getPos().first) >= this->_xy.first - B && floor((*it)->getPos().first) <= this->_xy.first + H))
	{
	  delete (*it);
	  Bonus.erase(it);
	  --it;
	}
      else if (floor((*it)->getPos().first) == this->_xy.first && (floor((*it)->getPos().second) >=_xy.second - G && floor((*it)->getPos().second) <= this->_xy.second + D))
	{
	  delete (*it);
	  Bonus.erase(it);
	  --it;
	}
    }
  BoxInteract.DestroyBox(Map, std::make_pair<unsigned int, unsigned int &>(this->_xy.first + H, this->_xy.second), Bonus, BoxDestroyed);
  BoxInteract.DestroyBox(Map, std::make_pair<unsigned int, unsigned int &>(this->_xy.first - B, this->_xy.second), Bonus, BoxDestroyed);
  BoxInteract.DestroyBox(Map, std::make_pair<unsigned int &, unsigned int>(this->_xy.first, this->_xy.second + D), Bonus, BoxDestroyed);
  BoxInteract.DestroyBox(Map, std::make_pair<unsigned int &, unsigned int>(this->_xy.first, this->_xy.second - G), Bonus, BoxDestroyed);
}

void Bomb::chainExplosion(std::vector<ICase **> &Map, std::list <Player> & player, std::pair<unsigned int, unsigned int> const &size_map, std::list<IBonus *> &Bonus, std::list<Bot> &bot, std::list<Bomb *> &bombs, std::list<std::pair<unsigned int, unsigned int> > &BoxDestroyed, int H, int B, int G, int D)
{
  std::list<Bomb *>::iterator it;
  
  for (it = bombs.begin(); it != bombs.end(); ++it)
    {
      if ((*it)->isAlive() && floor((*it)->getX()) == this->_xy.second && (floor((*it)->getY()) >= this->_xy.first - B && floor((*it)->getY()) <= this->_xy.first + H))
	(*it)->explode(Map, player, size_map, Bonus, bot, bombs, BoxDestroyed);
	else if ((*it)->isAlive() && floor((*it)->getY()) == this->_xy.first && (floor((*it)->getX()) >=_xy.second - G && floor((*it)->getX()) <= this->_xy.second + D))
	  (*it)->explode(Map, player, size_map, Bonus, bot, bombs, BoxDestroyed);
    }
}
