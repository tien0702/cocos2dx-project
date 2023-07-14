#include "Coin.h"

bool MyGame::Coin::init()
{
	if (!Sprite::init()) 
	{
		log("Init Coin %s failed!", _coinName.c_str());
		return false;
	}

	this->initWithFile("FHD/Icon/" + _iconPath);
	return true;
}

void MyGame::Coin::add(int amount)
{
	_amount += amount;
}

void MyGame::Coin::remove(int amount)
{
	_amount -= amount;
	if (_amount < 0) amount = 0;
}
