//
// CharacterUI.cpp for  in /home/calatr_m/cpp_rendu/CPP/cpp_bomberman/project/UI
// 
// Made by Caltraba Mickael
// Login   <calatr_m@epitech.net>
// 
// Started on  Sat May 23 14:11:08 2015 Caltraba Mickael
// Last update Sun Jun 14 18:41:50 2015 Caltraba Mickael
//

#include "CharacterUI.hpp"

CharacterUI::CharacterUI(int x, int y, float z, float a, int nb,
			 character *player, std::list<Bomb *> &bomb) :
  AObject(x, y, z, a, a, a),
  _player(player),
  _bomb(bomb)
{
  this->_speed = 3;
  this->_run = false;
  this->_anim = false;
  this->_key = NONE;
  this->_nb = nb;
}

CharacterUI::~CharacterUI()
{
}

float			CharacterUI::getMove() const {return (this->_transl);}
bool			CharacterUI::getPlayer() const{return (this->_player);}
Mouvement		CharacterUI::getKey() const {return (this->_key);}
std::list<Bomb *>	CharacterUI::getBomb() const {return (this->_bomb);}

void	CharacterUI::initPlayer()
{
  if (this->_nb == 1)
    {
      this->_input[SDLK_UP].first = &CharacterUI::keyUp;
      this->_input[SDLK_DOWN].first = &CharacterUI::keyDown;
      this->_input[SDLK_LEFT].first = &CharacterUI::keyLeft;
      this->_input[SDLK_RIGHT].first = &CharacterUI::keyRight;
      this->_input[SDLK_UP].second = &CharacterUI::execUp;
      this->_input[SDLK_DOWN].second = &CharacterUI::execDown;
      this->_input[SDLK_LEFT].second = &CharacterUI::execLeft;
      this->_input[SDLK_RIGHT].second = &CharacterUI::execRight;
    }
  else if (this->_nb == 2)
    {
      this->_input[SDLK_z].first = &CharacterUI::keyUp;
      this->_input[SDLK_s].first = &CharacterUI::keyDown;
      this->_input[SDLK_q].first = &CharacterUI::keyLeft;
      this->_input[SDLK_d].first = &CharacterUI::keyRight;
      this->_input[SDLK_z].second = &CharacterUI::execUp;
      this->_input[SDLK_s].second = &CharacterUI::execDown;
      this->_input[SDLK_q].second = &CharacterUI::execLeft;
      this->_input[SDLK_d].second = &CharacterUI::execRight;
    }
  else
    {
      this->_input[0].first = &CharacterUI::keyUp;
      this->_input[1].first = &CharacterUI::keyDown;
      this->_input[2].first = &CharacterUI::keyLeft;
      this->_input[3].first = &CharacterUI::keyRight;
      this->_input[0].second = &CharacterUI::execUp;
      this->_input[1].second = &CharacterUI::execDown;
      this->_input[2].second = &CharacterUI::execLeft;
      this->_input[3].second = &CharacterUI::execRight;
    }
}

bool	CharacterUI::initialize()
{
  std::string	name = "./lib/LibBomberman_linux_x64/assets/Bot/Bomberman.fbx";

  if (this->_nb == 1)
    name = "./lib/LibBomberman_linux_x64/assets/Player1/Bomberman.fbx";
  else if (this->_nb == 2)
    name = "./lib/LibBomberman_linux_x64/assets/Player2/Bomberman.fbx";
  if (this->_model.load(name) == false)
    {
      std::cout << "Error : Load .fbx." << std::endl;
      return (false);
    }
  initPlayer();
  this->_model.createSubAnim(0, "stop", 40, 40);
  this->_model.createSubAnim(0, "run", 10, 21);
  this->_model.createSubAnim(0, "win", 40, 60);
  return (true);
}

void	CharacterUI::keyUp()
{
  this->_key = UP;
  this->_vec.z = -this->_transl;
  this->_run = true;
  rotate(glm::vec3(0, 1, 0), 180);
}
void	CharacterUI::keyDown()
{
  this->_key = DOWN;
  this->_vec.z = this->_transl;
  this->_run = true;
  rotate(glm::vec3(0, 1, 0), 0);
}
void	CharacterUI::keyLeft()
{
  this->_key = LEFT;
  this->_vec.x = -this->_transl;
  this->_run = true;
  rotate(glm::vec3(0, 1, 0), 270);
}
void	CharacterUI::keyRight()
{
  this->_key = RIGHT;
  this->_vec.x = this->_transl;
  this->_run = true;
  rotate(glm::vec3(0, 1, 0), 90);
}

void	CharacterUI::execUp(){this->_y -= this->_transl;}
void	CharacterUI::execDown(){this->_y += this->_transl;}
void	CharacterUI::execRight(){this->_x += this->_transl;}
void	CharacterUI::execLeft(){this->_x -= this->_transl;}

void	CharacterUI::checkKey(gdl::Clock const &clock, gdl::Input &input,
			      SDL_Joystick *joy)
{
  std::map<int, std::pair<fkey, fexec> >::iterator	it;
  bool	key = false;
  int i = 0;

  this->_vec = glm::vec3(0, 0, 0);
  this->_transl = this->_speed * clock.getElapsed();
  for (it = this->_input.begin(); it != this->_input.end(); ++it)
    {
      if (input.getKey(it->first))
	{
	  (this->*_input[it->first].first)();
	  key = true;
	  break;
	}
      else if (joy != NULL)
	{
	  Uint8 hatValue = SDL_JoystickGetHat(joy, i);
	  if (hatValue == SDL_HAT_DOWN && (key = true))
	    keyDown();
	  else if (hatValue == SDL_HAT_LEFT && (key = true))
	    keyLeft();
	  else if (hatValue == SDL_HAT_RIGHT && (key = true))
	    keyRight();
	  else if (hatValue == SDL_HAT_UP && (key = true))
	    keyUp();
	  ++i;
	}
    }
  if (!key)
    {
      this->_key = NONE;
      this->_run = false;
    }
  setAnim();
}

void	CharacterUI::checkIA(gdl::Clock const &clock, Mouvement input)
{
  if (input != NONE)
    {
      this->_vec = glm::vec3(0, 0, 0);
      this->_transl = this->_speed * clock.getElapsed();
      if (input != 4)
	(this->*_input[static_cast<int>(input)].first)();
      else
	{
	  this->_key = NONE;
	  this->_run = false;
	}
      setAnim();
    }
}

bool	CharacterUI::updateBomb(gdl::Input &input, SDL_Joystick *joy)
{
  if (this->_nb == 1 && (input.getKey(SDLK_RCTRL)
			 || (joy != NULL
			     && SDL_JoystickGetButton(joy, 0))))
    return (this->_player->placeBomb(this->_bomb));
  else if (this->_nb == 2 && (input.getKey(SDLK_SPACE)
			      || (joy != NULL
				  && SDL_JoystickGetButton(joy, 0))))
    return (this->_player->placeBomb(this->_bomb));
  return (false);
}

void	CharacterUI::update(gdl::Input &input, float speed,
			    SDL_Joystick *joy)
{
  std::map<int, std::pair<fkey, fexec> >::iterator	it;
  int i = 0;

  this->_transl = speed;
  this->_speed = static_cast<float>(this->_player->getSpeed());
  for (it = this->_input.begin(); it != this->_input.end(); ++it)
    {
      if (input.getKey(it->first))
	{
	  (this->*_input[it->first].second)();
	  break;
	}
      else if (joy != NULL)
	{
	  Uint8 hatValue = SDL_JoystickGetHat(joy, i);
	  if (hatValue == SDL_HAT_DOWN)
	    execDown();
	  else if (hatValue == SDL_HAT_LEFT)
	    execLeft();
	  else if (hatValue == SDL_HAT_RIGHT)
	    execRight();
	  else if (hatValue == SDL_HAT_UP)
	    execUp();
	  ++i;
	}
    }
  translate(this->_vec);
}

void    CharacterUI::updateIA(Mouvement input, float speed)
{
  if (input != NONE)
    {
      this->_transl = speed;
      this->_speed = static_cast<float>(this->_player->getSpeed());
      (this->*_input[static_cast<int>(input)].second)();
      translate(this->_vec);
    }
}

void	CharacterUI::setAnim()
{
  if (this->_run && this->_run != this->_anim)
    {
      this->_model.setCurrentSubAnim("run", true);
      this->_anim = true;
    }
  else if (!this->_run && this->_run != this->_anim)
    {
      this->_model.setCurrentSubAnim("stop", true);
      this->_anim = false;
    }
}

bool		CharacterUI::win()
{
  static clock_t	 old = 0;
  clock_t		 news = 0;

  if (old == news)
    {
      old = clock();
      rotate(glm::vec3(0, 1, 0), 0);
      this->_model.setCurrentSubAnim("win", true);
    }
  news = clock();
  if ((news - old)/CLOCKS_PER_SEC < 1)
    return (false);
  old = 0;
  return (true);
}

void	CharacterUI::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  this->_model.draw(shader, getTransformation(), clock.getElapsed());
}
