#include "WinGame.h"

bool MyGame::WinGame::init()
{
	if (!SummaryGame::init())
	{
		return false;
	}


	this->addChild(_confirmBT);
	return true;
}

bool MyGame::WinGame::loadProperties()
{
	SummaryGame::loadProperties();
	return true;
}

bool MyGame::WinGame::loadComponent()
{
	SummaryGame::loadComponent();
	Size screenSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	_gameStateLb->setString("You Win");

	TTFConfig font = GameConfig::getIns()->getFont();
	_confirmBT = ui::Button::create("FHD/Button/confirm.png");
	_confirmBT->setTitleText("Confirm");
	_confirmBT->setTitleFontName(font.fontFilePath);
	_confirmBT->setTitleFontSize(font.fontSize * 0.8f);
	_confirmBT->setPosition(Vec2(screenSize.width / 2, _confirmBT->getContentSize().height + 10));
	_confirmBT->addTouchEventListener([=](Ref*, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			log("Confirm BT");
			gotoWorldMap();
		}
		});

	return true;
}
