#include "AudioManager.h"
#include "Settings/Setting.h"

MyGame::AudioManager* MyGame::AudioManager::_instance;

MyGame::AudioManager* MyGame::AudioManager::getIns()
{
	if (_instance == nullptr)
	{
		_instance = new AudioManager();
	}
	return _instance;
}

void MyGame::AudioManager::playBackgroundMusic(const std::string& filename, bool loop)
{
	if (AudioEngine::getState(_bgmID) != AudioEngine::AudioState::ERROR)
		AudioEngine::stop(_bgmID);
	_bgmID = AudioEngine::play2d(filename, loop, Setting::_BGM_Volume);
}

void MyGame::AudioManager::stopBackgroundMusic()
{
	AudioEngine::stop(_bgmID);
}

void MyGame::AudioManager::pauseBGM()
{
	AudioEngine::pause(_bgmID);
}

void MyGame::AudioManager::resumBGM()
{
	AudioEngine::resume(_bgmID);
}

void MyGame::AudioManager::setBackgroundMusicVolume(float volume)
{
	if (volume == 0)
	{
		AudioManager::getIns()->pauseBGM();
	}
	else
	{
		if (AudioEngine::getState(_bgmID) == AudioEngine::AudioState::PAUSED)
			AudioManager::getIns()->resumBGM();
		AudioEngine::setVolume(_bgmID, volume);
	}
}

void MyGame::AudioManager::playEffect(const std::string& filename)
{
	AudioEngine::play2d(filename, false, Setting::_SFX_Volume);
}

void MyGame::AudioManager::setEffectVolume(float volume)
{

}

void MyGame::AudioManager::playeButtonEffect()
{
	AudioManager::getIns()->playEffect("Audio/button-effect.mp3");
}


