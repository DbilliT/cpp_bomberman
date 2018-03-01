//
// maps.hh for maps in /home/bechad_p/rendu/cpp_bomberman/project/core/game/map
// 
// Made by Pierre Bechade
// Login   <bechad_p@epitech.net>
// 
// Started on  Thu May 14 13:45:39 2015 Pierre Bechade
// Last update Sun Jun 14 15:01:51 2015 paul david
//

#ifndef __MAPS_HPP__
# define __MAPS_HPP__

#include "CaseFactory.hpp"
#include "Bot.hpp"
#include "Player.hpp"

class Maps
{
public:
  Maps(const std::string &pfile, unsigned int nb_human, unsigned int nb_IA, const std::pair<std::string, std::string> &names);
  Maps(const std::pair<unsigned int, unsigned int> &size_map, unsigned int nb_human, unsigned int nb_IA, const std::pair<std::string, std::string> &names);
  Maps(const std::string &pfile);
  ~Maps();

  void			initMap();
  void			parseMap(const std::string &pfile, bool Continue);
  void			randomMap();
  void			randomFill();
  void			SpawnPoint();
  void			destroyWall(const std::pair<int, int> &);
  bool			algoWall(const std::pair<int, int> &);
  bool			placePlayer();
  char			interpreteType(char *type);
  bool			isPlacable(std::pair<int, int> const &pos_wall, std::vector<ICase **> &tmp, int nb_empty);
  bool			isOnlyWall() const;
  void			algoPosition();

  const std::pair<unsigned int, unsigned int>					&getSizeMap() const;
  const std::vector<std::vector<std::pair<unsigned int, unsigned int> >	>	&getPosPlayers() const;
  std::list<Player>								const &getInfoPlayers() const;
  std::list<Bot>								const &getInfoBot() const;
  std::vector<ICase **> const								&getMap() const;

private:
  unsigned int	_nb_human;
  unsigned int	_nb_IA;

  std::vector<std::vector<std::pair<unsigned int, unsigned int> > >	_pos_players;
  std::vector<std::pair<unsigned int, unsigned int> >			_pos_tmp;

  std::list<Player>					_info_players;
  std::list<Bot>     					_info_IA;

  std::pair<unsigned int, unsigned int>			_size_map;
  std::pair<std::string, std::string>			_names;
  std::vector<ICase **>					_map;
  std::vector<ICase **>					_tmp_map;
  CaseFactory						*_factory;
};

#endif /* __MAPS_HPP__ */
