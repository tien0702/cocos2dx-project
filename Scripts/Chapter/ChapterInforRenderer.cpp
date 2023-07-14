#include "ChapterInforRenderer.h"
#include "GameConfig.h"
#include "Scaler.h"

bool MyGame::ChapterInfoRenderer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	loadProperies();
	loadComponent();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {return true; };
	listener->onTouchEnded = [=](Touch* touch, Event* event) {
		if (isTouchInsideEmptySpace(touch)) this->turnOff();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->addChild(_darkLayer);
	this->addChild(_boxInfo);
	return true;
}

void MyGame::ChapterInfoRenderer::show(ChapterInfo* chapterInfo, Node* parent)
{
	// Update variable _chapterInfo
	_chapterInfo = chapterInfo;

	if (_chapterInfo == nullptr)
	{
		_chapterInfo = new ChapterInfo();
		_chapterInfo->setChapterName("????");
		_chapterInfo->setState(ChapterState::Uncompleted);
		_chapterState->setString("Comming Soon");
	}
	else
	{
		// Update Chapter Name
		_chapterName->setString(_chapterInfo->getChapterName());

		// Update Chapter Wave
		std::string waveInfo = std::string("Floors: ") + std::to_string(_chapterInfo->getMapIDs().size());
		_chapterWave->setString(waveInfo);

		// Update Chapter State
		std::string chapterState;
		auto chapState = _chapterInfo->getState();
		switch (chapState)
		{
		case MyGame::ChapterState::Uncompleted:
			chapterState = "Uncomplete";
			break;
		case MyGame::ChapterState::Completed:
			chapterState = "Completed";
			break;
		case MyGame::ChapterState::Unopened:
			chapterState = "Comming Soon";
			break;
		default:
			break;
		}
		_chapterState->setString("State: " + chapterState);
	}

	// Remove from parent 
	if (this->getParent() != nullptr) this->removeFromParent();

	// Show on parent
	parent->addChild(this, 100);
}

void MyGame::ChapterInfoRenderer::turnOff()
{
	this->removeFromParent();
}

bool MyGame::ChapterInfoRenderer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	Vec2 touchPos = touch->getLocation();
	bool isTouchOnNode = false;
	for (auto child : this->getChildren()) {
		auto nodeBoundingBox = child->getBoundingBox();
		if (child == _darkLayer) continue;
		if (nodeBoundingBox.containsPoint(touchPos)) {
			isTouchOnNode = true;
			break;
		}
	}
	if (!isTouchOnNode) {
		this->turnOff();
	}

	if (isTouchInsideEmptySpace(touch)) this->turnOff();
	return true;
}

bool MyGame::ChapterInfoRenderer::isTouchInsideEmptySpace(Touch* touch)
{
	Vec2 touchPos = touch->getLocation();
	bool isTouchOnNode = false;
	for (auto child : this->getChildren()) {
		auto nodeBoundingBox = child->getBoundingBox();
		if (child == _darkLayer) continue;
		if (nodeBoundingBox.containsPoint(touchPos)) {
			isTouchOnNode = true;
			break;
		}
	}
	if (!isTouchOnNode) {
		return true;
	}

	return false;
}

bool MyGame::ChapterInfoRenderer::loadComponent()
{
	// Init some value
	int margin = 10;

	// Init Dark Layer
	_darkLayer = LayerColor::create();
	_darkLayer->initWithColor(Color4B(0, 0, 0, 120));

	// Init Box Info
	auto size = Director::getInstance()->getOpenGLView()->getFrameSize();
	_boxInfo = Sprite::create("FHD/Background/box-info.png");
	_boxInfo->setPosition(size / 2);

	// Init hide button
	_hideBtn = ui::Button::create("FHD/Icon/cancel.png");
	_hideBtn->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			this->turnOff();
			break;
		default:
			break;
		}
		});
	_hideBtn->setPosition(Vec2(_boxInfo->getContentSize()));

	// Init Chapter Name
	auto fontName = _font;
	fontName.fontSize *= 1.5f;
	_chapterName = Label::createWithTTF(fontName, "Chapter Name");
	_chapterName->enableOutline(Color4B(0, 0, 0, 200), 2);
	_chapterName->setAlignment(TextHAlignment::CENTER);
	_chapterName->setPosition(Vec2(_boxInfo->getContentSize().width / 2,
		_boxInfo->getContentSize().height - _chapterName->getContentSize().height / 2 - margin));
	Scaler::scaleByScreen(_chapterName);
	_chapterName->retain();

	// Init Chapter Wave Info
	_chapterWave = Label::createWithTTF(_font, "Chapter Wave Info");
	_chapterWave->setAlignment(TextHAlignment::LEFT);
	_chapterWave->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_chapterWave->setPosition(Vec2(margin, _chapterName->getPosition().y - _chapterName->getContentSize().height / 2 -
	_chapterWave->getContentSize().height / 2 - margin));
	Scaler::scaleByScreen(_chapterWave);
	_chapterWave->retain();

	// Init Chapter State
	_chapterState = Label::createWithTTF(_font, "Chapter State");
	_chapterState->setAlignment(TextHAlignment::LEFT);
	_chapterState->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_chapterState->setPosition(margin, _chapterWave->getPosition().y - _chapterWave->getContentSize().height / 2 -
	_chapterState->getContentSize().height / 2 - margin);
	Scaler::scaleByScreen(_chapterState);
	_chapterState->retain();

	// addChild Box Info
	_boxInfo->addChild(_chapterName);
	_boxInfo->addChild(_chapterWave);
	_boxInfo->addChild(_chapterState);
	_boxInfo->addChild(_hideBtn);
	return true;
}

bool MyGame::ChapterInfoRenderer::loadProperies()
{
	_font = GameConfig::getIns()->getFont();
	_font.fontSize *= 0.7f;
	return true;
}
