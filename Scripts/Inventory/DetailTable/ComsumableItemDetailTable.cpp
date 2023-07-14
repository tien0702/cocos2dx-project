#include "ComsumableItemDetailTable.h"
#include "Player/Player.h"
#include "Common.h"
#include "Convert.h"
#include "Inventory/PlayerInventory.h"

bool MyGame::ConsumableDetailTable::init()
{
	if (!DetailTable::init()) {
		log("Init ConsumableDetailTable failed!");
		return false;
	}
	// Properties
	std::string bgBTPath;
	Vec2 equipPos;
	float distance = 10;

	// String
	bgBTPath = "FHD/Background/bt-bg.png";

	// create
	_useBT = ui::Button::create();
	_useBT->setTag(4);

	// Set Properties
	_useBT->loadTextureNormal(bgBTPath);
	_useBT->setTitleFontName(_font.fontFilePath);
	_useBT->setTitleFontSize(_font.fontSize);
	_useBT->setTitleText("Use");
	_useBT->setTitleColor(Color3B::GREEN);

	_useBT->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::ENDED:
			{
				ConsumableItem* consItem = dynamic_cast<ConsumableItem*>(_item);
				std::string result = PlayerInventory::getIns()->useItem(consItem);
				this->showItem(_slotBox);
				_slotBox->refresh();
			}
			break;
			default:
				break;
			}
		});
	// Position
	equipPos.x = _background->getContentSize().width * 0.75f;
	equipPos.y = _useBT->getContentSize().height / 2 + distance;

	// Set Position
	_useBT->setPosition(equipPos);
	_background->addChild(_useBT);

	return true;
}

void MyGame::ConsumableDetailTable::showItem(SlotBox* slotBox)
{
	_slotBox = slotBox;
	_item = _slotBox->getInvItem();
	if (slotBox->getInvItem()->getType() != ItemType::ComsumableType) return;
	_consumItem = dynamic_cast<ConsumableItem*>(slotBox->getInvItem());
	std::string description = "Quantity: " + std::to_string(_consumItem->getQuantity()) + "\n";
	description += _consumItem->getItemBonus()->getStatBns().getStatName();
	description += " : +";

	auto type = _consumItem->getItemBonus()->getStatModifiType();
	int value = _consumItem->getItemBonus()->getValueBns();
	description += Common::convertValueBonus(_consumItem->getItemBonus());
	description += "\n";
	description += "Time: ";
	description += StringUtils::format("%.2lf", _consumItem->getItemBonus()->getDuration()) + " s";
	_itemDescription->setString(description);
	DetailTable::showItem(slotBox);
}
