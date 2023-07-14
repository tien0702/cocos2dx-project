#include "ConsumableItem.h"
#include "Entity/Entity.h"
#include "GameData/ConsumableItemData.h"

bool MyGame::ConsumableItem::init()
{
	if (!Sprite::init()) {
		log("Init Consumable Item failed!");
		return false;
	}
	return true;
}

std::string MyGame::ConsumableItem::useForTarget(Entity* target)
{
	if (target == nullptr) return "Object not found";
	if (_quantity <= 0) return "It's over";
	GameData::ConsumableItemData* consumdata = new GameData::ConsumableItemData();

	if (consumdata->useItem(this))
	{
		target->addBonus(_bonus->clone());
		return "Used";
	}

	return "Use failed!";
}
