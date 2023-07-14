#include "OptionLayer.h"
#include "ui/CocosGUI.h"
#include "GameConfig.h"
#include "AudioManager/AudioManager.h"

bool MyGame::OptionLayer::init()
{
	if (!IInforLayer::init()) {
		log("Init Option Layer failed!");
		return false;;
	}

	if (!loadDefaultProperties()) {
		log("Load Default Properties failed!");
		return false;
	}

	//
	this->_nameLayer = "Option";
	this->_iconPath = "FHD/Icon/option.png";

	ui::Slider* sfxSlide, * bgmSlide;
	ui::Button* fixedJoyBt;
	Label* sfxLb, * bgmLb, * fixedJoyLb;
	Vec2 sfxPos, bgmPos, fixedJoyPos;

	std::vector<Sprite*> lines;
	Sprite* line1, line2;
	float lineHeight = 100;

	// Init Label
	sfxLb = Label::createWithTTF(_font, "SFX");
	bgmLb = Label::createWithTTF(_font, "BG Music");
	fixedJoyLb = Label::createWithTTF(_font, "Fixed Joystick");

	// Init Sound Effect slide
	sfxSlide = ui::Slider::create();
	sfxSlide->loadBarTexture(_trackPath);
	sfxSlide->loadSlidBallTextureNormal(_thumbPath);
	sfxSlide->loadProgressBarTexture(_progressBarPath);
	sfxSlide->addEventListener([&](Ref* pSender, ui::Slider::EventType type) {
		switch (type)
		{
		case cocos2d::ui::Slider::EventType::ON_SLIDEBALL_DOWN:
			AudioManager::getIns()->playeButtonEffect();
			break;
		case cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
		{
			ui::Slider* slider = dynamic_cast<ui::Slider*>(pSender);
			int percent = slider->getPercent();
			_SFX = percent;
		}
		break;
		default:
			break;
		}
		});

	// Init Background Music slide
	bgmSlide = ui::Slider::create();
	bgmSlide->loadBarTexture(_trackPath);
	bgmSlide->loadSlidBallTextureNormal(_thumbPath);
	bgmSlide->loadProgressBarTexture(_progressBarPath);
	bgmSlide->addEventListener([&](Ref* pSender, ui::Slider::EventType type) {
		switch (type)
		{
		case cocos2d::ui::Slider::EventType::ON_SLIDEBALL_DOWN:
			AudioManager::getIns()->playeButtonEffect();
			break;
		case cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
		{
			ui::Slider* slider = dynamic_cast<ui::Slider*>(pSender);
			int percent = slider->getPercent();
			_BGMusic = percent;
		}
		break;
		default:
			break;
		}
		});

	// Fixed Joystick
	fixedJoyBt = ui::Button::create((_isFixedJoystick) ? (_switchOnPath) : (_switchOffPath));
	fixedJoyBt->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				_isFixedJoystick = !_isFixedJoystick;
				fixedJoyBt->loadTextureNormal((_isFixedJoystick) ? (_switchOnPath) : (_switchOffPath));
				break;
			default:
				break;
			}
		});

	// Postion
	lines.push_back(createLine(bgmLb, bgmSlide));
	lines.push_back(createLine(sfxLb, sfxSlide));
	lines.push_back(createLine(fixedJoyLb, fixedJoyBt));

	// addChild
	Size lineSize = lines[0]->getContentSize();
	for (int i = 0; i < lines.size(); ++i)
	{
		Vec2 pos;
		pos.y = lineSize.height / 2 + (lineSize.height + lineHeight) * i;
		pos.y = _sizeLayer.height / 2 - pos.y;
		pos.x = _sizeLayer.width / 2 - lineSize.width / 2;
		lines[i]->setPosition(pos);
	}

	for (int i = 0; i < lines.size(); ++i)
	{
		this->addChild(lines[i]);
	}

	return true;
}

bool MyGame::OptionLayer::loadDefaultProperties()
{
	_font = GameConfig::getIns()->getFont();
	_BGMusic = 50;
	_SFX = 50;
	_isFixedJoystick = false;

	_switchOffPath = "FHD/Icon/switch-off.png";
	_switchOnPath = "FHD/Icon/switch-on.png";
	_thumbPath = "FHD/Icon/thumb-slide.png";
	_trackPath = "FHD/Background/track.png";
	_progressBarPath = "FHD/Background/progress.png";

	return true;
}

Sprite* MyGame::OptionLayer::createLine(Node* left, Node* right)
{
	float width = _sizeLayer.width / 2;
	Sprite* sprite = Sprite::create();
	sprite->setContentSize(Size(_sizeLayer.width / 2, 0));
	left->setPosition(Vec2(left->getContentSize().width / 2, 0));
	right->setPosition(Vec2(width - right->getContentSize().width / 2, 0));
	sprite->addChild(left);
	sprite->addChild(right);
	return sprite;
}
