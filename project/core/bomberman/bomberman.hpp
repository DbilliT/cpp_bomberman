//
// bomberman.hpp for bombermap.hpp in /home/bechad_p/rendu/cpp_bomberman/project/core/bomberman
// 
// Made by Pierre Bechade
// Login   <bechad_p@epitech.net>
// 
// Started on  Mon May 11 17:40:05 2015 Pierre Bechade
// Last update Sun Jun 14 20:08:44 2015 Pierre Bechade
//

#ifndef __BOMBERMAN_HPP__
# define __BOMBERMAN_HPP__

/* C++ LIB */
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <fstream>
#include <list>
#include <exception>
#include <stdexcept>
#include <vector>
#include <ctime>
#include <map>
#include <algorithm>
#include <cmath>
/* C LIB */
#include <dirent.h>
#include <sys/types.h>
/* XML LIB */
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
/* BOMBERMAN CORE LIB */
#include "maps.hpp"
#include "exception.hpp"
#include "menu.hpp"
/* UI LIB */
#include "GameEngine.hpp"
/* SOUND LIB */
#include "SoundManager.hpp"
/* MENU SDL */
#include "SDL_Class.hpp"
#include "Menu_SDL.hpp"
/* GAME */
#include "Bomb.hpp"
#include "Player.hpp"
#include "Save.hpp"
//_____________________________________//

namespace Bomberman
{
  class Bomberman
  {
  public:
    Bomberman();
    ~Bomberman();
    int run();
  private:
    bool _end;
  };
  int	main();
}

#endif /* __BOMBERMAN_HPP__ */
