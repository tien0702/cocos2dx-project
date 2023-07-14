#include "Effect.h"

// animation format
#define INDEX_START 1
#define ANIMATION_FORMAT(index) " (" + std::to_string(index + INDEX_START) + ")"

bool Effect::loadAnimationCacheWithFile(std::string filePath)
{
	return false;
}

bool Effect::loadAnimationCacheWithFile(std::string filePath, std::string spriteFileName, std::string animationName)
{
	std::string path, pathPlist, pathPNG, plist = ".plist", imgFile = ".png";

	path += filePath + spriteFileName;
	auto spriteCache = SpriteFrameCache::getInstance();
	auto aniCache = AnimationCache::getInstance();

	//if(spriteCache->getSpriteFrameByName("./" + spriteFileName + " (1)") != nullptr) return true;
	spriteCache->addSpriteFramesWithFile(path + plist, path + imgFile);
	Animation* ani = Effect::createAnimation(spriteFileName).first;
	ani->retain();
	aniCache->addAnimation(ani, animationName);
	return true;
}

std::pair<Animation*, int> Effect::createAnimation(std::string fileName)
{
	Vector<SpriteFrame*> frames;

	int index = 0;
	while (true)
	{
		std::string buffer;
		buffer += "./" + fileName + ANIMATION_FORMAT(index);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(buffer);
		if (frame != nullptr)
		{
			frames.pushBack(frame);
			++index;
		}
		else
		{
			break;
		}
	}
	std::pair<Animation*, int> anid;
	float duration = 1.0f / (float)index;
	Animation* animation = Animation::createWithSpriteFrames(frames, duration);
	return std::pair<Animation*, int>(animation, index);
}

Animation* Effect::createAnimation(std::string fileName, int numberFrames, float duration)
{
	Vector<SpriteFrame*> frames;
	for (int i = 0; i < numberFrames; ++i)
	{
		std::string buffer;
		buffer += "./" + fileName + ANIMATION_FORMAT(i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(buffer);
		if (frame == nullptr)
		{
			printf("Can't create frame name: %s\n", buffer.c_str());
			break;
		}
		frames.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frames, duration);
	return animation;
}
