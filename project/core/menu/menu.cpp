//
// menu.cpp for menu in /home/bechad_p/rendu/cpp_bomberman/project/UI/menu
// 
// Made by Pierre Bechade
// Login   <bechad_p@epitech.net>
// 
// Started on  Mon May 11 16:21:21 2015 Pierre Bechade
// Last update Sun Jun 14 17:18:21 2015 Pierre Bechade
//

#include "bomberman.hpp"

Menu::Menu()
{
  this->_isContinue = false;
  this->setFiles();
  this->setContinue();
  this->setHighscore();
  this->writeHighscore();
}

Menu::~Menu()
{
}

void	Menu::setHighscore()
{
  if (!this->_highscore.empty())
    this->_highscore.clear();
  rapidxml::xml_document<> doc;
  rapidxml::xml_node<> * root_node;
  std::ifstream theFile ("data/highscore/highscore.xml");
  if (!theFile.good())
    throw Wrong_file("data/highscore/highscore.xml");
  std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());

  buffer.push_back('\0');
  doc.parse<0>(&buffer[0]);
  root_node = doc.first_node("highscore");

  for (rapidxml::xml_node<> * player = root_node->first_node("player"); player; player = player->next_sibling())
    this->_highscore.push_back(std::make_pair(std::atoi(player->first_attribute("score")->value()), player->first_attribute("name")->value()));
  std::sort(this->_highscore.rbegin(), this->_highscore.rend());
}

void	Menu::writeHighscore()
{  
  rapidxml::xml_document<> doc;
  rapidxml::xml_node<>* decl = doc.allocate_node(rapidxml::node_declaration);
  decl->append_attribute(doc.allocate_attribute("version", "1.0"));
  doc.append_node(decl);

  rapidxml::xml_node<>* root = doc.allocate_node(rapidxml::node_element, "highscore");
  doc.append_node(root);
  std::ofstream file_stored("data/highscore/highscore.xml");
  std::string xml_as_string;
  for (std::vector<std::pair <int, std::string > >::const_iterator it = this->_highscore.begin() ; it != this->_highscore.end(); ++it)
    {
      std::string *s0 = new std::string(std::to_string((*it).first));
      rapidxml::xml_node<>* child = doc.allocate_node(rapidxml::node_element, "player");
      child->append_attribute(doc.allocate_attribute("name", (*it).second.c_str()));
      child->append_attribute(doc.allocate_attribute("score", s0->c_str()));
      root->append_node(child);
    }
  rapidxml::print(std::back_inserter(xml_as_string), doc);
  file_stored << doc;
  file_stored.close();
  doc.clear();
}

void	Menu::addHighscore(int score, const std::string &name)
{
  this->_highscore.push_back(std::make_pair(score, name));
  std::sort(this->_highscore.rbegin(), this->_highscore.rend());
}

void	Menu::setContinue()
{
  if (this->_files.empty())
    this->setFiles();
  if (this->_files.empty())
    {
      this->_isContinue = false;
      return ;
    }
  this->_continue = *(this->_files.end()-1);
  this->_isContinue = true;
}

void			Menu::setFiles()
{
  dirent*		de;
  DIR*			dp;
  const	std::string	path = "./data/save/";

  dp = opendir(path.empty() ? "." : path.c_str() );
  if (dp)
    {
      while (true)
  	{
  	  de = readdir(dp);
  	  if (de == NULL) break;
	  if (std::strncmp(de->d_name, "save_", 5) == 0)
	    this->_files.push_back( std::string( de->d_name ) );
  	}
      closedir(dp);
      std::sort(this->_files.begin(), this->_files.end());
    }
  else
    throw Wrong_file(path);
}

void			Menu::setMaps()
{
  dirent*		de;
  DIR*			dp;
  const	std::string	path = "./data/maps/";

  dp = opendir(path.empty() ? "." : path.c_str() );
  if (dp)
    {
      while (true)
  	{
  	  de = readdir(dp);
  	  if (de == NULL) break;
	  if (std::strncmp(de->d_name, ".", 1) != 0)
	    this->_Maps.push_back(std::string(de->d_name));
  	}
      closedir(dp);
      std::sort(this->_Maps.begin(), this->_Maps.end());
    }
  else
    throw Wrong_file(path);
}

const std::vector<std::string> &Menu::getFiles()
{ 
  if (this->_files.empty())
    this->setFiles();
  return (this->_files);
}

const std::vector<std::string> &Menu::getMaps()
{
  if (this->_Maps.empty())
    this->setMaps();
  return (this->_Maps);
}

const std::string &Menu::getContinue()
{
  if (this->_continue.empty())
    this->setContinue();
  return (this->_continue);
}

const std::vector<std::pair<int, std::string> > &Menu::getHighscore()
{
  if (this->_highscore.empty())
    this->setHighscore();
  return (this->_highscore);
}

const std::vector<std::string> &Menu::getCredit()
{
  if (this->_credit.empty())
    this->setCredit();
  return (this->_credit);
}

bool	Menu::getIsContinue()
{
  return (this->_isContinue);
}

void	Menu::setCredit()
{
  this->_credit.push_back("Bomberman crée par :");
  this->_credit.push_back("Paul David");
  this->_credit.push_back("Cedric De Lussigny");
  this->_credit.push_back("Alex Tanyeres");
  this->_credit.push_back("Pierre Béchade");
}

void	Menu::quit()
{
  std::exit(EXIT_SUCCESS);
}

void	Menu::load()
{
  return ;
}
