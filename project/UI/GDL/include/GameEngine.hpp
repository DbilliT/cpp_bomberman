//
// GameEngine.hpp for  in /home/calatr_m/test
// 
// Made by Caltraba Mickael
// Login   <calatr_m@epitech.net>
// 
// Started on  Fri May 22 15:33:47 2015 Caltraba Mickael
// Last update Sun Jun 14 17:46:36 2015 Caltraba Mickael
//


#ifndef GRAPHICGDL_HPP_
# define GRAPHICGDL_HPP_

#pragma once

#include <Game.hh>
#include <vector>
#include <iostream>
#include <random>
#include <SdlContext.hh>
#include <BasicShader.hh>
#include "Cube.hpp"
#include "Ground.hpp"
#include "Camera.hpp"
#include "CharacterUI.hpp"
#include "TextureManager.hpp"
#include "maps.hpp"
#include "Skybox.hpp"
#include "Save.hpp"

class SoundManager;

class GameEngine : public gdl::Game
{
public:
  GameEngine(Maps &, bool);
  virtual ~GameEngine();

  virtual bool	initialize();
  virtual bool	update();
  virtual void	draw();

  bool		updateMap();
  bool		updatePlayers();
  bool		updateIA();
  bool		updateBomb(std::list<std::pair<unsigned int, unsigned int> >);
  bool		updateBonus();
  void		updateFire();

  bool		checkDraw(int, int);
  bool		checkFire(int, int, int, int, int,
			  std::list<std::pair<unsigned int, unsigned int> >);
  std::string	getWin() const;
  void		save() const;
  bool		lose();
  bool		winner();
  int		getScore() const;

  bool		initShader();
  bool		initPlayers();
  bool		initBots();

  bool		createMap();
  bool		createBomb();
  bool		createSkybox();
  bool		createBlock(int, int, int, float, float, float,
			    std::string const &);

  void		drawMenu();
  int		keyMenu(glm::vec3, float *);
  bool		createMapMenu();
  int		updateMenu();

private:
  gdl::SdlContext			_context;
  gdl::Clock				_clock;
  gdl::Input				_input;
  gdl::BasicShader			_shader;
  SoundManager				&_sound;
  std::vector<SDL_Joystick *>		_joy;

  Camera				_camera;
  TextureManager			_manager;
  bool					_pointView;
  int					_widht;
  int					_height;
  std::string				_win;

  std::vector<Skybox *>						_skybox;
  AObject							*_ground;
  std::list<AObject *>						_global;
  std::list<std::pair<AObject *, std::pair<float, float> > >	_inbreakable;
  std::list<std::pair<AObject *, std::pair<float, float> > >	_objects;
  std::list<std::pair<AObject *, std::pair<float, float> > >	_bombs;
  std::list<std::pair<AObject *, std::pair<float, float> > >	_fire;
  std::list<std::pair<AObject *, std::pair<float, float> > >    _bonusUI;

  std::vector<std::pair<AObject *, int> >	_menu;
  int						_cursor;

  Maps					_map_info;
  std::vector<ICase **>			_map;
  std::pair<unsigned int, unsigned int>	_size_map;

  std::vector<CharacterUI *>		_character;
  std::vector<CharacterUI *>		_ia;

  std::list<Player>			_players;
  std::list<Bomb *>			_bomb;
  std::list<Bot>			_bot;
  std::list<IBonus *>			_bonus;
};

#endif
