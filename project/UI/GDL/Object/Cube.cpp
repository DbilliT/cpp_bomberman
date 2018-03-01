//
// Cube.cpp for  in /home/calatr_m/test
// 
// Made by Caltraba Mickael
// Login   <calatr_m@epitech.net>
// 
// Started on  Fri May 22 15:34:10 2015 Caltraba Mickael
// Last update Fri Jun 12 23:41:55 2015 Caltraba Mickael
//

#include "Cube.hpp"

gdl::Geometry  *Cube::_geometry = NULL;

Cube::Cube(int x, int y, float z, float a, float b, float c, bool destroy,
	   gdl::Texture &texture) :
  AObject(x, y, z, a, b, c),
  _texture(texture),
  _destroy(destroy)
{
}
Cube::~Cube()
{
  _geometry = NULL;
}

bool	Cube::initialize()
{
  if (Cube::_geometry == NULL)
    {
      Cube::_geometry = new gdl::Geometry;

      this->_geometry->pushVertex(glm::vec3(0.5, -0.5, 0.5));
      this->_geometry->pushVertex(glm::vec3(0.5, 0.5, 0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, 0.5, 0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, -0.5, 0.5));
      this->_geometry->pushUv(glm::vec2(0.0f, 0.0f));
      this->_geometry->pushUv(glm::vec2(1.0f, 0.0f));
      this->_geometry->pushUv(glm::vec2(1.0f, 1.0f));
      this->_geometry->pushUv(glm::vec2(0.0f, 1.0f));
      this->_geometry->pushNormal(glm::vec3(0.0f, 0.0f, 1.0f));
      this->_geometry->pushNormal(glm::vec3(0.0f, 0.0f, 1.0f));
      this->_geometry->pushNormal(glm::vec3(0.0f, 0.0f, 1.0f));
      this->_geometry->pushNormal(glm::vec3(0.0f, 0.0f, 1.0f));

      this->_geometry->pushVertex(glm::vec3(0.5, -0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(0.5, 0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, 0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, -0.5, -0.5));
      this->_geometry->pushUv(glm::vec2(0.0f, 0.0f));
      this->_geometry->pushUv(glm::vec2(1.0f, 0.0f));
      this->_geometry->pushUv(glm::vec2(1.0f, 1.0f));
      this->_geometry->pushUv(glm::vec2(0.0f, 1.0f));
      this->_geometry->pushNormal(glm::vec3(0.0f, 0.0f, -1.0f));
      this->_geometry->pushNormal(glm::vec3(0.0f, 0.0f, -1.0f));
      this->_geometry->pushNormal(glm::vec3(0.0f, 0.0f, -1.0f));
      this->_geometry->pushNormal(glm::vec3(0.0f, 0.0f, -1.0f));

      this->_geometry->pushVertex(glm::vec3(0.5, -0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(0.5, 0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(0.5, 0.5, 0.5));
      this->_geometry->pushVertex(glm::vec3(0.5, -0.5, 0.5));
      this->_geometry->pushUv(glm::vec2(0.0f, 0.0f));
      this->_geometry->pushUv(glm::vec2(1.0f, 0.0f));
      this->_geometry->pushUv(glm::vec2(1.0f, 1.0f));
      this->_geometry->pushUv(glm::vec2(0.0f, 1.0f));
      this->_geometry->pushNormal(glm::vec3(1.0f, 0.0f, 0.0f));
      this->_geometry->pushNormal(glm::vec3(1.0f, 0.0f, 0.0f));
      this->_geometry->pushNormal(glm::vec3(1.0f, 0.0f, 0.0f));
      this->_geometry->pushNormal(glm::vec3(1.0f, 0.0f, 0.0f));

      this->_geometry->pushVertex(glm::vec3(-0.5, -0.5, 0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, 0.5, 0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, 0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, -0.5, -0.5));
      this->_geometry->pushUv(glm::vec2(0.0f, 0.0f));
      this->_geometry->pushUv(glm::vec2(1.0f, 0.0f));
      this->_geometry->pushUv(glm::vec2(1.0f, 1.0f));
      this->_geometry->pushUv(glm::vec2(0.0f, 1.0f));
      this->_geometry->pushNormal(glm::vec3(-1.0f, 0.0f, 0.0f));
      this->_geometry->pushNormal(glm::vec3(-1.0f, 0.0f, 0.0f));
      this->_geometry->pushNormal(glm::vec3(-1.0f, 0.0f, 0.0f));
      this->_geometry->pushNormal(glm::vec3(-1.0f, 0.0f, 0.0f));

      this->_geometry->pushVertex(glm::vec3(0.5, 0.5, 0.5));
      this->_geometry->pushVertex(glm::vec3(0.5, 0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, 0.5, -0.5));
      this->_geometry->pushVertex(glm::vec3(-0.5, 0.5, 0.5));
      this->_geometry->pushUv(glm::vec2(0.0f, 0.0f));
      this->_geometry->pushUv(glm::vec2(1.0f, 0.0f));
      this->_geometry->pushUv(glm::vec2(1.0f, 1.0f));
      this->_geometry->pushUv(glm::vec2(0.0f, 1.0f));
      this->_geometry->pushNormal(glm::vec3(0.0f, 1.0f, 0.0f));
      this->_geometry->pushNormal(glm::vec3(0.0f, 1.0f, 0.0f));
      this->_geometry->pushNormal(glm::vec3(0.0f, 1.0f, 0.0f));
      this->_geometry->pushNormal(glm::vec3(0.0f, 1.0f, 0.0f));

      this->_geometry->build();
    }
  return (true);
}

void	Cube::update(gdl::Input&input, float speed){(void)input;(void)speed;}
void    Cube::checkKey(gdl::Clock const &clock, gdl::Input&input)
{(void)input;(void)clock;}

void	Cube::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  (void)clock;
  this->_texture.bind();
  this->_geometry->draw(shader, getTransformation(), GL_QUADS);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
