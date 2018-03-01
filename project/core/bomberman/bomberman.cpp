//
// bomberman.cpp for bomberman.cpp in /home/bechad_p/rendu/cpp_bomberman/project/core/bomberman
// 
// Made by Pierre Bechade
// Login   <bechad_p@epitech.net>
// 
// Started on  Mon May 11 17:39:56 2015 Pierre Bechade
// Last update Sun Jun 14 17:50:09 2015 Caltraba Mickael
//

#include "bomberman.hpp"

Bomberman::Bomberman::Bomberman() : _end(false)
{
  this->run();
}

Bomberman::Bomberman::~Bomberman()
{
}

int	Bomberman::Bomberman::run()
{
  SoundManager& sound=SoundManager::Instance();
  sound.loadSound();
  sound.loadMusic();

  Menu_SDL	menu(&sound);
  menu.main_menu();
  return (EXIT_SUCCESS);
}

int	Bomberman::main()
{
  srand(time(NULL));
  try
    {
      Bomberman init;
    }
  catch (std::bad_alloc &e)
    {
      std::cerr << e.what() << std::endl;
      return (EXIT_FAILURE);
    }
  catch (std::invalid_argument &e)
    {
      std::cerr << "Invalid argument: " << e.what() << std::endl;
      return (EXIT_FAILURE);
    }
  catch (Wrong_file &e)
    {
      std::exit(0);
      std::cerr << "This file is unreachable or does'nt exist :" << e.what() << std::endl;
      return (EXIT_FAILURE);
    }
  catch (SoundManagerIssue &e)
    {
      std::cerr << "Error on FMOD : " << e.what() << std::endl;
      return (EXIT_FAILURE);
    }
  catch (std::runtime_error &e)
    {
      std::cerr << e.what() << std::endl;
      return (EXIT_FAILURE);
    }
  catch (std::out_of_range &e)
    {
      std::cerr << e.what() << std::endl;
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
