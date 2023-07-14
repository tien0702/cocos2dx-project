#ifndef __BOX_CONTAINER_H__
#define __BOX_CONTAINER_H__

#include "cocos2d.h"
#include "VerticalLayout.h"
#include "HorizontalLayout.h"
#include "RowItem.h"

USING_NS_CC;

namespace MyGame
{
	class BoxContainer : public Sprite
	{
	public:
		void addChild(Node* node);
		CREATE_FUNC(BoxContainer);
	private:
		bool init();
	private:
		VerticalLayout* _verticalComponent;
		CC_SYNTHESIZE(int, _itemDistance, ItemDistance);
		CC_SYNTHESIZE(int, _itemMargin, ItemMargin);
		CC_SYNTHESIZE(Vec2, _itemAlignment, ItemAlignment);

	};
}

#endif // !__BOX_CONTAINER_H__
