#include "PlayerInventoryScene.h"
#include "Inventory/DetailTable/WeaponDetailTable.h"
#include "Inventory/DetailTable/ComsumableItemDetailTable.h"
#include "GameConfig.h"
#include "Scaler.h"
#include "GameData/ConsumableItemData.h"
#include "GameData/WeaponData.h"
#include "AudioManager/AudioManager.h"

bool MyGame::PlayerInventoryScene::init()
{
    if (!Scene::init()) {
        log("Init Player Inventory failed!");
        return false;
    }

	if (!loadProperties()) {
		log("Load Properties failed!");
		return false;
	}

	if (!loadInventory()) {
		log("Load list Inventory failed!");
		return false;
	}

	if (!loadButtons())
	{
		log("Load buttons inventory failed!");
		return false;
	}

	if (!initNavBar()) {
		log("Init Nav Bar failed!");
		return false;
	}

	Vec2 posNameLB;
	posNameLB.x = _fixedVisible.origin.x;
	posNameLB.y = _fixedVisible.size.height - 50;

	auto lb = Label::createWithTTF(_font, "Back");
	ui::Button* backBT = ui::Button::create();
	backBT->loadTextureNormal(_backBTPath);
	Scaler::scaleNodeToFit(lb, backBT, 10);
	lb->setPosition(backBT->getContentSize() / 2);
	backBT->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	backBT->setPosition(_fixedVisible.size);
	backBT->addChild(lb);
	backBT->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
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

	_currentIvn = IvnType::IvnItem;
	changeIvn(IvnType::IvnWeap);

	Size screenSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	auto rectNode = DrawNode::create();
	Vec2 vertices[4] = {
		Vec2(0, 0),
		Vec2(screenSize.width, 0),
		Vec2(screenSize.width, screenSize.height),
		Vec2(0, screenSize.height)
	};

	rectNode->drawPolygon(vertices, 4, Color4F::GRAY, 0, Color4F::WHITE);
	_currentName->setPosition(posNameLB);
	auto bg = Sprite::create(_backgroundPath);
	this->addChild(_currentName, 1);
	this->addChild(bg, 0);
	this->addChild(backBT);
    return true;
}

void MyGame::PlayerInventoryScene::backToMainScene()
{
    Director::getInstance()->popScene();
}

bool MyGame::PlayerInventoryScene::initNavBar()
{
	Sprite* navBar = Sprite::create(_navBarPath);
	Sprite* buttonBg = Sprite::create(_buttonNormalBGPath);
	Size btSize = buttonBg->getContentSize();
	Size navSize = navBar->getContentSize();
	for (int i = 0; i < (int)IvnType::AllIvnType; ++i)
	{
		Vec2 pos;
		pos.x = navSize.width / 2;
		pos.y = navSize.height - (btSize.height) * ((float)i + 0.75f) - (10 * i);
		_buttons[i]->setPosition(pos);
		navBar->addChild(_buttons[i]);
	}

	Vec2 posNav;
	posNav.x = _fixedVisible.origin.x + navBar->getContentSize().width / 2;
	posNav.y = _fixedVisible.origin.y + _fixedVisible.size.height / 2;
	navBar->setPosition(posNav);
	this->addChild(navBar, 1);
	return true;
}

bool MyGame::PlayerInventoryScene::loadButtons()
{
	for (int i = 0; i < (int)IvnType::AllIvnType; ++i)
	{
		_buttons[i] = ui::Button::create();
		_buttons[i]->loadTextureNormal(_buttonNormalBGPath);
		_buttons[i]->setZoomScale(-0.1);
		_buttons[i]->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
			{
				switch (type)
				{
				case cocos2d::ui::Widget::TouchEventType::BEGAN:
						AudioManager::getIns()->playeButtonEffect();
						break;
				case cocos2d::ui::Widget::TouchEventType::ENDED:
					changeIvn((IvnType)i);
					break;
				default:
					break;
				}
			});
		Sprite* icon = Sprite::create(_ivns[i]->getIvnIcon());
		icon->setPosition(_buttons[i]->getContentSize() / 2);
		_buttons[i]->addChild(icon);
	}

	return true;
}

bool MyGame::PlayerInventoryScene::loadInventory()
{
	GameData::ItemData* data = new GameData::ItemData();

	GameData::ConsumableItemData itemData;
	GameData::WeaponData weapData;

	// weap
	_ivns[(int)IvnType::IvnWeap] = new InventoryBase();
	_ivns[(int)IvnType::IvnWeap]->setTypeItemContains(ItemType::WeaponType);
	_ivns[(int)IvnType::IvnWeap]->init();
	_ivns[(int)IvnType::IvnWeap]->setTag(PlayerInventoryScene::TagIvnLayer);
	_ivns[(int)IvnType::IvnWeap]->retain();

	std::vector<MagicBook*>* weaps = weapData.getPlayerWeapons();
	for (int i = 0; i < weaps->size(); ++i)
	{
		_ivns[(int)IvnType::IvnWeap]->addItem(weaps->at(i));
	}
	_ivns[(int)IvnType::IvnWeap]->drawBySortType(SortItemType::UpQuality);

	// comsum
	_ivns[(int)IvnType::IvnItem] = new InventoryBase();
	_ivns[(int)IvnType::IvnItem]->setTypeItemContains(ItemType::ComsumableType);
	_ivns[(int)IvnType::IvnItem]->init();
	_ivns[(int)IvnType::IvnItem]->setTag(PlayerInventoryScene::TagIvnLayer);
	_ivns[(int)IvnType::IvnItem]->retain();

	std::vector<ConsumableItem*>* items = itemData.getPlayerConsumableItems();
	for (int i = 0; i < items->size(); ++i)
	{
		_ivns[(int)IvnType::IvnItem]->addItem(items->at(i));
	}
	_ivns[(int)IvnType::IvnItem]->drawBySortType(SortItemType::UpQuality);

	_ivns[(int)IvnType::IvnWeap]->setIvnName("Weapon");
	_ivns[(int)IvnType::IvnItem]->setIvnName("Consumable Item");

	_ivns[(int)IvnType::IvnWeap]->setIvnIcon("FHD/Icon/weapon-icon.png");
	_ivns[(int)IvnType::IvnItem]->setIvnIcon("FHD/Icon/consumable-icon.png");
	return true;
}

bool MyGame::PlayerInventoryScene::loadProperties()
{
	_backgroundPath = "FHD/Background/bg-ivn.jpg";
	_backBTPath = "FHD/Button/btn.png";
	_navBarPath = "FHD/Background/bg-nav-ivn.png";
	_buttonNormalBGPath = "FHD/Background/bt-bg-nav.png";
	_buttonSelectedBGPath = "FHD/Background/bt-bg-nav-selected.png";
	_fixedVisible = GameConfig::getIns()->getFixedVisible();

	_font = GameConfig::getIns()->getFont();
	//_font.fontSize = 20;
	_currentName = Label::create();
	_currentName->setTTFConfig(_font);
	_currentName->setAlignment(TextHAlignment::LEFT);
	_currentName->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);

	return true;
}

void MyGame::PlayerInventoryScene::changeIvn(IvnType newIndex)
{
	if (newIndex == _currentIvn) return;
	_buttons[(int)_currentIvn]->loadTextureNormal(_buttonNormalBGPath);
	_currentIvn = newIndex;
	this->removeChildByTag(PlayerInventoryScene::TagIvnLayer);
	_currentName->setString(_ivns[(int)_currentIvn]->getIvnName());
	this->addChild(_ivns[(int)_currentIvn], 2);
	_buttons[(int)_currentIvn]->loadTextureNormal(_buttonSelectedBGPath);
}
