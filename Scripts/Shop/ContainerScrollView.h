#ifndef __CONTAINER_SCROLL_VIEW_H__
#define __CONTAINER_SCROLL_VIEW_H__

#include "cocos2d.h"
#include "UI/CocosGUI.h"
#include "VerticalLayout.h"
#include "RowItem.h"

USING_NS_CC;

class ContainerScrollView : public ui::ScrollView
{
public:
	static ContainerScrollView* create(Size contanerSize);
	virtual void addChild(Node* child) override;
	virtual void setBackground(Sprite* background, Size innerOffset);
protected:
	virtual bool init(Size contanerSize);

protected:
	Size _containerSize;
	CC_SYNTHESIZE(int, _lineHeight, LineHeight);
	CC_SYNTHESIZE(int, _borderBackground, BorderBackground);
	CC_SYNTHESIZE(VerticalLayout*, _verticalComponent, VerticalComponent);
};

#endif // !__CONTAINER_SCROLL_VIEW_H__
