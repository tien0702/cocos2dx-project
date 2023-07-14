#include "RowItem.h"

RowItem* RowItem::create(Size size)
{
	auto layer = new (std::nothrow) RowItem();
	if (layer && layer->init(size))
	{
		layer->autorelease();
		return layer;
	}
	return nullptr;
}

void RowItem::addChild(Node* child)
{
	Node::addChild(child);
	_horizontalComponent->horizontal(_itemDistance, _itemMargin, _itemAligment);
	_contentSize.height = child->getContentSize().height;
}

void RowItem::reSort(int distance, int borgerBG, int aligment)
{
	_horizontalComponent->horizontal(distance, borgerBG, aligment);
}

void RowItem::sortByFirstElement(int borgerBG, int maxItems)
{
	auto children = getChildren();
	children.eraseObject(_horizontalComponent);
	_horizontalComponent->horizontalBy(children.at(0)->getContentSize(), borgerBG, maxItems);
}

bool RowItem::init(Size size)
{
	this->setContentSize(size);
	if(!Node::init())
	{
		return false;
	}

	_itemDistance = 20;
	_itemMargin = 10;
	_itemAligment = 1;

	_horizontalComponent = HorizontalLayout::create();

	this->addChild(_horizontalComponent);
	return true;
}
