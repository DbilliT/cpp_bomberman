//
// SDL_Class.cpp for  in /home/tanyer_a/rendu/Tek_2/cpp_bomberman/menu_sdl
// 
// Made by Alexandre Tanyeres
// Login   <tanyer_a@epitech.net>
// 
// Started on  Mon Jun  1 16:50:16 2015 Alexandre Tanyeres
// Last update Sun Jun 14 20:22:58 2015 paul david
//

#include "bomberman.hpp"
#include "playvpx.h"

#define LARGEUR _width
#define HAUTEUR _height

bool		INTRO = true;

SDL_Class::SDL_Class()
{
  this->_width = 1920;
  this->_height = 1080;
  SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
  SDL_ShowCursor(SDL_DISABLE);
  this->_window = SDL_CreateWindow("Jambon Beurre Man",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   LARGEUR, HAUTEUR, SDL_WINDOW_OPENGL);
  SDL_GLContext glcontext = SDL_GL_CreateContext(this->_window);
  TTF_Init();
  glEnable(GL_TEXTURE_2D);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,this->_width, this->_height,0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (INTRO == true)
    this->cutscene("data/cutscene/bomb.ivf");
  INTRO = false;
  SDL_GL_DeleteContext(glcontext);
}

SDL_Class::~SDL_Class()
{
  TTF_Quit();
  SDL_DestroyWindow(this->_window);
  SDL_Quit();
}

void		SDL_Class::cutscene(const std::string &pfile)
{
  SoundManager& sound=SoundManager::Instance();
  bool		pass = false;
  sound.playMusic("data/sound/music.mp3/Intro.mp3", 0);
  int nn = 0;
  Vpxdata data;

  playvpx_init(&data,pfile.c_str());

  while(playvpx_loop(&data) && pass == false) {
    SDL_Event event;
    while (SDL_PollEvent(&event))
      {
	if (event.type == SDL_KEYDOWN)
	  {
	    pass = true;
	    sound.stopMusic();
	    sound.playMusic("data/sound/music.mp3/Pirate.mp3", 0);
	  }
      }
    GLuint tex = playvpx_get_texture(&data);
    if (!tex) { continue; }
    gfx_tex_blit(tex,0,0,this->_width,this->_height);
    SDL_GL_SwapWindow(this->_window);
    nn += 1;
  }
  playvpx_deinit(&data);
}

void		SDL_Class::square(int x, int y,
				  int h, int w,
				  int R, int G, int B)
{
  SDL_Surface	*rec;
  SDL_Rect	pos;
  
  pos.x = x;
  pos.y = y;
  rec = SDL_CreateRGBSurface(0, h, w, 32, 0, 10, 0, 0);
  if (rec == NULL)
    return ;
  SDL_FillRect(rec, NULL, SDL_MapRGB(SDL_GetWindowSurface(this->_window)->format, R, G, B));
  SDL_BlitSurface(rec, NULL, SDL_GetWindowSurface(this->_window), &pos);
  SDL_FreeSurface(rec);
}

void		SDL_Class::write(std::string const &sentence,
				 int x, int y, int size,
				 int R, int G, int B,
				 std::string const &name)
{
  SDL_Surface	*text;
  SDL_Rect	pos;
  TTF_Font	*police;
  SDL_Color	color;

  color.r = R;
  color.g = G;
  color.b = B;
  pos.x = x;
  pos.y = y;
  police = TTF_OpenFont(name.c_str(), size);//.ttf
  if (police == NULL)
    return ;
  text = TTF_RenderText_Blended(police, sentence.c_str(), color);
  SDL_BlitSurface(text, NULL, SDL_GetWindowSurface(this->_window), &pos);
  TTF_CloseFont(police);
  SDL_FreeSurface(text);
}

void	        SDL_Class::image(int x, int y, std::string const &name)
{
  SDL_Surface	*imgf;
  SDL_Rect	pos;

  pos.x = x;
  pos.y = y;
  imgf = SDL_LoadBMP(name.c_str());
  if (imgf == NULL)
    return ;
  SDL_SetColorKey(imgf, SDL_TRUE, SDL_MapRGB(imgf->format, 100, 200, 100));
  SDL_BlitSurface(imgf, NULL, SDL_GetWindowSurface(this->_window), &pos);
  SDL_FreeSurface(imgf);
}

void            SDL_Class::screen(int x, int y, std::string const &name, int t)
{
  SDL_Rect      pos;
  SDL_Surface *img;
  SDL_Surface *img_original;

  pos.x = x;
  pos.y = y;
  img = IMG_Load(name.c_str());
  img_original = img;

  if (img == NULL)
    {
      img = SDL_LoadBMP("data/SDL_Features/no-preview.bmp");
      if (img == NULL)
        return ;
    }
  else
    {
      if (t == 1)
  	img = rotozoomSurfaceXY(img, 0, 0.227, 0.227, 0);
      else
  	img = rotozoomSurfaceXY(img, 0, 0.21, 0.21, 0);
    }
  SDL_BlitSurface(img, NULL, SDL_GetWindowSurface(this->_window), &pos);
  SDL_FreeSurface(img);
  SDL_FreeSurface(img_original);
}

void		SDL_Class::map(std::string const &name, int x, int y, float z)
{
  SDL_Rect      pos;
  SDL_Surface *img;
  SDL_Surface *img_original;

  (void)z;
  pos.x = x;
  pos.y = y;
  img = SDL_LoadBMP(name.c_str());
  img_original = img;
  if (img == NULL)
    return ;
  img = rotozoomSurfaceXY(img, 0, z, z, 0);
  SDL_BlitSurface(img, NULL, SDL_GetWindowSurface(this->_window), &pos);
  SDL_FreeSurface(img);
  SDL_FreeSurface(img_original);
}
