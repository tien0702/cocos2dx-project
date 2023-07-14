#include "HorizontalLayout.h"

bool HorizontalLayout::init()
{
	if (!Node::init())
		return false;
	return true;
}

void HorizontalLayout::horizontal(int distance, int margin, int alignment)
{
	auto children = getNodesChildren();
	// Calculate total height of children
	int totalWidth = 0;
	for (auto child : children) {
		totalWidth += child->getContentSize().width;
	}
	// parent size
	Size parentSize = getParentSize();

	if (alignment == 0) {
		distance = (parentSize.width - totalWidth - margin * 2) / (children.size() - 1);
	}

	// Calculate y position of first child
	int firstX = margin;
	if (children.size() != 0) firstX += children.at(0)->getContentSize().width / 2;

	// Set position of each child
	int currentX = firstX;
	for (auto child : children)
	{
		child->setPositionX(currentX);
		currentX += child->getContentSize().width + distance;
	}
}

void HorizontalLayout::horizontalBy(Size sizeTemplate, int border, int number)
{
	auto children = getNodesChildren();
	if (children.size() == 0) return;

	int totalWidth = sizeTemplate.width * number;
	Size parentSize = getParentSize();
	int distance = (parentSize.width - totalWidth - border * 2) / number;

	// Calculate y position of first child
	int firstX = border;
	if (children.size() != 0) firstX += children.at(0)->getContentSize().width / 2;
	// Set position of each child
	int currentX = firstX;
	for (auto child : children)
	{
		child->setPositionX(currentX);
		currentX += child->getContentSize().width + distance;
	}
}

std::vector<Node*> HorizontalLayout::getNodesChildren()
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

Size HorizontalLayout::getParentSize()
{
	return this->getParent()->getContentSize();
}
