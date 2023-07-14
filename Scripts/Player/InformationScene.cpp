#include "InformationScene.h"
#include "GameConfig.h"
#include "Input/JoystickMove.h"
#include "AudioManager/AudioManager.h"
#include "Scaler.h"

bool MyGame::InformationScene::init()
{
	if (!Scene::init()) {
		log("Init Information Scene failed!");
		return false;
	}

	// Load properties 
	_font = GameConfig::getIns()->getFont();
	_backgroundPath = "FHD/Background/bgr2.png";
	_backgroundButtonPath = "FHD/Background/bg-bt-infor.png";
	_homeIconPath = "FHD/Button/btn.png";

	// Size and Position
	Size frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	Vec2 centerScreen = frameSize / 2;

	// Calculate _sizeOfInforLayer, _posOfInforLayer
	Rect fixedVisible = GameConfig::getIns()->getFixedVisible();
	_sizeOfInforLayer = fixedVisible.size * 0.8f;
	_posOfInforLayer.x = fixedVisible.origin.x + fixedVisible.size.width - (_sizeOfInforLayer.width / 2 + MarginSide);
	_posOfInforLayer.y = fixedVisible.size.height / 2;

	// Init layers
	if (!initLayerInfor(new AttributeLayer(), LayerName::AttributeLayer)) {
		log("Init attribute failed!");
		return false;
	}

	if (!initLayerInfor(new OptionLayer(), LayerName::Option_Layer)) {
		log("Init option layer failed!");
		return false;
	}

	// Create buttons
	if (!createButtons()) {
		log("Create button failed!");
		return false;
	}

	auto bgSprite = Sprite::create(_backgroundPath);
	bgSprite->setPosition(centerScreen);

	// Add buttons
	for (auto bt : _buttons) { this->addChild(bt, 1); }

	// Set Current index is Attribute layer
	_currentIndex = LayerName::AllLayer;
	this->changeLayer(LayerName::AttributeLayer);

	ui::Button* homeBT = ui::Button::create(_homeIconPath);
	auto lb = Label::createWithTTF(_font, "Back");
	Scaler::scaleNodeToFit(lb, homeBT, 10);
	lb->setPosition(homeBT->getContentSize() / 2);
	homeBT->addChild(lb);
	homeBT->setPosition(frameSize - homeBT->getContentSize() / 2 - Size(30, 30));
	homeBT->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				this->backToMainScene();
				break;
			default:
				break;
			}
		});

	// addChild
	this->addChild(bgSprite, 0);
	this->addChild(homeBT, 1);
	return true;
}

bool MyGame::InformationScene::initLayerInfor(IInforLayer* layer, LayerName indexLayer)
{
	Size visibleSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	//

	_layers[(int)indexLayer] = layer;
	_layers[(int)indexLayer]->setSizeLayer(_sizeOfInforLayer);
	_layers[(int)indexLayer]->init();
	_layers[(int)indexLayer]->retain();
	_layers[(int)indexLayer]->setTag(LayerTag);

	_buttons[(int)indexLayer] = ui::Button::create(_backgroundButtonPath);
	_buttons[(int)indexLayer]->retain();
	_buttons[(int)indexLayer]->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				AudioManager::getIns()->playeButtonEffect();
				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
				this->changeLayer(indexLayer);
				break;
			default:
				break;
			}
		});


	// Init Icon And Name
	Label* nameLayer;
	Sprite* iconLayer;
	Vec2 posIcon, posName;
	std::string nameStr, iconPath;

	nameStr = layer->getNameLayer();
	iconPath = layer->getIconPath();

	nameLayer = Label::createWithTTF(_font, nameStr);
	iconLayer = Sprite::create(iconPath.c_str());

	posName.x = _buttons[(int)indexLayer]->getContentSize().width / 2;
	posName.y = nameLayer->getContentSize().height / 2;

	posIcon.x = _buttons[(int)indexLayer]->getContentSize().width / 2;
	posIcon.y = _buttons[(int)indexLayer]->getContentSize().height - iconLayer->getContentSize().height / 2;
	posIcon.y = _buttons[(int)indexLayer]->getContentSize().height / 2;

	nameLayer->setPosition(posName);
	iconLayer->setPosition(posIcon);
	_buttons[(int)indexLayer]->addChild(iconLayer);
	//_buttons[(int)indexLayer]->addChild(nameLayer);
	return true;
}

bool MyGame::InformationScene::createButtons()
{
	Vec2 originPos;
	Size sizeBt = _buttons[(int)LayerName::AttributeLayer]->getContentSize();
	float disButton = 10, zoomScale = -0.01;
	originPos.x = sizeBt.width / 2 + MarginSide;
	originPos.y = _posOfInforLayer.y + _sizeOfInforLayer.height / 2 - sizeBt.height / 2;

	for (int i = 0; i < (int)LayerName::AllLayer; ++i)
	{
		auto bt = _buttons[i];
		Vec2 pos;

		bt->setZoomScale(zoomScale);
		pos.x = originPos.x;
		pos.y = originPos.y - (sizeBt.height + disButton) * i;
		bt->setPosition(pos);
		bt->setVisible(false);
	}

	return true;
}

void MyGame::InformationScene::changeLayer(LayerName indexLayer)
{
	if (indexLayer == _currentIndex) {
		return;
	}
	_currentIndex = indexLayer;
	auto layer = _layers[(int)_currentIndex];
	layer->setPosition(_posOfInforLayer);
	this->removeChildByTag(LayerTag);
	this->addChild(layer, 1);
}

void MyGame::InformationScene::backToMainScene()
{
	Director::getInstance()->popScene();
}
