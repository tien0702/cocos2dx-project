#include "Player.h"
#include "GameData/EntityData.h"
#include "GameData/WeaponData.h"
#include "Inventory/PlayerInventory.h"
#include "GameData/AbilityData.h"
#include "GameData/RewardData.h"
#include "GameData/SkillData.h"
#include "GameData/PlayerData.h"

MyGame::Player* MyGame::Player::_instance;

MyGame::Player* MyGame::Player::getIns()
{
	if (_instance == nullptr) {
		_instance = new Player();
	}
	return _instance;
}

void MyGame::Player::releaseCharacter()
{
	if (_character == nullptr) return;
	_character->removeAllChildren();
	CC_SAFE_DELETE(_character);
	_character = nullptr;
}

MyGame::Player::Player()
{
	GameData::EntityData* data = new GameData::EntityData();
	GameData::WeaponData weapData;
	_character = data->getCharacter();
	MagicBook* weap = weapData.getWeaponEquipped();
	_character->equipWeap(weap);
	_character->init();


	// ability
	GameData::AbilityData* abData = new GameData::AbilityData();
	ActiveSkill* ability = abData->getAbilityByID(1);
	ability->init();
	_character->equipAbility(ability);
}

MyGame::Character* MyGame::Player::getCharacter()
{
	if (_character == nullptr)
	{
		GameData::EntityData* data = new GameData::EntityData();
		_character = data->getCharacter();
	}
	return _character;
}

MagicBook* MyGame::Player::getWeaponEquiped()
{
	return nullptr;
}

void MyGame::Player::addCoin(Coin* coin)
{
	GameData::RewardData* rData = new GameData::RewardData();
	rData->addCoin(coin);
}

Coin* MyGame::Player::getCoin(CoinType type)
{
	// reward
	GameData::RewardData* rData = new GameData::RewardData();
	CoinInfo* goldInfo, * rubyInfo;
	goldInfo = new CoinInfo();
	rubyInfo = new CoinInfo();
	goldInfo->setCoinName("Gold");
	rubyInfo->setCoinName("Ruby");
	Coin* gold = rData->getCoinByName(goldInfo);
	Coin* ruby = rData->getCoinByName(rubyInfo);

	switch (type)
	{
	case MyGame::CoinType::Coin_Gold:
		return gold;
		break;
	case MyGame::CoinType::Coin_Ruby:
		return ruby;
		break;
	default:
		break;
	}

	return nullptr;
}
