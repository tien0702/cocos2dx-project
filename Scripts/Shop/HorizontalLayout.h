#ifndef __HORIZONTAL_LAYOUT_H__
#define __HORIZONTAL_LAYOUT_H__

#include "cocos2d.h"

USING_NS_CC;

class HorizontalLayout : public Node
{
public:
	CREATE_FUNC(HorizontalLayout);
	void horizontal(int distacne, int margin, int alignment);
	void horizontalBy(Size sizeTemplate, int border, int number);
private:
	bool init();
	std::vector<Node*> getNodesChildren();
	Size getParentSize();
};

#endif // !__HORIZONTAL_LAYOUT_H__
