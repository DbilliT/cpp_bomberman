//
// Sound.hpp for Sound in /home/bechad_p/rendu/cpp_bomberman/project/sound
// 
// Made by Pierre Bechade
// Login   <bechad_p@epitech.net>
// 
// Started on  Wed Jun  3 14:26:00 2015 Pierre Bechade
// Last update Tue Jun  9 17:28:22 2015 Pierre Bechade
//

#include <fmod.hpp>
#include <fmod.h>

class SoundManager
{
public:
  static SoundManager &Instance();
  //----LOAD------//
  void	loadSound();
  void	loadMusic();
  //----PLAY------//
  void	playSound(const std::string &pfile);
  void	loadOneSound(const std::string &pfile);
  void  playMusic(const std::string &pfile, int loop);
  void  loadOneMusic(const std::string &pfile, bool loop);
  void	repeatMusic(const std::string &pfile, int nb);
  //----VOLUME----//
  void	setVolumeMusic(float);
  void	setVolumeSound(float);
  void	setPause(int state);
  void	stopMusic();
private:
  FMOD::System				*_system;
  FMOD_RESULT				_result;

  FMOD::Channel				*_musicChannel;
  FMOD::Channel				*_soundChannel;

  std::map<std::string, FMOD::Sound*>	_noise;
  int					_volumeSound;
  int					_volumeMusic;

  SoundManager (const SoundManager&){}
  static SoundManager m_instance;
  SoundManager();
  ~SoundManager();
};
