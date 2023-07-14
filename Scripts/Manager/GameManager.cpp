#include "GameManager.h"
#include "Map/GameMap.h"
#include "Scene/LoadingScene.h"
#include "UI/HUDLayer.h"
#include "GameData/ChapterData.h"

GameManager* GameManager::_instance;

GameManager* GameManager::getIns()
{
	if (_instance == nullptr)
	{
		_instance = new GameManager();
	}
	return _instance;
}

void GameManager::playChapterID(int id)
{
	GameData::ChapterData* data = new GameData::ChapterData();
	_chapter = data->getChapterByID(id);
	_chapter->startChapter();
}

void GameManager::startGame()
{
}

void GameManager::exitGame()
{
	cocos2d::Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

Character* GameManager::getCharacter()
{
	return Player::getIns()->getCharacter();
}

GameManager::GameManager()
{

}
