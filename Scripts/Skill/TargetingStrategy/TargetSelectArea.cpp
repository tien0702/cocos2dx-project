#include "TargetSelectArea.h"
#include "Skill/Skill.h"
#include "Entity/Entity.h"
#include "Skill/StateMachine/SkillStateMachine.h"
#include "Manager/GameManager.h"
#include "Entity/DetectEntity.h"

bool MyGame::TargetSelectArea::init()
{
	if (!Node::init()) return false;

	this->scheduleUpdate();
	return true;
}

void MyGame::TargetSelectArea::target(Skill* skill)
{
	_skill = skill;

	loadRangeVisual();
	loadAoERadius();

	// 
	_skill->getOwner()->addChild(_rangeVisual);
	_skill->getOwner()->addChild(_aoERadiusVisual);
	_skill->getStateMachine()->setState(SkillStateType::Targeting);

	// 
	setAtPositionEnemyNeares();
	this->scheduleUpdate();
	Director::getInstance()->getRunningScene()->addChild(this);
}

void MyGame::TargetSelectArea::activeSkill(Vec2 position)
{
	_skill->getActivation()->activate(_skill, position, 0, Vec2(0 ,0));
}

bool MyGame::TargetSelectArea::loadRangeVisual()
{
	float range = _skill->getStatByID(Stat::Range)->getFinalValue();
	_rangeVisual = DrawNode::create();
	_rangeVisual->drawCircle(Vec2::ZERO, range, 360.0f, 360, false, Color4F(0, 0, 0, 100));
	_rangeVisual->retain();
	_rangeVisual->setLineWidth(7);

	return true;
}

bool MyGame::TargetSelectArea::loadAoERadius()
{
	float area = _skill->getStatByID(Stat::AoERadius)->getFinalValue();
	_aoERadiusVisual = DrawNode::create();
	_aoERadiusVisual->drawCircle(Vec2::ZERO, area, 360.0f, 360, false, Color4F(47, 132, 234, 40));
	_aoERadiusVisual->drawCircle(Vec2::ZERO, 10, 360.0f, 360, false, Color4F(0, 0, 0, 140));
	_aoERadiusVisual->retain();
	_aoERadiusVisual->setLineWidth(6);
	return false;
}

void MyGame::TargetSelectArea::update(float dt)
{
	if (!checkInput())
	{
		activeSkill(calculatePosition());
		reset();
		_skill->getStateMachine()->setState(SkillStateType::Cooldown);
	}
	else
	{
		updateAoERadius(getDirectionInput());
	}
}

Vec2 MyGame::TargetSelectArea::getDirectionInput() const
{
	InputID id = _skill->getActivationButtonID();
	ButtonSkill* button = PlayerInput::getIns()->getInputSkill(id);
	return button->getDirection();
}

Vec2 MyGame::TargetSelectArea::calculatePosition() const
{
	Vec2 ownerPos = _skill->getOwner()->getParent()->convertToWorldSpace(_skill->getOwner()->getPosition());
	Vec2 areaPos = _aoERadiusVisual->getPosition();
	Vec2 position = ownerPos + areaPos;
	return position;
}

void MyGame::TargetSelectArea::setAtPositionEnemyNeares()
{
	float actionRange = _skill->getStatByID(Stat::Range)->getFinalValue();
	Node* enemy = DetectEntity::getNearestEnemy(_skill->getOwner(), actionRange);
	if (enemy != nullptr)
	{
		Vec2 position = _skill->getOwner()->convertToNodeSpace(enemy->getPosition());
		_aoERadiusVisual->setPosition(position);
	}
}

void MyGame::TargetSelectArea::updateAoERadius(Vec2 direction) const
{
	if (direction == Vec2::ZERO) return;
	float range = _skill->getStatByID(Stat::Range)->getFinalValue();
	Vec2 newPos = direction * range;
	_aoERadiusVisual->setPosition(newPos);
}

void MyGame::TargetSelectArea::reset()
{
	_rangeVisual->removeFromParent();
	_aoERadiusVisual->removeFromParent();
	this->removeFromParent();
	this->unscheduleUpdate();
}

bool MyGame::TargetSelectArea::initBody()
{
	return false;
}

bool MyGame::TargetSelectArea::onContactBegin(PhysicsContact& contact)
{
	return false;
}
