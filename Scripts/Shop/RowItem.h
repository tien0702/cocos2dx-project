#ifndef __ROW_ITEM_H__
#define __ROW_ITEM_H__

#include "cocos2d.h"
#include "HorizontalLayout.h"

USING_NS_CC;

class RowItem : public Node
{
public:
	static RowItem* create(Size size);
	void addChild(Node* child);
	void reSort(int distance, int borgerBG, int aligment);
	void sortByFirstElement(int borgerBG, int maxItems);
private:
	bool init(Size size);
private:
	HorizontalLayout* _horizontalComponent;
	CC_SYNTHESIZE(int, _itemDistance, ItemDistance);
	CC_SYNTHESIZE(int, _itemMargin, ItemMargin);
	CC_SYNTHESIZE(int, _itemAligment, ItemAligment);
};

#endif // !__ROW_ITEM_H__
