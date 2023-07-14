#include "VerticalLayout.h"

bool VerticalLayout::init()
{
	if (!Node::init())
		return false;

	return true;
}

void VerticalLayout::vertical(int distance, int margin, bool isTop)
{
	auto children = getNodesChildren();
	// Calculate total height of children
	int totalHeight = 0;
	for (auto child : children) {
		totalHeight += child->getContentSize().height;
	}
	// parent size
	Size parentSize = getParentSize();

	// Calculate y position of first child
	int firstY = parentSize.height - margin * 2 - totalHeight;
	if (children.size() != 0) firstY += children.at(0)->getContentSize().height / 2;

	// Set position of each child
	int currentY = firstY;
	for (auto child : children)
	{
		child->setPositionY(currentY);
		currentY += child->getContentSize().height + distance;
	}
}

std::vector<Node*> VerticalLayout::getNodesChildren()
{
	auto children_ = this->getParent()->getChildren();
	children_.eraseObject(this);

	std::vector<Node*> children;
	for (auto child : children_)
	{
		children.push_back(child);
	}

	return children;
}

Size VerticalLayout::getParentSize()
{
	return this->getParent()->getContentSize();
}
