//
// Save.cpp for Save in /home/bechad_p/rendu/cpp_bomberman/project/core/game/Save
// 
// Made by Pierre Bechade
// Login   <bechad_p@epitech.net>
// 
// Started on  Mon Jun  8 17:11:42 2015 Pierre Bechade
// Last update Sun Jun 14 15:23:56 2015 Pierre Bechade
//

#include "bomberman.hpp"

Save::Save(const std::vector<ICase **> &maps, const std::pair<unsigned int, unsigned int> &size_map, const std::list<Player> &players, const std::list<Bot> &bot, int w, int h) : _map(maps), _size_map(size_map), _info_players(players), _info_IA(bot), _widht(w), _height(h)
{
}

Save::~Save()
{
}

void	Save::CreateSave()
{
  this->currentDateTime();
  this->xmlSave();
  this->screenSave();
}

void    Save::xmlSave() const
{
  rapidxml::xml_document<> doc;
  rapidxml::xml_node<>* decl = doc.allocate_node(rapidxml::node_declaration);
  std::list<std::string *>	_free;
  decl->append_attribute(doc.allocate_attribute("version", "1.0"));
  doc.append_node(decl);

  rapidxml::xml_node<>* root = doc.allocate_node(rapidxml::node_element, "map");

  std::string s = std::to_string(this->_size_map.first);
  char const *pchar_y = s.c_str();
  std::string s2 = std::to_string(this->_size_map.second);
  char const *pchar_x = s2.c_str();

  root->append_attribute(doc.allocate_attribute("x", pchar_x));
  root->append_attribute(doc.allocate_attribute("y", pchar_y));
  doc.append_node(root);

  unsigned int x, y;
  char *s6;
  std::ofstream file_stored("data/save/save_" + this->_ctime + ".xml");
  std::string xml_as_string;

  for (y = 0; y < this->_size_map.first; y++)
    {
      for (x = 0; x < this->_size_map.second; x++)
        {
          if (this->_map[y][x]->getType() != EMPTY)
            {
	      _free.push_back(new std::string(std::to_string(x)));
	      std::string *s0 = _free.back();
	      _free.push_back(new std::string(std::to_string(y)));
	      std::string *s1 = _free.back();
              s6 = new char[2];
              s6[0] = this->_map[y][x]->getType() + '0';
              s6[1] = '\0';
	      
	      rapidxml::xml_node<>* child = doc.allocate_node(rapidxml::node_element, "case");
              child->append_attribute(doc.allocate_attribute("x", s0->c_str()));
              child->append_attribute(doc.allocate_attribute("y", s1->c_str()));
              child->append_attribute(doc.allocate_attribute("type", s6));
              root->append_node(child);
            }
        }
      x = 0;
    }
  rapidxml::xml_node<>* root2 = doc.allocate_node(rapidxml::node_element, "character");
  if (!this->_info_players.empty() || !this->_info_IA.empty())
    doc.append_node(root2);
  if (!this->_info_players.empty())
    {
      for (std::list<Player>::const_iterator it=this->_info_players.begin(); it != this->_info_players.end(); ++it)
        {
	  _free.push_back(new std::string((*it).getName()));
	  std::string *s0 = _free.back();
	  _free.push_back(new std::string(std::to_string((*it).getX())));
	  std::string *s1 = _free.back();
	  _free.push_back(new std::string(std::to_string((*it).getY())));
	  std::string *s2 = _free.back();
	  _free.push_back(new std::string(std::to_string((*it).getColor())));
	  std::string *s3 = _free.back();
	  _free.push_back(new std::string(std::to_string((*it).getSpeed())));
	  std::string *s4 = _free.back();
	  _free.push_back(new std::string(std::to_string((*it).getBombPower())));
	  std::string *s5 = _free.back();
	  _free.push_back(new std::string(std::to_string((*it).getNbBomb())));
	  std::string *s6 = _free.back();
	  rapidxml::xml_node<>* child = doc.allocate_node(rapidxml::node_element, "player");
          child->append_attribute(doc.allocate_attribute("human", "true"));
          child->append_attribute(doc.allocate_attribute("name", s0->c_str()));
          child->append_attribute(doc.allocate_attribute("x", s1->c_str()));
          child->append_attribute(doc.allocate_attribute("y", s2->c_str()));
          child->append_attribute(doc.allocate_attribute("color", s3->c_str()));
          child->append_attribute(doc.allocate_attribute("speed", s4->c_str()));
          child->append_attribute(doc.allocate_attribute("power", s5->c_str()));
          child->append_attribute(doc.allocate_attribute("bomb", s6->c_str()));
          root2->append_node(child);
        }
    }
  if (!this->_info_IA.empty())
    {
      for (std::list<Bot>::const_iterator it=this->_info_IA.begin(); it != this->_info_IA.end(); ++it)
        {
	  _free.push_back(new std::string(std::to_string((*it).getX())));
	  std::string *s1 = _free.back();
	  _free.push_back(new std::string(std::to_string((*it).getY())));
	  std::string *s2 = _free.back();
	  _free.push_back(new std::string(std::to_string((*it).getColor())));
	  std::string *s3 = _free.back();
	  _free.push_back(new std::string(std::to_string((*it).getSpeed())));
	  std::string *s4 = _free.back();
	  _free.push_back(new std::string(std::to_string((*it).getBombPower())));
	  std::string *s5 = _free.back();
	  _free.push_back(new std::string(std::to_string((*it).getNbBomb())));
	  std::string *s6 = _free.back();
	  rapidxml::xml_node<>* child = doc.allocate_node(rapidxml::node_element, "player");
          child->append_attribute(doc.allocate_attribute("human", "false"));
          child->append_attribute(doc.allocate_attribute("x", s1->c_str()));
          child->append_attribute(doc.allocate_attribute("y", s2->c_str()));
          child->append_attribute(doc.allocate_attribute("color", s3->c_str()));
          child->append_attribute(doc.allocate_attribute("speed", s4->c_str()));
          child->append_attribute(doc.allocate_attribute("power", s5->c_str()));
          child->append_attribute(doc.allocate_attribute("bomb", s6->c_str()));
          root2->append_node(child);
        }
    }
  rapidxml::print(std::back_inserter(xml_as_string), doc);
  file_stored << doc;
  file_stored.close();
  doc.clear();
  for (std::list<std::string *>::iterator it=_free.begin(); it != _free.end(); ++it)
    delete (*it);
}

void		Save::screenSave() const
{
  glPixelStorei(GL_PACK_ALIGNMENT, 1);

  int           Size = this->_widht * this->_height * 3;
  char          *buff = new char[Size];
  unsigned char TGAheader[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  unsigned char header[6] = { static_cast<unsigned char>((this->_widht % 256)),
                              static_cast<unsigned char>((this->_widht / 256)),
                              static_cast<unsigned char>((this->_height % 256)),
                              static_cast<unsigned char>((this->_height / 256)), 24, 0};
  std::FILE		*file;
  std::string		tmp;

  glReadPixels(static_cast<GLint>(0), static_cast<GLint>(0), static_cast<GLint>(this->_widht), static_cast<GLint>(this->_height), GL_BGR, GL_UNSIGNED_BYTE, buff);
  tmp = "data/saveScreen/screen";
  tmp += this->_ctime;
  tmp += ".tga";
  if (!(file = std::fopen(tmp.c_str(), "wb")))
    throw Wrong_file(tmp.c_str());
  std::fwrite(TGAheader, sizeof(unsigned char), 12, file);
  std::fwrite(header, sizeof(unsigned char), 6, file);
  std::fwrite(buff, sizeof(GLubyte), Size, file);
  std::fclose(file);
  delete buff;
}

std::string		Save::currentDateTime()
{
  std::time_t		now = std::time(0);
  std::tm		tstruct;
  char			buf[80];

  tstruct = *std::localtime(&now);
  std::strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
  std::string tmp = buf;
  this->_ctime = tmp;
  return (tmp);
}
