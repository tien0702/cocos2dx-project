#include "ItemShopSlot.h"
#include "GameConfig.h"

MyGame::ItemShopSlot* MyGame::ItemShopSlot::create(IItemInventory* item)
{
	auto layer = new (std::nothrow) ItemShopSlot();
	if (layer && layer->init(item))
	{
		layer->autorelease();
		return layer;
	}
	return nullptr;
}

void MyGame::ItemShopSlot::updateComponent()
{
	_icon->setPositionX(_contentSize.width / 2);
	_icon->setPositionY(_contentSize.height - _icon->getContentSize().height / 2 - 10);
	_price->setPositionX(_contentSize.width / 2);
	_price->setPositionY(_price->getContentSize().height / 2);
}

bool MyGame::ItemShopSlot::init(IItemInventory* item)
{
	_item = item;
	if (!ui::Button::init())
	{
		return false;
	}
	loadBackground();

	_icon = Sprite::create("FHD/Icon/" + _item->getIconPath() + ".png");

	_price = Label::createWithTTF(GameConfig::getIns()->getFont(), "0");
	_price->setString(std::to_string(_item->getPrice()) + " G");
	_price->setScale(0.6f);
	_price->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_price->setAlignment(TextHAlignment::CENTER);

	auto borderLine = DrawNode::create();
	borderLine->drawRect(Vec2::ZERO, _contentSize, Color4F::WHITE);

	updateComponent();
	this->setSwallowTouches(false);
	this->addChild(borderLine);
	this->addChild(_icon, 1);
	this->addChild(_price, 1);
	return true;
}

bool MyGame::ItemShopSlot::loadBackground()
{
	std::string path = "FHD/" + _qualityBGPath;

	switch (_item->getQuality())
	{
	case ItemQuality::NormalItem:
		path += "NormalBG.png";
		break;
	case ItemQuality::RareItem:
		path += "RareBG.png";
		break;
	case ItemQuality::LegendaryItem:
		path += "LegendaryBG.png";
		break;
	default:
		break;
	}

	this->loadTextureNormal(path);
	this->setZoomScale(0.02f);
	return false;
}
