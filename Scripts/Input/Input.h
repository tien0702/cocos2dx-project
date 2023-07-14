#ifndef __INPUT_H__
#define __INPUT_H__

#include "cocos2d.h"
#include "Input/JoystickMove.h"

USING_NS_CC;

class Input : public Node
{
public:
	static Input* getIns();
	void resetInput();
	void AddKey(cocos2d::EventKeyboard::KeyCode key);
	bool GetKey(cocos2d::EventKeyboard::KeyCode key);
	Vec2 getDirection(bool normalize);
	void setEnable(bool enable);
protected:
	bool init();
	static Input* _instance;
	Vec2 _direction;
	bool _enable = true;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> _keyUsed;

	void loadDefaultKey();
	// event listener keyboard
	void onKeyPress(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* ev);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* ev);

	friend class JoystickMove;
};

#endif // !__INPUT_H__
