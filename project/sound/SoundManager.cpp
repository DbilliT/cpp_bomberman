//
// Sound.cpp for Sound.cpp in /home/bechad_p/rendu/cpp_bomberman/project/sound
// 
// Made by Pierre Bechade
// Login   <bechad_p@epitech.net>
// 
// Started on  Wed Jun  3 14:27:07 2015 Pierre Bechade
// Last update Sun Jun 14 16:32:44 2015 Pierre Bechade
//

#include "bomberman.hpp"
#include <fmod.hpp>

SoundManager SoundManager::m_instance=SoundManager();

SoundManager::SoundManager()
{
  this->_system = NULL;
  this->_result = FMOD::System_Create(&this->_system);
  this->_system->setOutput(FMOD_OUTPUTTYPE_DSOUND );
  this->_system->init(1024, FMOD_INIT_NORMAL, 0);
  this->_soundChannel = NULL;
  this->_musicChannel = NULL;
  this->_volumeSound = 1;
  this->_volumeMusic = 1;
}

SoundManager::~SoundManager()
{
  if (!this->_noise.empty())
    {
      this->_noise["data/sound/noise.wav/back.wav"]->release();
      this->_noise["data/sound/noise.wav/move.wav"]->release();
      this->_noise["data/sound/noise.wav/guncann.wav"]->release();
      this->_noise["data/sound/noise.wav/place_bomb.wav"]->release();
      this->_noise["data/sound/noise.wav/explose_bomb.wav"]->release();
      this->_noise["data/sound/noise.wav/win.wav"]->release();
      this->_noise["data/sound/noise.wav/kill.wav"]->release();
      this->_noise["data/sound/noise.wav/bonus.wav"]->release();

      this->_noise["data/sound/music.mp3/Pirate.mp3"]->release();
      this->_noise["data/sound/music.mp3/Intro.mp3"]->release();
      this->_noise["data/sound/music.mp3/IGame1.mp3"]->release();
    }
  this->_system->release();
}

SoundManager& SoundManager::Instance()
{
  return (m_instance);
}

void	SoundManager::loadSound()
{
  this->loadOneSound("data/sound/noise.wav/back.wav");
  this->loadOneSound("data/sound/noise.wav/move.wav");
  this->loadOneSound("data/sound/noise.wav/guncann.wav");
  this->loadOneSound("data/sound/noise.wav/win.wav");
  this->loadOneSound("data/sound/noise.wav/place_bomb.wav");
  this->loadOneSound("data/sound/noise.wav/explose_bomb.wav");
  this->loadOneSound("data/sound/noise.wav/kill.wav");
  this->loadOneSound("data/sound/noise.wav/bonus.wav");
}

void	SoundManager::loadOneSound(const std::string &pfile)
{
  this->_noise[pfile] = NULL;
  this->_result = this->_system->createSound(pfile.c_str(), FMOD_CREATESAMPLE,NULL, &this->_noise[pfile]);
  if(this->_result != FMOD_OK)
    throw SoundManagerIssue ("Can't load " + pfile);
}

void	SoundManager::loadMusic()
{
  this->loadOneMusic("data/sound/music.mp3/Pirate.mp3", true);
  this->loadOneMusic("data/sound/music.mp3/Intro.mp3", false);
  this->loadOneMusic("data/sound/music.mp3/IGame1.mp3", false);
}

void	SoundManager::loadOneMusic(const std::string &pfile, bool loop)
{
  this->_noise[pfile] = NULL;
  if (loop == true)
    {
      this->_result = this->_system->createStream(pfile.c_str(), FMOD_LOOP_NORMAL, 0, &this->_noise[pfile]);
      if(this->_result != FMOD_OK)
	throw SoundManagerIssue ("Can't load " + pfile);
    }
  else
    {
      this->_result = this->_system->createStream(pfile.c_str(), FMOD_CREATESAMPLE, 0, &this->_noise[pfile]);
      if(this->_result != FMOD_OK)
	throw SoundManagerIssue ("Can't load " + pfile);
    }
}

void	SoundManager::playSound(const std::string &pfile)
{
  this->_result = this->_system->playSound(this->_noise[pfile.c_str()], NULL, false, &this->_soundChannel);
  if(this->_result != FMOD_OK)
    throw SoundManagerIssue ("Can't play sound : " + pfile);
  this->_soundChannel->setVolume(this->_volumeSound);
  this->_system->update();
}

void	SoundManager::playMusic(const std::string &pfile, int loop)
{
  (void) loop;
  this->_result = this->_system->playSound(this->_noise[pfile.c_str()], NULL, false, &this->_musicChannel);
  if(this->_result != FMOD_OK)
    throw SoundManagerIssue ("Can't play music : pfile");
  this->_musicChannel->setVolume(this->_volumeMusic);
  this->_system->update();
}

void	SoundManager::setVolumeSound(float volume)
{
  this->_volumeSound = volume;
  this->_soundChannel->setVolume(volume);
}

void	SoundManager::setVolumeMusic(float volume)
{
  this->_volumeMusic = volume;
  this->_musicChannel->setVolume(volume);
}

void	SoundManager::repeatMusic(const std::string &pfile, int nb)
{
  (void) pfile;
  (void) nb;
  return ;
}

void	SoundManager::setPause(int state)
{
  (void) state;
  return ;
}

void	SoundManager::stopMusic()
{
  this->_musicChannel->stop();
}
