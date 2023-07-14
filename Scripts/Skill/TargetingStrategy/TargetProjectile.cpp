#include "TargetProjectile.h"
#include "Skill/Skill.h"
#include "Entity/Entity.h"
#include "Entity/DetectEntity.h"
#include "Character/Character.h"
#include "Skill/StateMachine/SkillStateMachine.h"
#include "ObjectTag.h"
#include "Entity/DetectEntity.h"
#include "Enemy/Enemy.h"
#include "UI/Effect.h"
#include "Bitmask.h"
#include "Manager/GameManager.h"

bool MyGame::TargetProjectile::init()
{
	if (!Node::init())
		return false;

	this->scheduleUpdate();
	return true;
}

void MyGame::TargetProjectile::target(Skill* skill)
{
	_skill = skill;

	// visual
	_directionVisual = DrawNode::create();
	_directionVisual->retain();

	float actionRange = _skill->getStatByID(Stat::MaximumProjectileRange)->getFinalValue();
	float range = _skill->getStatByID(Stat::AoEHeight)->getFinalValue();

	Color4F color = Color4F(0, 0, 0, 170);
	Color4F boderColor = Color4F(70, 70, 70, 170);

	// circle
	Vec2 center = Vec2(0, 0);
	float radius = _skill->getOwner()->getEntitySize().height / 2;
	float angle = 180.0f;
	unsigned int segments = 360;
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	//_directionVisual->drawSolidCircle(center, radius, angle, segments, scaleX, scaleY, color);

	// poligon
	drawDirection();
	_skill->getOwner()->addChild(_directionVisual);


	rotateToEnemyNeares();

	// 
	this->scheduleUpdate();
	Director::getInstance()->getRunningScene()->addChild(this);
}

void MyGame::TargetProjectile::activeSkill(Vec2 position)
{
	Vec2 direction = calculateDirection();
	_skill->getActivation()->activate(_skill, position, _directionVisual->getRotation(), direction);
}

void MyGame::TargetProjectile::update(float dt)
{
	if (!checkInput())
	{
		activeSkill(calculatePosition());
		reset();
		changeStateToCooldown();
	}
	else
	{
		updateDirectionVisual();
	}
}

void MyGame::TargetProjectile::updateDirectionVisual()
{
	Vec2 direction = getInputDirection();
	if (direction == Vec2::ZERO) return;
	float rotation = calculateRotation(direction);
	_directionVisual->setRotation(CC_RADIANS_TO_DEGREES(rotation));
}

void MyGame::TargetProjectile::reset()
{
	this->removeFromParent();
	_directionVisual->removeFromParent();
}

void MyGame::TargetProjectile::changeStateToCooldown()
{
	_skill->getStateMachine()->setState(SkillStateType::Cooldown);
}

Vec2 MyGame::TargetProjectile::getInputDirection()
{
	Vec2 direction;
	direction = PlayerInput::getIns()->getInputSkill(_skill->getActivationButtonID())->getDirection();
	return direction;
}

float MyGame::TargetProjectile::calculateRotation(Vec2 direction)
{
	float angle = Vec2::angle(Vec2(1, 0), direction);
	if (direction.y > 0)
		angle = -angle;
	return angle;
}

Vec2 MyGame::TargetProjectile::calculateDirection()
{
	Vec2 direction = Vec2(1, 0).forAngle(CC_DEGREES_TO_RADIANS(-_directionVisual->getRotation()));
	return direction;
}

Vec2 MyGame::TargetProjectile::calculatePosition()
{
	Vec2 ownerPos = _skill->getOwner()->getParent()->convertToWorldSpace(_skill->getOwner()->getPosition());
	Size ownerSize = _skill->getOwner()->getEntitySize();
	Vec2 normalize = ownerPos;
	normalize.normalize();

	Vec2 position = ownerPos + (calculateDirection() * ownerSize.width / 2);
	return position;
}

void MyGame::TargetProjectile::drawDirection()
{
	float actionRange = _skill->getStatByID(Stat::MaximumProjectileRange)->getFinalValue();
	float range = _skill->getStatByID(Stat::AoEHeight)->getFinalValue();

	Color4F color = Color4F(0, 0, 0, 170);
	Color4F boderColor = Color4F(70, 70, 70, 170);

	float offset = actionRange * 0.2f;

	offset = std::min(30.0f, offset);

	Vec2 vecs[] = {
		Vec2(offset, 0),
		Vec2(0, range / 2),
		Vec2(actionRange - offset, range / 2),
		Vec2(actionRange, 0),
		Vec2(actionRange - offset, -range / 2),
		Vec2(0, -range / 2) };

	_directionVisual->drawPolygon(vecs, 6, color, 2, boderColor);

	_directionVisual->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_directionVisual->setPosition(Vec2::ZERO);
}

void MyGame::TargetProjectile::rotateToEnemyNeares()
{
	float actionRange = _skill->getStatByID(Stat::MaximumProjectileRange)->getFinalValue();
	Node* enemy = DetectEntity::getNearestEnemy(_skill->getOwner(), actionRange);
	if (enemy != nullptr)
	{
		Vec2 direction = enemy->getPosition() - _skill->getOwner()->getPosition();
		float rotation = calculateRotation(direction);
		_directionVisual->setRotation(CC_RADIANS_TO_DEGREES(rotation));
	}
}
