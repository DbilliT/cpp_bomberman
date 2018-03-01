#include "GL/glu.h"
#include "SDL2-2.0.3/include/SDL.h"
#include "SDL2-2.0.3/include/SDL_opengl.h"
#include "SDL2_image-2.0.0/SDL_image.h"
#include "SDL2_ttf-2.0.12/SDL_ttf.h"
#include "SDL2_gfx-1.0.1/SDL2_rotozoom.h"

#define WIDTH	1920
#define HEIGHT	1080

class SDL_Class
{
public:
  SDL_Class();
  ~SDL_Class();
  void		square(int, int, int, int, int, int, int);
  void		write(std::string const &, int, int, int, int, int, int, std::string const &);
  void		image(int, int, std::string const &);
  void          screen(int, int, std::string const &, int);
  void          cutscene(const std::string &pfile);
  void		map(std::string const &, int, int, float);
  SDL_Window	*_window;
private:
  int		_width;
  int		_height;
};
