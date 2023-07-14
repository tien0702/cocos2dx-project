#include "ShopScene.h"
#include "AudioManager/AudioManager.h"
#include "GameData/ConsumableItemData.h"
#include "Shop/ShopContainer.h"
#include "GameData/PlayerData.h"
#include "Player/Player.h"
#include "Scaler.h"
#include "GameConfig.h"


bool MyGame::ShopScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	loadGoldBar();
	loadComponent();

	auto items = getConsumItems();
	auto detailItem = DetailItem::create("FHD/Background/DesTable.png");
	auto container = ShopContainer::create("FHD/Background/InvContainer.png", items, 7, detailItem);

	container->setPositionY(Director::getInstance()->getWinSize().height / 2 - 60);
	detailItem->setPositionY(Director::getInstance()->getWinSize().height / 2 - 60);
	detailItem->setGoldBar(_goldBar);

	int midW = Director::getInstance()->getWinSize().width / 2;
	container->setPositionX(midW - 300);
	detailItem->setPositionX(midW + 400);
	

	auto bg = Sprite::create("FHD/Background/bgr2.png");
	bg->setPosition(Director::getInstance()->getOpenGLView()->getFrameSize() / 2);
	this->addChild(bg);
	this->addChild(container);
	this->addChild(detailItem);
	this->addChild(_goldBar);
	this->addChild(_backBtn);

	return true;
}

std::vector<MyGame::IItemInventory*> MyGame::ShopScene::getConsumItems()
{
	auto consumData = GameData::ConsumableItemData();
	auto consumItems = consumData.getConsumableItems();

	std::vector<MyGame::IItemInventory*> items;
	for (auto item : consumItems)
	{
		items.push_back(item);
	}

	std::sort(items.begin(), items.end(),
		[=](IItemInventory*& i1, IItemInventory*& i2) {
			return i1->getQuality() < i2->getQuality();
		});
	return items;
}

bool MyGame::ShopScene::loadGoldBar()
{

	Coin* gold, * ruby;
	gold = Player::getIns()->getCoin(CoinType::Coin_Gold);
	_goldBar = CoinBar::create(gold);
	_goldBar->setPositionX(Director::getInstance()->getOpenGLView()->getFrameSize().width / 2 - 260);
	_goldBar->setPositionY(Director::getInstance()->getOpenGLView()->getFrameSize().height - 100);
	_goldBar->setScale(0.9f);
	return true;
}

bool MyGame::ShopScene::loadComponent()
{
	_backBtn = ui::Button::create("FHD/Button/button-world-map.png");
	auto backLb = Label::createWithTTF(GameConfig::getIns()->getFont(), "Back");
	backLb->setPosition(_backBtn->getContentSize() / 2);
	Scaler::scaleNodeToFit(backLb, _backBtn, 10);
	_backBtn->addChild(backLb);

	_backBtn->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
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

	_backBtn->setPositionX(GameConfig::getIns()->getFixedVisible().getMaxX() - _backBtn->getContentSize().width / 2 - 10);
	_backBtn->setPositionY(GameConfig::getIns()->getFixedVisible().getMaxY() - _backBtn->getContentSize().height / 2 - 10);
	return true;
}
