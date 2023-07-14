#include "SkillEquipRenderer.h"
#include "GameConfig.h"

MyGame::SkillEquipRenderer* MyGame::SkillEquipRenderer::create(Skill* s1, Skill* s2)
{
	auto layer = new (std::nothrow) SkillEquipRenderer();
	if (layer && layer->init(s1, s2))
	{
		layer->autorelease();
		return layer;
	}
	return nullptr;
}

bool MyGame::SkillEquipRenderer::init(Skill* s1, Skill* s2)
{
	_s1 = s1;
	_s2 = s2;
	if (!Layer::init())
	{
		return false;
	}
	loadComponent();
	loadPosition();

	this->addChild(_background);
	this->addChild(_s1Sprite);
	this->addChild(_s2Sprite);
	return true;
}

void MyGame::SkillEquipRenderer::setS1(Skill* s1)
{
	_s1 = s1;
	_s1Sprite->initWithFile("FHD/Icon/" + _s1->getInfo()->getIconName() + ".png");
}

void MyGame::SkillEquipRenderer::setS2(Skill* s2)
{
	_s2 = s2;
	_s2Sprite->initWithFile("FHD/Icon/" + _s2->getInfo()->getIconName() + ".png");
}

bool MyGame::SkillEquipRenderer::loadComponent()
{
	_s1Sprite = Sprite::create("FHD/Icon/" + _s1->getInfo()->getIconName() + ".png");
	_s2Sprite = Sprite::create("FHD/Icon/" + _s2->getInfo()->getIconName() + ".png");

	auto font = GameConfig::getIns()->getFont();
	_talenLb = Label::createWithTTF(font, "Talen");
	_ultiLb = Label::createWithTTF(font, "Ultimate");

	_talenLb->setPosition(_s1Sprite->getContentSize() / 2);
	_ultiLb->setPosition(_s2Sprite->getContentSize() / 2);

	_talenLb->setScale(0.4f);
	_ultiLb->setScale(0.4f);

	_s1Sprite->addChild(_talenLb, 10);
	_s2Sprite->addChild(_ultiLb, 10);

	_background = DrawNode::create();
	return true;
}

bool MyGame::SkillEquipRenderer::loadPosition()
{
	int margin = 10, border = 10;
	_s1Sprite->setPosition(Vec2(0 - _s1Sprite->getContentSize().width / 2 - margin, 0));
	_s2Sprite->setPosition(Vec2(0 + _s2Sprite->getContentSize().width / 2 + margin, 0));
	Size bgSize;
	bgSize.width = _s1Sprite->getContentSize().width + _s2Sprite->getContentSize().width + border * 4;
	bgSize.height = _s1Sprite->getContentSize().height + 2 * border;

	_background->drawRect(Vec2::ZERO, bgSize, Color4F::WHITE);
	_background->drawSolidRect(Vec2::ZERO, bgSize, Color4F(0, 0, 0, 0.7f));
	_background->setPosition(bgSize / (-2));

	// equipped str

	auto equippedStr = Label::createWithTTF(GameConfig::getIns()->getFont(), "Equipped");
	equippedStr->setPosition(Vec2(0, bgSize.height / 2 + equippedStr->getContentSize().height / 2));
	equippedStr->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	equippedStr->setAlignment(TextHAlignment::CENTER);
	this->addChild(equippedStr);
	return true;
}
