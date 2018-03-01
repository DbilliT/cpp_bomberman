//
// Camera.cpp for  in /home/calatr_m/cpp_rendu/CPP/cpp_bomberman/project/UI/Game
// 
// Made by Caltraba Mickael
// Login   <calatr_m@epitech.net>
// 
// Started on  Sat May 30 11:23:39 2015 Caltraba Mickael
// Last update Fri Jun 12 06:30:39 2015 Caltraba Mickael
//

#include "Camera.hpp"

Camera::Camera()
{
}
Camera::~Camera()
{
}

std::pair<float, std::pair<float, float> >	Camera::getPoint() const
{return (this->_pointView);}

void            Camera::initialize(gdl::BasicShader &shader,
				   std::vector<CharacterUI *> const &character,
				   std::vector<CharacterUI *> const &ia,
				   unsigned int const size, bool point)
{
  this->_projection = glm::perspective(60.0f,
				       1920.0f / 1080.0f,
				       1.0f, 100000.0f);
  shader.bind();
  shader.setUniform("projection", this->_projection);
  this->_size = size;
  this->_fixPoint = point;
  update(shader, character, ia);
}

void		Camera::update(gdl::BasicShader &shader,
			       std::vector<CharacterUI *> const &character,
			       std::vector<CharacterUI *> const &ia)
{
  calculationPoint(character, ia);
  this->_transformation =
    glm::lookAt(glm::vec3(this->_pointView.second.first,
  			  this->_pointView.first + 3,
			  this->_pointView.second.second + 5),
  		glm::vec3(this->_pointView.second.first, 0,
			  this->_pointView.second.second),
  		glm::vec3(0, 1, 0));
  if (this->_fixPoint)
    {
      this->_transformation =
	glm::lookAt(glm::vec3(this->_size / 2,
			      this->_size + 4, (this->_size / 2) + 3),
		    glm::vec3(this->_size / 2, 0, this->_size / 2),
		    glm::vec3(0, 1, 0));
    }
  shader.bind();
  shader.setUniform("view", this->_transformation);
}

void            Camera::updateCameraMenu(gdl::BasicShader &shader)
{
  glm::mat4     transformation;

  transformation = glm::lookAt(glm::vec3(1.5, 2, 3),
                               glm::vec3(1.5, 0, 0),
                               glm::vec3(0, 1, 0));
  shader.bind();
  shader.setUniform("view", transformation);
}

void		Camera::calculationPoint(std::vector<CharacterUI *>
					 const &character,
					 std::vector<CharacterUI *> const &ia)
{
  std::pair<float, float>			pointC;
  std::pair<float, float>			pointI;

  pointC = findX(character);
  if (!ia.empty())
    {
      pointI = findX(ia);
      if (pointC.first < pointI.first)
	pointC.first = pointI.first;
      if (pointC.second > pointI.second)
	pointC.second = pointI.second;
    }
  this->_pointView.second.first = (pointC.first + pointC.second) / 2;
  this->_pointView.first = (-pointC.first / 2) + (pointC.second / 2);
  pointC = findY(character);
  if (!ia.empty())
    {
      pointI = findY(ia);
      if (pointC.first < pointI.first)
	pointC.first = pointI.first;
      if (pointC.second > pointI.second)
	pointC.second = pointI.second;
    }
  this->_pointView.second.second = (pointC.first + pointC.second) / 2;
  this->_pointView.first = (this->_pointView.first +
			    (-pointC.first) + (pointC.second)) * -1;
  this->_pointView.first = (this->_pointView.first *
			    (1 - (this->_size / 1080)));
  if (this->_pointView.first >= static_cast<int>(this->_size) - 2)
    this->_pointView.first = static_cast<int>(this->_size) - 2;
  if (this->_pointView.first < 3)
    this->_pointView.first = 3;
}

std::pair<float, float>		Camera::findX(std::vector<CharacterUI *>
					      const &vec)
{
  std::pair<float, float>	values;
  size_t			i;

  values.first = vec[0]->getX();
  values.second = vec[0]->getX();
  for (i = 0; i < vec.size(); ++i)
    {
      if (vec[i]->getX() > values.first)
	values.first = vec[i]->getX();
      if (vec[i]->getX() < values.second)
	values.second = vec[i]->getX();
    }
  return (values);
}

std::pair<float, float>		Camera::findY(std::vector<CharacterUI *>
					      const &vec)
{
  std::pair<float, float>	values;
  size_t			i;

  values.first = vec[0]->getY();
  values.second = vec[0]->getY();
  for (i = 0; i < vec.size(); ++i)
    {
      if (vec[i]->getY() > values.first)
	values.first = vec[i]->getY();
      if (vec[i]->getY() < values.second)
	values.second = vec[i]->getY();
    }
  return (values);
}
