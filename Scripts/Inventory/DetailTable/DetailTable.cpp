#include "DetailTable.h"
#include "Inventory/SlotBox/SlotBox.h"

bool MyGame::DetailTable::init()
{
	if (!Layer::init()) {
		log("Init DetailTable failed!");
		return false;
	}

	_font = GameConfig::getIns()->getFont();
	TTFConfig fontName, fontDes;
	Size sizeBG;
	Vec2 posName, posDes, posHeader;
	float distance = 10;

	// Load properties
	fontName = _font;
	fontDes = _font;
	fontDes.fontSize = _font.fontSize * 0.7f;
	_bgPath = "FHD/Background/DesTable.png";
	_background = Sprite::create(_bgPath);
	_header = Sprite::create("FHD/Background/header-des.png");

	// Size
	sizeBG = _background->getContentSize();


	// Init Properties
	_itemName = Label::create();
	_itemDescription = Label::create();

	_itemName->setTTFConfig(fontName);
	_itemDescription->setTTFConfig(fontDes);

	_itemName->setWidth(_header->getContentSize().width - distance * 2);
	_itemDescription->setWidth(_header->getContentSize().width - distance * 2);

	_itemName->setAlignment(TextHAlignment::LEFT);
	_itemDescription->setAlignment(TextHAlignment::LEFT);

	_itemName->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_itemDescription->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);

	_itemName->setColor(Color3B::GREEN);
	_itemDescription->setColor(Color3B::GRAY);

	//
	_itemName->retain();
	_itemDescription->retain();

	// Vec2, Postion
	posHeader.x = _background->getContentSize().width / 2;
	posHeader.y = _background->getContentSize().height - _header->getContentSize().height / 2;

	posName.x =  10;
	posName.y = _header->getContentSize().height / 2;

	posDes.x = -sizeBG.width / 2 + distance;
	posDes.y = sizeBG.height / 2 - _header->getContentSize().height - distance * 2;

	// Set Position
	_header->setPosition(posHeader);
	_itemName->setPosition(posName);
	_itemDescription->setPosition(posDes);

	// addChild
	_header->addChild(_itemName, 1);
	_background->addChild(_header);
	this->addChild(_background, 0);
	this->addChild(_itemDescription, 1);
	return true;
}

void MyGame::DetailTable::showItem(SlotBox* slotBox)
{
	_item = slotBox->getInvItem();
	_itemName->setColor(this->getColor(_item->getQuality()));
	_itemName->setString(_item->getItemName());
}

Color3B MyGame::DetailTable::getColor(ItemQuality quality)
{
	Color3B color;
	switch (quality)
	{
	case MyGame::ItemQuality::NormalItem:
		color = Color3B::GREEN;
		break;
	case MyGame::ItemQuality::RareItem:
		color = Color3B(199, 49, 201);
		break;
	case MyGame::ItemQuality::LegendaryItem:
		color = Color3B::YELLOW;
		break;
	default:
		break;
	}
	return color;
}
