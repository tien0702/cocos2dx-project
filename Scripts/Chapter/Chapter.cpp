#include "Chapter.h"
#include "Manager/GameManager.h"
#include "ChapterMap.h"
#include "GameReward/Reward.h"
#include "GameData/RewardData.h"
#include "Scene/LoadingScene.h"
#include "Scene/WinGame.h"
#include "Scene/LoseGame.h"
#include "GameData/PlayerData.h"
#include "Character/State/CharacterStateMachine.h"


#include <iostream>
#include <future>
#include <chrono>

MyGame::Chapter::Chapter()
{
	_bonuses = new std::list<Bonus*>();
}

bool MyGame::Chapter::isCompleted()
{
	return _isCompleted;
}

void MyGame::Chapter::nextMap()
{
	// Check completed map
	if (_curMap == _mapIDs.size() - 1)
	{
		this->sumaryChap(true);
	}
	else
	{
		this->playAt(_curMap + 1);
	}
}

void MyGame::Chapter::startChapter()
{
	_curMap = 0;
	Player::getIns()->getCharacter()->getStateMachine()->setState("spawn");
	this->playAt(_curMap);
}

void MyGame::Chapter::exitChapter()
{
	for (Bonus* bonus : (*_bonuses))
	{
		GameManager::getIns()->getCharacter()->removeBonus(bonus);
	}
	_bonuses->clear();
}

void MyGame::Chapter::replay()
{
	this->playAt(_curMap);
}

void MyGame::Chapter::playAt(int index)
{
	if (index < 0 || index > _mapIDs.size() - 1)
		index = 0;
	_curMap = index;
	//Loading Scene
	LoadingScene* loadingScene = LoadingScene::create();
	auto director = Director::getInstance();

	Scene* chapterMap = ChapterMap::createChapterMap(_mapIDs.at(index));
	if (director->getRunningScene() == nullptr)
	{
		director->runWithScene(chapterMap);
	}
	else
	{
		director->replaceScene(chapterMap);
		director->pushScene(loadingScene);
	}
}

void MyGame::Chapter::sumaryChap(bool isWin)
{
	Scene* summaryScene = nullptr;
	if (isWin)
	{
		summaryScene = WinGame::create();
	}
	else
	{
		summaryScene = LoseGame::create();
	}

	Director::getInstance()->replaceScene(summaryScene);
}

void MyGame::Chapter::applyBonus(Bonus* bonus)
{
	_bonuses->push_back(bonus);
	Player::getIns()->getCharacter()->addBonus(bonus);
}

void MyGame::Chapter::clearBonuses()
{
	for (Bonus* bns : *_bonuses)
	{
		Player::getIns()->getCharacter()->removeBonus(bns);
	}

	_bonuses->clear();
}

void MyGame::Chapter::giveReward()
{
	GameData::PlayerData::giveReward(_reward);
	clearBonuses();
}
