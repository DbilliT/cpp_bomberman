//
// menu.hh for menu in /home/bechad_p/rendu/cpp_bomberman/project/UI/menu
// 
// Made by Pierre Bechade
// Login   <bechad_p@epitech.net>
// 
// Started on  Mon May 11 16:21:10 2015 Pierre Bechade
// Last update Sun Jun 14 17:20:27 2015 Pierre Bechade
//

#ifndef __MENU_HPP__
# define __MENU_HPP__

class Menu
{
public:
  Menu();
  ~Menu();
  //------------GETTER-------------//
  const std::vector<std::pair<int, std::string> >	&getHighscore();
  const std::string					&getContinue();
  const std::vector<std::string>			&getFiles();
  const std::vector<std::string>			&getCredit();
  const std::vector<std::string>			&getMaps();
  bool							getIsContinue();
  //------------SETTER-------------//
  void							setHighscore();
  void							setContinue();
  void							setFiles();
  void							setMaps();
  void							setCredit();
  //------------FUNCTS-------------//
  void							load();
  void							writeHighscore();
  void							addHighscore(int score, const std::string &name);
  void							quit();
private:
  std::string						_continue;
  std::vector<std::string>				_files;
  std::vector<std::string>				_Maps;
  std::vector<std::pair <int, std::string> >		_highscore;
  std::vector<std::string>				_credit;
  bool							_isContinue;
};

#endif /* __MENU_HPP__ */
