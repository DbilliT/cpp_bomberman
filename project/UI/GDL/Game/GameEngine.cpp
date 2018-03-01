//
// GameEngine.cpp for  in /home/calatr_m/test
// 
// Made by Caltraba Mickael
// Login   <calatr_m@epitech.net>
// 
// Started on  Fri May 22 15:33:38 2015 Caltraba Mickael
// Last update Sun Jun 14 20:49:25 2015 Caltraba Mickael
//

#include "GameEngine.hpp"
#include "SoundManager.hpp"

GameEngine::GameEngine(Maps &Map, bool point) :
  gdl::Game(),
  _sound(SoundManager::Instance()),
  _pointView(point),
  _win("-1"),
  _map_info(Map),
  _map(Map.getMap()),
  _size_map(Map.getSizeMap()),
  _players(Map.getInfoPlayers()),
  _bot(Map.getInfoBot())
{
  this->_widht = 1920;
  this->_height = 1080;
  this->_joy.push_back(NULL);
  this->_joy.push_back(NULL);
}
GameEngine::~GameEngine()
{
  std::list<AObject *>::iterator	it;
  size_t				i;

  this->_sound.stopMusic();
  for (it = this->_global.begin(); it != this->_global.end(); ++it)
    delete (*it);
  for (i = 0; i != this->_skybox.size(); ++i)
    delete (this->_skybox[i]);
  delete this->_ground;
  if (!this->_joy.empty())
    {
      for (int i = 0; i < SDL_NumJoysticks(); ++i) 
  	{
  	  SDL_JoystickEventState(SDL_IGNORE);
  	  SDL_JoystickClose(this->_joy[i]);
  	}
    }
  SDL_JoystickEventState(SDL_IGNORE);
  this->_context.stop();
}


//____PRINCIPAL_FUNCTIONS______________

bool		GameEngine::initialize()
{
  if (!initShader())
    return (false);
  if (!this->_manager.init())
    return (false);
  if (!this->_players.empty() && this->_players.size() <= 2)
    {
      if (!initPlayers())
	return (false);
    }
  else
    {
      std::cout << "Error : Too few players." << std::endl;
      return (false);
    }
  if (!this->_bot.empty())
    if (!initBots())
      return (false);
  if (!createMap())
    return (false);
  if (!createSkybox())
    return (false);
  if (!createMapMenu())
    return (false);
  this->_camera.initialize(this->_shader, this->_character, this->_ia,
			   (this->_size_map.second > this->_size_map.first) ?
			   this->_size_map.second : this->_size_map.first,
			   this->_pointView);
  this->_sound.playMusic("data/sound/music.mp3/IGame1.mp3", 1);
  SDL_Init(SDL_INIT_JOYSTICK);   
  if (SDL_NumJoysticks() >= 1)                                               
    {
      SDL_Joystick             *pJoy = NULL;
      this->_joy.push_back(pJoy);
      SDL_JoystickEventState(SDL_ENABLE);                                    
      this->_joy[0] = SDL_JoystickOpen(0);
    }
  if (SDL_NumJoysticks() == 2)
    {
      SDL_Joystick             *p2Joy = NULL;
      this->_joy.push_back(p2Joy);
      this->_joy[1] = SDL_JoystickOpen(1); 
    }
  return (true);
}

bool		GameEngine::update()
{
  static bool	win = true;
  static bool	sound_win = false;

  if (this->_input.getInput(SDLK_ESCAPE)
      || (!this->_joy.empty() && SDL_JoystickGetButton(this->_joy[0], 7)))
    {
      int	ret;
      this->_cursor = 0;
      while ((ret = updateMenu()) == 0)
	drawMenu();
      if (ret == 2)
	{
	  win = true;
	  return (false);
	}
    }
  else if (this->_input.getInput(SDL_QUIT))
    return (false);
  if (this->_input.getInput(SDLK_F5))
    save();
  this->_context.updateClock(this->_clock);
  this->_context.updateInputs(this->_input);
  if (this->_joy.size() > 0)
    SDL_JoystickUpdate();
  if (this->_players.size() == 0)
    return (lose());
  if (win && (!updatePlayers() || !updateIA()))
    return (false);
  if ((this->_players.size() == 1 && this->_bot.size() == 0))
    {
      if (sound_win == false && (sound_win = true))
	this->_sound.playSound("data/sound/noise.wav/win.wav");
      if ((win = this->_character[0]->win()) == true)
	{
	  sound_win = false;
	  return (winner());
	}
    }
  if (win && !updateMap())
    return (false);
  this->_camera.update(this->_shader, this->_character, this->_ia);
  return (true);
}

void	GameEngine::draw()
{
  std::list<std::pair<AObject *, std::pair<float, float> > >::const_iterator it; 
  size_t		i = 0;
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  for (it = this->_objects.begin(); it != this->_objects.end();
       ++it)
    {
      if (checkDraw((*it).second.first, (*it).second.second))
  	(*it).first->draw(this->_shader, this->_clock);
    }
  for (it = this->_inbreakable.begin(); it != this->_inbreakable.end();
       ++it)
    {
      if (checkDraw((*it).second.first, (*it).second.second))
  	(*it).first->draw(this->_shader, this->_clock);
    }
  this->_ground->draw(this->_shader, this->_clock);
  for (i = 0; i != this->_ia.size(); ++i)
    this->_ia[i]->draw(this->_shader, this->_clock);
  for (i = 0; i != this->_character.size(); ++i)
    this->_character[i]->draw(this->_shader, this->_clock);
  for (it = this->_bombs.begin(); it != this->_bombs.end(); ++it)
    (*it).first->draw(this->_shader, this->_clock);
  for (i = 0; i != this->_skybox.size(); ++i)
    this->_skybox[i]->draw(this->_shader, this->_clock);
  for (it = this->_fire.begin(); it != this->_fire.end(); ++it)
    (*it).first->draw(this->_shader, this->_clock);
  for (it = this->_bonusUI.begin(); it != this->_bonusUI.end(); ++it)
    (*it).first->draw(this->_shader, this->_clock);
  this->_context.flush();
}


//____UPDATE_FUNCTIONS____________________

bool		GameEngine::updatePlayers()
{
  std::list<Player>::iterator	it;
  size_t			i;
  std::pair<bool, double>	speed;
  
  i = 0;
  for (it = this->_players.begin(); it != this->_players.end(); ++it)
    {
      if ((*it).isAlive())
	{
	  this->_character[i]->checkKey(this->_clock, this->_input,
					this->_joy[i]);
	  speed = (*it).Move(this->_character[i]->getKey(),
			     this->_map, 
			     this->_character[i]->getBomb(),
			     this->_size_map,
			     this->_character[i]->getMove());
	  (*it).checkBonus(this->_bonus);
	  if (speed.first)
	    this->_character[i]->update(this->_input,
					static_cast<float>(speed.second),
					this->_joy[i]);
	  if (this->_character[i]->updateBomb(this->_input, this->_joy[i]))
	    {
	      this->_sound.playSound("data/sound/noise.wav/place_bomb.wav");
	      if (!createBomb())
		return (false);
	    }
	  ++i;
	}
      else
      	{
	  this->_sound.playSound("data/sound/noise.wav/kill.wav");
      	  this->_players.erase(it);
      	  it = this->_players.begin();
      	  this->_character.erase(this->_character.begin() + i);
	  if (i == 0)
	    {
	      SDL_Joystick *tmp = this->_joy[0];

	      this->_joy[0] = this->_joy[1];
	      this->_joy[1] = tmp;
	    }
      	  i = 0;
      	}
    }
  return (true);
}

bool		GameEngine::updateIA()
{
  std::list<Bot>::iterator	it;
  size_t			i;
  std::pair<bool, double>	speed;

  i = 0;
  for (it = this->_bot.begin(); it != this->_bot.end(); ++it)
    {
      if ((*it).isAlive())
	{
	  this->_ia[i]->checkIA(this->_clock, NONE);
	  speed = (*it).Move(NONE, this->_map,
			     this->_ia[i]->getBomb(), this->_size_map,
			     this->_ia[i]->getMove());
	  (*it).checkBonus(this->_bonus);
	  if (speed.first)
	    this->_ia[i]->updateIA(NONE, static_cast<float>(speed.second));
	  if (this->_ia[i]->updateBomb(this->_input, NULL))
	    {
	      this->_sound.playSound("data/sound/noise.wav/place_bomb.wav");
	      if (!createBomb())
		return (false);
	    }
	  ++i;
	}
      else
	{
	  this->_sound.playSound("data/sound/noise.wav/kill.wav");
	  this->_bot.erase(it);
	  it = this->_bot.begin();
	  this->_ia.erase(this->_ia.begin() + i);
	  i = 0;
	}
    }
  return (true);
}

bool	GameEngine::updateMap()
{
  std::list<Bomb *>::iterator				it;
  std::list<std::pair<unsigned int, unsigned int> >	sup;
  std::list<std::pair<AObject *, std::pair<float, float> > >::iterator sit;

  for (it = this->_bomb.begin(); it != this->_bomb.end(); ++it)
    {
      if ((*it)->isAlive())
	sup.merge((*it)->countdown(this->_map, this->_players, this->_size_map,
				   this->_bonus, this->_bot, this->_bomb));
    }
  if (!updateBomb(sup))
    return (false);
  if (!updateBonus())
    return (false);
  updateFire();
  sit = this->_objects.begin();
  while (!sup.empty())
    {
      if (sup.front().second == static_cast<unsigned int>((*sit).second.first) 
	  &&
	  sup.front().first == static_cast<unsigned int>((*sit).second.second))
	{
	  this->_objects.erase(sit);
	  sup.pop_front();
	  sit = this->_objects.begin();
	}
      else
	++sit;
    }
  return (true);
}

bool		GameEngine::updateBonus()
{
  std::list<IBonus *>::iterator		it;
  std::list<std::pair<AObject *, std::pair<float, float> > >::iterator ite;
  std::pair<unsigned int, unsigned int>	pos;

  ite = this->_bonusUI.begin();
  for (it = this->_bonus.begin(); it != this->_bonus.end(); ++it)
    {
      if (ite == this->_bonusUI.end())
	break;
      pos = (*it)->getPos();
      if (pos.second == (*ite).second.first &&
	  pos.first == (*ite).second.second)
	++ite;
    }
  if (ite != this->_bonusUI.end())
    {
      this->_sound.playSound("data/sound/noise.wav/bonus.wav");
      this->_bonusUI.erase(ite);
      if (!updateBonus())
	return (false);
    }
  if (this->_bonus.size() != this->_bonusUI.size())
    {
      ite = this->_bonusUI.begin();
      for (it = this->_bonus.begin(); it != this->_bonus.end(); ++it)
	{
	  pos =(*it)->getPos();
	  if ((pos.second != (*ite).second.first &&
	       pos.first != (*ite).second.second) ||
	      ite == this->_bonusUI.end())
	    {
	      BonusType	bonus = (*it)->getType();
	      std::string	type = "Boost";

	      if (bonus == POWERUP)
		type = "Power";
	      else if (bonus == BOMBUP)
		type = "BombUp";
	      if (!createBlock(pos.second, pos.first, 0.2, 0.5, 0.5, 0.5,type))
		return (false);
	      it = this->_bonus.begin();
	      ite = this->_bonusUI.begin();
	    }
	  ++ite;
	}
    }
  return (true);
}

bool		GameEngine::updateBomb(std::list<std::pair<unsigned int,
				       unsigned int> > sup)
{
  if (!this->_bomb.empty() && !this->_bomb.front()->isAlive())
    {
      if (!checkFire(-1, 0, 1, this->_bombs.front().second.second,
		     static_cast<int>(this->_size_map.first), sup))
	return (false);
      if (!checkFire(1, 0, 1, this->_bombs.front().second.second, 
			  static_cast<int>(this->_size_map.first), sup))
	return (false);
      if (!checkFire(-1, 1, 0, this->_bombs.front().second.first,
			  static_cast<int>(this->_size_map.second), sup))
	return (false);
      if (!checkFire(1, 1, 0, this->_bombs.front().second.first,
			  static_cast<int>(this->_size_map.second), sup))
	return (false);
      this->_sound.playSound("data/sound/noise.wav/explose_bomb.wav");
      this->_bomb.pop_front();
      this->_bombs.pop_front();
    }
  return (true);
}

void		GameEngine::updateFire()
{
  while (!this->_fire.empty() && !this->_fire.front().first->updateFire())
    this->_fire.pop_front();
}

bool		GameEngine::checkFire(int mult, int x, int y, int point,
				      int max, std::list<std::pair<unsigned int
				      , unsigned int> > sup)
{
  std::list<std::pair<unsigned int, unsigned int> >::iterator	it;
  std::pair<unsigned int, unsigned int>				tmp;
  int		first = this->_bombs.front().second.second;
  int		second = this->_bombs.front().second.first;
  int		power = this->_bomb.front()->getPower();
  bool		ret = false;
  std::random_device rd;

  if (!createBlock(second, first, 0, 1, 0.7, 0.9, "Fire"))
    return (false);
  for (int i = 0; i != power * mult; i += mult)
    {
      if (point + i >= 0 && point + i < max && 
	  this->_map[first + (i * y)][second + (i * x)]->isFree())
	{
	  if (sup.empty())
	    {
	      if (!createBlock(second + (i * x), first + (i * y), 0,
			       (x == 0) ? 0.7 : 1, (x == 0) ? 1 : 0.7, 0.9,
			       "Fire"))
		return (false);
	    }
	  else
	    {
	      for (it = sup.begin(); it != sup.end(); ++it)
		{
		  if (x != 0 &&
		      (static_cast<int>((*it).second) == second + (i * x) &&
		       static_cast<int>((*it).first) == first))
		    ret = true;
		
		  if (y != 0 &&
		      (static_cast<int>((*it).first) == first + (i * y) &&
		       static_cast<int>((*it).second) == second))
		    ret = true;
		  if (!createBlock(second + (i * x), first + (i * y), 0,
				   (x == 0) ? 0.7 : 1, (x == 0) ? 1 : 0.7, 0.9,
				   "Fire"))
		    return (false);
		  if (ret)
		    return (true);
		}
	    }
	}
      else
	return (true);
    }
  return (true);
}

bool		GameEngine::checkDraw(int x, int y)
{
  std::pair<float, std::pair<float, float> >	view;

  view = this->_camera.getPoint();
  if ((x < (view.second.first - view.first - 13) ||
       y < (view.second.second - view.first - 10)) ||
      (x > (view.second.first + view.first + 13) ||
       y > (view.second.second + view.first + 2)))
    return (false);
  return (true);
}


//____CREATION_BLOCK__________________

bool		GameEngine::createMap()
{
  int		y;
  int		x;
  std::string	str;

  for (y = 0; y < static_cast<int>(this->_size_map.first); ++y)
    {
      for (x = 0; x < static_cast<int>(this->_size_map.second); ++x)
	{
	  CaseType	type = this->_map[y][x]->getType();

	  if (type != EMPTY)
	    {
	      if (type == BOX)
		str = "Box";
	      else
		str = "Wall";
	      if (createBlock(x, y, 0, 1, 1, 1, str) == false)
		return (false);
	    }
	}
    }
  this->_ground = new Ground(-0.5 + (this->_size_map.second / 2), -0.5 + (this->_size_map.first / 2), -0.5, 1 + this->_size_map.second , 1 + this->_size_map.first);
  if (this->_ground->initialize() == false)
    return (false);
  for (x = -1; x < static_cast<int>(this->_size_map.second) +1; ++x)
    if (createBlock(x, -1, 0, 1, 1, 1,"Wall") == false)
      return (false);
  for (x = -1; x < static_cast<int>(this->_size_map.second) + 1; ++x)
    if (createBlock(x, this->_size_map.first, 0, 1, 1, 1, "Wall") == false)
      return (false);
  for (y = 0; y < static_cast<int>(this->_size_map.first); ++y)
    if (createBlock(-1, y, 0, 1, 1, 1, "Wall") == false)
      return (false);
  for (y = 0; y < static_cast<int>(this->_size_map.first); ++y)
    if (createBlock(this->_size_map.second, y, 0, 1, 1,1, "Wall") == false)
      return (false);
  return (true);
}

bool	GameEngine::createBomb()
{
  return (createBlock(this->_bomb.back()->getX(), this->_bomb.back()->getY(), -0.1, 0.8, 0.8, 0.8, "Bomb"));
}

bool		GameEngine::createSkybox()
{
  for (int i = 0; i != 4; ++i)
    {
      Skybox	*skybox = new Skybox(static_cast<int>(this->_size_map.first / 2), static_cast<int>(this->_size_map.second / 2), 0, static_cast<float>(this->_size_map.first * static_cast<int>(this->_size_map.second) * 5));

      if (!skybox->initializeBox(i))
	return (false);
      this->_skybox.push_back(skybox);
    }
  return (true);
}

bool	GameEngine::createBlock(int x, int y, int z, float a, float b, float c,
				std::string const & type)
{
  bool		dest = true;
  std::pair<AObject *, std::pair<float, float> >	block;
  if (type == "Wall")
    dest = false;
  AObject   *cube = new Cube(x, y, z, a, b, c, dest,
			     this->_manager.getTexture(type));
  if (cube->initialize() == false)
    return (false);
  block.first = cube;
  block.second.first = x;
  block.second.second = y;
  if (type == "Fire")
    this->_fire.push_back(block);
  else if (type == "Wall")
    this->_inbreakable.push_back(block);
  else if (type == "Box")
    this->_objects.push_back(block);
  else if (type == "Bomb")
    this->_bombs.push_back(block);
  else if (type == "BombUp" || type == "Boost" || type == "Power")
    this->_bonusUI.push_back(block);
  this->_global.push_back(cube);
  return (true);
}


//____INITIALIZE_______________________

bool		GameEngine::initShader()
{
  if (!this->_context.start(this->_widht, this->_height, "Jam-Bomberman"))
    {
      std::cout << "Error : Init windows." << std::endl;
      return (false);
    }
  glEnable(GL_DEPTH_TEST);
  if (!this->_shader.load("./lib/LibBomberman_linux_x64/shaders/basic.fp",
			  GL_FRAGMENT_SHADER) ||
      !this->_shader.load("./lib/LibBomberman_linux_x64/shaders/basic.vp",
			  GL_VERTEX_SHADER) || !this->_shader.build())
    {
      std::cout << "Error : Init Shader." << std::endl;
      return (false);
    }
  glEnable(GL_TEXTURE_2D);
  return (true);
}

bool		GameEngine::initPlayers()
{
  std::list<Player>::iterator		it; 
  int					nb;

  nb = 1;
  for (it = this->_players.begin() ; it != this->_players.end(); ++it)
    {
      CharacterUI	*player;

      player = new CharacterUI((*it).getX(), (*it).getY(), 0.2, 0.008,
			       nb, &(*it), this->_bomb);
      if (!player->initialize())
	return (false);
      this->_character.push_back(player);
      this->_global.push_back(player);
      ++nb;
    }
  return (true);
}

bool		GameEngine::initBots()
{
  std::list<Bot>::iterator		it; 

  for (it = this->_bot.begin() ; it != this->_bot.end(); ++it)
    {
      CharacterUI	*player;

      player = new CharacterUI((*it).getX(), (*it).getY(), 0.20, 0.008,
			       0, &(*it), this->_bomb);
      if (!player->initialize())
	return (false);
      this->_ia.push_back(player);
      this->_global.push_back(player);
    }
  return (true);
}



//____MENU_____________________________

int		GameEngine::updateMenu()
{
  int		ret;
  static float	i = 0;
  glm::vec3	rotat(0, 1, 0);

  this->_context.updateClock(this->_clock);
  this->_context.updateInputs(this->_input);
  ret = keyMenu(rotat, &i);
  this->_menu[this->_cursor].first->rotate(rotat, i);
  this->_camera.updateCameraMenu(this->_shader);
  i += 1;
  return (ret);
}

int		GameEngine::keyMenu(glm::vec3 rotat, float *i)
{
  if (this->_input.getInput(SDLK_RETURN)
      || (!this->_joy.empty() && SDL_JoystickGetButton(this->_joy[0], 1)))
    return ((this->_cursor == 0) ? 1 : 2);
  else if (this->_input.getInput(SDLK_RIGHT)
	   || (!this->_joy.empty() &&
	       SDL_JoystickGetHat(this->_joy[0], 0) == SDL_HAT_RIGHT))
    {
      if (this->_cursor < 1)
	{
	  *i = 0;
	  this->_menu[this->_cursor].first->rotate(rotat, 0);
	  ++this->_cursor;
	}
    }
  else if (this->_input.getInput(SDLK_LEFT)
	   || (!this->_joy.empty() &&
	       SDL_JoystickGetHat(this->_joy[0], 0) == SDL_HAT_LEFT))
    {
      if (this->_cursor > 0)
	{
	  *i = 0;
	  this->_menu[this->_cursor].first->rotate(rotat, 0);
	  --this->_cursor;
	}
    }
  return (0);
}

bool            GameEngine::createMapMenu()
{
  int           x;
  std::string	str = "Continue";

  for (x = 0; x < 6; x+=3)
    {
      std::pair<AObject *, int>        block;
      AObject   *cube = new Cube(x, 0, 0, 1, 1, 1, false,
				 this->_manager.getTexture(str));
      if (!cube->initialize())
	return (false);
      block.first = cube;
      block.second = x;
      this->_menu.push_back(block);
      this->_global.push_back(cube);
      str = "Quit";
    }
  return (true);
}

void            GameEngine::drawMenu()
{
  size_t        i;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  for (i = 0; i < this->_menu.size(); ++i)
    this->_menu[i].first->draw(this->_shader, this->_clock);
  this->_context.flush();
}


//____FUNCTIONS_____________________

std::string	GameEngine::getWin() const {return (this->_win);}
bool		GameEngine::lose() {this->_win = "0"; return (false);}
bool		GameEngine::winner()
{this->_win = this->_players.front().getName(); return (false);}
int		GameEngine::getScore() const
{
  if (this->_players.empty())
    return (-1);
  return (this->_players.front().getScore());
}
void		GameEngine::save() const
{
  Save		save(this->_map, this->_size_map, this->_players, this->_bot,
		     this->_widht, this->_height);
  save.CreateSave();
}

