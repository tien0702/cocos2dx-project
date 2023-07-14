#include "BonusCard.h"
#include "Entity/Entity.h"
#include "Common.h"

bool MyGame::BonusCard::init()
{
	if (!Button::init())
	{
		log("Init BonusCard failed!");
		return false;
	}

	this->setZoomScale(0.04f);
	this->loadTextureNormal(_backgroundPath);
	_font.fontSize = 16;
	// 
	Vec2 namePos, desPos;

	namePos.x = _contentSize.width / 2;
	namePos.y = _contentSize.height - 50;

	desPos.x = _contentSize.width / 2;
	desPos.y = _contentSize.height / 2;
	//

	// 
	_cardNameLB = Label::createWithTTF(_font, "Card Name");
	_cardDescriptionLB = Label::createWithTTF(_font, "Description");

	_cardDescriptionLB->setWidth(_contentSize.width - 20);
	_cardDescriptionLB->setAlignment(TextHAlignment::CENTER);

	_cardNameLB->setPosition(namePos);
	_cardDescriptionLB->setPosition(desPos);

	this->addChild(_cardNameLB);
	this->addChild(_cardDescriptionLB);
	return true;
}

MyGame::BonusCard::BonusCard(std::string name, Bonus* bonus)
{
	this->_cardName = name;
	this->_bonus = bonus;
}

void MyGame::BonusCard::endBonus()
{
	if (_target == nullptr)
	{
		log("Target is null, can't end bonus!");
		return;
	}

	int statID = _bonus->getStatBns().getID();
	_target->getEntityStatByID(statID)->removeBonus(_bonus);
	_using = false;
	_target = nullptr;
}

void MyGame::BonusCard::setSelected(bool val)
{
	(val) ? (loadTextureNormal(_backgroundPathSelected)) : (loadTextureNormal(_backgroundPath));
}

void MyGame::BonusCard::reveal()
{
	this->_cardNameLB->setString(this->_cardName);
	this->_cardDescriptionLB->setString(this->getDescription());
}

std::string MyGame::BonusCard::getDescription()
{
	std::string desc = _bonus->getStatBns().getStatName();
	desc += ": +" + Common::convertValueBonus(_bonus);

	return desc;
}
