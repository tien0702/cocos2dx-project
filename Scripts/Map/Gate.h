#ifndef __GATE_H__
#define __GATE_H__

#include "cocos2d.h"

USING_NS_CC;

namespace MyGame
{
	class Entity;
	
	class Gate : public Sprite
	{
	public:
		virtual bool initWithValueMap(ValueMap val);
		void open();
		void close();
	protected:
		std::string _mapPath = "Map/";
		std::string _effectPath = "Effect/";
		std::string _mapName;
		std::string _effectName;
		Entity* _player;

		bool _open = false;
	protected:
		virtual void update(float dt);
		virtual bool loadProperties();
		virtual bool initAnimation();
	};
}

#endif // !__GATE_H__
