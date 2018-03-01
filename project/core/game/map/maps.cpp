//
// maps.cpp for maps in /home/bechad_p/rendu/cpp_bomberman/project/core/maps
// 
// Made by Pierre Bechade
// Login   <bechad_p@epitech.net>
// 
// Started on  Mon May 11 17:15:25 2015 Pierre Bechade
// Last update Sun Jun 14 16:17:09 2015 Pierre Bechade
//

#include "bomberman.hpp"
#include "CaseFactory.hpp"

Maps::Maps(const std::string &pfile, unsigned int nb_human, unsigned int nb_IA, const std::pair<std::string, std::string> &names) :
  _nb_human(nb_human),
  _nb_IA(nb_IA),
  _names(names)
{
  _factory = new CaseFactory;
  std::ifstream	infile(pfile);
  if (!infile.good())
    throw Wrong_file(pfile);
  this->parseMap(pfile, false);
}

Maps::Maps(const std::string &pfile) : _nb_human(0), _nb_IA(0)
{
  _factory = new CaseFactory;
  std::ifstream	infile(pfile);
  if (!infile.good())
    throw Wrong_file(pfile);
  this->parseMap(pfile, true);
}

Maps::Maps(const std::pair<unsigned int, unsigned int> &size_map, unsigned int nb_human, unsigned int nb_IA, const std::pair<std::string, std::string> &names) :
  _nb_human(nb_human),
  _nb_IA(nb_IA),
  _size_map(size_map),
  _names(names)
{
  if (((this->_size_map.first * this->_size_map.second) / 3) < (this->_nb_human + this->_nb_IA))
    throw std::invalid_argument("Choose a size of map that can handle the nombers of players you selected");
  if (this->_nb_human == 0 && this->_nb_IA == 0)
    throw std::invalid_argument("You don't have any players, please choose more than 0 player(s) to play.");
  _factory = new CaseFactory;
  this->randomMap();
}

Maps::~Maps()
{
}

void	Maps::randomMap()
{
  this->initMap();
  this->randomFill();
  this->placePlayer();
}

void	Maps::algoPosition()
{
  unsigned int	nb_total, i;
  int rd = 0, rd2 = 0, result = 0, tmp_pos = 0, tmp_pos2 = 0, i2 = 0, y = 0;
  std::vector<std::pair<unsigned int, unsigned int> > new_pos;
  std::vector<std::pair<int, std::pair<int, int> > >		vector_tmp;
  std::vector<std::pair<int, std::pair<int, int> > >		check_pos;
  std::vector<std::pair<int, std::pair<int, int> > >		max_value;

  i = 0;
  nb_total = this->_nb_human + this->_nb_IA;
  new_pos.push_back(this->_pos_players.at(rd).at(rd2));
  this->_pos_players.erase(this->_pos_players.begin()+rd);

  while (new_pos.size() < nb_total)
    {
      for (std::vector<std::vector<std::pair <unsigned int, unsigned int> > >::iterator it = this->_pos_players.begin() ; it != this->_pos_players.end(); ++it)
	{
	  for (std::vector<std::pair <unsigned int, unsigned int> >::iterator it3 = new_pos.begin() ; it3 != new_pos.end(); ++it3)
	    {
	      for (std::vector<std::pair <unsigned int, unsigned int> >::iterator it2 = (*it).begin() ; it2 != (*it).end(); ++it2)
		{
		  result = abs((static_cast<int>((*it3).second) - static_cast<int>((*it2).second))) + abs((static_cast<int>((*it3).first) - static_cast<int>((*it2).first)));
		  vector_tmp.push_back(std::make_pair(result, std::make_pair(y, i2)));
		  i2++;
		}
	      i2 = 0;
	      std::sort(vector_tmp.rbegin(), vector_tmp.rend());
	      check_pos.push_back(vector_tmp.front());
	      vector_tmp.clear();
	    }
	  std::sort(check_pos.begin(), check_pos.end());
	  if (max_value.empty())
	    max_value = check_pos;
	  else if (check_pos.front().first > max_value.front().first)
	    {
	      max_value = check_pos;
	      tmp_pos2 = max_value.front().second.first;
	      tmp_pos = max_value.front().second.second;
	    }
	  y++;
	  check_pos.clear();
	}
      max_value.clear();
      new_pos.push_back(this->_pos_players.at(tmp_pos2).at(tmp_pos));
      this->_pos_players.erase(this->_pos_players.begin()+tmp_pos2);
      i2 = 0, y = 0, tmp_pos = 0, tmp_pos2 = 0;
    }

  for (std::vector<std::pair <unsigned int, unsigned int> >::iterator it = new_pos.begin() ; it != new_pos.end(); ++it)
    {
      if (i < this->_nb_human)
	{
	  this->_info_players.push_back(Player(std::make_pair(((*it).first), (*it).second), 0, this->_names.first));
	  std::swap(this->_names.first, this->_names.second);
	}
      else
	this->_info_IA.push_back(Bot(std::make_pair((*it).first, (*it).second), 0));
      i++;
    }

}

bool			Maps::placePlayer()
{
  std::vector<ICase **> tmp;

  for (unsigned int y = 0; y < this->_size_map.first; y++)
    {
      tmp.push_back(new ICase *[this->_size_map.second]);
      for (unsigned int x = 0; x < this->_size_map.second; x++)
	tmp[y][x] = this->_factory->CreateCase(this->_map[y][x]->getType());
    }
  this->_tmp_map = tmp;
  for (unsigned int y = 0; y < this->_size_map.first; y++)
    {
      for (unsigned int x = 0; x < this->_size_map.second; x++)
	if (this->_tmp_map[y][x]->getType() == EMPTY && this->isPlacable(std::make_pair(y, x), tmp, 1) == true)
	  {
	    delete this->_tmp_map[y][x];
	    this->_tmp_map[y][x] = this->_factory->CreateCase(WALL);
	    this->_pos_tmp.push_back(std::make_pair(y, x));
	    this->_pos_players.push_back(this->_pos_tmp);
	    this->_pos_tmp.clear();
	  }
	else
	  this->_pos_tmp.clear();
    }

  if (this->_pos_players.size() < (this->_nb_human + this->_nb_IA))
    {
      tmp.clear();
      for (unsigned int y = 0; y < this->_size_map.first; y++)
  	{
  	  for (unsigned int x = 0; x < this->_size_map.second; x++)
  	    {
  	      if (((this->_map[y][x]->getType() == WALL) || (this->_map[y][x]->getType() == BOX)) && ((algoWall(std::make_pair(y, x)) == true) && rand() % 4 == 1))
  		  {
  		    delete this->_map[y][x];
  		    this->_map[y][x] = this->_factory->CreateCase(EMPTY);
  		  }
  	    }
  	}
      this->_pos_players.clear();
      this->_pos_tmp.clear();
      tmp.clear();
      return (placePlayer());
    }
  if (this->_pos_players.empty())
    throw std::runtime_error("The Generation of random map failed. Maybe choose a higher map size to avoid this issue");
  this->algoPosition();
  return (true);
}

bool	Maps::isPlacable(std::pair<int, int> const &pos_wall, std::vector<ICase **> &tmp, int nb_empty)
{
  int	x, y;

  if (nb_empty >= 3)
    {
      this->_tmp_map = tmp;
      return (true);
    }
  for (y = -1; y <= 1; y++)
    {
      x = 0;
      if (pos_wall.first + y >= 0 && pos_wall.first + y < static_cast<int>(this->_size_map.first))
	if (pos_wall.second + x >= 0 && pos_wall.second + x < static_cast<int>(this->_size_map.second))
	  if (tmp[pos_wall.first + y][pos_wall.second + x]->getType() == EMPTY && y != 0)
	    {
	      delete tmp[pos_wall.first][pos_wall.second];
	      tmp[pos_wall.first][pos_wall.second] = this->_factory->CreateCase(WALL);
	      this->_pos_tmp.push_back(std::make_pair(pos_wall.first + y, pos_wall.second + x));
	      return (isPlacable(std::make_pair(pos_wall.first + y, pos_wall.second + x), tmp, ++nb_empty));
	    }
    }
  for (x = -1; x <= 1; x++)
    {
      y = 0;
      if (pos_wall.first + y >= 0 && pos_wall.first + y < static_cast<int>(this->_size_map.first))
  	if (pos_wall.second + x >= 0 && pos_wall.second + x < static_cast<int>(this->_size_map.second))
	  if (tmp[pos_wall.first + y][pos_wall.second + x]->getType() == EMPTY && x != 0)
	    {
	      delete tmp[pos_wall.first][pos_wall.second];
	      tmp[pos_wall.first][pos_wall.second] = this->_factory->CreateCase(WALL);
	      this->_pos_tmp.push_back(std::make_pair(pos_wall.first + y, pos_wall.second + x));
	      return (isPlacable(std::make_pair(pos_wall.first + y, pos_wall.second + x), tmp, ++nb_empty));
	    }
    }
  if (nb_empty >= 3)
    {
      this->_tmp_map = tmp;
      return (true);
    }
  tmp.clear();
  return (false);
}

bool	Maps::algoWall(const std::pair<int, int> &pos_wall)
{
  int	x, y;

  for (y = -1; y <= 1; y++)
    {
      x = 0;
      if (pos_wall.first + y >= 0 && pos_wall.first + y < static_cast<int>(this->_size_map.first) && y != 0)
	if (pos_wall.second + x >= 0 && pos_wall.second + x < static_cast<int>(this->_size_map.second))
	  if (this->_map[pos_wall.first + y][pos_wall.second + x]->getType() == EMPTY || this->_map[pos_wall.first + y][pos_wall.second + x]->getType() == BOX)
	    return (true);
    }
  for (x = -1; x <= 1; x++)
    {
      y = 0;
      if (pos_wall.first + y >= 0 && pos_wall.first + y < static_cast<int>(this->_size_map.first) && x != 0)
	if (pos_wall.second + x >= 0 && pos_wall.second + x < static_cast<int>(this->_size_map.second))
	  if (this->_map[pos_wall.first + y][pos_wall.second + x]->getType() == EMPTY || this->_map[pos_wall.first + y][pos_wall.second + x]->getType() == BOX)
	    return (true);
    }
  return (false);
}

void	Maps::destroyWall(const std::pair<int, int> &pos_wall)
{
  delete this->_map[pos_wall.first][pos_wall.second];
  this->_map[pos_wall.first][pos_wall.second] = this->_factory->CreateCase(EMPTY);
}

void	Maps::initMap()
{
  unsigned int i, j;

  for (i = 0; i < this->_size_map.first; i++)
    {
      this->_map.push_back(new ICase *[this->_size_map.second]);
      for (j = 0; j < this->_size_map.second; j++)
	this->_map[i][j] = this->_factory->CreateCase(EMPTY);
    }
}

void	Maps::randomFill()
{
  const int maze_size_x=this->_size_map.second;
  const int maze_size_y=this->_size_map.first;
  std::vector < std::vector < bool > > maze;
  std::list < std::pair < int, int> > drillers;

  maze.resize(maze_size_y);
  for (int y=0;y<maze_size_y;y++)
    maze[y].resize(maze_size_x);

  for (int x=0;x<maze_size_x;x++)
    for (int y=0;y<maze_size_y;y++)
      maze[y][x]=false;

  int p = 0;
  drillers.push_back(std::make_pair(maze_size_x/2,maze_size_y/2));
  std::list < std::pair < int, int> >::iterator m,_m;
  while (p != 2)
    {
      if (drillers.size() == 0)
	{
	  drillers.clear();
	  if (maze_size_x > 10)
	    drillers.push_back(std::make_pair(maze_size_x/2 - (p * 2),maze_size_y/2));
	  else if (maze_size_y > 10)
	    drillers.push_back(std::make_pair(maze_size_x/2, maze_size_y/2 - (p * 2)));
	  else
	    drillers.push_back(std::make_pair(maze_size_x/2,maze_size_y/2));
	  p++;
	}
      m=drillers.begin();
      _m=drillers.end();
      while (m != drillers.end())
        {
          bool remove_driller=false;
          switch(rand()%4)
            {
            case 0:
              (*m).second-=2;
              if ((*m).second<0 || maze[(*m).second][(*m).first])
                {
                  remove_driller=true;
                  break;
                }
              maze[(*m).second+1][(*m).first]=true;
              break;
            case 1:
              (*m).second+=2;
              if ((*m).second>=maze_size_y || maze[(*m).second][(*m).first])
                {
                  remove_driller=true;
                  break;
                }
              maze[(*m).second-1][(*m).first]=true;
              break;
            case 2:
              (*m).first-=2;
              if ((*m).first<0 || maze[(*m).second][(*m).first])
                {
                  remove_driller=true;
                  break;
                }
              maze[(*m).second][(*m).first+1]=true;
              break;
            case 3:
              (*m).first+=2;
              if ((*m).first>=maze_size_x || maze[(*m).second][(*m).first])
                {
                  remove_driller=true;
                  break;
                }
              maze[(*m).second][(*m).first-1]=true;
              break;
            }
          if (remove_driller)
            m = drillers.erase(m);
          else
            {
              drillers.push_back(std::make_pair((*m).first,(*m).second));
              drillers.push_back(std::make_pair((*m).first,(*m).second));
              maze[(*m).second][(*m).first]=true;
              ++m;
            }
        }
    }

  for (int y = 0; y < maze_size_y; y++)
    {
      for (int x = 0; x < maze_size_x; x++)
	{
	  if (maze[y][x]==false)
	    this->_map[y][x] = _factory->CreateCase(WALL);
	  else if (rand() % 10 < 3)
	    this->_map[y][x] = _factory->CreateCase(EMPTY);
	  else
	    this->_map[y][x] = _factory->CreateCase(BOX);
	}
    }
  for (int y = 0; y < maze_size_y; y++)
    {
      for (int x = 0; x < maze_size_x; x++)
  	{   
  	  if (this->_map[y][x]->getType() == WALL && rand() % 3 < 2 && algoWall(std::make_pair(y, x)) == true)
  	    {
	      delete this->_map[y][x];
  	      if (rand()% 3 < 1)
		this->_map[y][x] = _factory->CreateCase(EMPTY);
  	      else
		this->_map[y][x] = _factory->CreateCase(BOX);
  	    }
  	}
    }
  if (isOnlyWall() == true)
    {
      delete this->_map[this->_size_map.first/2][this->_size_map.second/2];
      this->_map[this->_size_map.first/2][this->_size_map.second/2] = _factory->CreateCase(EMPTY);
      for (unsigned int y = 0; y < this->_size_map.first; y++)
	{
	  for (unsigned int x = 0; x < this->_size_map.second; x++)
	    {
	      if (rand() % 2 == 1 && algoWall(std::make_pair(y, x)))
		{
		  delete this->_map[y][x];
		  this->_map[y][x] = _factory->CreateCase(BOX);
		}
	      else if (rand() % 2 == 1 && algoWall(std::make_pair(y, x)))
		{
		   delete this->_map[y][x];
		  this->_map[y][x] = _factory->CreateCase(EMPTY);
		}
	    }
	}
    }
}

bool	Maps::isOnlyWall() const
{
  
  for (unsigned int y = 0; y < this->_size_map.first; y++)
    {
      for (unsigned int x = 0; x < this->_size_map.second; x++)
	if (this->_map[y][x]->getType() != WALL)
	  return (false);
    }
  return (true);
}

void	Maps::parseMap(const std::string &pfile, bool Continue)
{
  rapidxml::xml_document<> doc;
  rapidxml::xml_node<> * root_node;
  std::ifstream theFile (pfile);
  std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());

  buffer.push_back('\0');
  doc.parse<0>(&buffer[0]);
  root_node = doc.first_node("map");

  this->_size_map = std::make_pair(std::atoi(root_node->first_attribute("y")->value()), std::atoi(root_node->first_attribute("x")->value()));
  this->initMap();

  for (rapidxml::xml_node<> * case_node = root_node->first_node("case"); case_node; case_node = case_node->next_sibling())
    this->_map[std::atoi(case_node->first_attribute("y")->value())][std::atoi(case_node->first_attribute("x")->value())] = this->_factory->CreateCase(static_cast<CaseType>(std::atoi(case_node->first_attribute("type")->value())));

  if (Continue == true)
    {
      root_node = doc.first_node("character");

      for (rapidxml::xml_node<> * player_node = root_node->first_node("player"); player_node; player_node = player_node->next_sibling())
	{
	  if (std::strncmp(player_node->first_attribute("human")->value(), "true", 4) == 0)
	    this->_info_players.push_back(Player(std::make_pair(std::atoi(player_node->first_attribute("y")->value())+0.5, std::atoi(player_node->first_attribute("x")->value())+0.5), std::atoi(player_node->first_attribute("color")->value()), player_node->first_attribute("name")->value(), std::atoi(player_node->first_attribute("speed")->value()), std::atoi(player_node->first_attribute("power")->value()), std::atoi(player_node->first_attribute("bomb")->value())));
	  else
	    this->_info_IA.push_back(Bot(std::make_pair(std::atoi(player_node->first_attribute("y")->value())+0.5, std::atoi(player_node->first_attribute("x")->value())+0.5), std::atoi(player_node->first_attribute("color")->value()), std::atoi(player_node->first_attribute("speed")->value()), std::atoi(player_node->first_attribute("power")->value()), std::atoi(player_node->first_attribute("bomb")->value())));
	}
    }
  else
    {
      if (((this->_size_map.first * this->_size_map.second) / 3) < (this->_nb_human + this->_nb_IA))
	throw std::invalid_argument("Choose a size of map that can handle the nombers of players you selected");
      for (unsigned int y = 0; y < this->_size_map.first; y++)
	{
	  for (unsigned int x = 0; x < this->_size_map.second; x++)
	    {
	      if (this->_map[y][x]->getType() == EMPTY)
		{
		  this->_pos_tmp.push_back(std::make_pair(y, x));
		  this->_pos_players.push_back(this->_pos_tmp);
		  this->_pos_tmp.clear();
		}
	    }
	}
      if (this->_pos_players.size() < (this->_nb_human + this->_nb_IA))
	throw std::invalid_argument("Choose a size of map that can handle the nombers of players you selected");
      this->algoPosition();
    }
}

std::vector<ICase **> const &Maps::getMap() const
{
  return (this->_map);
}

const std::pair<unsigned int, unsigned int> &Maps::getSizeMap() const
{
  return (this->_size_map);
}

const std::vector<std::vector<std::pair<unsigned int, unsigned int> > > &Maps::getPosPlayers() const
{
  return (this->_pos_players);
}

std::list<Player> const &Maps::getInfoPlayers() const
{
  return (this->_info_players);
}

std::list<Bot> const &Maps::getInfoBot() const
{
  return (this->_info_IA);
}
