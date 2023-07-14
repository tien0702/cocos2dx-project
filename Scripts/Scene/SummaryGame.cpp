#include "SummaryGame.h"
#include "Manager/GameManager.h"
#include "GameConfig.h"
#include "Common.h"
#include "Player/Player.h"

bool MyGame::SummaryGame::init()
{
	if (!Scene::init())
	{
		return false;
	}
	if (!loadProperties())
	{
		return false;
	}

	if (!loadComponent())
	{
		return false;
	}

	//bgr
	auto bgr = Sprite::create("FHD/Background/bgr2.png");
	bgr->setPosition(Director::getInstance()->getOpenGLView()->getFrameSize() / 2);
	bgr->setOpacity(180);
	this->addChild(bgr, -1);

	rewardRender();
	this->addChild(_gameStateLb);
	return true;
}

void MyGame::SummaryGame::rewardRender()
{
	showCoins();
	showItems();
}

bool MyGame::SummaryGame::loadProperties()
{
	_chapter = GameManager::getIns()->getChapter();
	_font = GameConfig::getIns()->getFont();
	_font.fontSize = 150;

	auto reward = _chapter->getChapterReward();
	if (reward == nullptr) return true;
	_exp = reward->getExpReward();
	auto coins = reward->getCoins();
	for (auto coin : coins)
	{
		_coins.push_back(coin.second);
	}
	auto items = reward->getItems();

	for (auto item : items)
	{
		_items.push_back(item);
	}
	return true;
}

bool MyGame::SummaryGame::loadComponent()
{
	Size screenSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	_gameStateLb = Label::createWithTTF(_font, "Game State");
	_gameStateLb->setAlignment(TextHAlignment::CENTER);
	_gameStateLb->setPosition(Vec2(screenSize.width / 2,
		screenSize.height - _gameStateLb->getContentSize().height - 10));

	return true;
}

void MyGame::SummaryGame::showCoins()
{
	if (_coins.empty()) return;

	int width = Director::getInstance()->getOpenGLView()->getFrameSize().width;
	vector<Size> sizes;
	for (auto coin : _coins)
	{
		coin->init();
		sizes.push_back(coin->getContentSize());
	}

	auto positions = Common::getPositionXCenter(sizes, width, 10);

	for (int i = 0; i < _coins.size(); ++i)
	{
		Size coinSize = _coins.at(i)->getContentSize();
		Vec2 position = positions.at(i);
		position.y = Director::getInstance()->getOpenGLView()->getFrameSize().height / 2 + coinSize.height / 2 + 20;

		_coins.at(i)->setPosition(position);
		// show quantity
		TTFConfig font = _font;
		std::string amountStr = std::to_string(_coins.at(i)->getAmount());
		font.fontSize = 20;
		Label* quantity = Label::createWithTTF(font, amountStr);
		quantity->setAlignment(TextHAlignment::RIGHT);
		quantity->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
		quantity->setPosition(Vec2(coinSize.width, 0));

		_coins.at(i)->addChild(quantity);
		this->addChild(_coins.at(i));
	}
}

void MyGame::SummaryGame::showItems()
{
	if (_items.empty()) return;
	int width = Director::getInstance()->getOpenGLView()->getFrameSize().width;
	
	vector<Size> sizes;
	vector<Sprite*> items;
	for (auto item : _items)
	{
		Sprite* itemSprite = Sprite::create("FHD/Icon/" + item->getIconPath() + ".png");
		sizes.push_back(itemSprite->getContentSize());
		items.push_back(itemSprite);
	}

	auto positions = Common::getPositionXCenter(sizes, width, 20);

	for (int i = 0; i < items.size(); ++i)
	{
		Size itemSize = items.at(i)->getContentSize();

		Vec2 position = positions.at(i);
		position.y = Director::getInstance()->getOpenGLView()->getFrameSize().height / 2 - itemSize.height / 2 - 20;

		items.at(i)->setPosition(position);

		// Show quantity
		TTFConfig font = _font;
		std::string amountStr = std::to_string(_items.at(i)->getQuantity());
		font.fontSize = 20;
		Label* quantity = Label::createWithTTF(font, amountStr);
		quantity->setAlignment(TextHAlignment::RIGHT);
		quantity->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
		quantity->setPosition(Vec2(itemSize.width, 0));

		items.at(i)->addChild(quantity);
		this->addChild(items.at(i));
	}
}

void MyGame::SummaryGame::showExp()
{
}

void MyGame::SummaryGame::gotoWorldMap()
{
	auto homeScene = HomeScene::create();
	Director::getInstance()->replaceScene(homeScene);

	auto worldMapScene = WorldMap::create();
	Director::getInstance()->pushScene(worldMapScene);

}
