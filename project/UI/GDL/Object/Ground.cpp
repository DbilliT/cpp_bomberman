//
// Ground.cpp for  in /home/calatr_m/cpp_rendu/CPP/cpp_bomberman/project/UI
// 
// Made by Caltraba Mickael
// Login   <calatr_m@epitech.net>
// 
// Started on  Fri May 29 16:35:30 2015 Caltraba Mickael
// Last update Thu Jun 11 23:57:44 2015 Caltraba Mickael
//

#include "Ground.hpp"

gdl::Geometry  *Ground::_geometry = NULL;

Ground::Ground(float x, float y, float z, float a, float b) :
  AObject(x, y, z, a, b, 0)
{
}
Ground::~Ground()
{
  _geometry = NULL;
}

bool    Ground::initialize()
{
  if (this->_texture.load("./project/UI/GDL/Ressources/Ground.tga") == false)
    {
      std::cerr << "Cannot load the cube texture" << std::endl;
      return (false);
    }
  if (Ground::_geometry == NULL)
    {
      Ground::_geometry = new gdl::Geometry;

      this->_geometry->pushVertex(glm::vec3(0.5,-0.5,-0.5));
      this->_geometry->pushVertex(glm::vec3(0.5,-0.5,0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5,-0.5,0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5,-0.5,-0.5));
      this->_geometry->pushUv(glm::vec2(0.0f,0.0f));
      this->_geometry->pushUv(glm::vec2(1.0f,0.0f));
      this->_geometry->pushUv(glm::vec2(1.0f,1.0f));
      this->_geometry->pushUv(glm::vec2(0.0f,1.0f)); 

      this->_geometry->build();
    }
  return (true);
}

void    Ground::update(gdl::Clock const &clock,gdl::Input&input,
		       std::list<AObject *> const &object)
{
  (void)clock;
  (void)input;
  (void)object;
}

void    Ground::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)clock;
  this->_texture.bind();
  this->_geometry->draw(shader, getTransformation(), GL_QUADS);
}

