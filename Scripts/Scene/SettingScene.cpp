#include "SettingScene.h"
#include "Settings/Setting.h"
#include "GameConfig.h"
#include "AudioManager/AudioManager.h"
#include "Scaler.h"

bool MyGame::SettingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	loadComponents();

	this->addChild(_background, 0);
	this->addChild(_backgroundMusic, 1);
	this->addChild(_soundEffectVolume, 1);
	this->addChild(_backBtn, 1);
	return true;
}

bool MyGame::SettingScene::loadComponents()
{
	_font = GameConfig::getIns()->getFont();
	loadButtonComponent();
	loadSliderComponent();
	return true;
}

bool MyGame::SettingScene::loadProperties()
{
	return true;
}

bool MyGame::SettingScene::loadButtonComponent()
{
	// Path
	std::string path, normalTexturePath;
	path = "FHD/Button/";
	normalTexturePath = path + "btn.png";
	Rect fixedVisible = GameConfig::getIns()->getFixedVisible();

	// Init
	auto lb = Label::createWithTTF(_font, "Back");
	_backBtn = ui::Button::create();
	_backBtn->loadTextureNormal(normalTexturePath);
	lb->setPosition(_backBtn->getContentSize() / 2);
	Scaler::scaleNodeToFit(lb, _backBtn, 10);
	_backBtn->addChild(lb);
	_backBtn->setPosition(Scaler::calculatePosition(
		Vec2(fixedVisible.getMaxX() - _backBtn->getContentSize().width / 2 - 10, fixedVisible.getMaxY() - _backBtn->getContentSize().height / 2 - 10)));
	_backBtn->addTouchEventListener([this](Ref*, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::BEGAN) {
			AudioManager::getIns()->playeButtonEffect();
		}
		else if (type == ui::Widget::TouchEventType::ENDED) {
			Setting::save();
			Director::getInstance()->popScene();
		}
		});
	return true;
}

bool MyGame::SettingScene::loadSliderComponent()
{
	// Path
	std::string path, progressPath, trackPath, thumbPath, bgPath;
	path = "FHD/Slider/";
	progressPath = path + "progress.png";
	trackPath = path + "track.png";
	thumbPath = path + "thumb-slide.png";
	bgPath = "FHD/Background/bg-infor.jpg";

	// Label
	Label* BG, * SFX;
	BG = Label::createWithTTF(_font, "BG Music");
	SFX = Label::createWithTTF(_font, "SFX");
	BG->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	SFX->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);

	// Background
	_backgroundMusic = cocos2d::ui::Slider::create();
	_backgroundMusic->loadBarTexture(trackPath);
	_backgroundMusic->loadSlidBallTextureNormal(thumbPath);
	_backgroundMusic->loadProgressBarTexture(progressPath);
	_backgroundMusic->setPercent(Setting::_BGM_Volume * 100.0f);
	_backgroundMusic->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_backgroundMusic->addEventListener([=](cocos2d::Ref* sender, cocos2d::ui::Slider::EventType eventType)
		{
			if (eventType == cocos2d::ui::Slider::EventType::ON_SLIDEBALL_DOWN)
			{
				AudioManager::getIns()->playeButtonEffect();
			}
			else if (eventType == cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
			{
				cocos2d::ui::Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
				int percent = slider->getPercent();
				Setting::_BGM_Volume = percent * 0.01f;
				AudioManager::getIns()->setBackgroundMusicVolume(Setting::_BGM_Volume);
			}
		});
	_backgroundMusic->addChild(BG);

	// Sound Effect
	_soundEffectVolume = cocos2d::ui::Slider::create();
	_soundEffectVolume->loadBarTexture(trackPath);
	_soundEffectVolume->loadSlidBallTextureNormal(thumbPath);
	_soundEffectVolume->loadProgressBarTexture(progressPath);
	_soundEffectVolume->setPercent(Setting::_SFX_Volume * 100.0f);
	_soundEffectVolume->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_soundEffectVolume->addEventListener([=](cocos2d::Ref* sender, cocos2d::ui::Slider::EventType eventType)
		{
			if (eventType == cocos2d::ui::Slider::EventType::ON_SLIDEBALL_DOWN)
			{
				AudioManager::getIns()->playeButtonEffect();
			}
			else if (eventType == cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
			{
				cocos2d::ui::Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(sender);
				int percent = slider->getPercent();
				Setting::_SFX_Volume = percent * 0.01f;
			}
		});
	_soundEffectVolume->addChild(SFX);

	// Background
	_background = Sprite::create(bgPath);

	// Position
	float distance = 250, offset = 50;
	BG->setPosition(Scaler::calculatePosition(Vec2(-distance, _soundEffectVolume->getContentSize().height / 2)));
	SFX->setPosition(Scaler::calculatePosition(Vec2(-distance, _backgroundMusic->getContentSize().height / 2)));

	float height = Director::getInstance()->getOpenGLView()->getFrameSize().height;

	_backgroundMusic->setPosition(Scaler::calculatePosition(Vec2(distance + offset, height * 0.7f)));
	_soundEffectVolume->setPosition(Scaler::calculatePosition(Vec2(distance + offset, height * 0.6f)));
	_background->setPosition(_background->getContentSize() / 2);

	return true;
}
