//
// Skybox.cpp for  in /home/calatr_m/cpp_rendu/CPP/cpp_bomberman/project/UI
// 
// Made by Caltraba Mickael
// Login   <calatr_m@epitech.net>
// 
// Started on  Sun Jun  7 16:00:39 2015 Caltraba Mickael
// Last update Fri Jun 12 00:00:44 2015 Caltraba Mickael
//

#include "Skybox.hpp"

Skybox::Skybox(int x, int y, int z, float a) :
  AObject(x, y, z, a, a, a)
{
  this->_resource[0] = "./project/UI/GDL/Ressources/Sun.tga";
  this->_resource[1] = "./project/UI/GDL/Ressources/Right.tga";
  this->_resource[2] = "./project/UI/GDL/Ressources/Left.tga";
  this->_resource[3] = "./project/UI/GDL/Ressources/Down.tga";
}
Skybox::~Skybox()
{
}

bool    Skybox::initializeBox(int i)
{
  this->_geometry = new gdl::Geometry;
  if (this->_texture.load(this->_resource[static_cast<int>(i)]) == false)
    {
      std::cerr << "Cannot load the cube texture" << std::endl;
      return (false);
    }
  if (i == 0)
    {
      this->_geometry->pushVertex(glm::vec3(0.5, -0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(0.5, 0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, 0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, -0.5, -0.5));
      this->_geometry->pushUv(glm::vec2(0.0f, 0.0f));
      this->_geometry->pushUv(glm::vec2(1.0f, 0.0f));
      this->_geometry->pushUv(glm::vec2(1.0f, 1.0f));
      this->_geometry->pushUv(glm::vec2(0.0f, 1.0f));
    }
  else if (i == 1)
    {
      this->_geometry->pushVertex(glm::vec3(0.5, -0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(0.5, 0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(0.5, 0.5, 0.5));
      this->_geometry->pushVertex(glm::vec3(0.5, -0.5, 0.5));
      this->_geometry->pushUv(glm::vec2(0.0f, 0.0f));
      this->_geometry->pushUv(glm::vec2(1.0f, 0.0f));
      this->_geometry->pushUv(glm::vec2(1.0f, 1.0f));
      this->_geometry->pushUv(glm::vec2(0.0f, 1.0f));
    }
  else if (i == 2)
    {
      this->_geometry->pushVertex(glm::vec3(-0.5, -0.5, 0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, 0.5, 0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, 0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, -0.5, -0.5));
      this->_geometry->pushUv(glm::vec2(0.0f, 0.0f));
      this->_geometry->pushUv(glm::vec2(1.0f, 0.0f));
      this->_geometry->pushUv(glm::vec2(1.0f, 1.0f));
      this->_geometry->pushUv(glm::vec2(0.0f, 1.0f));
    }
  else
    {
      this->_geometry->pushVertex(glm::vec3(0.5, -0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(0.5, -0.5, 0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, -0.5, 0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, -0.5, -0.5));
      this->_geometry->pushUv(glm::vec2(0.0f, 0.0f));
      this->_geometry->pushUv(glm::vec2(1.0f, 0.0f));
      this->_geometry->pushUv(glm::vec2(1.0f, 1.0f));
      this->_geometry->pushUv(glm::vec2(0.0f, 1.0f));
    }

  this->_geometry->build();
  return (true);
}

void    Skybox::update(gdl::Input&input, float speed){(void)input;(void)speed;}
void    Skybox::checkKey(gdl::Clock const &clock, gdl::Input&input)
{(void)input;(void)clock;}

void    Skybox::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)clock;
  this->_texture.bind();
  this->_geometry->draw(shader, getTransformation(), GL_QUADS);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

