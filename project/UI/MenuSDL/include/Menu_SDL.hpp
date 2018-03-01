#ifndef MENU_SDL_HPP_
#define MENU_SDL_HPP_

#define POSX 270
#define MAX(x, y) ((x)>(y)?(x):(y))

#include <fstream>
#include <cstdlib>

class Menu_SDL
{
private:
  SDL_Class	*_SDL;
  Menu		*_CoreMenu;
  typedef void (Menu_SDL::*function)();
  std::vector<function> m_menu;
  std::vector<function> p_menu;
  int			_sound;
  int			_effect;
  bool			_cam;
public:
  Menu_SDL(SoundManager *m_instance);
  ~Menu_SDL();
  void		main_menu();
  void		init();
protected:
  void		play_menu();
  void		highscore_menu();
  void		option_menu();
  void		credit_menu();
  void		new_menu();
  void		load_menu();
  void          advanced_menu();
  void          aff_reso(int, int);
  void          aff_enable(int,  bool);
  void		put_font();
  const std::pair<std::string, std::string>  	name(int);
  int		input();
  void		map_inf();
  void		map_gen(int, int, std::string const &);
  void		title(std::string);
  void		end(std::string const &, int);
  void		select(int);
  void		interv(int, int, int);
  void		jauge(int, int, int, int);
  void		lauchGame(bool, bool, int, int, int, int, const std::string &, const std::pair<std::string, std::string> &);
  SoundManager	*_MSound;
};

#endif
