#include "BoxContainer.h"

void MyGame::BoxContainer::addChild(Node* node)
{
	Node::addChild(node);
	_verticalComponent->vertical(_itemDistance, _itemMargin, _itemAlignment.y > 0);
}

bool MyGame::BoxContainer::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	_verticalComponent = VerticalLayout::create();
	_verticalComponent->retain();

	_itemAlignment = Vec2(1, 1);
	_itemMargin = 10;
	_itemDistance = 10;

	this->addChild(_verticalComponent);
	return true;
}
