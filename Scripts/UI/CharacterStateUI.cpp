#include "CharacterStateUI.h"
#include "Player/Player.h"
#include "Character/Character.h"
#include "GameConfig.h"
#include "Player/InformationScene.h"
#include "AudioManager/AudioManager.h"

bool MyGame::CharacterStateUI::init()
{
	if (!Sprite::create()) {
		log("Init Character State Bar failed!");
		return false;
	}

	if (!loadProperties()) {
		log("Load properties failed!");
		return false;
	}
	this->initWithFile(_bgPath);

	// Register
	_character->attach(EntityObserverType::OnTakeDame, this);
	_character->attach(EntityObserverType::OnRebornHP, this);
	_character->attach(EntityObserverType::OnRecoveryHP, this);

	_character->attach(EntityObserverType::OnTakeMP, this);
	_character->attach(EntityObserverType::OnRebornMP, this);
	_character->attach(EntityObserverType::OnRecoveryMP, this);

	// Track
	Sprite* trackHp = Sprite::create(_HPtrackPath);
	Sprite* trackMp = Sprite::create(_MPtrackPath);

	// Create Level Info
	std::string info = "Level. " + std::to_string(_character->getLevel());
	_levelInfo = Label::createWithTTF(_font, info);
	_levelInfo->setAlignment(TextHAlignment::LEFT);
	_levelInfo->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);

	std::string avatarPath = "FHD/Icon/avatar.png";
	_avatar = ui::Button::create();
	_avatar->loadTextureNormal(avatarPath);
	_avatar->setZoomScale(0.1f);
	_avatar->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				AudioManager::getIns()->playeButtonEffect();
				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				PlayerInput::getIns()->cleanInput();
				this->gotoInformationScene();
				break;
			default:
				break;
			}
		});

	// hp mp bar
	_hpBar = ui::LoadingBar::create(_hpProgressPath);
	_hpBar->setDirection(ui::LoadingBar::Direction::LEFT);

	_mpBar = ui::LoadingBar::create(_mpProgressPath);
	_mpBar->setDirection(ui::LoadingBar::Direction::LEFT);

	TTFConfig f = _font;
	f.fontSize = f.fontSize * 0.4f;

	_hpInfo = Label::createWithTTF(f, "0");
	_hpInfo->setPositionX(_hpBar->getContentSize().width / 2);
	_hpInfo->setPositionY(_hpBar->getContentSize().height / 2);

	_mpInfo = Label::createWithTTF(f, "0");
	_mpInfo->setPositionX(_mpBar->getContentSize().width / 2);
	_mpInfo->setPositionY(_mpBar->getContentSize().height / 2);

	_hpBar->addChild(_hpInfo, 1);
	_mpBar->addChild(_mpInfo, 1);

	updateHP();
	updateMP();

	int border = 5;
	Vec2 pos, posHp, posMp, posAvatar, posLv;
	pos.x = GameConfig::getIns()->getFixedVisible().origin.x + _contentSize.width / 2;
	pos.y = GameConfig::getIns()->getFixedVisible().getMaxY() - _contentSize.height / 2;

	posAvatar.x = _avatar->getContentSize().width / 2 + border;
	posAvatar.y = _avatar->getContentSize().height / 2 + border;

	posLv.x = _contentSize.width / 2 - posAvatar.x;
	posLv.y = _contentSize.height * 0.75f;

	posHp.x = _contentSize.width / 2 + posAvatar.x;
	posHp.y = _contentSize.height * 0.5f;

	posMp.x = _contentSize.width / 2 + posAvatar.x;
	posMp.y = _contentSize.height * 0.25f;

	this->setPosition(pos);
	_levelInfo->setPosition(posLv);
	_hpBar->setPosition(posHp);
	_mpBar->setPosition(posMp);
	_avatar->setPosition(posAvatar);
	trackHp->setPosition(posHp);
	trackMp->setPosition(posMp);


	this->addChild(_levelInfo);
	this->addChild(trackHp, 2);
	this->addChild(trackMp, 2);

	this->addChild(_hpBar, 1);
	this->addChild(_mpBar, 1);
	this->addChild(_avatar);

	this->retain();
	return true;
}

bool MyGame::CharacterStateUI::loadProperties()
{
	_character = Player::getIns()->getCharacter();
	_entityHealth = _character->getHealth();

	_font = GameConfig::getIns()->getFont();
	_font.fontSize = _font.fontSize;

	std::string folder = "FHD/";

	_bgPath = folder + _bgPath;
	_HPtrackPath = folder + _HPtrackPath;
	_MPtrackPath = folder + _MPtrackPath;
	_hpProgressPath = folder + _hpProgressPath;
	_mpProgressPath = folder + _mpProgressPath;
	return true;
}

void MyGame::CharacterStateUI::gotoInformationScene()
{
	InformationScene* scene = new InformationScene();
	scene->init();
	Director::getInstance()->pushScene(scene);
}

void MyGame::CharacterStateUI::onTakeDame()
{
	updateHP();
}

void MyGame::CharacterStateUI::onRecoveryHP()
{
	updateHP();
}

void MyGame::CharacterStateUI::onReborn()
{
	updateHP();
}

void MyGame::CharacterStateUI::onRecoveryMp()
{
	updateMP();
}

void MyGame::CharacterStateUI::onRebornMp()
{
	updateMP();
}

void MyGame::CharacterStateUI::onTakeMp()
{
	updateMP();
}

void MyGame::CharacterStateUI::updateHP()
{
	float maxHP = _entityHealth->getMaxHp()->getFinalValue();
	float hp = _entityHealth->getHp()->getFinalValue();
	float percent = hp / maxHP;
	percent *= 100.0f;
	_hpBar->setPercent(percent);
	_hpInfo->setString(std::to_string((int)hp) + " / " + std::to_string((int)maxHP));
}

void MyGame::CharacterStateUI::updateMP()
{
	float maxMp = _character->getEntityStatByID(Stat::MP)->getFinalValue();
	float mp = _character->getEntityStatByID(Stat::CurrentMana)->getFinalValue();
	float percentMp = mp / maxMp;
	percentMp *= 100.0f;
	_mpBar->setPercent(percentMp);
	_mpInfo->setString(std::to_string((int)mp) + " / " + std::to_string((int)maxMp));
}
