#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "BaseStat.h"
#include "Entity/EntityHealth.h"
#include "Entity/EntityMana.h"
#include "Entity/EntitySubject.h"
#include "Entity/BonusLevel.h"
#include "Inventory/Item/IItemInventory.h"

namespace MyGame
{
	enum EntityType
	{
		UnknowType,
		CharacterType,
		NPCType,
		EnemyType
	};

	class Entity : public Sprite, public EntitySubject
	{
	public:
		static const int AnimationTag = 1;
	public:
		virtual bool init();
	public:
		virtual void takeDamage(DamageMessage* data);

		virtual void addStat(BaseStat* newStat);
		virtual void addBonus(Bonus* bns);
		virtual void removeBonus(Bonus* bns);

		virtual std::string equipItem(IItemInventory* item);
	public:
		virtual void spawn();
	public: // Get - Set
		virtual void setAnimation(std::string animationName);
		virtual void setAnimation(std::string animationName, float time);
		virtual void setAnimation(Animation* animation);
		virtual void setStats(std::list<BaseStat*>* statas);
		virtual void setStates(std::vector<std::string> states);

		virtual int getCurrentStateID();
		virtual Sprite* getSprite() { return this->_sprite; }
		BaseStat* getEntityStatByID(int id);
		std::list<BaseStat*>* getStats() { return this->_stats; }
	protected:
		virtual bool loadProperties();
		virtual bool initAnimation();
		virtual void update(float dt);
	protected:
		// Entity info
		CC_SYNTHESIZE(int, _id, ID);
		CC_SYNTHESIZE(int, _level, Level);
		CC_SYNTHESIZE(int, _weight, Weight);
		CC_SYNTHESIZE(long, _exps, Exp);
		CC_SYNTHESIZE(Size, _eneitySize, EntitySize);
		CC_SYNTHESIZE(std::string, _entityName, EntityName);
		CC_SYNTHESIZE(EntityType, _type, Type);

		// Health and stats
		CC_SYNTHESIZE(EntityHealth*, _entityHealth, Health);
		CC_SYNTHESIZE(EntityMana*, _entityMana, Mana);
		std::list<BaseStat*>* _stats;
		std::vector <std::string> _states;
		std::map<int, BaseStat*> _entityStats;

		// sprite
		CC_SYNTHESIZE(std::string, _portraitFileName, PortraitFileName);
		CC_SYNTHESIZE(std::string, _spriteFileName, SpriteFileName);
	protected:
		Sprite* _sprite;
		Sprite* _portrait;
	};
}

#endif // !__ENTITY_H__
