#include "WorldMap.h"
#include "GameConfig.h"
#include "Common.h"
#include "AudioManager/AudioManager.h"
#include "Manager/GameManager.h"
#include "GameData/ChapterData.h"
#include "Scaler.h"
#include "SkillCollection.h"
#include "ShopScene.h"

bool MyGame::WorldMap::init()
{
	if (!Scene::init()) {
		log("Init WorldMap failed!");
		return false;
	}
	if (!loadProperties()) {
		log("Load Properties WorldMap failed!");
		return false;
	}

	this->loadCoins();
	this->loadComponent();
	this->loadPosition();

	_worldView->addChild(_worldTileMap);
	for (int i = 0; i < _locationBtns->size(); ++i)
	{
		_worldTileMap->addChild(_locationBtns->at(i));
	}
	_worldTileMap->setScale(Director::getInstance()->getVisibleSize().width / _worldTileMap->getContentSize().width);
	_worldView->setPosition(Director::getInstance()->getOpenGLView()->getFrameSize() / 2);
	this->addChild(_backBT, 1);
	this->addChild(_openEquipSkill, 1);
	this->addChild(_shopBtn, 1);
	this->addChild(_worldView, 0);
	return true;
}

bool MyGame::WorldMap::loadProperties()
{
	std::string filePath = "Map/world-map.tmx";
	_worldTileMap = TMXTiledMap::create(filePath);
	if (_worldTileMap == nullptr) return false;

	auto objGr = _worldTileMap->getObjectGroup("Point");
	auto locationsMap = objGr->getObjects();

	_locationBtns = new std::vector<LocationInfoBtn*>();
	_chaptersInfo = new std::vector<ChapterInfo*>();

	auto data = GameData::ChapterData();
	for (int i = 0; i < locationsMap.size(); ++i)
	{
		ValueMap val = locationsMap.at(i).asValueMap();
		int id = val["ChapterID"].asInt();
		ChapterInfo* chapterInfo = data.getChapterInfoByID(id);
		auto location = LocationInfoBtn::create(chapterInfo);
		location->setZoomScale(0.02f);
		_locationBtns->push_back(location);
		_chaptersInfo->push_back(chapterInfo);
	}

	_worldView = ui::ScrollView::create();
	_worldView->setDirection(ui::ScrollView::Direction::BOTH);
	_worldView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_worldView->setBounceEnabled(false);
	_worldView->setScrollBarOpacity(0);
	_worldView->setContentSize(Director::getInstance()->getVisibleSize());
	_worldView->setInnerContainerSize(_worldTileMap->getContentSize());
	_worldView->jumpToBottomLeft();
	_font = GameConfig::getIns()->getFont();

	return true;
}

bool MyGame::WorldMap::loadComponent()
{
	Rect fixedVisible = GameConfig::getIns()->getFixedVisible();
	float margin = 10;
	Size frameSize = Common::getFrameSize();

	// int shop btn
	_shopBtn = ui::Button::create("FHD/Button/store.png");
	_shopBtn->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			AudioManager::getIns()->playeButtonEffect();
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			auto shopScene = ShopScene::create();
			Director::getInstance()->pushScene(shopScene);
		}
		break;
		default:
			break;
		}
		});


	// Init BackBtn
	_backBT = ui::Button::create("FHD/Button/button-world-map.png");
	_backBT->setPosition(Vec2(fixedVisible.origin.x + _backBT->getContentSize().width / 2,
		frameSize.height - _backBT->getContentSize().height / 2));

	auto backLb = Label::createWithTTF(_font, "Back");
	backLb->setPosition(_backBT->getContentSize() / 2);
	Scaler::scaleNodeToFit(backLb, _backBT, margin);
	_backBT->addChild(backLb);

	_backBT->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			AudioManager::getIns()->playeButtonEffect();
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			Director::getInstance()->popScene();
		}
		break;
		default:
			break;
		}
		});

	// Init skill equipped
	_openEquipSkill = ui::Button::create("FHD/Button/skill-icon.png");
	_openEquipSkill->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			AudioManager::getIns()->playeButtonEffect();
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			auto scene = SkillCollection::create();
			Director::getInstance()->pushScene(scene);
		}
		break;
		default:
			break;
		}
		});

	// Init Attack Btn
	_attackBtn = ui::Button::create("FHD/Button/button-world-map.png");
	_attackBtn->setPosition(Vec2(fixedVisible.origin.x + fixedVisible.size.width
		- _attackBtn->getContentSize().width / 2 - 10,
		_attackBtn->getContentSize().height / 2 + 10));

	auto atkLb = Label::createWithTTF(_font, "Attack");
	atkLb->setPosition(_attackBtn->getContentSize() / 2);
	Scaler::scaleNodeToFit(atkLb, _attackBtn, margin);
	_attackBtn->addChild(atkLb);
	_attackBtn->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			AudioManager::getIns()->playeButtonEffect();
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			// reset char
			Player::getIns()->getCharacter()->removeAllChildren();
			Player::getIns()->getCharacter()->init();
			GameManager::getIns()->playChapterID(_selectChapter->getChapterID());
		}
		break;
		default:
			break;
		}
		});

	// Init Chapter Info Renderer
	_chapterInfoRenderer = new ChapterInfoRenderer();
	_chapterInfoRenderer->init();

	// addChild Chapter Info Renderer
	_chapterInfoRenderer->addChild(_attackBtn);

	return true;
}

bool MyGame::WorldMap::loadCoins()
{
	Coin* gold, * ruby;
	gold = Player::getIns()->getCoin(CoinType::Coin_Gold);
	ruby = Player::getIns()->getCoin(CoinType::Coin_Ruby);
	_goldBar = CoinBar::create(gold);
	_rubyBar = CoinBar::create(ruby);

	// position
	Rect fixedVisible = GameConfig::getIns()->getFixedVisible();
	_goldBar->setPosition(Vec2(fixedVisible.getMidX() - _goldBar->getNodeSize().width / 2 - _goldBar->getIcon()->getContentSize().width / 2 - 10,
		fixedVisible.getMaxY() - _goldBar->getIcon()->getContentSize().height / 2 - 30));

	_rubyBar->setPosition(Vec2(fixedVisible.getMidX() + _rubyBar->getNodeSize().width / 2 + _rubyBar->getIcon()->getContentSize().width / 2 + 10,
		fixedVisible.getMaxY() - _rubyBar->getIcon()->getContentSize().height / 2 - 30));

	this->addChild(_rubyBar, 2);
	this->addChild(_goldBar, 2);
	return true;
}

void MyGame::WorldMap::loadPosition()
{
	Size size = Director::getInstance()->getOpenGLView()->getFrameSize();
	auto objGr = _worldTileMap->getObjectGroup("Point");
	auto locationsMap = objGr->getObjects();
	for (int i = 0; i < locationsMap.size(); ++i)
	{
		ValueMap val = locationsMap.at(i).asValueMap();
		Vec2 pos;
		pos.x = val["x"].asFloat();
		pos.y = val["y"].asFloat();
		_locationBtns->at(i)->setPosition(pos);
		_locationBtns->at(i)->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				AudioManager::getIns()->playeButtonEffect();
				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
			{
				// addChild Chapter Info Renderer
				_selectChapter = _chaptersInfo->at(i);
				_chapterInfoRenderer->show(_chaptersInfo->at(i), this);
			}
			break;
			default:
				break;
			}
			});
	}

	_worldView->setPosition(size / 2);
	_openEquipSkill->setPosition(Vec2(GameConfig::getIns()->getFixedVisible().getMaxX() - _openEquipSkill->getContentSize().width / 2 - 10,
		GameConfig::getIns()->getFixedVisible().getMidY() + 100));

	_shopBtn->setPositionX(_openEquipSkill->getPositionX() - 140);
	_shopBtn->setPositionY(_openEquipSkill->getPositionY());
}

void MyGame::WorldMap::onEnter()
{
	Scene::onEnter();
	Coin* gold, * ruby;
	gold = Player::getIns()->getCoin(CoinType::Coin_Gold);
	ruby = Player::getIns()->getCoin(CoinType::Coin_Ruby);
	_goldBar->setAmount(gold->getAmount());
	_rubyBar->setAmount(ruby->getAmount());
}
