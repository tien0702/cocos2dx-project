#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Entity/Entity.h"
#include "Inventory/Item/IItemInventory.h"
#include "Equipment/Weapon/MagicBook.h"
#include "CharacterAttack.h"
#include "Ability/ActiveSkill.h"
#include "Character/CharacterSubject.h"
#include "Skill/Skill.h"

USING_NS_CC;

namespace MyGame
{
	class CharacterStateMachine;
	class Character : public Entity, public CharacterSubject
	{
	public:
		virtual bool init();
		CREATE_FUNC(Character);
		CharacterStateMachine* getStateMachine() { return this->_stateMachine; }
		virtual void takeDamage(DamageMessage* data);
		void addKnowNPC(std::string name);
		bool checkKnowNPC(std::string name);

		void equipAbility(ActiveSkill* ability);
		void unequipAbility(ActiveSkillLocation location);

		ActiveSkill* getAbilityEquiplocation(ActiveSkillLocation location);
		Skill* getSkillEquiplocation(ActiveSkillLocation location);
		MagicBook* getWeapon() { return _magicBook; }
		std::string equipWeap(MagicBook* weap);
	public: // Get - Set
		virtual int getCurrentStateID();
		virtual bool initAnimation();
		virtual bool loadSkill();
		virtual void die();
		virtual void update(float dt);
		bool initBody();
	protected:
		CharacterAttack* _characterAttack;
		CharacterStateMachine* _stateMachine;
		MagicBook* _magicBook;
		std::map<ActiveSkillLocation, ActiveSkill*>* _abilitiesEquipped;
		std::map<ActiveSkillLocation, Skill*>* _skillsEquipped;
		std::list<std::string> _knowNPCs;
	};
}

#endif // !__CHARACTER_H__
