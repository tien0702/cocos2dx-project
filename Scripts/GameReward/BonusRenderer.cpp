#include "BonusRenderer.h"
#include "UI/HUDLayer.h"
#include "Input/PlayerInput.h"
#include "Manager/GameManager.h"
#include "GameData/PlayerData.h"

bool MyGame::BonusRenderer::init()
{
	if (!Layer::init())
	{
		log("Init BounusRenderer failed!");
		return false;
	}
	std::string path = "FHD/Button/";
	Vec2 posBT;
	TTFConfig font = GameConfig::getIns()->getFont();

	_darkColor = LayerColor::create();
	_darkColor->initWithColor(Color4B(0, 0, 0, 120));

	_selectBT = ui::Button::create();
	_selectBT->loadTextureDisabled(path + "btn2-disable.png");
	_selectBT->loadTextureNormal(path + "btn2.png");
	_selectBT->setTitleFontName(font.fontFilePath);
	_selectBT->setTitleFontSize(font.fontSize);
	_selectBT->setTitleText("Select");
	_selectBT->setEnabled(false);
	_selectBT->retain();

	_selectBT->addTouchEventListener([this](Ref*, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			this->disable();
			this->useBonus();
			_bonusDeck->removeCard(_bonusCardTarget);
		}
		});

	// refresh
	_refresh = ui::Button::create();
	_refresh->loadTextureDisabled(path + "btn2-disable.png");
	_refresh->loadTextureNormal(path + "btn2.png");
	_refresh->setTitleFontName(font.fontFilePath);
	_refresh->setTitleFontSize(font.fontSize - 10);
	_refresh->setEnabled(false);
	_refresh->retain();
	this->checkRefreshBtn();
	_refresh->addTouchEventListener([this](Ref*, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			this->disable();
			this->showing();
			this->checkRefreshBtn();
			GameData::PlayerData::takeCoin(20, CoinType::Coin_Ruby);
		}
		});

	//
	int dis = 40;
	posBT.x = Director::getInstance()->getOpenGLView()->getFrameSize().width / 2 + _selectBT->getContentSize().width / 2 + 40;
	posBT.y = _selectBT->getContentSize().height / 2 + 100;
	_selectBT->setPosition(posBT);

	_refresh->setPosition(Vec2(Director::getInstance()->getOpenGLView()->getFrameSize().width / 2 - _selectBT->getContentSize().width / 2 - 40,
		posBT.y));


	this->addChild(_darkColor, 0);
	this->addChild(_selectBT, 0);
	this->addChild(_refresh, 0);
	return true;
}

void MyGame::BonusRenderer::showing()
{
	_isShowing = true;
	PlayerInput::getIns()->disable();

	_cards = this->getCards();
	this->calculatePosition(_cards);

	for (int i = 0; i < _cards.size(); ++i)
	{
		_cards.at(i)->reveal();
		this->addChild(_cards.at(i));
		_cards.at(i)->addTouchEventListener([=](Ref*, ui::Widget::TouchEventType type) {
			if (type == ui::Widget::TouchEventType::ENDED) {
				this->selectCard(_cards.at(i));
			}
			});
	}

	HUDlayer::getIns()->addChild(this);
}

void MyGame::BonusRenderer::disable()
{
	_isShowing = false;
	PlayerInput::getIns()->enable();

	//_bonusCardTarget->use(_bonusDeck->getTargetEntity());
	for (auto card : _cards)
	{
		card->removeFromParent();
	}

	std::remove_if(_children.begin(), _children.end(),
		[&](Node* child) { return (child->getTag() == CardTag); }
	);
	this->removeFromParent();
}

MyGame::BonusRenderer::BonusRenderer(BonusDeck* bonusDeck)
{
	_bonusDeck = bonusDeck;
}

std::vector<MyGame::BonusCard*> MyGame::BonusRenderer::getCards()
{
	return _bonusDeck->takeBonusCard(3);
}

void MyGame::BonusRenderer::calculatePosition(std::vector<BonusCard*> cards)
{
	Size frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	float width = frameSize.width * 0.6f;
	float distance = width / ((cards.size() - 1) * 1.0f);
	float middle = frameSize.width / 2.0f;

	for (int i = 0; i < cards.size(); ++i)
	{
		Vec2 pos;
		pos.x = (middle - width / 2) + (distance * i);
		pos.y = Director::getInstance()->getWinSize().height / 2.0f;
		cards.at(i)->setPosition(pos);
	}
}

void MyGame::BonusRenderer::selectCard(BonusCard* target)
{
	if (target == nullptr) return;

	if (_bonusCardTarget == target)
	{
		_bonusCardTarget->setSelected(false);
		_selectBT->setEnabled(false);
		_bonusCardTarget = nullptr;
	}
	else
	{
		if(_bonusCardTarget != nullptr) _bonusCardTarget->setSelected(false);
		_bonusCardTarget = target;
		_bonusCardTarget->setSelected(true);
		_selectBT->setEnabled(true);
	}
}

void MyGame::BonusRenderer::useBonus()
{
	GameManager::getIns()->getChapter()->applyBonus(_bonusCardTarget->getBonus());
}

void MyGame::BonusRenderer::checkRefreshBtn()
{
	std::string text = "Refresh " + std::to_string(20) + " / " + std::to_string(GameData::PlayerData::getCoin(CoinType::Coin_Ruby)->getAmount());
	_refresh->setTitleText(text);
	bool enoughCoin = GameData::PlayerData::canTakeCoin(20, CoinType::Coin_Ruby);
	_refresh->setEnabled(enoughCoin);
}
