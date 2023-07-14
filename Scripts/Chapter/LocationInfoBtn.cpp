#include "LocationInfoBtn.h"
#include "AudioManager/AudioManager.h"
#include "ChapterInforRenderer.h"
#include "GameConfig.h"

MyGame::LocationInfoBtn* MyGame::LocationInfoBtn::create(ChapterInfo* chapterInfo)
{
	LocationInfoBtn* btn = new (std::nothrow) LocationInfoBtn();
	if (btn && btn->init(chapterInfo))
	{
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return nullptr;
}

bool MyGame::LocationInfoBtn::init(ChapterInfo* chapterInfo)
{
	if (!ui::Button::init())
	{
		return false;
	}
	_chapterInfo = chapterInfo;
	std::string path = "FHD/Icon/";
	_pin = path + "pin.png";
	_pinCompleted = path + "pin-completed.png";
	_pinUnopened = path + "pin-unopened.png";

	auto chapState = _chapterInfo->getState();
	switch (chapState)
	{
	case MyGame::ChapterState::Uncompleted:
		loadTextureNormal(_pin);
		break;
	case MyGame::ChapterState::Completed:
		loadTextureNormal(_pinCompleted);
		break;
	case MyGame::ChapterState::Unopened:
		loadTextureNormal(_pinUnopened);
		break;
	default:
		break;
	}

	// Map name
	TTFConfig font = GameConfig::getIns()->getFont();
	font.fontSize = font.fontSize * 1.5f;
	Label* mapName = Label::createWithTTF(font, _chapterInfo->getChapterName());
	mapName->setPosition(Vec2(_contentSize.width / 2, _contentSize.height + mapName->getContentSize().height / 2 + 10));
	mapName->setTextColor(Color4B(255, 235, 155, 255));
	mapName->enableOutline(Color4B::RED, 1);
	this->addChild(mapName);
	return true;
}
