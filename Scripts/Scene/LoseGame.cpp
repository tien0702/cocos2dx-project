#include "LoseGame.h"
#include "Manager/GameManager.h"

bool MyGame::LoseGame::init()
{
	if (!SummaryGame::init()) {
		return false;
	}

	this->addChild(_confirmBT);
	this->addChild(_replayBtn);
	return true;
}

bool MyGame::LoseGame::loadProperties()
{
	SummaryGame::loadProperties();
	return true;
}

bool MyGame::LoseGame::loadComponent()
{
	SummaryGame::loadComponent();
	Size screenSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	_gameStateLb->setString("You Lose");
	TTFConfig font = GameConfig::getIns()->getFont();

	float distance = 50;
	//
	_confirmBT = ui::Button::create("FHD/Button/btn2.png");
	_confirmBT->setTitleText("Confirm");
	_confirmBT->setTitleFontName(font.fontFilePath);
	_confirmBT->setTitleFontSize(font.fontSize * 0.8f);
	_confirmBT->setPosition(Vec2(screenSize.width / 2 + _confirmBT->getContentSize().width / 2 + distance, _confirmBT->getContentSize().height + 10));
	_confirmBT->addTouchEventListener([=](Ref*, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			GameManager::getIns()->getChapter()->giveReward();
			gotoWorldMap();
		}
		});

	// relay button
	_replayBtn = ui::Button::create("FHD/Button/btn2.png");
	_replayBtn->setTitleText("Replay " + getCostReplay());
	_replayBtn->setTitleFontName(font.fontFilePath);
	_replayBtn->setTitleFontSize(font.fontSize * 0.8f);
	_replayBtn->setEnabled(canReplay());
	_replayBtn->setPosition(Vec2(screenSize.width / 2 - _replayBtn->getContentSize().width / 2 - distance, _confirmBT->getContentSize().height + 10));
	_replayBtn->addTouchEventListener([=](Ref*, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {

		}
		});
	return true;
}

bool MyGame::LoseGame::canReplay()
{
	return true;
}

std::string MyGame::LoseGame::getCostReplay()
{
	return "20";
}
