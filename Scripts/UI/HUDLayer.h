#ifndef __HUBLAYER_H__
#define __HUBLAYER_H__

#include "cocos2d.h"
#include "Input/JoystickMove.h"
#include "Input/PlayerInput.h"
#include "Player/InformationScene.h"
#include "UI/CharacterStateUI.h"
#include "ui/CocosGUI.h"
#include "Scene/PlayerInventoryScene.h"

USING_NS_CC;

namespace MyGame
{
	class HUDlayer : public Layer
	{
	public:
		static const int TagNotify = 4;
	public:
		static HUDlayer* getIns();
		void setCam(Camera* cam) { this->_camFollow = cam; }
		void notify(std::string message, Color3B color);

	protected:
		virtual bool init();
		CREATE_FUNC(HUDlayer)
	protected:
		static HUDlayer* _instance;
		CharacterStateUI* _charStateUI;
		PlayerInput* _playerInput;
		Size _winSize;
		Rect _fixedVisible;
		TTFConfig _font;
		Camera* _camFollow;
		std::string _invIconPath;

		// Notify
		Vec2 _posNotify;
		Spawn* _aniNotify;
	protected:
		virtual void update(float dt);
		void gotoInventoryScene();
		bool loadProperties();
		bool onTouchBegan(Touch* touch, Event* event);
	};
}

#endif // !__HUBLAYER_H__
