#include "AttributeLayer.h"
#include "Player/Player.h"
#include "GameConfig.h"
#include "ui/CocosGUI.h"

#include "StatRenderer.h"
#include "CharacterWindowView.h"
#include "SkillBtnShowDetail.h"

bool MyGame::AttributeLayer::init()
{
	if (!IInforLayer::init()) {
		log("Init Attribute Layer failed!");
		return false;
	}

	_iconPath = "FHD/Icon/attribute-icon.png";
	_nameLayer = "Attribute";

	float distance = 10;
	
	Size statSize(700, 400);
	Size windowSize(420, 300);

	StatRenderer* statRenderer = new StatRenderer();
	CharacterWindowView* charWindow = new CharacterWindowView();

	statRenderer->setWindowSize(statSize);
	charWindow->setWindowSize(windowSize);

	charWindow->setPosition(-_sizeLayer.width / 2, _sizeLayer.height / 2 - windowSize.height / 2);
	statRenderer->setPosition(charWindow->getPosition().x + windowSize.width / 2 + statSize.width / 2 + distance,
		_sizeLayer.height / 2 - statSize.height / 2);

	statRenderer->init();
	charWindow->init();
	this->addChild(statRenderer, 3);
	this->addChild(charWindow, 4);

	// skill
	SkillBtnShowDetail* talen = new SkillBtnShowDetail();
	talen->setSkillTarget(Player::getIns()->getCharacter()->getSkillEquiplocation(ActiveSkillLocation::TalenSkill));
	talen->init();
	talen->setPosition(charWindow->getPosition() - Vec2(0, windowSize.height / 2 + talen->getContentSize().height / 2 + _sizeLayer.height * 0.1f));

	SkillBtnShowDetail* ultimate = new SkillBtnShowDetail();
	ultimate->setSkillTarget(Player::getIns()->getCharacter()->getSkillEquiplocation(ActiveSkillLocation::UltimateSkill));
	ultimate->init();
	ultimate->setPosition(talen->getPosition() - Vec2(Vec2(0, talen->getContentSize().height + _sizeLayer.height * 0.1f)));

	this->addChild(talen, 4);
	this->addChild(ultimate, 4);

	return true;
}
