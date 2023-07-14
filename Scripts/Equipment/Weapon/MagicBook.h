#ifndef __MAGIC_BOOK_H__
#define __MAGIC_BOOK_H__

#include "Equipment/Weapon/IWeapon.h"
#include "Equipment/IEquipment.h"
#include "Inventory/Item/IItemInventory.h"
#include "Projectile/Projectile.h"
#include "Skill/PassiveSkill.h"

namespace MyGame
{
	class MagicBook : public IItemInventory, public IWeapon, public IEquipment, public Sprite
	{
	public:
		virtual bool init();
		virtual void initProjectile();
		virtual void destroyProjectile();
		virtual void addStateAlloweds(int idState);
		virtual void removeStateAlloweds(int idState);
	protected:
		CC_SYNTHESIZE(int, _projectileID, ProjectileID);
		CC_SYNTHESIZE(int, _manaNeeded, ManaNeeded);
		CC_SYNTHESIZE(std::list<int>, _stateAlloweds, StateAlloweds);
		CC_SYNTHESIZE(PassiveSkill*, _skillWeap, SkillWeap);

		CC_SYNTHESIZE(Entity*, _owner, Owner);
		DrawNode* _rangeVisual;
	};
}

#endif // !__MAGIC_BOOK_H__
