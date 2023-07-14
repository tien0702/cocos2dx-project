#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "cocos2d.h"

USING_NS_CC;

class Effect
{
public:
	static bool loadAnimationCacheWithFile(std::string filePaht);
	static bool loadAnimationCacheWithFile(std::string filePaht, std::string spriteFileName, std::string animationName);
	static std::pair<Animation*, int> createAnimation(std::string fileName);
	static Animation* createAnimation(std::string fileName, int numberFrames, float duration);
};

#endif // !__EFFECT_H__
