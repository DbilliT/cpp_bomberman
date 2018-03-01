#include <cmath>
#include "character.hpp"
#include "IBonus.hpp"

character::character(std::pair<double, double> const &pos, unsigned int color) : _xy(pos), _color(color), _kick(false), _nbBomb(1), _bombUsed(0), _bombPower(2), _speed(3)
{
  this->Alive = true;
  this->_xy.first += 0.5;
  this->_xy.second += 0.5;
  this->move[UP] = &character::up;
  this->move[DOWN] = &character::down;
  this->move[LEFT] = &character::left;
  this->move[RIGHT] = &character::right;
}
character::character(std::pair<double, double> const &pos, unsigned int color, float speed, unsigned int power, unsigned int bomb) :  _xy(pos), _color(color), _kick(false), _nbBomb(bomb), _bombUsed(0), _bombPower(power), _speed(speed)
{
  this->Alive = true;
  this->_xy.first += 0.5;
  this->_xy.second += 0.5;
  this->move[UP] = &character::up;
  this->move[DOWN] = &character::down;
  this->move[LEFT] = &character::left;
  this->move[RIGHT] = &character::right;
}
character::~character()
{}

/*----------get----------*/
bool	character::isAlive() const
{return this->Alive;}
std::pair <double, double>	character::getXY() const
{return this->_xy;}
double		character::getY() const
{return this->_xy.first;}
double		character::getX() const
{return this->_xy.second;}
bool			character::getKick() const
{return this->_kick;}
unsigned int		character::getNbBomb() const
{return this->_nbBomb;}
unsigned int		character::getBombUsed() const
{return this->_bombUsed;}
unsigned int		character::getBombPower() const
{return this->_bombPower;}
float		character::getSpeed() const
{return this->_speed;}
unsigned int		character::getColor() const
{return this->_color;}
/*----------set----------*/
void			character::setAlive(bool a)
{this->Alive = a;}
void			character::setX(double x)
{this->_xy.second = x;}
void			character::setY(double y)
{this->_xy.first = y;}
void			character::setKick(bool kick)
{this->_kick = kick;}
void			character::setNbBomb(unsigned int nb)
{this->_nbBomb = nb;}
void			character::setBombUsed(unsigned int nb)
{this->_bombUsed = nb;}
void			character::setBombPower(unsigned int nb)
{this->_bombPower = nb;}
void			character::setSpeed(float nb)
{
  if (nb <= 6)
    this->_speed = nb;
}
void			character::setXY(double y, double x)
{this->_xy.first = y;
this->_xy.second = x;}
/*----------fct----------*/
void			character::checkBonus(std::list<IBonus *> &Bonus)
{
  std::list<IBonus *>::iterator it;

  for (it = Bonus.begin(); it != Bonus.end(); ++it)
    {
      if ((*it)->getPos().first == static_cast<unsigned int>(this->_xy.first) && (*it)->getPos().second == static_cast<unsigned int>(this->_xy.second))
	{
	  (*it)->pickedUp(*this);
	  Bonus.erase(it);
	  break;
	}
    }
}

bool pop_bomb (const Bomb *value)
{
  return (!value->isAlive());
}

bool			character::placeBomb(std::list<Bomb *> &Bombs)
{
  this->BombPlanted.remove_if(pop_bomb);
  std::list<Bomb *>::iterator it;
  for (it = Bombs.begin(); it != Bombs.end(); ++it)
    {
      if ((*it)->getY() == static_cast<unsigned int>(this->_xy.first) && (*it)->getX() == static_cast<unsigned int>(this->_xy.second))
	return false;
    }
  _bombUsed = this->BombPlanted.size();
  if (_bombUsed < _nbBomb)
    {
      Bomb	*bomb = new Bomb(this->_xy.second, this->_xy.first, this->_bombPower);
      this->BombPlanted.push_back(bomb);
      Bombs.push_back(bomb);
      return true;
    }
  return false;
}
std::pair<bool, double>			character::Move(Mouvement direction, std::vector<ICase **> const &Map, std::list<Bomb *> const &bombs, std::pair<unsigned int, unsigned int> const &size, double speed)
{
  if (speed >= 1)
    speed = 0.9;
  if (this->move.find(direction) == this->move.end())
    return std::make_pair(false, 0);
  return ((this->*move[direction])(Map, bombs, size, speed));
}

std::pair<bool, double>			character::down(std::vector<ICase **> const &Map, std::list<Bomb *> const &bombs, std::pair<unsigned int, unsigned int> const &size, double speed)
{
  if (ceil(this->_xy.first) == size.first)
  {
    if (size.first - this->_xy.first > 0.3)
      {
	if ((size.first - this->_xy.first) - speed > 0.3)
	  this->_xy.first += speed;
	else
	  {
	    if ((speed = size.first - this->_xy.first - 0.3) < 0.9999)
	      return std::make_pair(false, 0);
	    this->_xy.first += speed;
	  }
	return std::make_pair(true,speed);
      }
    return std::make_pair(false, 0);
  }
  if (Map[static_cast<int>(ceil(this->_xy.first))][static_cast<int>(floor(this->_xy.second))]->isFree())
    {
      if (floor(this->_xy.second) > 0 )
	if (Map[static_cast<int>(floor(this->_xy.first))][static_cast<int>(floor(this->_xy.second) - 1)]->isFree()
	    && !Map[static_cast<int>(ceil(this->_xy.first))][static_cast<int>(floor(this->_xy.second)) - 1]->isFree()
	    && (this->_xy.second - floor(this->_xy.second)) <= 0.25
	    && (ceil(this->_xy.first) - this->_xy.first)  < 0.3)
	  return std::make_pair(false,0);
      if (ceil(this->_xy.second) < size.second)
	if (Map[static_cast<int>(floor(this->_xy.first))][static_cast<int>(ceil(this->_xy.second))]->isFree()
	  && !Map[static_cast<int>(ceil(this->_xy.first))][static_cast<int>(ceil(this->_xy.second))]->isFree()
	    && (ceil(this->_xy.second) - this->_xy.second) <= 0.25
	    && (ceil(this->_xy.first) - this->_xy.first) < 0.3)
	  return std::make_pair(false,0);
      for (std::list<Bomb *>::const_iterator it = bombs.begin(); it != bombs.end(); ++it)
	if (ceil(this->_xy.first) == (*it)->getY() && floor(this->_xy.second) == (*it)->getX())
	  {
	    if (ceil(this->_xy.first) - this->_xy.first - speed > 0.3)
	      this->_xy.first += speed;
	    else
	      {
		if ((speed = ceil(this->_xy.first) - this->_xy.first - 0.3) < 0.9999)
		  return std::make_pair(false, 0);
		this->_xy.first += speed;
	      }
	    return std::make_pair(true, speed);
	  }
      this->_xy.first += speed;
      return std::make_pair(true, speed);
    }
  else if ((ceil(this->_xy.first) - this->_xy.first) > 0.3)
    {
      if (ceil(this->_xy.first) - this->_xy.first - speed > 0.3)
	this->_xy.first += speed;
      else
	{
	  if ((speed = ceil(this->_xy.first) - this->_xy.first - 0.3) < 0.9999)
	    return std::make_pair(false, 0);
	  this->_xy.first += speed;
	}
      return std::make_pair(true,speed);
    }
  return std::make_pair(false, 0);
}

std::pair<bool, double>			character::up(std::vector<ICase **> const &Map, std::list<Bomb *> const &bombs, std::pair<unsigned int, unsigned int> const &size, double speed)
{
  unsigned int mY = floor(this->_xy.first) - 1;
  if (ceil(this->_xy.first) == 0)
    mY = floor(this->_xy.first);
  if (floor(this->_xy.first) == 0)
    {
      if (this->_xy.first > 0.3)
	{
	  if (this->_xy.first - speed > 0.3)
	    this->_xy.first -= speed;
	  else
	    {
	      if ((speed = this->_xy.first - 0.3) < 0.9999)
		return std::make_pair(false, 0);
	      this->_xy.first -= speed;
	    }
	  return std::make_pair(true,speed);
	}
      return std::make_pair(false, 0);
    }
  if (Map[static_cast<int>(floor(this->_xy.first) - 1)][static_cast<int>(floor(this->_xy.second))]->isFree())
    {
      if (floor(this->_xy.second) > 0)
	if (Map[static_cast<int>(floor(this->_xy.first))][static_cast<int>(floor(this->_xy.second) - 1)]->isFree()
	    && !Map[mY][static_cast<int>(floor(this->_xy.second)) - 1]->isFree()
	    && (this->_xy.second - floor(this->_xy.second)) < 0.25
	    && (this->_xy.first - floor(this->_xy.first)) < 0.3)
	  return std::make_pair(false, 0);
      if (ceil(this->_xy.second) < size.second)
	if (Map[static_cast<int>(floor(this->_xy.first))][static_cast<int>(ceil(this->_xy.second))]->isFree()
	  && !Map[mY][static_cast<int>(ceil(this->_xy.second))]->isFree()
	    && (ceil(this->_xy.second) - this->_xy.second) < 0.25
	    && (this->_xy.first - floor(this->_xy.first)) < 0.3)
	  return std::make_pair(false, 0);
      for (std::list<Bomb *>::const_iterator it = bombs.begin(); it != bombs.end(); ++it)
	if (floor(this->_xy.first) - 1 == (*it)->getY() && floor(this->_xy.second) == (*it)->getX())
	  {
	    if ((this->_xy.first - (floor(this->_xy.first))) - speed > 0.3)
	      this->_xy.first -= speed;
	    else
	      {
		if ((speed = this->_xy.first - floor(this->_xy.first) - 0.3) < 0.9999)
		  return std::make_pair(false, 0);
		this->_xy.first -= speed;
	      }
	    return std::make_pair(true, speed);
	  }
      this->_xy.first -= speed;
      return std::make_pair(true, speed);
    }
  else if ((this->_xy.first - (floor(this->_xy.first))) > 0.3)
    {
      if ((this->_xy.first - (floor(this->_xy.first))) - speed > 0.3)
	this->_xy.first -= speed;
      else
	{
	  if ((speed = this->_xy.first - floor(this->_xy.first) - 0.3) < 0.9999)
	    return std::make_pair(false, 0);
	  this->_xy.first -= speed;
	}
      return std::make_pair(true, speed);
    }
  return std::make_pair(false, 0);
}

std::pair<bool, double>	character::right(std::vector<ICase **> const &Map, std::list<Bomb *> const &bombs, std::pair<unsigned int, unsigned int> const &size, double speed)
{
  if (ceil(this->_xy.second) == size.second)
    {
      if (ceil(this->_xy.second) - this->_xy.second > 0.3)
	{
	  if (ceil(this->_xy.second) - this->_xy.second - speed > 0.3)
	    this->_xy.second += speed;
	  else
	    {
	      if ((speed = size.second - this->_xy.second - 0.3) < 0.9999)
		return std::make_pair(false, 0);
	      this->_xy.second += speed;
	    }
	  return std::make_pair(true, speed);
	}
      return std::make_pair(false, 0);
    }
  if (Map[static_cast<int>(floor(this->_xy.first))][static_cast<int>(ceil(this->_xy.second))]->isFree())
    {
      if (floor(this->_xy.first) > 0 )
	if (Map[static_cast<int>(floor(this->_xy.first) - 1)][static_cast<int>(floor(this->_xy.second))]->isFree()
	    && !Map[static_cast<int>(floor(this->_xy.first) - 1)][static_cast<int>(ceil(this->_xy.second))]->isFree()
	    && (this->_xy.first - floor(this->_xy.first)) <= 0.25
	    && (ceil(this->_xy.second) - this->_xy.second)  < 0.3)
	  return std::make_pair(false,0);
      if (ceil(this->_xy.first) < size.first)
	if (Map[static_cast<int>(ceil(this->_xy.first))][static_cast<int>(floor(this->_xy.second))]->isFree()
	  && !Map[static_cast<int>(ceil(this->_xy.first))][static_cast<int>(ceil(this->_xy.second))]->isFree()
	    && (ceil(this->_xy.first) - this->_xy.first) <= 0.25
	    && (ceil(this->_xy.second) - this->_xy.second) < 0.3)
	  return std::make_pair(false,0);
      for (std::list<Bomb *>::const_iterator it = bombs.begin(); it != bombs.end(); ++it)
	if (floor(this->_xy.first) == (*it)->getY() && ceil(this->_xy.second) == (*it)->getX())
	  {
	    if (ceil(this->_xy.second) - this->_xy.second - speed > 0.3)
	      this->_xy.second += speed;
	    else
	      {
		if ((speed = ceil(this->_xy.second) - this->_xy.second - 0.3) < 0.9999)
		  return std::make_pair(false, 0);
		this->_xy.second += speed;
	      }
	    return std::make_pair(true, speed);
	  }
      this->_xy.second += speed;
      return std::make_pair(true, speed);
    }
  else if ((ceil(this->_xy.second) - this->_xy.second) > 0.3)
    {
      if (ceil(this->_xy.second) - this->_xy.second - speed > 0.3)
	this->_xy.second += speed;
      else
	{
	  if ((speed = ceil(this->_xy.second) - this->_xy.second - 0.3) < 0.9999)
	    return std::make_pair(false, 0);
	  this->_xy.second += speed;
	}
      return std::make_pair(true, speed);
    }
  return std::make_pair(false, 0);;
}

std::pair<bool, double>	character::left(std::vector<ICase **> const &Map, std::list<Bomb *> const &bombs, std::pair<unsigned int, unsigned int> const &size, double speed)
{
  unsigned int mX = floor(this->_xy.second) - 1;
  if (floor(this->_xy.second) == 0)
    mX = floor(this->_xy.second);
  if (floor(this->_xy.second) == 0)
    {
      if (this->_xy.second > 0.3)
	{
	  if (this->_xy.second - speed > 0.3)
	    this->_xy.second -= speed;
	  else
	    {
	      if ((speed = this->_xy.second - 0.3) < 0.9999)
		return std::make_pair(false, 0);
	      this->_xy.second -= speed;
	    }
	  return std::make_pair(true, speed);
	}
      return std::make_pair(false, 0);
    }
  if (Map[static_cast<int>(floor(this->_xy.first))][static_cast<int>(floor(this->_xy.second) - 1)]->isFree())
    {
      if (floor(this->_xy.first) > 0)
	if (Map[static_cast<int>(floor(this->_xy.first) - 1)][static_cast<int>(floor(this->_xy.second))]->isFree()
	    && !Map[static_cast<int>(floor(this->_xy.first) - 1)][mX]->isFree()
	    && (this->_xy.first - floor(this->_xy.first)) <= 0.25
	    && (this->_xy.second - floor(this->_xy.second)) < 0.3)
	  return std::make_pair(false, 0);
      if (ceil(this->_xy.first) < size.first)
	if (Map[static_cast<int>(ceil(this->_xy.first))][static_cast<int>(floor(this->_xy.second))]->isFree()
	  && !Map[static_cast<int>(ceil(this->_xy.first))][mX]->isFree()
	    && (ceil(this->_xy.first) - this->_xy.first) <= 0.25
	    && (this->_xy.second - floor(this->_xy.second)) < 0.3)
	  return std::make_pair(false, 0);
      for (std::list<Bomb *>::const_iterator it = bombs.begin(); it != bombs.end(); ++it)
	if (floor(this->_xy.first) == (*it)->getY() && (floor(this->_xy.second) - 1) == (*it)->getX())
	  {
	    if (this->_xy.second - floor(this->_xy.second) - speed > 0.3)
	      this->_xy.second -= speed;
	    else
	      {
		if ((speed = this->_xy.second - floor(this->_xy.second) - 0.3) < 0.9999)
		  return std::make_pair(false, 0);
		this->_xy.second -= speed;
	      }
	    return std::make_pair(true, speed);
	  }
      this->_xy.second -= speed;
      return std::make_pair(true, speed);
    }
  else if ((this->_xy.second - (floor(this->_xy.second))) > 0.3)
    {
      if (this->_xy.second - floor(this->_xy.second) - speed > 0.3)
	this->_xy.second -= speed;
      else
	{
	  if ((speed = this->_xy.second - floor(this->_xy.second) - 0.3) < 0.9999)
	    return std::make_pair(false, 0);
	  this->_xy.second -= speed;
	}
      return std::make_pair(true, speed);
    }
  return std::make_pair(false, 0);
}

