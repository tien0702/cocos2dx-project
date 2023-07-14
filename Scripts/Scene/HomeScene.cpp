#include "HomeScene.h"
#include "GameConfig.h"
#include "Common.h"
#include "Manager/GameManager.h"
#include "SettingScene.h"
#include "AudioManager/AudioManager.h"

bool MyGame::HomeScene::init()
{
	if (!Scene::init()) {
		log("Init HomeScene failed!");
		return false;
	}

	if (!loadProperties()) {
		log("Load Properties failed!");
		return false;
	}

	this->loadPostion();
	this->loadEventForButton();

	for (int i = 0; i < HomeOption::TotalOption; ++i)
	{
		this->addChild(_options[i], 1);
	}

	Sprite* bgr = Sprite::create("FHD/Background/background.jpg");
	bgr->setPosition(Director::getInstance()->getVisibleSize() / 2);
	bgr->setScale(Director::getInstance()->getVisibleSize().height / bgr->getContentSize().height);
	this->addChild(bgr, 0);
	//this->addChild(_gameNameLB);
	AudioManager::getIns()->playBackgroundMusic("Audio/bgm1.mp3", true);
	return true;
}

bool MyGame::HomeScene::loadProperties()
{
	_font = GameConfig::getIns()->getFont();
	for (int i = 0; i < HomeOption::TotalOption; ++i)
	{
		_options[i] = ui::Button::create();
		_options[i]->loadTextureNormal("FHD/Background/home-bt-scene.png");
		_options[i]->setTitleFontName(_font.fontFilePath);
		_options[i]->setTitleFontSize(35);
		_options[i]->setTitleText(_optionName[i]);
		_options[i]->setZoomScale(0.1);
		_options[i]->setTitleColor(Color3B::WHITE);
	}

	TTFConfig fontGameName = _font;
	fontGameName.fontSize = 100;
	_gameNameLB = Label::createWithTTF(fontGameName, _nameGame);
	_gameNameLB->setAlignment(TextHAlignment::CENTER);
	_gameNameLB->setPosition(Vec2(Common::getFrameSize().width / 2, 
		Common::getFrameSize().height - _gameNameLB->getContentSize().height / 2 - 20));
	
	return true;
}

void MyGame::HomeScene::loadPostion()
{
	Size size = Director::getInstance()->getOpenGLView()->getFrameSize();
	for (int i = 0; i < HomeOption::TotalOption; ++i)
	{
		Vec2 pos;
		pos.x = size.width / 2;
		pos.y = size.height / 2 - (_options[i]->getContentSize().height + 10) * i;
		_options[i]->setPosition(pos);
	}
}

void MyGame::HomeScene::loadEventForButton()
{
	_options[HomeOption::StartGame]->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			AudioManager::getIns()->playeButtonEffect();
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			this->gotoWorldMap();
		}
		break;
		default:
			break;
		}
		});

	_options[HomeOption::SettingGame]->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			AudioManager::getIns()->playeButtonEffect();
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			auto settingScene = SettingScene::create();
			Director::getInstance()->pushScene(settingScene);
		}
		break;
		default:
			break;
		}
		});

	_options[HomeOption::ExitGame]->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			AudioManager::getIns()->playeButtonEffect();
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			GameManager::getIns()->exitGame();
		}
		break;
		default:
			break;
		}
		});
}

void MyGame::HomeScene::gotoWorldMap()
{
	auto scene = WorldMap::create();
	Director::getInstance()->pushScene(scene);
}
