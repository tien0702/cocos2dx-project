#ifndef __CHEST_H__
#define __CHEST_H__

#include "cocos2d.h"
#include "GameReward/BonusRenderer.h"

USING_NS_CC;

namespace MyGame
{
	class Chest : public Sprite
	{
	public:
		virtual bool initWithClosedImage(std::string closedImagePath, 
			std::string openImagepath, Node* targetOpen, BonusRenderer* bounce);

		void open();
		void close();
		bool isOpened();

	private:
		virtual void update(float dt);
		bool _isOpen;
		std::string _openImagePath;
		Sprite* _openImage;
		BonusRenderer* _bounce;
		Node* _targetOpen;
	};
}

#endif // !__CHEST_H__
