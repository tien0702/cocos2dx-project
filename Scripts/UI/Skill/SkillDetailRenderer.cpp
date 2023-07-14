#include "SkillDetailRenderer.h"
#include "GameConfig.h"
#include "Common.h"
#include "Convert.h"
#include "Scaler.h"
#include "AudioManager/AudioManager.h"
#include "Player/Player.h"
#include "GameData/PlayerData.h"

MyGame::SkillDetailRenderer* MyGame::SkillDetailRenderer::create(Size layerSize)
{
	SkillDetailRenderer* layer = new (std::nothrow) SkillDetailRenderer();
	if (layer && layer->init(layerSize))
	{
		layer->autorelease();
		return layer;
	}
	return nullptr;
}

bool MyGame::SkillDetailRenderer::init(Size layerSize)
{
	_layerSize = layerSize;
	if (!Layer::init())
	{
		return false;
	}

	loadComponent();
	loadPosition();

	this->addChild(_background);
	this->addChild(_skillDetails);
	this->addChild(_skillNameStr);
	this->addChild(_equipBtn);
	return true;
}

void MyGame::SkillDetailRenderer::render(Skill* skill, SkillEquipRenderer* equipRender)
{
	// draw bgr
	_background->clear();
	_background->drawRect(Vec2::ZERO, _layerSize, Color4F::WHITE);
	_background->drawSolidRect(Vec2::ZERO, _layerSize, Color4F(0, 0, 0, 0.7f));

	// update content
	_skillNameStr->setString(skill->getInfo()->getSkillName());
	loadDescription(skill);

	// update button event
	_equipBtn->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			AudioManager::getIns()->playeButtonEffect();
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			auto pData = GameData::PlayerData();
			InputID inputID = skill->getActivationButtonID();
			switch (inputID)
			{
			case MyGame::InputID::BT_Skill_Ultimate:
				pData.updateUltimate(skill->getInfo()->getSkillName());
				equipRender->setS2(skill);
				break;
			case MyGame::InputID::BT_Skill_Talen:
				pData.updateTalen(skill->getInfo()->getSkillName());
				equipRender->setS1(skill);
				break;
			default:
				break;
			}
		}
		break;
		default:
			break;
		}
		});
	loadPosition();
}

bool MyGame::SkillDetailRenderer::loadComponent()
{
	// get font
	_font = GameConfig::getIns()->getFont();

	//
	_skillNameStr = Label::createWithTTF(_font, "o");
	_skillNameStr->setTextColor(Color4B::MAGENTA);
	_skillNameStr->enableOutline(Color4B::BLACK, 1);
	_skillNameStr->enableShadow(Color4B::BLACK, Size(2, -2));
	_skillNameStr->setScale(2.0f);

	_skillDetails = Label::createWithTTF(_font, "o");
	_skillDetails->setMaxLineWidth(_layerSize.width - 60);
	_skillDetails->setLineHeight(_skillDetails->getContentSize().height + 10);
	_skillDetails->setAlignment(TextHAlignment::LEFT);
	_skillDetails->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);

	// background
	_background = DrawNode::create();

	// button
	auto lb = Label::createWithTTF(_font, "Equip");
	_equipBtn = ui::Button::create();
	_equipBtn->loadTextureNormal("FHD/Button/btn.png");
	lb->setTag(1);
	lb->setPosition(_equipBtn->getContentSize() / 2);
	Scaler::scaleNodeToFit(lb, _equipBtn, 10);
	_equipBtn->addChild(lb);
	return true;
}

bool MyGame::SkillDetailRenderer::loadPosition()
{
	_skillNameStr->setPosition(Vec2(_layerSize.width / 2, _layerSize.height));
	_skillDetails->setPosition(Vec2(20, _layerSize.height - _skillNameStr->getContentSize().height * 2));
	_equipBtn->setPosition(Vec2(_layerSize.width - _equipBtn->getContentSize().width / 2 - 10
		, _equipBtn->getContentSize().height / 2 + 10));
	return true;
}

void MyGame::SkillDetailRenderer::loadDescription(Skill* skill)
{
	auto power = skill->getSkillPower();
	float valP = power->getPowerValue() * 0.1f;
	float valNumber = power->getPowerNumber();
	auto inputId = skill->getActivationButtonID();

	// name
	std::string name = "Name: " + skill->getInfo()->getSkillName();

	// equip location
	std::string location = (inputId == InputID::BT_Skill_Talen) ? ("Talen") : ("Ultimate");
	location = "Equip Location: " + location;

	// cooldown
	std::string cooldown = "Cooldown: " + Common::formatFloat(skill->getStatByID(Stat::Cooldown)->getFinalValue() * 0.001f) + " s";

	// mana cost
	std::string manaCost = "Mana Cost: " + std::to_string(skill->getStatByID(Stat::ManaCost)->getFinalValue());

	// action
	std::string activeDes = "Deals " + Common::formatFloat(valP) + "% + "
		+ Common::formatFloat(valNumber) + " " + Convert::ElementTypeToString(skill->getSkillPower()->getElemType()) + " damage.";

	activeDes = "Description: " + activeDes;
	std::string description = name + "\n" + location + "\n" + cooldown + "\n" + manaCost + "\n" + activeDes;

	_skillDetails->setString(description);
}
