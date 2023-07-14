#ifndef __VERTICAL_LAYOUT_H__
#define __VERTICAL_LAYOUT_H__

#include "cocos2d.h"

USING_NS_CC;

class VerticalLayout : public Node
{
public:
	bool init();
	void vertical(int distance, int margin, bool isTop);
	CREATE_FUNC(VerticalLayout);
private:

	std::vector<Node*> getNodesChildren();
	Size getParentSize();
};

#endif // !__VERTICAL_LAYOUT_H__
