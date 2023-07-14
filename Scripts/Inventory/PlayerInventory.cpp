#include "PlayerInventory.h"
#include "Player/Player.h"

MyGame::PlayerInventory* MyGame::PlayerInventory::_instance;

MyGame::PlayerInventory* MyGame::PlayerInventory::getIns()
{
	if (_instance == nullptr) 
	{
		_instance = new PlayerInventory();
	}

	return _instance;
}

std::string MyGame::PlayerInventory::equipItem(IItemInventory* item)
{
	ItemType itemType = item->getType();
	std::string result = "";
	switch (itemType)
	{
	case MyGame::ItemType::Other:
		break;
	case MyGame::ItemType::WeaponType:
		result = this->equipWeapon(dynamic_cast<MagicBook*>(item));
		break;
	case MyGame::ItemType::ComsumableType:
		break;
	case MyGame::ItemType::CollectableType:
		break;
	default:
		break;
	}
	return result;
}

std::string MyGame::PlayerInventory::unequip(EquipableLocation location)
{
	return std::string();
}

std::string MyGame::PlayerInventory::useItem(ConsumableItem* item)
{
	return item->useForTarget(_character);
}

void MyGame::PlayerInventory::addItem(IItemInventory* item)
{
}

void MyGame::PlayerInventory::removeItem(IItemInventory* item)
{
}

std::string MyGame::PlayerInventory::equipWeapon(MagicBook* weap)
{
	return _character->equipWeap(weap);
}

std::string MyGame::PlayerInventory::unequipWeapon()
{
	return "";
}

MyGame::PlayerInventory::PlayerInventory()
{
	_character = Player::getIns()->getCharacter();
	_equipped = new std::map<EquipableLocation, IItemInventory*>();
	_equipped->insert(std::pair<EquipableLocation, IItemInventory*>(EquipableLocation::WeaponLocation, nullptr));
	_equipped->insert(std::pair<EquipableLocation, IItemInventory*>(EquipableLocation::RuneTopLocation, nullptr));
	_equipped->insert(std::pair<EquipableLocation, IItemInventory*>(EquipableLocation::RuneMiddleLocation, nullptr));
	_equipped->insert(std::pair<EquipableLocation, IItemInventory*>(EquipableLocation::RuneBottomLocation, nullptr));
}
