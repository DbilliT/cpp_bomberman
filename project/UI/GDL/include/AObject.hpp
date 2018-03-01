//
// AObject.hh for Graphic in /home/calatr_m/test
// 
// Made by Caltraba Mickael
// Login   <calatr_m@epitech.net>
// 
// Started on  Tue May 19 13:36:15 2015 Caltraba Mickael
// Last update Thu Jun 11 23:59:26 2015 Caltraba Mickael
//

#ifndef _AOBJECT_HH_
# define _AOBJECT_HH_

#include <SdlContext.hh>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <AShader.hh>
#include "ICase.hpp"

class Player;
class IBonus;

class AObject
{
public:
  AObject(float x, float y, float z, float a, float b, float c) : 
    _position(x, z, y),
    _rotation(0, 0, 0),
    _scale(a, c, b)
  {
    _time = clock();
    _x = static_cast<float>(x);
    _y = static_cast<float>(y);
  }
  virtual ~AObject() {}

  virtual bool	initialize() {return (true);}
  virtual void	checkKey(gdl::Clock const &clock, gdl::Input &input)
  {(void)clock;(void)input;}
  virtual void	update(gdl::Input &input, float speed)
  {(void)input;(void)speed;}
  virtual void	draw(gdl::AShader &shader, gdl::Clock const &clock) = 0;
  
  void			translate(glm::vec3 const &v){_position += v;}
  void			rotate(glm::vec3 const &axis, float angle)
  {_rotation = axis * angle;}
  void			addRotate(glm::vec3 const &axis)
  {_rotation += axis;}
  void			scale(glm::vec3 const &scale){_scale *= scale;}
  float			getX() const {return (_x);}
  float			getY() const {return (_y);}
  void			setPos(int x, int y)
  {
    glm::vec3	pos(x, 0, y);
    _position = pos;
  }
  glm::mat4		getTransformation()
  {
    glm::mat4	transform(1);
    transform = glm::translate(transform, _position);
    transform = glm::scale(transform, _scale);
    transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
    transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
    transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));

    return (transform);
  }
  bool		updateFire() const
  {
    clock_t       elapsed = clock() - _time;
    
    if (static_cast<float>(elapsed)/CLOCKS_PER_SEC >= 0.15)
      return (false);
    return (true);
  }

protected:  
  clock_t               _time;
  glm::vec3	_position;
  glm::vec3	_rotation;
  glm::vec3	_scale;
  float		_x;
  float		_y;
};

#endif
