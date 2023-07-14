#include "SlotBox.h"
#include "GameConfig.h"
#include "ConsumableItem/ConsumableItem.h"
#include "Equipment/Weapon/MagicBook.h"

bool MyGame::SlotBox::init()
{
	if (!ui::Button::init()) {
		log("Init SlotBox failed!");
		return false;
	}
	this->loadBackground(_item->getQuality());

	Sprite* itemAvt = Sprite::create("FHD/Icon/" + _item->getIconPath() + ".png");
	itemAvt->setPosition(this->getContentSize() / 2);

	_font = GameConfig::getIns()->getFont();
	_font.fontSize = _font.fontSize * 0.6f;

	std::string infoStr;

	_itemInfo = Label::createWithTTF(_font, "o");
	_itemInfo->setAlignment(TextHAlignment::CENTER);
	_itemInfo->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	_itemInfo->setPosition(Vec2(_contentSize.width / 2, 0));

	refresh();

	this->scheduleUpdate();
	this->addChild(itemAvt, 1);
	this->addChild(_itemInfo, 2);
	return true;
}

MyGame::SlotBox::SlotBox(IItemInventory* item)
{
	this->_item = item;
}

void MyGame::SlotBox::refresh()
{
	std::string infoStr;

	if (_item->getType() == ItemType::ComsumableType)
	{
		int quantity = static_cast<ConsumableItem*>(_item)->getQuantity();
		infoStr = std::to_string(quantity);
	}
	else if (_item->getType() == ItemType::WeaponType)
	{
		auto mBook = static_cast<MagicBook*>(_item);
		if (mBook->getIsEquip())
		{
			Label* equipText = Label::createWithTTF(_font, "Equipped");
			equipText->setPosition(_contentSize / 2);
			equipText->setTag(3);
			this->addChild(equipText, 4);
		}
		else
		{
			removeChildByTag(3);
		}
		int lv = mBook->getLevel();
		infoStr = "lv. " + std::to_string(lv);
	}
	_itemInfo->setString(infoStr);
}

void MyGame::SlotBox::update(float dt)
{

}

bool MyGame::SlotBox::loadProperties()
{
	return false;
}

void MyGame::SlotBox::loadBackground(ItemQuality quality)
{
	std::string path = "FHD/" + _qualityBGPath;

	switch (quality)
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
	this->setZoomScale(0);
}
