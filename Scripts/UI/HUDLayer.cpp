#include "HUDLayer.h"

#include "Inventory/InventoryBase.h"
#include "GameData/ItemData.h"

#include "Combat/InfoTargetEnemy.h"
#include "Player/StatRenderer.h"
#include "Player/CharacterWindowView.h"
#include "Scene/SettingSceneInGame.h"
#include "AudioManager/AudioManager.h"


MyGame::HUDlayer* MyGame::HUDlayer::_instance;

MyGame::HUDlayer* MyGame::HUDlayer::getIns()
{
	if (_instance == nullptr)
	{
		_instance = new HUDlayer();
		_instance->init();
	}
	return _instance;
}

void MyGame::HUDlayer::notify(std::string message, Color3B color)
{
	Node* target = this->getChildByTag(TagNotify);
	if (target != nullptr) this->removeChild(target);

	TTFConfig font = _font;
	font.fontSize = _font.fontSize * 2;
	Label* notify = Label::createWithTTF(font, message);
	notify->setColor(color);
	notify->setPosition(_posNotify);

	notify->runAction(_aniNotify->clone());
	this->addChild(notify);
	this->runAction(Sequence::createWithTwoActions(DelayTime::create(_aniNotify->getDuration()),
		CallFunc::create([=]() {notify->removeFromParent(); })));
}


bool MyGame::HUDlayer::init()
{
	if (!Layer::init()) {
		log("init HUDlayer failed!");
		return false;
	}

	if (!loadProperties()) {
		log("Load properties HUD Layer failed!");
		return false;
	}

	Vec2 posInvBt;
	_charStateUI->init();

	auto bt = ui::Button::create();
	bt->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				PlayerInput::getIns()->cleanInput();
				gotoInventoryScene();
				break;
			default:
				break;
			}
		});
	bt->loadTextureNormal(_invIconPath);

	// open settings
	ui::Button* openSettingBtn = ui::Button::create();
	openSettingBtn->loadTextureNormal("FHD/Icon/option.png");
	auto fixedVisible = GameConfig::getIns()->getFixedVisible();
	openSettingBtn->setPosition(Vec2(fixedVisible.getMaxX() - openSettingBtn->getContentSize().width / 2 - 10,
		fixedVisible.getMaxY() - openSettingBtn->getContentSize().height / 2 - 10));

	openSettingBtn->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				AudioManager::getIns()->playeButtonEffect();
				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
			{
				auto scene = SettingSceneInGame::create();
				Director::getInstance()->pushScene(scene);
			}
				break;
			default:
				break;
			}
		});
	// listener
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(HUDlayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	// Position
	posInvBt.x = _fixedVisible.origin.x + bt->getContentSize().width / 2;
	posInvBt.y = _charStateUI->getContentSize().height + bt->getContentSize().height / 2 + 10;
	posInvBt.y = _fixedVisible.origin.y + _fixedVisible.size.height - posInvBt.y;

	// Set Position
	bt->setPosition(posInvBt);

	// add child
	this->addChild(bt);
	this->addChild(openSettingBtn);
	this->addChild(InfoTargetEnemy::getIns());
	this->addChild(_playerInput);
	this->addChild(_charStateUI);

	this->scheduleUpdate();
	return true;
}

void MyGame::HUDlayer::update(float dt)
{

}

void MyGame::HUDlayer::gotoInventoryScene()
{
	PlayerInput::getIns()->cleanInput();
	PlayerInventoryScene* scene = PlayerInventoryScene::create();
	Director::getInstance()->pushScene(scene);
}

bool MyGame::HUDlayer::loadProperties()
{
	_invIconPath = "FHD/Icon/inventory-icon.png";

	_font = GameConfig::getIns()->getFont();
	_font.fontSize = 15;
	_winSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	_fixedVisible = GameConfig::getIns()->getFixedVisible();
	_playerInput = PlayerInput::getIns();
	_charStateUI = new CharacterStateUI();

	float time = 1.0f;
	auto fade = FadeOut::create(time);
	auto fly = MoveBy::create(time, Vec2(0, 30));
	_aniNotify = Spawn::createWithTwoActions(fly, fade);
	_aniNotify->retain();
	_posNotify = Vec2(_winSize.width / 2, _winSize.height * 0.8f);
	return true;
}

bool MyGame::HUDlayer::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 touchLocation = touch->getLocation();

	return false;
}
