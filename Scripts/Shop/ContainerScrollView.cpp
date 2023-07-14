#include "ContainerScrollView.h"

ContainerScrollView* ContainerScrollView::create(Size contanerSize)
{
	auto layer = new (std::nothrow) ContainerScrollView();
	if (layer && layer->init(contanerSize))
	{
		layer->autorelease();
		return layer;
	}
	return nullptr;
}

void ContainerScrollView::addChild(Node* child)
{
	RowItem* row = dynamic_cast<RowItem*>(child);
	if (row == nullptr)
	{
		log("child is not RowItem");
		return;
	}
	row->sortByFirstElement(10, _containerSize.width);
	ScrollView::addChild(child);
	_verticalComponent->vertical(_lineHeight, _borderBackground, true);
}

void ContainerScrollView::setBackground(Sprite* background, Size innerOffset)
{
	this->setBackGroundImage(background->getTexture()->getPath());
	setContentSize(background->getContentSize());
	setInnerContainerSize(_contentSize - innerOffset);
}

bool ContainerScrollView::init(Size contanerSize)
{
	_containerSize = contanerSize;
	if (!ui::ScrollView::init())
	{
		return false;
	}
	this->setDirection(ui::ScrollView::Direction::VERTICAL);
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->setBounceEnabled(true);
	this->setScrollBarOpacity(0);
	this->jumpToTop();
	_verticalComponent = VerticalLayout::create();
	ui::ScrollView::addChild(_verticalComponent);
	return true;
}
