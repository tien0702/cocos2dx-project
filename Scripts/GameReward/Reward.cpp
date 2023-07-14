#include "Reward.h"
#include "Inventory/PlayerInventory.h"
#include "Player/Player.h"

//MyGame::Reward::Reward(Character* character)
//{
//	this->_character = character;
//	_expReward = 0;
//}

void MyGame::Reward::add(Reward* reward)
{
	if (reward == nullptr) return;
	this->addCoins(reward->getCoins());
	this->addExp(reward->getExpReward());
	this->addItems(reward->getItems());
}

void MyGame::Reward::addCoin(Coin* coin)
{
	CoinType type = coin->getCoin_Type();
	if (_coins.find(type) == _coins.end())
	{
		std::pair<CoinType, Coin*> newCoin = std::pair<CoinType, Coin*>(type, coin);
		_coins.insert(newCoin);
	}

	_coins.at(type)->add(coin->getAmount());
}

void MyGame::Reward::addCoins(std::map<CoinType, Coin*> coins)
{
	for (auto coin : coins)
	{
		this->addCoin(coin.second);
	}
}

void MyGame::Reward::removeCoin(Coin* coin)
{
}

void MyGame::Reward::addItem(ConsumableItem* item)
{
	if (item == nullptr)
	{
		log("Item is null");
		return;
	}

	auto itemIterator = std::find_if(
		_items.begin(),
		_items.end(),
		[=](ConsumableItem* listItem) { return listItem->getID() == item->getID(); }
	);
	if (itemIterator != _items.end()) {
		int value = (*itemIterator)->getQuantity() + item->getQuantity();
		(*itemIterator)->setQuantity(value);
	}
	else {
		_items.push_back(item);
	}
}

void MyGame::Reward::addItems(std::list<ConsumableItem*> items)
{
	for (ConsumableItem* item : items) {
		addItem(item);
	}
}

void MyGame::Reward::removeItem(ConsumableItem* item) // TODO: 
{
}

void MyGame::Reward::addExp(int amount)
{
	_expReward += amount;
}

void MyGame::Reward::removeExp(int amount)
{
	this->_expReward -= amount;
	if (_expReward < 0) _expReward = 0;
}

void MyGame::Reward::setItems(std::list<ConsumableItem*> items)
{
	this->_items = items;
}

void MyGame::Reward::setCoins(std::map<CoinType, Coin*> coins)
{
	_coins = coins;
}

void MyGame::Reward::giveReward()
{
	// Exp
	int characterExp = _character->getExp();
	characterExp += _expReward;

	/*while (m_exp >= getNextLevelExp()) {
		int levelUpExp = getNextLevelExp() - m_player->getExp();
		m_player->addExperience(levelUpExp);
		m_player->levelUp();
	}*/

	// Coin
	for (auto coin : _coins)
	{
		Player::getIns()->addCoin(coin.second);
	}

	// Item
	for (IItemInventory* item : _items)
	{
		PlayerInventory::getIns()->addItem(item);
	}
}

int MyGame::Reward::getNextLevelExp()
{
	return 0;
}
