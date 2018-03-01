//
// CharacterUI.hpp for  in /home/calatr_m/cpp_rendu/CPP/cpp_bomberman/project/UI/include
// 
// Made by Caltraba Mickael
// Login   <calatr_m@epitech.net>
// 
// Started on  Sat May 23 13:56:49 2015 Caltraba Mickael
// Last update Sun Jun 14 08:07:35 2015 Caltraba Mickael
//

#ifndef _CHARACTERUI_HPP_
# define _CHARACTERUI_HPP_

#include <Model.hh>
#include "Cube.hpp"
#include "Bot.hpp"
#include "Player.hpp"

class CharacterUI : public AObject
{
public:
  typedef void	(CharacterUI::*fkey)();
  typedef void	(CharacterUI::*fexec)();

  CharacterUI(int, int, float, float, int, character *, std::list<Bomb *> &);
  ~CharacterUI();

  virtual bool		initialize();
  virtual void		checkKey(gdl::Clock const &, gdl::Input &,
				 SDL_Joystick *);
  virtual void		update(gdl::Input &, float, SDL_Joystick *);
  virtual void		draw(gdl::AShader &, gdl::Clock const &);

  void			initPlayer();

  void			checkIA(gdl::Clock const &, Mouvement);
  void			updateIA(Mouvement, float);
  bool			updateBomb(gdl::Input &, SDL_Joystick *);

  float			getMove() const;
  Mouvement		getKey() const;
  bool			getPlayer() const;
  std::list<Bomb *>	getBomb() const;

  void			setAnim();
  bool			win();
  
private:
  gdl::Model		_model;
  glm::vec3		_vec;
  float			_transl;

  float			_speed;
  bool			_run;
  bool			_anim;
  Mouvement		_key;

  int			_nb;
  character		*_player;
  std::list<Bomb *>	&_bomb;

  std::map<int, std::pair<fkey, fexec> >	_input;
  void			keyUp();
  void			keyDown();
  void			keyLeft();
  void			keyRight();

  void			execUp();
  void			execDown();
  void			execLeft();
  void			execRight();
  
};

#endif
