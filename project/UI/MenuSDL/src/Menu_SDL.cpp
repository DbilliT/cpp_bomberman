#include "bomberman.hpp"

Menu_SDL::Menu_SDL(SoundManager *m_instance) : _MSound(m_instance)
{
  this->init();
  this->_sound = 1;
  this->_effect = 1;
  this->m_menu.push_back(&Menu_SDL::play_menu);
  this->m_menu.push_back(&Menu_SDL::highscore_menu);
  this->m_menu.push_back(&Menu_SDL::option_menu);
  this->m_menu.push_back(&Menu_SDL::credit_menu);
  this->p_menu.push_back(&Menu_SDL::new_menu);
  this->p_menu.push_back(&Menu_SDL::load_menu);
  this->_cam = false;
}

void Menu_SDL::init()
{
  this->_SDL = new SDL_Class;
  this->_CoreMenu = new Menu;
}

Menu_SDL::~Menu_SDL()
{
  delete this->_SDL;
  delete this->_CoreMenu;
}

void    Menu_SDL::interv(int x, int y, int val)
{
  int   place = 150;

  this->_SDL->write("-", x, y, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  if (val > 9)
    {
      if (val < 100)
        this->_SDL->write(std::to_string(val), x + (place / 2) - 10, y, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
      else if (val > 99 && val < 1000)
        this->_SDL->write(std::to_string(val), x + (place / 3) + 5, y, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
      else
        this->_SDL->write(std::to_string(val), x + (place / 4) + 5, y, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
    }
  else
    this->_SDL->write(std::to_string(val), x + (place / 2), y, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("+", x + place, y, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
}

void	Menu_SDL::aff_enable(int pos, bool choice)
{
  pos = 250 + (pos * 100);
  if (choice == true)
    {
      this->_SDL->image(POSX + 220, pos + 5, "data/SDL_Features/arrow_left.bmp");      
      this->_SDL->write("yes", POSX + 270, pos, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
    }
  else
    {
      this->_SDL->image(POSX + 355, pos + 5, "data/SDL_Features/arrow_right.bmp");
      this->_SDL->write("no", POSX + 285, pos, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
    }
}

void	Menu_SDL::aff_reso(int pos, int reso)
{
  pos = 250 + (pos * 100);
  (void)reso;
}

void	Menu_SDL::title(std::string str)
{
  this->_SDL->write(str, POSX - 30, 200, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
}

void    Menu_SDL::jauge(int x, int y, int val, int sur)
{
  this->_SDL->square(x, y, 220, 5, 255, 255, 255);
  this->_SDL->square(x + 10, y + 10, ((val * 200) / sur), 15, 254, 195, 0);
  this->_SDL->square(x, y + 30, 220, 5, 255, 255, 255);
  this->_SDL->square(x, y, 5, 35, 255, 255, 255);
  this->_SDL->square(x + 215, y, 5, 35, 255, 255, 255);
}


void	Menu_SDL::select(int pos)
{
  int	LARGEUR = 410;
  int	HAUTEUR = 57;
  int	APPAISSEUR = 2;

  int	X = POSX - 10;
  int	Y = 250 + (pos * 100);
  this->_SDL->square(X, Y, LARGEUR, APPAISSEUR, 254, 195, 0);
  this->_SDL->square(X + LARGEUR, Y, APPAISSEUR,HAUTEUR, 254, 195, 0);
  this->_SDL->square(X, Y, APPAISSEUR, HAUTEUR, 254, 195, 0);
  this->_SDL->square(X, Y + HAUTEUR, LARGEUR + 2, APPAISSEUR, 254, 195, 0);
  this->_SDL->image(X - 65, Y, "data/SDL_Features/select-icon.bmp");
}

//menus

void	Menu_SDL::main_menu()
{
  bool	gameRunning = true;
  int	pos = 0;
  int	key = 0;
  int	tempsPrecedent = 0;
  int	tempsActuel = 0;

  while (gameRunning)
    {
      tempsActuel = SDL_GetTicks();
      if (tempsActuel - tempsPrecedent > 30)
	{      
	  this->put_font();
	  this->_SDL->write("play", POSX, 250, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->_SDL->write("highscores", POSX, 350, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->_SDL->write("options", POSX, 450, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->_SDL->write("keyboard", POSX, 550, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->_SDL->write("quit", POSX, 650, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->select(pos);
	  SDL_UpdateWindowSurface(this->_SDL->_window); 
	  tempsPrecedent = tempsActuel;
	}
      key = this->input();
      if (key == 1)
	gameRunning = false;
      else if (key == 2)
	(pos == 4) ? pos = 0 : ++pos;
      else if (key == 3)
	(pos == 0) ? pos = 4 : --pos;
      else if (key == 4)
	{
	  if (pos == 4)
	    gameRunning = false;
	  else
	    {
	      (this->*m_menu[pos])();
	      tempsPrecedent = 0;
	    }
	}      
    }
}

void	Menu_SDL::play_menu()
{
  bool	gameRunning = true;
  bool	ACTU = false;
  int   pos = 0;
  int   key = 0;
  int	tempsPrecedent = 0;
  int	tempsActuel = 0;

  while (gameRunning)
    {
      tempsActuel = SDL_GetTicks();
      if (tempsActuel - tempsPrecedent > 30 || ACTU == true)
	{
	  ACTU = false;
	  this->put_font();
	  this->title("play");
	  this->_SDL->write("continue", POSX, 250, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->_SDL->write("new game", POSX, 350, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->_SDL->write("load", POSX, 450, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->_SDL->write("map generator", POSX, 550, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->_SDL->write("return", POSX, 650, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->select(pos);
	  SDL_UpdateWindowSurface(this->_SDL->_window);
	  tempsPrecedent = tempsActuel;
	}
      key = this->input();
      if (key == 1)
	gameRunning = false;
      else if (key == 2)
        (pos == 4) ? pos = 0 : ++pos;
      else if (key == 3)
        (pos == 0) ? pos = 4 : --pos;
      else if (key == 4)
        {
	  if (pos == 0 && this->_CoreMenu->getIsContinue() == true)
	    {
	      this->lauchGame(false, true, 10, 10, 2, 2, "data/level1", this->name(0));
	      ACTU = true;
	    }
	  if (pos == 1)
	    {
	      (this->*p_menu[0])();
	      tempsPrecedent = 0;
	    }
	  if (pos == 2)
	    {
	      (this->*p_menu[1])();
	      tempsPrecedent = 0;
	    }
	  if (pos == 3)
	    this->map_inf();
	  if (pos == 4)
	    gameRunning = false;
        }
    }
}

void	Menu_SDL::highscore_menu()
{
  std::vector<std::pair<int, std::string> > highscore;
  int	y = 250;
  int	i;
  int	key;
  bool	GameRunning = true;

  i = 0;
  highscore = this->_CoreMenu->getHighscore();
  this->put_font();
  	  this->title("highscore");
  for (std::vector<std::pair<int, std::string> >::iterator it = highscore.begin() ; it != highscore.end() && i < 10; ++it)
    {
      this->_SDL->write((*it).second, POSX, y, 30, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
      this->_SDL->write(std::to_string((*it).first), POSX + 250 , y, 30, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
      i++;
      y = y + 70;
    }
  SDL_UpdateWindowSurface(this->_SDL->_window);
  while (GameRunning)
    {
      key = this->input();
      if (key == 1 || key == 4)
	GameRunning = false;
    }
}

void	Menu_SDL::option_menu()
{
  bool  gameRunning = true;
  int   pos = 0;
  int   key = 0;
  int   tempsPrecedent = 0;
  int   tempsActuel = 0;
  int	lvl = 2;
  int	tmp_son;
  int	tmp_effect;

  tmp_son = this->_sound;
  tmp_effect = this->_effect;
  while (gameRunning)
    {
      tempsActuel = SDL_GetTicks();
      if (tempsActuel - tempsPrecedent > 30)
        {
          this->put_font();
	  this->title("option");
          this->_SDL->write("music :", POSX, 250, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->jauge(POSX + 160, 263, tmp_son, 100);
	  this->_SDL->write("effect :", POSX, 350, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->jauge(POSX + 160, 363, tmp_effect, 100);
	  this->_SDL->write("difficulty :", POSX, 450, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->interv(POSX + 210, 450, lvl);
	  this->_SDL->write("apply", POSX, 550, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->_SDL->write("advanced option", POSX, 650, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
          this->_SDL->write("return", POSX, 750, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
          this->select(pos);
          SDL_UpdateWindowSurface(this->_SDL->_window);
          tempsPrecedent = tempsActuel;
        }
      key = this->input();
      if (key == 1)
	  gameRunning = false;
      else if (key == 2)
        (pos == 5) ? pos = 0 : ++pos;
      else if (key == 3)
        (pos == 0) ? pos = 5 : --pos;
      else if (key == 4)
        {
	  if (pos == 3)
	    {
	      this->_sound = tmp_son;
	      this->_effect = tmp_effect;
	      this->_MSound->setVolumeMusic((float)this->_sound);
	      this->_MSound->setVolumeSound((float)this->_effect);
	    }
	  if (pos == 4)
	    this->advanced_menu();
	  if (pos == 5)
	    gameRunning = false;
	}
      else if (key == 6)
        {
          if (pos == 0 && tmp_son > 0)
            --tmp_son;
          else if (pos == 1 && tmp_effect > 0)
            --tmp_effect;
	  else if (pos == 2 && lvl > 1)
	    --lvl;
        }
      else if (key == 7)
        {
          if (pos == 0 && tmp_son < 100)
            ++tmp_son;
	  else if (pos == 1 && tmp_effect < 100)
            ++tmp_effect;
	  else if (pos == 2 && lvl < 4)
            ++lvl;
	}
    }
}

void	Menu_SDL::advanced_menu()
{
  bool	gameRunning = true;
  int	key = 0;
  int	tempsPrecedent = 0;
  int	tempsActuel = 0;
  unsigned int	pos = 0;
  int		res = 0;

  while (gameRunning)
    {
      tempsActuel = SDL_GetTicks();
      if (tempsActuel - tempsPrecedent > 30)
	{
          this->put_font();
	  this->title("option > advanced option");
          this->_SDL->write("resolution", POSX, 250, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->aff_reso(0, res);
	  this->_SDL->write("camera", POSX, 350, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->aff_enable(1, this->_cam);
	  this->_SDL->write("apply", POSX, 450, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
          this->_SDL->write("return", POSX, 550, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
          this->select(pos);
          SDL_UpdateWindowSurface(this->_SDL->_window);
          tempsPrecedent = tempsActuel;
	}
      key = this->input();
      if (key == 1)
	  gameRunning = false;
      else if (key == 2)
        (pos == 3) ? pos = 0 : ++pos;
      else if (key == 3)
        (pos == 0) ? pos = 3 : --pos;
      else if (key == 4)
        {
	  if (pos == 3)
	    gameRunning = false;
	}
      else if (key == 6)
        {
          if (pos == 0 && res > 0)
            --res;
          else if (pos == 1)
            this->_cam = false;
        }
      else if (key == 7)
        {
          if (pos == 0 && res < 6)
            ++res;
	  else if (pos == 1)
            this->_cam = true;
	}
    }
}

void	Menu_SDL::credit_menu()
{
  this->put_font();
  this->_SDL->write("player 1:", POSX - 20, 195, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("move up", POSX, 225, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("move down", POSX, 250, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("move left", POSX, 275, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("move right", POSX, 300, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("place bomb", POSX, 325, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");

  this->_SDL->write("UP", POSX + 250, 225, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("DOWN", POSX + 250, 250, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("LEFT", POSX + 250, 275, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("RIGHT", POSX + 250, 300, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("ctrl right", POSX + 250, 325, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");

  this->_SDL->write("player 2:", POSX - 20, 375, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("move up", POSX, 405, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("move down", POSX, 430, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("move left", POSX, 455, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("move right", POSX, 480, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("place bomb", POSX, 505, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");

  this->_SDL->write("Z", POSX + 250, 405, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("S", POSX + 250, 430, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("Q", POSX + 250, 455, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("D", POSX + 250, 480, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("space", POSX + 250, 505, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");

  this->_SDL->write("SAVE", POSX, 555, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("f5", POSX + 250, 555, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("menu", POSX, 605, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("echap", POSX + 250, 605, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  SDL_UpdateWindowSurface(this->_SDL->_window);
  while (this->input() != 1);
}

void	Menu_SDL::new_menu()
{
  bool gameRunning = true;
  bool	ACTU = false;
  int   pos = 0;
  int   key = 0;
  int   tempsPrecedent = 0;
  int   tempsActuel = 0;
  bool	mapR = false;
  int	X = 15;
  int	Y = 15;
  int	player = 1;
  int	bot = 5;
  unsigned int		i;
  std::string	tmp;

  while (gameRunning)
    {
      tempsActuel = SDL_GetTicks();
      if (tempsActuel - tempsPrecedent > 30 || ACTU == true)
        {
          this->put_font();
	  this->title("play > new game");
	  if (mapR == false)
	    this->_SDL->image(POSX + 130, 455, "data/SDL_Features/arrow_left.bmp");
	  else
	    this->_SDL->image(POSX + 350, 455, "data/SDL_Features/arrow_right.bmp");
	  if (pos == 3 && mapR == false)
	    this->_SDL->square(POSX - 35, 515, 414, 237, 254, 194, 0);
          else
	    this->select(pos);
          this->_SDL->write("player :", POSX, 250, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->interv(POSX + 210, 250, player);
          this->_SDL->write("bot :", POSX, 350, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->interv(POSX + 210, 350, bot);
	  this->_SDL->write("map", POSX, 450, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
          if (mapR == false)
	    {
	      tmp = this->_CoreMenu->getMaps().at(i);
	      tmp.erase(tmp.end() - 4, tmp.end());

	      this->_SDL->write("perso", 450, 450, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	      this->_SDL->screen(POSX - 30, 520, "data/mapsScreen/" + tmp + ".tga", 2);
	      this->_SDL->image(POSX - 25, 615, "data/SDL_Features/arrow_left.bmp");      
	      this->_SDL->image(POSX + 333, 615, "data/SDL_Features/arrow_right.bmp");      
	      this->_SDL->write(tmp, POSX + 5, 520, 20, 254, 195, 0, "data/SDL_Features/BEBAS.ttf");
	    }
	  else
	    {
	      this->_SDL->write("random", 450, 450, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	      this->_SDL->write("X :", 350, 550, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	      this->interv(POSX + 210, 550, X);
	      this->_SDL->write("Y :", 350, 650, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	      this->interv(POSX + 210, 650, Y);
	    }
	  this->_SDL->write("start", POSX, 750, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->_SDL->write("return", POSX, 850, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
          SDL_UpdateWindowSurface(this->_SDL->_window);
          tempsPrecedent = tempsActuel;
        }
      key = this->input();
      if (key == 1)
        gameRunning = false;
      else if (key == 2)
        pos = (pos == 6) ? 0 : (pos == 3 && mapR == false) ? pos + 2 : pos + 1;
      else if (key == 3)
        pos = (pos == 0) ? 6 : (pos == 5 && mapR == false) ? pos - 2 : pos - 1;
      else if (key == 4)
        {
	  if (pos == 5 && mapR == true)
	    {
	      this->lauchGame(true, false, Y, X, player, bot, "", this->name(player));
	      ACTU = true;
	    }
	  if (pos == 5 && mapR == false)
	    {
	      this->lauchGame(false, false, 0, 0, player, bot, this->_CoreMenu->getMaps().at(i), this->name(player));
	      ACTU = true;
	    }
	  if (pos == 6)
	    gameRunning = false;
	}
      else if (key == 6)
	{
	  if (pos == 0 && player == 2)
	    --player;
	  if (pos == 1 && bot > 0)
	    --bot;
	  if (pos == 2)
	    mapR = true;
	  if (pos == 3 && X > 2 && mapR == true)
	    --X;
	  if (pos == 3 && mapR == false)
	    (i == this->_CoreMenu->getMaps().size() - 1) ? i = 0 : ++i;
	  if (pos == 4 && Y > 2)
	    --Y;
	}
      else if (key == 7)
	{
	  if (pos == 0 && player == 1)
	    ++player;
	  if (pos == 1)
	    ++bot;
	  if (pos == 2)
	    mapR = false;
	  if (pos == 3 && mapR == true)
	    ++X;
	  if (pos == 3 && mapR == false)
	    (i == 0) ? i = this->_CoreMenu->getMaps().size() - 1 : --i;	    
	  if (pos == 4)
	    ++Y;
	}
      (bot == 0) ? player = 2 : 0;
    }
}

void	Menu_SDL::load_menu()
{
  bool	gameRunning = true;
  bool	ACTU = false;
  int	key = 0;
  int	tempsPrecedent = 0;
  int	tempsActuel = 0;
  unsigned int	pos = 0;
  std::string	tmp;

  while (gameRunning)
    {
      tempsActuel = SDL_GetTicks();
      if (tempsActuel - tempsPrecedent > 30 || ACTU == false)
	{
	  ACTU = false;
	  this->put_font();
	  if (!this->_CoreMenu->getFiles().empty())
	    {
	      tmp = this->_CoreMenu->getFiles().at(pos);
	      tmp.erase(0, 5);
	      tmp.erase(tmp.end() - 4, tmp.end());
	      this->_SDL->write(tmp, POSX - 10, 350, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	      this->_SDL->screen(POSX - 51, 450, "data/saveScreen/screen" + tmp + ".tga", 1);
	    }
	  else
	    this->_SDL->write("no save", POSX + 105, 350, 40, 255, 194, 0, "data/SDL_Features/BEBAS.ttf");
	  this->title("play > load");
	  this->_SDL->image(POSX - 50, 550, "data/SDL_Features/arrow_left.bmp");
	  this->_SDL->image(POSX + 350, 550, "data/SDL_Features/arrow_right.bmp");
	  SDL_UpdateWindowSurface(this->_SDL->_window); 
	  tempsPrecedent = tempsActuel;
	}
      key = this->input();
      if (key == 1)
	gameRunning = false;
      else if (!this->_CoreMenu->getFiles().empty())
	{
	  if (key == 4)
	    {
	      lauchGame(true, true,  0, 0, 0, 0, this->_CoreMenu->getFiles().at(pos), this->name(0));
	      ACTU = false;
	    }
	  else if (key == 6)
	    (pos == this->_CoreMenu->getFiles().size() - 1) ? pos = 0 : ++pos;
	  else if (key == 7)
	    (pos == 0) ? pos = this->_CoreMenu->getFiles().size() - 1 : --pos;
	}
    }
}

void	Menu_SDL::put_font()
{
  this->_SDL->image(0, 0, "data/SDL_Features/Wallpaper-colo.bmp");
  this->_SDL->write("bechad_p", POSX, 1000, 15, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("calatr_m", POSX + (80 * 1), 1000, 15, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("deluss_c", POSX + (80 * 2), 1000, 15, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("tanyer_a", POSX + (80 * 3), 1000, 15, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
  this->_SDL->write("david_k", POSX + (80 * 4), 1000, 15, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
}

int	Menu_SDL::input()
{
  SDL_Event event;
  
  if (SDL_WaitEvent(&event))
    {
      if (event.type == SDL_QUIT)
	exit(0);
      if (event.type == SDL_KEYDOWN)
	{
	  switch (event.key.keysym.sym)
	    {
	    case SDLK_ESCAPE:
	      this->_MSound->playSound("data/sound/noise.wav/back.wav");
	      return (1);
	      break;
	    case SDLK_DOWN:
	      this->_MSound->playSound("data/sound/noise.wav/move.wav");
	      return (2);
	      break;
	    case SDLK_UP:
	      this->_MSound->playSound("data/sound/noise.wav/move.wav");
	      return (3);
	      break;
	    case SDLK_RETURN:
	      this->_MSound->playSound("data/sound/noise.wav/guncann.wav");
	      return (4);
	      break;
	    case SDLK_BACKSPACE:
	      return (5);
	      break;   
	    case SDLK_LEFT:
	      return (6);
	      break;
	    case SDLK_RIGHT:
	      return (7);
	      break;
	    case SDLK_a ... SDLK_z:
	      return event.key.keysym.sym;
	      break;
	    }
	}
    }
  return (0);
}

const std::pair<std::string, std::string>	Menu_SDL::name(int nbp)
{
  if (nbp == 0)
    return std::make_pair("", "");
  bool	gameRunning = true;
  std::string	tmp1;
  std::string	tmp2;
  int	key = 0;
  int	tempsPrecedent = 0;
  int	tempsActuel = 0;
  int	pos = 0;
  unsigned int	nbc1 = 0;
  unsigned int	nbc2 = 0;

  while (gameRunning)
    {
      tempsActuel = SDL_GetTicks();
      if (tempsActuel - tempsPrecedent > 30)
	{
	  this->put_font();
	  this->_SDL->write("name player 1:", POSX - 10, 320, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->_SDL->write(tmp1, POSX, 350, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  if (nbp == 2)
	    {
	      this->_SDL->write("name player 2:", POSX - 10, 420, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	      this->_SDL->write(tmp2, POSX, 450, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	    }
	  this->_SDL->write("play", POSX, 550, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->select(pos + 1);
	  SDL_UpdateWindowSurface(this->_SDL->_window); 
	  tempsPrecedent = tempsActuel;
	}
      key = this->input();
      if (key == 4 && pos == 2)
	gameRunning = false;
      else if (key == 2)
	{
	  if (nbp == 1 && pos == 0)
	    pos = pos + 2;
	  else
	    (pos == 2) ? pos = 0 : ++pos;
	}
      else if (key == 3)
	{
	  if (nbp == 1 && pos == 2)
	    pos = pos - 2;
	  else
	    (pos == 0) ? pos = 2 : --pos;
	}
      else if (key == 5)
	{
	  if (pos == 0)
	    {
	      if (nbc1 != 0)
		{
		  tmp1.pop_back();
		  --nbc1;
		}
	    }
	  else if (pos == 1)
	    {
	      if (nbc2 != 0)
		{
		  tmp2.pop_back();
		  --nbc2;
		}
	    }
	}
      else if (key >= 97)
	{
	  if (pos == 0)
	    {
	      if (nbc1 != 10)
		{
		  ++nbc1;
		  tmp1.append(reinterpret_cast<char *>(&key));
		}
	    }
	  else if (pos == 1)
	    {
	      if (nbc2 <= 10)
		{
		  ++nbc2;
		  tmp2.append(reinterpret_cast<char *>(&key));
		}
	    }
	}      
    }
  if (nbp == 1)
    return std::make_pair(tmp1, "");
  return (std::make_pair(tmp1, tmp2));
}

void		Menu_SDL::map_inf()
{
  bool	gameRunning = true;
  int	pos = 0;
  int	key = 0;
  int	tempsPrecedent = 0;
  int	tempsActuel = 0;
  unsigned int	nbc = 0;
  int	x = 2;
  int	y = 2;
  std::string	str;

  while (gameRunning)
    {
      tempsActuel = SDL_GetTicks();
      if (tempsActuel - tempsPrecedent > 30)
	{
	  this->put_font();
	  this->_SDL->write("map generator", POSX - 30, 170, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->_SDL->write("map name:", POSX - 10, 220, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->_SDL->write(str, POSX, 250, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->_SDL->write("X :", POSX, 350, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->interv(POSX + 210, 350, x);
	  this->_SDL->write("Y :", POSX, 450, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->interv(POSX + 210, 450, y);
	  this->_SDL->write("continue", POSX, 550, 40, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->select(pos);
	  SDL_UpdateWindowSurface(this->_SDL->_window); 
	  tempsPrecedent = tempsActuel;
	}
      key = this->input();
      if (key == 1)
	gameRunning = false;
      else if (key == 2)
	(pos == 3) ? pos = 0 : ++pos;
      else if (key == 3)
	(pos == 0) ? pos = 3 : --pos;
      else if (key == 4 && pos == 3)
	{
	  this->map_gen(x, y, str);
	  gameRunning = false;
	}
      else if (key == 6)
	{
	  if (pos == 1)
	    (x != 2) ? --x : 0;
	  if (pos == 2)
	    (y != 2) ? --y : 0;
	}
      else if (key == 7)
	{
	  if (pos == 1)
	    (x != 50) ? ++x : 0;
	  if (pos == 2)
	    (y != 50) ? ++y : 0;
	}
      else if (key == 5)
	{
	  if (pos == 0)
	    {
	      if (nbc > 0)
		{
		  --nbc;
		  str.pop_back();
		}
	    }
	}
      else if (key >= 97)
	{
	  if (pos == 0)
	    {
	      if (nbc <= 10)
		{
		  ++nbc;
		  str.append(reinterpret_cast<char *>(&key));
		}
	    }    
	}
    }
}

void		Menu_SDL::map_gen(int x, int y, std::string const &names)
{
  std::vector<std::vector<int>	>	maps;
  std::vector<std::vector<int>	>	old;
  std::vector<int>			tmp;
  int			i;
  int			j;

  for (i = 0; i != y; ++i)
    {
      for (j = 0; j != x; ++j)
	tmp.push_back(2);
      maps.push_back(tmp);
    }
  old = maps;
  std::pair<int, int>	pos;

  bool	gameRunning = true;
  int	key = 0;
  int	tempsPrecedent = 0;
  int	tempsActuel = 0;

  pos.first = 0;
  pos.second = 0;

  float t = (900 / MAX(x, y));
  float f = (900.0 / (MAX(x, y) * 100.0));
  while (gameRunning)
    {
      tempsActuel = SDL_GetTicks();
      if (tempsActuel - tempsPrecedent > 30)
	{
	  i = 0;
	  this->_SDL->image(0, 0, "data/SDL_Features/Wallpaper-gen.bmp");
	  this->_SDL->square(150, 0, 920, 1080, 85, 85, 85);
	  this->_SDL->write("map generator", 450, 8, 50, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  while (i != y)
	    {
	      j = 0;
	      while (j != x)
		{
		  if (maps[i][j] == 0)
		    this->_SDL->map("data/SDL_Features/grass.bmp", 160 + (i * t), 90 + (j * t), f);
		  else if (maps[i][j] == 1)
		    this->_SDL->map("data/SDL_Features/wall.bmp", 160 + (i * t), 90 + (j * t), f);
		  else
		    this->_SDL->map("data/SDL_Features/box.bmp", 160 + (i * t), 90 + (j * t), f);
		  ++j;
		}
	      ++i;
	    }
	  this->_SDL->square(155 + (pos.first * t), 85 + (pos.second * t), 10 + t, 10 + t, 254, 195, 0);
	  if (maps[pos.first][pos.second] == 0)
	    this->_SDL->map("data/SDL_Features/grass.bmp", 160 + (pos.first * t), 90 + (pos.second * t), f);
	  else if (maps[pos.first][pos.second] == 1)
	    this->_SDL->map("data/SDL_Features/wall.bmp", 160 + (pos.first * t), 90 + (pos.second * t), f);
	  else
	    this->_SDL->map("data/SDL_Features/box.bmp", 160 + (pos.first * t), 90 + (pos.second * t), f);
	  this->_SDL->write("x : " + std::to_string(pos.first + 1), 170, 995, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->_SDL->write("y : " + std::to_string(pos.second + 1), 270, 995, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->_SDL->map("data/SDL_Features/grass.bmp", 370, 995, 0.3);
	  this->_SDL->write(": A", 410, 995, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->_SDL->map("data/SDL_Features/box.bmp", 470, 995, 0.3);
	  this->_SDL->write(": Z", 510, 995, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->_SDL->map("data/SDL_Features/wall.bmp", 570, 995, 0.3);
	  this->_SDL->write(": E", 610, 995, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");
	  this->_SDL->write("press enter to continue", 800, 995, 20, 255, 255, 255, "data/SDL_Features/BEBAS.ttf");

	  key = this->input();
	  if (key == 1)
	    gameRunning = false;
	  else if (key == 4)
	    {
	      std::string name = "./data/map_generator/model_map/" + names;

	      std::ofstream	fd(name, std::ios::out | std::ios::trunc);

	      if (fd)
		{
		  fd << "x:" << y << "\ny:" << x << "\n";
		  for (j = 0; j != x; ++j)
		    {
		      for (i = 0; i != y; ++i)
			fd << maps[i][j];
		      fd << "\n";
		    }
		  fd.close();
		  std::string	exec = "./data/map_generator/map_generator " + name;
	      
		  system(exec.c_str());
		  delete this->_CoreMenu;
                  this->_CoreMenu = new Menu;
		}
	      gameRunning = false;
	    }
	  else if (key == 2)
	    (pos.second != (x - 1)) ? ++pos.second : 0;
	  else if (key == 3)
	    (pos.second != 0) ? --pos.second : 0;
	  else if (key == 6)
	    (pos.first != 0) ? --pos.first : 0;
	  else if (key == 7)
	    (pos.first != (y - 1)) ? ++pos.first : 0;
	  else if (key == 97)
	    maps[pos.first][pos.second] = 0;
	  else if (key == 122)
	    maps[pos.first][pos.second] = 2;
	  else if (key == 101)
	    maps[pos.first][pos.second] = 1;
	  SDL_UpdateWindowSurface(this->_SDL->_window); 
	  tempsPrecedent = tempsActuel;
	}
      else
	SDL_Delay(1);
    }
}

void	Menu_SDL::end(std::string const &nbp, int score)
{
  this->_SDL->image(0, 0, "data/SDL_Features/Wallpaper-pale.bmp");
  if (nbp == "0")
    {
      this->_SDL->image(95, 220, "data/SDL_Features/lose.bmp");
      this->_SDL->write("you lose", POSX + 150, 250, 200, 224, 30, 30, "data/SDL_Features/GrinchedRegular.ttf");
      this->_SDL->write("you're so bad", POSX + 350, 425, 35, 224, 30, 30, "data/SDL_Features/GrinchedRegular.ttf");
    }
  else
    {
      this->_CoreMenu->addHighscore(score, nbp);
      this->_CoreMenu->writeHighscore();
      this->_SDL->image(95, 220, "data/SDL_Features/win.bmp");
      this->_SDL->write("the winner is ...", POSX + 200, 350, 100, 64, 204, 51, "data/SDL_Features/GrinchedRegular.ttf");
      this->_SDL->write(nbp, POSX + 220, 475, 150, 64, 204, 51, "data/SDL_Features/GrinchedRegular.ttf");
      this->_SDL->write("score : " + std::to_string(score), POSX + 260, 605, 65, 64, 204, 51, "data/SDL_Features/GrinchedRegular.ttf");
    }
  SDL_UpdateWindowSurface(this->_SDL->_window);
  this->input();
  this->input();
}

void    Menu_SDL::lauchGame(bool mapR, bool isCont, int Y, int X, int player, int bot, const std::string &pfile, const std::pair<std::string, std::string> &names)
{
  try
    {
      Maps		*mp;
      std::string	winner;
      int		score;

      if (isCont == true && mapR == true)
	mp = new Maps("data/save/" + pfile);
      else if (isCont == true)
	{
	  std::ifstream infile("data/save/" + this->_CoreMenu->getContinue());
	  if (!infile.good())
	    throw Wrong_file("data/save/" + this->_CoreMenu->getContinue());
	  mp = new Maps("data/save/" + this->_CoreMenu->getContinue());
        }
      else if (mapR == true)
	mp = new Maps(std::make_pair(Y, X), player, bot, names);
      else
        mp = new Maps("data/maps/" + pfile, player, bot, names);
      delete this->_SDL;
      delete this->_CoreMenu;
      this->_MSound->stopMusic();
      GameEngine	*engine;
      int		tempsPrecedent = 0;
      int		tempsActuel = 0;
      bool		ret = true;

      tempsActuel = SDL_GetTicks();
      engine = new GameEngine(*mp, this->_cam);
      if (engine->initialize() == false)
        {
	  std::cout << "Error : Inconue." << std::endl;
	  std::exit(EXIT_FAILURE);
        }
      while (ret)
      	{
      	  if (tempsActuel - tempsPrecedent > 30)
      	    {
	      if ((ret = engine->update()))
		engine->draw();
	      tempsPrecedent = tempsActuel;
	    }
	  else
	    SDL_Delay(1);
	  tempsActuel = SDL_GetTicks();
	}
      winner = engine->getWin();
      score = engine->getScore();
      delete engine;
      delete mp;
      this->init();
      this->_MSound->playMusic("data/sound/music.mp3/Pirate.mp3", -1);
      if (winner != "-1")
	end(winner, score);
    }
  catch (Wrong_file &e)
    {
      std::cerr << "This file is unreachable or does'nt exist :" << e.what() << std::endl;
      std::exit(EXIT_FAILURE);
    }
  catch (std::invalid_argument &e)
    {
      this->_SDL->write("too many bots", POSX, 650, 40, 255, 0, 0, "data/SDL_Features/BEBAS.ttf");
      SDL_UpdateWindowSurface(this->_SDL->_window);
      this->input();
      this->input();
      std::cerr << "Invalid argument: " << e.what() << std::endl;
    }
}
