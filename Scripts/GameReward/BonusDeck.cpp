#include "BonusDeck.h"

MyGame::BonusDeck::BonusDeck()
{
	_bonuses = new std::vector<BonusCard*>();
}

MyGame::BonusCard* MyGame::BonusDeck::takeBonusCard()
{
	if (_bonuses->empty()) return nullptr;

	this->shuffle();
	BonusCard* card = _bonuses->back();
	card->setTargetEntity(_entity);
	_bonuses->pop_back();

	return card;
}

std::vector<MyGame::BonusCard*> MyGame::BonusDeck::takeBonusCard(int amount)
{
	std::vector<MyGame::BonusCard*> cards;
	this->shuffle();
	cards.push_back(_bonuses->at(0));
	cards.push_back(_bonuses->at(1));
	cards.push_back(_bonuses->at(2));
	return cards;
}

void MyGame::BonusDeck::shuffle()
{
	std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
	std::shuffle(_bonuses->begin(), _bonuses->end(), engine);
}

void MyGame::BonusDeck::addBonus(std::string name, Bonus* bns)
{
	if (bns == nullptr)
	{
		log("Bonus is null");
		return;
	}

	BonusCard* card = new BonusCard(name, bns);
	card->init();
	_bonuses->push_back(card);
}

void MyGame::BonusDeck::removeCard(BonusCard* card)
{
	log("before: %d", _bonuses->size());
	std::remove_if(_bonuses->begin(), _bonuses->end(), 
		[=](BonusCard* c) {return c->getBonus()->getBnsID() == card->getBonus()->getBnsID(); });
	log("affter: %d", _bonuses->size());
}
