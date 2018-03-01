//
// Save.hpp for Save in /home/bechad_p/rendu/cpp_bomberman/project/core/game/Save
// 
// Made by Pierre Bechade
// Login   <bechad_p@epitech.net>
// 
// Started on  Mon Jun  8 17:11:48 2015 Pierre Bechade
// Last update Mon Jun  8 18:44:19 2015 Pierre Bechade
//

#ifndef __SAVE_HPP__
# define __SAVE_HPP__

class Save
{
public:
  Save(const std::vector<ICase **> &maps, const std::pair<unsigned int, unsigned int> &size_map, const std::list<Player> &players, const std::list<Bot> &bot, int widht, int height);
  ~Save();
  void			CreateSave();
  void			xmlSave() const;
  void			screenSave() const;
  std::string    	currentDateTime();

private:
  std::vector<ICase **>			_map;
  std::pair<unsigned int, unsigned int> _size_map;
  std::list<Player>                     _info_players;
  std::list<Bot>                        _info_IA;
  int					_widht;
  int					_height;
  std::string				_ctime;
};
#endif /* __SAVE_HPP__ */
