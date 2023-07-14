#include "CharacterMoveState.h"
#include "Character/Character.h"
#include "Map/GameMap.h"
#include "Input/Input.h"
#include "Input/PlayerInput.h"
#include "ObjectTag.h"
#include "Settings/Setting.h"
#include "AudioManager/AudioManager.h"

int idSound;

void MyGame::CharacterMoveState::enter(Character* owner)
{
	this->_owner = owner;
	this->initAnimation();
	this->loadProperties();
	idSound = AudioEngine::play2d("Audio/footstep.mp3", true, Setting::_SFX_Volume);
}

std::string MyGame::CharacterMoveState::updateState(float dt)
{
	Vec2 dirInput = Input::getIns()->getDirection(false);
	if (dirInput == Vec2::ZERO) return "idle";

	if (PlayerInput::getIns()->getInput(InputID::BT_Skill_Dash)) return "prepare-dash";
	this->updateFlipX(dirInput);
	this->move(dt);
	return "run";
}

void MyGame::CharacterMoveState::exit()
{
	AudioEngine::stop(idSound);
	_owner->getPhysicsBody()->setVelocity(Vec2::ZERO);
}

bool MyGame::CharacterMoveState::initAnimation()
{
	std::string spriteFileName = _owner->getSpriteFileName() + "-" + "run";
	Animation* animation = AnimationCache::getInstance()->getAnimation(spriteFileName);
	_owner->setAnimation(animation);
	return true;
}

bool MyGame::CharacterMoveState::loadProperties()
{
	Node* runingScene = Director::getInstance()->getRunningScene();
	Node* node = runingScene->getChildByTag(ObjectTag::ChapterMap);
	Node* map = node->getChildByTag(ObjectTag::Map);
	_map = dynamic_cast<GameMap*>(map);
	_moveSpeed = _owner->getEntityStatByID(Stat::MoveSpeed);
	return true;
}

void MyGame::CharacterMoveState::handleMoveMeta(int metaType, Vec2 vel)
{
	switch (metaType)
	{
	case MetaType::insideRed:
		_owner->getPhysicsBody()->setVelocity(Vec2::ZERO);
		break;
	case MetaType::insideGreen:
		_owner->getPhysicsBody()->setVelocity(vel);
		break;
	default:
		_owner->getPhysicsBody()->setVelocity(vel);
		break;
	}
}

void MyGame::CharacterMoveState::updateFlipX(Vec2 dir)
{
	if (dir.x == 0) return;
	_owner->getSprite()->setFlippedX(dir.x > 0);
}

Vec2 MyGame::CharacterMoveState::calculateVelocity()
{
	Vec2 dirInput = Input::getIns()->getDirection(true);
	Vec2 curVel, maxVel, tarVel;
	int speed = _moveSpeed->getFinalValue() / _scaleFactor;
	curVel = _owner->getPhysicsBody()->getVelocity();
	maxVel = dirInput * speed;
	tarVel.x = MathUtil::lerp(curVel.x, maxVel.x, _accelRate);
	tarVel.y = MathUtil::lerp(curVel.y, maxVel.y, _accelRate);

	return tarVel;
}

Vec2 MyGame::CharacterMoveState::calculateNextPos(float time)
{
	Vec2 dirInput = Input::getIns()->getDirection(true);
	int speed = _moveSpeed->getFinalValue();
	Vec2 nextPos = getGroundPosOwner() + dirInput * speed * time;
	return nextPos;
}

Vec2 MyGame::CharacterMoveState::getGroundPosOwner() const
{
	return Vec2(_owner->getPosition().x, 
		_owner->getPosition().y - (_owner->getEntitySize().height / 2.0f));
}

Vec2 MyGame::CharacterMoveState::getHeadPosOwner() const
{
	return Vec2(_owner->getPosition().x,
		_owner->getPosition().y + (_owner->getEntitySize().height / 2.0f));
}

void MyGame::CharacterMoveState::move(float dt)
{
	Vec2 tarVel = this->calculateVelocity();
	Vec2 nextPoint = this->calculateNextPos(dt);
	int metaType = _map->getMetaAtPos(nextPoint);
	handleMoveMeta(metaType, tarVel);
}

bool MyGame::CharacterMoveState::canMove()
{
	return false;
}

bool MyGame::CharacterMoveState::checkPrepareDash()
{
	if (!PlayerInput::getIns()->getInput(InputID::BT_Skill_Dash)) return false;
	bool result = _owner->getAbilityEquiplocation(ActiveSkillLocation::DashSkill)->canUse();
	return result;
}