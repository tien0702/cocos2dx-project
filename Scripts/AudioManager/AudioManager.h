#ifndef __AUDIO_MANAGER_H__
#define __AUDIO_MANAGER_H__
#include "cocos2d.h"

USING_NS_CC;

#include "cocos/audio/include/AudioEngine.h"


namespace MyGame
{
	class AudioManager
	{
	public:
		static AudioManager* getIns();
		void playBackgroundMusic(const std::string& filename, bool loop);
		void stopBackgroundMusic();
		void pauseBGM();
		void resumBGM();
		void setBackgroundMusicVolume(float volume);
		void playEffect(const std::string& filename);
		void setEffectVolume(float volume);

		void playeButtonEffect();
	private:
		static AudioManager* _instance;
	private:
		int _bgmID;
	};
}

#endif // !__AUDIO_MANAGER_H__
