#ifndef __SETTING_H__
#define __SETTING_H__

#include "cocos2d.h"
USING_NS_CC;

class Setting
{
public:
	static bool loadSettings();
	static void save();
	static void reset();
public:
	static float _BGM_Volume;
	static float _SFX_Volume;
	static float _Effect_Volume;
	static bool _fixedJoystick;

private:
	static std::string getPath();
	static bool readConfigFile();
	static bool initConfigFile();
private:
	static char* _fileName;
};

#endif // !__SETTING_H__
