#ifndef __GAME_CONFIG_H__
#define __GAME_CONFIG_H__

#include "cocos2d.h"

USING_NS_CC;

class GameConfig
{
public:
	static GameConfig* getIns();
	TTFConfig getFont();
	Rect getFixedVisible() { return _fixedVisible; }
	float getScaler();
private:
	GameConfig();
	static GameConfig* _instance;
private:
	TTFConfig _font;
	Rect _fixedVisible;
	Size defaultSize;
};

#endif // !__GAME_CONFIG_H__
