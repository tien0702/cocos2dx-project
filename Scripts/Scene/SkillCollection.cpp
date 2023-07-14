#include "SkillCollection.h"
#include "UI/Skill/SkillListRenderer.h"
#include "UI/Skill/SkillDetailRenderer.h"
#include "UI/Skill/SkillEquipRenderer.h"
#include "GameData/SkillData.h"
#include "GameConfig.h"
#include "Scaler.h"
#include "AudioManager/AudioManager.h"
#include "GameData/PlayerData.h"

bool MyGame::SkillCollection::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// background
	auto background = Sprite::create("FHD/Background/bgr2.png");
	background->setPosition(Director::getInstance()->getOpenGLView()->getFrameSize() / 2);
	this->addChild(background);

	// equip renderer
	GameData::PlayerData pData = GameData::PlayerData();
	auto s1 = pData.getTalen();
	auto s2 = pData.getUltimate();
	auto equipRenderer = SkillEquipRenderer::create(s1, s2);

	// detail renderer
	auto detailLayer = SkillDetailRenderer::create(Size(900, 500));


	// list
	auto skills = getSkills();
	auto skillList = SkillListRenderer::create(skills, detailLayer, equipRenderer);


	skillList->setPosition(100, 100);
	detailLayer->setPosition(300, 100);
	equipRenderer->setPosition(Vec2(1400, 500));

	// back bt

	auto backBtn = ui::Button::create("FHD/Button/button-world-map.png");

	auto backLb = Label::createWithTTF(GameConfig::getIns()->getFont(), "Back");
	backLb->setPosition(backBtn->getContentSize() / 2);
	Scaler::scaleNodeToFit(backLb, backBtn, 10);
	backBtn->addChild(backLb);
	backBtn->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			AudioManager::getIns()->playeButtonEffect();
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			Director::getInstance()->popScene();
		}
		break;
		default:
			break;
		}
		});

	backBtn->setPosition(Vec2(GameConfig::getIns()->getFixedVisible().getMaxX() - backBtn->getContentSize().width / 2 - 10, 
		GameConfig::getIns()->getFixedVisible().getMaxY() - backBtn->getContentSize().height / 2 - 10));

	this->addChild(backBtn);
	this->addChild(equipRenderer);
	this->addChild(skillList);
	this->addChild(detailLayer);

	return true;
}

std::vector<MyGame::Skill*>* MyGame::SkillCollection::getSkills()
{
	auto skillData = GameData::SkillData();
	auto skills = skillData.getPlayerSkills();
	return skills;
}
