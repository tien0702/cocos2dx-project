#include "DetailItem.h"
#include "GameConfig.h"
#include "AudioManager/AudioManager.h"
#include "GameData/PlayerData.h"

MyGame::DetailItem* MyGame::DetailItem::create(std::string backgroundPath)
{
	auto layer = new (std::nothrow) DetailItem();
	if (layer && layer->init(backgroundPath))
	{
		layer->autorelease();
		return layer;
	}
	return nullptr;
}

bool MyGame::DetailItem::init(std::string backgroundPath)
{
	if (!Sprite::init())
	{
		return false;
	}
	initWithFile(backgroundPath);
	loadComponent();
	loadPosition();

	this->addChild(_itemName);
	this->addChild(_itemNum);
	this->addChild(_itemDescription);
	this->addChild(_paymentBtn);
	this->addChild(_addBtn);
	this->addChild(_minusBtn);
	return true;
}

bool MyGame::DetailItem::loadComponent()
{
	_font = GameConfig::getIns()->getFont();
	_addBtn = ui::Button::create();
	_addBtn->loadTextureNormal("FHD/Button/add-btn.png");
	_addBtn->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			AudioManager::getIns()->playeButtonEffect();
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			if (!canAddItem()) break;
			_currentNum += 1;
			_itemNum->setString(std::to_string(_currentNum));
			_totalPrice->setString(std::to_string(_currentNum * _item->getPrice()) + " G");
		}
		break;
		default:
			break;
		}
		});

	_minusBtn = ui::Button::create();
	_minusBtn->loadTextureNormal("FHD/Button/minus-btn.png");
	_minusBtn->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			AudioManager::getIns()->playeButtonEffect();
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			if (!canMinusItem()) break;
			_currentNum -= 1;
			_itemNum->setString(std::to_string(_currentNum));
			_totalPrice->setString(std::to_string(_currentNum * _item->getPrice()) + " G");
		}
		break;
		default:
			break;
		}
		});

	_paymentBtn = ui::Button::create();
	_paymentBtn->loadTextureNormal("FHD/Button/btn2.png");

	_paymentBtn->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			AudioManager::getIns()->playeButtonEffect();
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			int newAmount = _goldBar->get_Coin()->getAmount() - _currentNum * _item->getPrice();
			_goldBar->setAmount(newAmount);
			buy();
			// reset
			_currentNum = 1;
			_itemNum->setString(std::to_string(_currentNum));
			_totalPrice->setString(std::to_string(_currentNum * _item->getPrice()) + " G");
		}
		break;
		default:
			break;
		}
		});

	_totalPrice = Label::createWithTTF(_font, "0");
	_totalPrice->setScale(0.8f);
	_totalPrice->setPosition(_paymentBtn->getContentSize() / 2);
	_paymentBtn->addChild(_totalPrice);

	_itemName = Label::createWithTTF(_font, "Name");
	_itemName->setScale(1.2f);
	_itemDescription = Label::createWithTTF(_font, "description");

	_itemNum = Label::createWithTTF(_font, "1");
	_itemNum->retain();
	_itemName->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_itemName->setAlignment(TextHAlignment::CENTER);
	_itemNum->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_itemNum->setAlignment(TextHAlignment::CENTER);
	_itemDescription->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	_itemDescription->setAlignment(TextHAlignment::LEFT);
	_itemDescription->setWidth(_contentSize.width - 20);

	_itemName->retain();
	_itemDescription->retain();
	_itemNum->retain();
	_totalPrice->retain();
	_paymentBtn->retain();
	_addBtn->retain();
	_minusBtn->retain();
	return true;
}

bool MyGame::DetailItem::loadPosition()
{
	_itemName->setPosition(Vec2(_contentSize.width / 2, _contentSize.height - _itemName->getContentSize().height / 2 - 10));
	
	int h = 140;
	_addBtn->setPositionX(_contentSize.width / 2 + 100);
	_addBtn->setPositionY(h);
	_minusBtn->setPositionX(_contentSize.width / 2 - 100);
	_minusBtn->setPositionY(h);
	_itemNum->setPositionX(_contentSize.width / 2);
	_itemNum->setPositionY(h);

	_paymentBtn->setPositionX(_contentSize.width / 2);
	_paymentBtn->setPositionY(h - 70);
	_itemDescription->setPositionX(30);
	_itemDescription->setPositionY(_contentSize.height - 100);
	return true;
}

bool MyGame::DetailItem::canAddItem()
{
	auto pData = GameData::PlayerData();
	int needCoin = _currentNum * _item->getPrice();

	return pData.canTakeCoin(needCoin, CoinType::Coin_Gold);
}

bool MyGame::DetailItem::canMinusItem()
{
	return _currentNum > 1;
}

void MyGame::DetailItem::buy()
{
	auto pData = GameData::PlayerData();
	int needCoin = _currentNum * _item->getPrice();
	pData.takeCoin(needCoin, CoinType::Coin_Gold);

	auto item = dynamic_cast<ConsumableItem*>(_item);
	item->setQuantity(_currentNum);
	pData.addItem(item);
}

void MyGame::DetailItem::renderItem(IItemInventory* item)
{
	_item = item;
	_itemName->setString(_item->getItemName());
	_itemDescription->setString(_item->getDescription());
	_currentNum = 1;
	_itemNum->setString(std::to_string(_currentNum));
	_totalPrice->setString(std::to_string(_currentNum * _item->getPrice()) + " G");
}
