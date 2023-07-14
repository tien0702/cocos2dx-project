#include "LoadingScene.h"
#include "GameConfig.h"
#include "Chapter/ChapterMap.h"
#include <iostream>
#include <future>
#include <chrono>


std::vector<std::string> getAllFile(std::string folderPath)
{
	return std::vector<std::string>();
}

bool LoadingScene::init()
{
	if (!Scene::init()) {
		log("Init Loading Scene failed!");
		return false;
	}
	if (!loadProperties()) {
		log("Load properties failed!");
		return false;
	}
	Vec2 posBg, posProcess, posLb;


	_processBar = ui::Slider::create();
	_processBar->loadProgressBarTexture(_processbarPath);
	_processBar->loadBarTexture(_trackPath);

	_processValueLb = Label::createWithTTF(_font, "100.0 %");

	posBg = Director::getInstance()->getOpenGLView()->getFrameSize() / 2;
	posProcess.x = (Director::getInstance()->getOpenGLView()->getFrameSize() / 2).width;
	posProcess.y = 70;
	posLb.x = posProcess.x - _processBar->getContentSize().width / 2 - _processValueLb->getContentSize().width - 5;
	posLb.y = posProcess.y;

	_processBar->setPosition(posProcess);
	_processValueLb->setPosition(posLb);

	Sprite* bg = Sprite::create(_bgFolderPath);
	bg->setPosition(posBg);
	bg->setOpacity(bg->getOpacity() * 0.5f);
	_elapsedTime = 0.0f;
	this->addChild(bg);
	this->addChild(_processValueLb);
	this->addChild(_processBar);
	this->scheduleUpdate();
	return true;
}

void LoadingScene::startLoadingChapterMap(int mapID)
{
	// use std::async to loading
	auto future = std::async(std::launch::async, [=]() {
		// create a instance
		auto chapterMap = ChapterMap::createChapterMap(mapID);
		//chapterMap->retain();

		return chapterMap;
		});

	this->schedule([&](float delta) {
		auto loadedPercent = future.wait_for(std::chrono::seconds(0));
		if (loadedPercent == std::future_status::ready) {
			auto chapterMap = future.get();
			chapterMap->autorelease();
			auto scene = TransitionFade::create(0.5f, chapterMap);
			Director::getInstance()->replaceScene(scene);
		}
		else {
			_processValue += delta;
			auto percent = _processValue * 100;
			_processBar->setPercent(percent);
			_processValueLb->setString(StringUtils::format("%d%%", static_cast<int>(percent)));
		}

		}, "update_loading_bar");
}

void LoadingScene::updateProgressBar(float progress)
{
	_elapsedTime += progress;
	updateProcess();
	updatePercent();
	updateValueLabel();
}

bool LoadingScene::loadProperties()
{
	_completeProcess = false;
	_processValue = 0.0f;

	_bgFolderPath = "FHD/" + _bgFolderPath;
	_trackPath = "FHD/" + _trackPath;
	_processbarPath = "FHD/" + _processbarPath;
	_font = GameConfig::getIns()->getFont();
	_font.fontSize *= 0.8f;
	return true;
}

void LoadingScene::update(float dt)
{
	_elapsedTime += dt;
	updateProcess();
	updatePercent();
	updateValueLabel();
	if (_elapsedTime >= _timeLoading) { completedLoading(); }
}

void LoadingScene::updateProcess()
{
	_processValue = MathUtil::lerp(_processValue, 100.0f, 0.05);
}

void LoadingScene::updatePercent()
{
	_processBar->setPercent(_processValue);
}

void LoadingScene::updateValueLabel()
{
	char valueStr[10];
	sprintf(valueStr, "%0.2lf", _processValue);
	_processValueLb->setString(std::string(valueStr) + " %");
}

void LoadingScene::completedLoading()
{
	Director::getInstance()->popScene();
}
