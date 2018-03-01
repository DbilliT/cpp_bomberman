#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

#include <utility>
#include <map>
#include <iostream>
#include <string>
#include "Bomb.hpp"

enum Mouvement
  {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
    NONE = 4
  };

class IBonus;

class character
{
public:
  character(std::pair<double, double> const &pos, unsigned int color);
  character(std::pair<double, double> const &pos, unsigned int color, float speed, unsigned int power, unsigned int bomb);
  ~character();
private:
  std::pair<bool, double>                                           up(std::vector<ICase **> const &, std::list<Bomb *> const &, std::pair<unsigned int, unsigned int> const &, double speed);
  std::pair<bool, double>                                           down(std::vector<ICase **> const &, std::list<Bomb *> const &, std::pair<unsigned int, unsigned int> const &, double speed);
  std::pair<bool, double>                                           left(std::vector<ICase **> const &, std::list<Bomb *> const &, std::pair<unsigned int, unsigned int> const &, double speed);
  std::pair<bool, double>                                           right(std::vector<ICase **> const &, std::list<Bomb *> const &, std::pair<unsigned int, unsigned int> const &, double speed);

  typedef std::pair<bool, double> (character::*fmove)(std::vector<ICase **> const &, std::list<Bomb *> const &, std::pair<unsigned int, unsigned int> const &, double speed);

  std::map<Mouvement, fmove> move;
protected:
  std::pair <double, double>	_xy;
  const unsigned int				_color;
  bool						_kick;
  unsigned int					_nbBomb;
  unsigned int					_bombUsed;
  unsigned int					_bombPower;
  float					_speed;
  bool						Alive;
  std::list<Bomb *>				BombPlanted;
public:
  /*----------get----------*/
  bool						isAlive() const;
  std::pair <double, double>			getXY() const;
  double					getX() const;
  double					getY() const;
  bool						getKick() const;
  unsigned int					getNbBomb() const;
  unsigned int					getBombUsed() const;
  unsigned int					getBombPower() const;
  float					getSpeed() const;
  unsigned int					getColor() const;
  /*----------set----------*/
  void						setAlive(bool a);
  void						setXY(double, double);
  void						setX(double);
  void						setY(double);
  void						setKick(bool);
  void						setNbBomb(unsigned int);
  void						setBombUsed(unsigned int);
  void						setBombPower(unsigned int);
  void						setSpeed(float);
  /*----------fct----------*/
  bool						placeBomb(std::list<Bomb *> &Bombs);
  std::pair<bool, double>						Move(Mouvement, std::vector<ICase **> const &, std::list<Bomb *> const &, std::pair<unsigned int, unsigned int> const &, double speed);
  void						checkBonus(std::list<IBonus *> &);
  
};

#endif
