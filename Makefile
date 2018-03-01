##
## Makefile for Makrfile in /home/bechad_p/rendu/cpp_bomberman
## 
## Made by Pierre Bechade
## Login   <bechad_p@epitech.net>
## 
## Started on  Mon May 11 15:53:15 2015 Pierre Bechade
## Last update Sun Jun 14 20:36:10 2015 Pierre Bechade
##

CXX		=	g++

RM		=	rm -f

CXXFLAGS	=	-W -Wall -Werror -std=c++11

LDFLAGS		+=	-ldl -Wl,-E -pthread
LDFLAGS		+=	-L./lib/LibBomberman_linux_x64/libs/ -lgdl_gl -lGL -lGLEW -lrt -lfbxsdk -lSDL2 -lpthread -Wl,-rpath=./lib/LibBomberman_linux_x64/libs/
LDFLAGS		+=	-L./lib/libSDL2/libSoA/ -lSDL2 -lSDL2_ttf -lSDL2_image `sdl-config --cflags --libs`
LDFLAGS		+=	-DPLAYVPX_SDL -DPLAYVPX_MAIN -lGL -lGLU ./lib/libvpx-1.4.0/libvpx.a
LDFLAGS		+=	-L./lib/fmodstudioapi10603linux/api/lowlevel/lib/x86_64/ -lfmod -Wl,-rpath=./lib/fmodstudioapi10603linux/api/lowlevel/lib/x86_64/
LDFLAGS		+=	-Wl,-rpath=./lib/libSDL2/libSoA/ -lSDL2_gfx

CXXFLAGS	+=	-I./project/core/bomberman/.
CXXFLAGS	+=	-I./project/core/game/map/.
CXXFLAGS	+=	-I./project/core/game/Bomb/.
CXXFLAGS	+=	-I./project/core/game/players/.
CXXFLAGS	+=	-I./project/core/game/ICase/.
CXXFLAGS	+=	-I./project/core/game/Case/.
CXXFLAGS	+=	-I./project/core/game/Box/.
CXXFLAGS	+=	-I./project/core/game/CaseFactory/.
CXXFLAGS	+=	-I./project/core/game/BonusFactory/.
CXXFLAGS	+=	-I./project/core/game/IBonus/.
CXXFLAGS	+=	-I./project/core/game/BombUp/.
CXXFLAGS	+=	-I./project/core/game/PowerUp/.
CXXFLAGS	+=	-I./project/core/game/Boost/.
CXXFLAGS	+=	-I./project/core/game/Save/.
CXXFLAGS	+=	-I./project/core/game/Wall/.
CXXFLAGS	+=	-I./project/core/exception/.
CXXFLAGS	+=	-I./project/core/menu/.
CXXFLAGS	+=	-I./lib/rapidxml-1.13/.
CXXFLAGS	+=	-I./lib/LibBomberman_linux_x64/includes/.
CXXFLAGS	+=	-I./project/UI/GDL/include/.
CXXFLAGS	+=	-I./project/sound/.
CXXFLAGS	+=	-I./lib/fmodstudioapi10603linux/api/lowlevel/inc/.
CXXFLAGS        +=      -I./lib/libSDL2/.
CXXFLAGS        +=      -I./lib/libvpx-1.4.0/vpx/.
CXXFLAGS        +=      -I./lib/libvpx-1.4.0/.
CXXFLAGS        +=      -I./lib/playvpx/.
CXXFLAGS        +=      -I./project/UI/MenuSDL/include/.

NAME		=	bomberman

SRCS		=	./project/core/bomberman/bomberman.cpp			\
			./project/main.cpp					\
			./project/core/game/map/maps.cpp			\
			./project/core/menu/menu.cpp				\
			./project/core/game/Box/Box.cpp				\
			./project/core/game/Case/Case.cpp			\
			./project/core/game/Wall/Wall.cpp			\
			./project/core/game/CaseFactory/CaseFactory.cpp		\
			./project/UI/GDL/Game/GameEngine.cpp			\
			./project/UI/GDL/Game/Camera.cpp			\
			./project/UI/GDL/Game/TextureManager.cpp		\
			./project/UI/GDL/Object/Cube.cpp			\
			./project/UI/GDL/Object/Ground.cpp			\
			./project/UI/GDL/Object/CharacterUI.cpp			\
			./project/UI/GDL/Object/Skybox.cpp			\
			./project/core/game/players/character.cpp		\
			./project/core/game/players/Player.cpp			\
			./project/core/game/players/Bot.cpp			\
			./project/core/game/Bomb/Bomb.cpp			\
			./project/core/game/Bomb/CaseAction.cpp			\
			./project/core/game/Boost/Boost.cpp			\
			./project/core/game/BombUp/BombUp.cpp			\
			./project/core/game/PowerUp/PowerUp.cpp			\
			./project/core/game/BonusFactory/BonusFactory.cpp	\
			./project/core/game/Save/Save.cpp			\
			./project/sound/SoundManager.cpp			\
			./project/UI/MenuSDL/src/Menu_SDL.cpp			\
			./project/UI/MenuSDL/src/SDL_Class.cpp			\
			./lib/playvpx/playvpx.cpp				\

OBJS		=	$(SRCS:.cpp=.o)

all:			$(NAME)

$(NAME):		$(OBJS)
			$(CXX) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
			$(RM) $(OBJS)

fclean:			clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:			fclean clean all
