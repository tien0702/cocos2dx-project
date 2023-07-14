#include "SlotBoxEquipment.h"

bool MyGame::SlotBoxEquipment::init()
{
	if (!SlotBox::init()) {
		log("Init SlotBoxEquipment failed!");
		return false;
	}

	if (!loadProperties()) {
		log("Load Properties SlotBoxEquipment failed!");
		return false;
	}

	return true;
}

MyGame::SlotBoxEquipment::SlotBoxEquipment(IItemInventory* item) : SlotBox(item)
{
	this->_item = item;
}

bool MyGame::SlotBoxEquipment::loadProperties()
{
	SlotBox::loadProperties();
	_equippedPath = "FHD/Background/equipped.png";

	_equippedSprite = Sprite::create(_equippedPath);

	Vec2 pos;
	pos.x = _contentSize.width / 2;
	pos.y = _equippedSprite->getContentSize().height / 2;
	_equippedSprite->setPosition(pos);

	return true;
}
