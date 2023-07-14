#include "WeaponDetailTable.h"
#include "Player/Player.h"
#include "Inventory/PlayerInventory.h"
#include "Common.h"

bool MyGame::WeaponDetailTable::init()
{
	if (!DetailTable::init()) {
		log("Init WeaponDetailTable failed!");
		return false;
	}

	// Properties
	std::string bgBTPath;
	Vec2 equipPos, upgPos, atkBnsPos, statBnsPos, desPos;
	float distance = 10;

	TTFConfig font = _font;
	font.fontSize = _font.fontSize * 0.8f;

	// String
	bgBTPath = "FHD/Background/bt-bg.png";

	// Create
	_equipBT = ui::Button::create();
	_upgradeBT = ui::Button::create();

	// Set properties
	_atkBns = Label::create();
	_statBns = Label::create();

	_atkBns->setTTFConfig(font);
	_statBns->setTTFConfig(font);

	_atkBns->setWidth(_header->getContentSize().width - distance * 2);
	_statBns->setWidth(_header->getContentSize().width - distance * 2);

	_atkBns->setAlignment(TextHAlignment::LEFT);
	_statBns->setAlignment(TextHAlignment::LEFT);

	_atkBns->setString("No Infor");
	_statBns->setString("No Infor");

	_atkBns->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	_statBns->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);

	_atkBns->setColor(Color3B::GREEN);
	_statBns->setColor(Color3B::GRAY);

	_equipBT->loadTextureNormal(bgBTPath);
	_upgradeBT->loadTextureNormal(bgBTPath);

	_equipBT->setTitleFontName(_font.fontFilePath);
	_upgradeBT->setTitleFontName(_font.fontFilePath);

	_equipBT->setTitleText("Equip");
	_upgradeBT->setTitleText("Upgrade");


	_equipBT->setTitleFontSize(_font.fontSize * 0.7f);
	_upgradeBT->setTitleFontSize(_font.fontSize * 0.7f);

	_equipBT->setTitleColor(Color3B::GREEN);
	_upgradeBT->setTitleColor(Color3B::GREEN);

	_equipBT->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				PlayerInventory::getIns()->equipItem(_item);
				_slotBox->refresh();
				break;
			default:
				break;
			}
		});

	// Position
	equipPos.x = _background->getContentSize().width * 0.75f;
	equipPos.y = _equipBT->getContentSize().height / 2 + distance;

	upgPos.x = _background->getContentSize().width * 0.25f;
	upgPos.y = _equipBT->getContentSize().height / 2 + distance;

	atkBnsPos.x = distance;
	atkBnsPos.y = _background->getContentSize().height - _header->getContentSize().height - distance;

	statBnsPos.x = distance;
	statBnsPos.y = _background->getContentSize().height - _header->getContentSize().height - distance - _atkBns->getContentSize().height;

	desPos.x = distance;
	desPos.y = statBnsPos.y - _statBns->getContentSize().height - distance;
	

	// Retain
	_atkBns->retain();
	_statBns->retain();
	// Set Position
	_equipBT->setPosition(equipPos);
	_upgradeBT->setPosition(upgPos);
	_itemDescription->setPosition(desPos);

	_atkBns->setPosition(atkBnsPos);
	_statBns->setPosition(statBnsPos);

	_background->addChild(_equipBT);
	_background->addChild(_upgradeBT);
	_background->addChild(_atkBns);
	_background->addChild(_statBns);
	return true;
}

void MyGame::WeaponDetailTable::showItem(SlotBox* slotBox)
{
	_slotBox = slotBox;
	_item = slotBox->getInvItem();
	_magicBook = dynamic_cast<MagicBook*>(_item);
	if (_magicBook == nullptr) {
		log("MagicBook is null!");
		return;
	}
	_atkBns->setString("Base Attack: " + std::to_string(_magicBook->getBnsATK()));

	auto type = _magicBook->getStatBonus()->getStatModifiType();
	int value = _magicBook->getStatBonus()->getValueBns();
	std::string strVal = ": ";

	strVal += Common::convertValueBonus(_magicBook->getStatBonus());

	_statBns->setString(_magicBook->getStatBonus()->getStatBns().getStatName() + strVal);
	DetailTable::showItem(slotBox);
}

void MyGame::WeaponDetailTable::gotoUpgradeLayer()
{

}
