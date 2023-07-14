#include "Character.h"
#include "Input/Input.h"
#include "Character/State/CharacterStateMachine.h"
#include "Character/State/CharacterIdleState.h"
#include "Character/State/CharacterMoveState.h"
#include "Character/State/CharacterAttackState.h"
#include "Character/State/CharacterPrepareDash.h"
#include "Character/State/CharacterDashState.h"
#include "Character/State/CharacterDieState.h"
#include "Character/State/CharacterSpawnState.h"
#include "ui/FloatingNumber.h"
#include "Bitmask.h"
#include "ObjectTag.h"
#include "Skill/PassiveSkill.h"
#include "GameData/WeaponData.h"
#include "Input/PlayerInput.h"
#include "ui/Effect.h"
#include "Skill/Skill.h"
#include "GameData/SkillData.h"
#include "GameData/PlayerData.h"

bool MyGame::Character::init()
{
	if (!Entity::init()) {
		log("init character failed!");
	}
	this->initAnimation();
	this->setTag(ObjectTag::Player);
	_portrait = Sprite::create(_portraitFileName);
	this->initBody();

	// Character Attack
	_characterAttack = new CharacterAttack(this);
	_characterAttack->init();

	// State Machine
	_stateMachine = new CharacterStateMachine();
	auto charSpawn = new CharacterSpawnState();
	auto charIdle = new CharacterIdleState();
	auto charMove = new CharacterMoveState();
	auto charAttack = new CharacterAttackState();
	auto prepareDash = new CharacterPrepareDash();
	auto dash = new CharacterDashState();
	auto die = new CharacterDieState();
	_stateMachine->init(this, "spawn", charSpawn);

	_stateMachine->addState("idle", charIdle);
	_stateMachine->addState("run", charMove);
	_stateMachine->addState("attack", charAttack);
	_stateMachine->addState("prepare-dash", prepareDash);
	_stateMachine->addState("dash", dash);
	_stateMachine->addState("die", die);
	_entityHealth->reborn();

	loadSkill();

	// addChild
	this->addChild(_sprite, 1);
	this->addChild(_stateMachine);
	this->addChild(_characterAttack);

	return true;
}

bool MyGame::Character::loadSkill()
{
	auto pData = GameData::PlayerData();
	auto talen = pData.getTalen();
	talen->setOwner(this);
	talen->init();

	auto ulti = pData.getUltimate();
	ulti->setOwner(this);
	ulti->init();

	// insert skill
	if (_skillsEquipped == nullptr) _skillsEquipped = new std::map<ActiveSkillLocation, Skill*>();
	if (_skillsEquipped->find(ActiveSkillLocation::TalenSkill) == _skillsEquipped->end())
		_skillsEquipped->insert(std::pair<ActiveSkillLocation, Skill*>(ActiveSkillLocation::TalenSkill, nullptr));
	if (_skillsEquipped->find(ActiveSkillLocation::UltimateSkill) == _skillsEquipped->end())
		_skillsEquipped->insert(std::pair<ActiveSkillLocation, Skill*>(ActiveSkillLocation::UltimateSkill, nullptr));

	_skillsEquipped->at(ActiveSkillLocation::TalenSkill) = talen;
	_skillsEquipped->at(ActiveSkillLocation::UltimateSkill) = ulti;

	this->addChild(talen);
	this->addChild(ulti);
	return true;
}

void MyGame::Character::takeDamage(DamageMessage* data)
{
	_entityHealth->takeDamage(data);
	FloatingNumber::getIns()->showDamage(_position, data);
	if (this->getHealth()->isDead())
	{
		this->die();
	}
}

void MyGame::Character::addKnowNPC(std::string name)
{
	_knowNPCs.push_back(name);
}

bool MyGame::Character::checkKnowNPC(std::string name)
{
	auto result = std::find(_knowNPCs.begin(), _knowNPCs.end(), name);
	if (result == _knowNPCs.end())
		return false;
	return true;
}

void MyGame::Character::equipAbility(ActiveSkill* ability)
{
	if (ability == nullptr)
	{
		log("Ability is null");
		return;
	}

	if (_abilitiesEquipped == nullptr)
	{
		_abilitiesEquipped = new std::map<ActiveSkillLocation, ActiveSkill*>();
	}


	this->addChild(ability);
	auto val = std::pair<ActiveSkillLocation, ActiveSkill*>(ability->getEquipLocation(), ability);
	_abilitiesEquipped->insert(val);
}

void MyGame::Character::unequipAbility(ActiveSkillLocation location)
{
	if (_abilitiesEquipped == nullptr) return;

	if (_abilitiesEquipped->find(location) == _abilitiesEquipped->end()) return;

	_abilitiesEquipped->at(location)->removeFromParent();
	_abilitiesEquipped->erase(location);
}

ActiveSkill* MyGame::Character::getAbilityEquiplocation(ActiveSkillLocation location)
{
	if (_abilitiesEquipped->find(location) == _abilitiesEquipped->end()) return nullptr;
	return _abilitiesEquipped->at(location);
}

Skill* MyGame::Character::getSkillEquiplocation(ActiveSkillLocation location)
{
	if (_skillsEquipped->find(location) == _skillsEquipped->end()) return nullptr;
	return _skillsEquipped->at(location);
}

std::string MyGame::Character::equipWeap(MagicBook* weap)
{
	if (this->_magicBook != nullptr)
	{
		BaseStat* attackStat = this->getEntityStatByID(Stat::ATK);
		int baseVal = attackStat->getBaseValue();
		attackStat->setBaseValue(baseVal - _magicBook->getBnsATK());

		auto statTarget = this->getEntityStatByID(_magicBook->getStatBonus()->getStatBns().getID());
		statTarget->removeBonus(_magicBook->getStatBonus());
		_magicBook->setIsEquip(false);
		_magicBook->destroyProjectile();
	}

	_magicBook = weap;
	_magicBook->setIsEquip(true);
	_magicBook->initProjectile();
	BaseStat* attackStat = this->getEntityStatByID(Stat::ATK);
	int baseVal = attackStat->getBaseValue();
	attackStat->setBaseValue(baseVal + _magicBook->getBnsATK());

	this->getEntityStatByID(_magicBook->getStatBonus()->getStatBns().getID())->addBonus(_magicBook->getStatBonus());

	if (_characterAttack != nullptr)
		_characterAttack->init();
	return "";
}

int MyGame::Character::getCurrentStateID()
{
	return _stateMachine->getCurrentState()->getIDState();
}

bool MyGame::Character::initAnimation()
{
	std::string path, pathPlist, pathPNG, plist = ".plist", imgFile = ".png";

	path = "FHD/Entity/";
	path += _spriteFileName + "-";

	std::vector<std::string> aniDefault;
	aniDefault.push_back("idle");
	aniDefault.push_back("run");
	aniDefault.push_back("attack");
	aniDefault.push_back("evade");
	aniDefault.push_back("shot");
	aniDefault.push_back("dash");
	aniDefault.push_back("spawn");
	aniDefault.push_back("prepare-dash");
	aniDefault.push_back("die");
	auto spriteCache = SpriteFrameCache::getInstance();
	auto aniCache = AnimationCache::getInstance();


	for (std::string aniName : aniDefault)
	{
		std::string animationStr = _spriteFileName + "-" + aniName;
		spriteCache->addSpriteFramesWithFile(path + aniName + plist, path + aniName + imgFile);
		Animation* animation = Effect::createAnimation(animationStr).first;
		animation->retain();
		aniCache->addAnimation(animation, animationStr);
	}
	_sprite = Sprite::createWithSpriteFrame(aniCache->getAnimation(_spriteFileName + "-" + aniDefault.at(0))->getFrames().front()->getSpriteFrame());
	_sprite->retain();

	return true;
}

void MyGame::Character::die()
{
	_stateMachine->setState("die");
}

void MyGame::Character::update(float dt)
{
	Entity::update(dt);
}

bool MyGame::Character::initBody()
{
	PhysicsBody* body;
	PhysicsMaterial physicsMaterial = PhysicsMaterial(1, 0, 1);
	body = PhysicsBody::createBox(this->_eneitySize, physicsMaterial);
	body->setContactTestBitmask(Bitmask::BitmaskContactTest::Player);
	body->setCollisionBitmask(Bitmask::BitmaskCollision::Player);
	body->setCategoryBitmask(Bitmask::BitmaskCategory::Player);
	body->setRotationEnable(false);
	this->setPhysicsBody(body);
	return true;
}
