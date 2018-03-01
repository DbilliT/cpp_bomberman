//
// Camera.hpp for  in /home/calatr_m/cpp_rendu/CPP/cpp_bomberman/project/UI/include
// 
// Made by Caltraba Mickael
// Login   <calatr_m@epitech.net>
// 
// Started on  Sat May 30 11:23:29 2015 Caltraba Mickael
// Last update Thu Jun 11 23:56:53 2015 Caltraba Mickael
//

#ifndef _CAMERA_HPP_
# define _CAMERA_HPP_

#include <BasicShader.hh>
#include <vector>
#include "CharacterUI.hpp"

class Camera
{
public:
  Camera();
  ~Camera();
  
  void		initialize(gdl::BasicShader &,
			   std::vector<CharacterUI *> const &,
			   std::vector<CharacterUI *> const &,
			   unsigned int const, bool);
  void		update(gdl::BasicShader &, std::vector<CharacterUI *> const &,
		       std::vector<CharacterUI *> const &);
  void		updateCameraMenu(gdl::BasicShader &);


  std::pair<float, std::pair<float, float> >	getPoint() const;


  void		calculationPoint(std::vector<CharacterUI *> const &,
				 std::vector<CharacterUI *> const &);
  std::pair<float, float>	findX(std::vector<CharacterUI *> const &);
  std::pair<float, float>	findY(std::vector<CharacterUI *> const &);
  
private:
  glm::mat4					_transformation;
  glm::mat4					_projection;
  std::pair<float, std::pair<float, float> >	_pointView;
  unsigned int					_size;
  bool						_fixPoint;
};

#endif
