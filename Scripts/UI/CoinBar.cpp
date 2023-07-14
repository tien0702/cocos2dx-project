#include "CoinBar.h"
#include "Scaler.h"
#include "GameConfig.h"

MyGame::CoinBar* MyGame::CoinBar::create(Coin* coin)
{
	CoinBar* layer = new (std::nothrow) CoinBar();
	if (layer && layer->init(coin))
	{
		layer->autorelease();
		return layer;
	}
	return nullptr;
}

void MyGame::CoinBar::refresh()
{
	_coinAmount->setString(std::to_string(_coin->getAmount()));
}

void MyGame::CoinBar::setAmount(int amount)
{
	_coinAmount->setString(std::to_string(amount));
}

bool MyGame::CoinBar::init(Coin* coin)
{
	if (!Node::init())
	{
		return false;
	}
	_coin = coin;
	Size size = Scaler::calculateContentSize(Size(300, 70));
	_nodeSize = size;
	DrawNode* bg = DrawNode::create();
	bg->drawRect(Vec2::ZERO, size, Color4F::WHITE);
	bg->drawSolidRect(Vec2::ZERO, size, Color4F(0, 0, 0, 0.5));

	//
	TTFConfig font = GameConfig::getIns()->getFont();
	font.fontSize *= Director::getInstance()->getContentScaleFactor();
	_coinAmount = Label::createWithTTF(font, std::to_string(_coin->getAmount()));
	_coinAmount->setAlignment(TextHAlignment::LEFT);
	_coinAmount->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);

	// icon
	_iconCoin = Sprite::create("FHD/Icon/" + _coin->getIconPath());

	// button
	_moreBtn = ui::Button::create();

	// position
	Vec2 coinPos, iconPos;
	coinPos = Vec2(-size.width / 2 + _iconCoin->getContentSize().width + 70, size.height / 2);
	iconPos = Vec2(-size.width / 2 + _iconCoin->getContentSize().width, size.height / 2);
	_coinAmount->setPosition(coinPos);
	_iconCoin->setPosition(iconPos);

	this->addChild(bg, 0);
	this->addChild(_coinAmount, 1);
	bg->addChild(_iconCoin, 2);
	return true;
}
