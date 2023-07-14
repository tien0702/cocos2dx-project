
#include "ChapterMap.h"
#include "Input/Input.h"
#include "Input/PlayerInput.h"
#include "Input/JoystickMove.h"
#include "GameData/EntityData.h"
#include "Player/Player.h"
#include "Map/Gate.h"
#include "Scene/LoadingScene.h"
#include "Enemy/EnemyPool.h"

#include "GameData/ChapterData.h"
#include "Manager/GameManager.h"
#include "Chapter/EnemyWave.h"
#include "ObjectTag.h"
#include "GameData/WeaponData.h"
#include "GameData/RewardData.h"

// include test
#include "GameReward/BonusRenderer.h"

int _chapterID;
ChapterMapInfo* tempChapterMapInfo;

Scene* MyGame::ChapterMap::createChapterMap(int id)
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	_chapterID = id;
	GameData::ChapterData* chapterData = new GameData::ChapterData();
	auto chapterMapInfo = chapterData->getChapterMapInfoByID(_chapterID);
	tempChapterMapInfo = chapterMapInfo;

	auto layer = ChapterMap::create();
	layer->setTag(ObjectTag::ChapterMap);
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}

bool MyGame::ChapterMap::init()
{
	this->_chapterMapID = _chapterID;
	_chapterMapInfo = tempChapterMapInfo;

	if (!Scene::initWithPhysics()) {
		log("init MainScene failed!");
		return false;
	}

	if (!loadProperties()) {
		log("Load Properties MainScene faild!");
		return false;
	}

	PlayerInput::getIns()->cleanInput();
	InfoTargetEnemy::getIns()->changeTarget(nullptr);
	// map
	_map->addChild(_player, INT_MAX);
	//_map->setFrontObj(_player);
	PlayerInput::getIns()->reloadSkillBtns();

	// addChild
	this->addChild(Input::getIns(), SceneLayer::Default);
	this->addChild(_map, SceneLayer::Map);
	this->addChild(_camFollow, SceneLayer::Default);
	this->addChild(HUDlayer::getIns(), SceneLayer::HUDlayer);
	this->scheduleUpdate();

	this->playWaveAt(_curWave);
	return true;
}

void MyGame::ChapterMap::startChapter(Chapter* chapter)
{
	if (chapter == nullptr) return;
	_chapter = chapter;
	std::string notify = "";
}

void MyGame::ChapterMap::nextWave()
{
	_waves.at(_curWave)->exit();
	if (_curWave == _waves.size() - 1)
	{
		this->onCompletedChapter();
	}
	else
	{
		++_curWave;
		this->playWaveAt(_curWave);
	}
}

void MyGame::ChapterMap::playWaveAt(int index)
{
	std::string message = "Wave " + std::to_string(_curWave + 1) + " / " + std::to_string(_waves.size());
	HUDlayer::getIns()->notify(message, Color3B::WHITE);
	_waves.at(_curWave)->initWave();
	_waves.at(_curWave)->enter(this);
}

void MyGame::ChapterMap::exitMap()
{
}

void MyGame::ChapterMap::update(float dt)
{
	HUDlayer::getIns()->setPosition(_defaultCamera->getPosition() - Director::getInstance()->getOpenGLView()->getFrameSize() / 2);

	if (_isCompleted)
	{
		if (_chest == nullptr)
		{
			_gate->open();
		}
		else
		{
			if (_chest->isOpened())
			{
				_chest->setVisible(false);
				_gate->open();
			}
		}
		return;
	}

	if (_waves.at(_curWave)->_isCompleted) this->nextWave();
}

bool MyGame::ChapterMap::loadProperties()
{
	this->initMap();
	this->playerSetting();
	this->initBonusDeck();
	this->initEnemyWaves();
	this->loadComponent();
	this->loadReward();
	return true;
}

bool MyGame::ChapterMap::loadComponent()
{
	// HUDlayer
	HUDlayer::getIns()->setCam(this->_defaultCamera);
	// Camera 
	Rect fieldOfView;
	fieldOfView.origin.setZero();
	fieldOfView.size = _map->getContentSize();
	_camFollow = new CameraFollow(_defaultCamera, _player, fieldOfView);
	_camFollow->init();

	// Mics 
	PlayerInput::getIns()->cleanInput();
	PlayerInput::getIns()->enable();
	_chapter = GameManager::getIns()->getChapter();

	// remove from parent 
	if (HUDlayer::getIns()->getParent() != nullptr)
		HUDlayer::getIns()->getParent()->removeChild(HUDlayer::getIns(), false);
	if (_player->getParent() != nullptr)
		_player->getParent()->removeChild(_player, false);
	if (Input::getIns()->getParent() != nullptr)
		Input::getIns()->getParent()->removeChild(Input::getIns());
	return true;
}

bool MyGame::ChapterMap::loadReward()
{
	GameData::RewardData data;
	_reward = data.getRewardByID(_chapterMapInfo->getRewardID());
	return true;
}

bool MyGame::ChapterMap::initMap()
{
	// Map
	std::string tileMapName = _chapterMapInfo->getTileMapName();
	std::string mapPath = "Map/" + tileMapName + ".tmx";
	_map = new GameMap();
	_map->initWithTMXFile(mapPath);

	//Gate 
	ValueMap gateVal = _map->getObjectInPoint(GameMap::Gate);
	_gate = new Gate();
	_gate->initWithValueMap(gateVal);

	GameManager::getIns()->setGameMap(_map);

	return true;
}

bool MyGame::ChapterMap::playerSetting()
{
	// Character 
	_player = Player::getIns()->getCharacter();
	auto val = _map->getObjectInPoint(GameMap::Teleport);
	_player->setPosition(val["x"].asInt(), val["y"].asInt());
	return true;
}

bool MyGame::ChapterMap::initBonusDeck()
{
	// Bonus Deck 
	GameData::RewardData* rewarData = new GameData::RewardData();
	BonusDeck* deck = rewarData->getBonusDeckByID(_chapterMapInfo->getBonusDeckID());
	if (deck != nullptr)
	{
		deck->setTargetEntity(_player);
		_bonusRenderer = new BonusRenderer(deck);
		_bonusRenderer->init();

		// Chest
		std::string chestPath = "FHD/Icon/chest-close.png";
		ValueMap chestVal = _map->getObjectInPoint(GameMap::Chest);
		Vec2 chestPos;
		chestPos.x = chestVal["x"].asFloat();
		chestPos.y = chestVal["y"].asFloat();
		_chest = new Chest();
		_chest->initWithClosedImage(chestPath, chestPath, _player, _bonusRenderer);
		_chest->setPosition(chestPos);
	}
	return true;
}

bool MyGame::ChapterMap::initEnemyWaves()
{
	GameData::ChapterData* chapterData = new GameData::ChapterData();
	// Enemy Wave 
	_waves = chapterData->getEnemyWaveInChapterMap(this->_chapterMapID);
	for (auto wave : _waves)
	{
		auto info = wave->getInfoEnemies();
		for (auto i : info)
		{
			EnemyPool::getIns()->initEnemyByName(i.first);
		}
	}
	_curWave = 0;

	return true;
}

void MyGame::ChapterMap::startWave()
{
	_curWave = 0;
	this->playWaveAt(_curWave);
}

void MyGame::ChapterMap::onCompletedChapter()
{
	_isCompleted = true;
	std::string message = "Completed Chapter";
	HUDlayer::getIns()->notify(message, Color3B::GREEN);

	this->addChild(_gate, SceneLayer::Effect);
	if (_chest != nullptr)
	{
		this->addChild(_chest, SceneLayer::Effect);
		_chest->open();
		this->giveReward();
	}
}

void MyGame::ChapterMap::giveReward()
{
	Reward* chapterReward = GameManager::getIns()->getChapter()->getChapterReward();
	if (chapterReward == nullptr)
	{
		log("Reward null");
		return;
	}

	if (!_chapterMapInfo->getCleared())
	{
		chapterReward->add(_reward);
		_chapterMapInfo->setCleared(true);
	}
}
