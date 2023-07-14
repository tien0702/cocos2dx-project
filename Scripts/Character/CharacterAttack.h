#ifndef __CHARACTER_ATTACK_H__
#define __CHARACTER_ATTACK_H__

#include "cocos2d.h"

USING_NS_CC;

namespace MyGame
{
	class Character;
	class MagicBook;
	class BaseStat;
	class CharacterAttack : public Node
	{
	public:
		virtual bool init();
		CharacterAttack(Character* character);
		bool loadProperties();
	private:
		CC_SYNTHESIZE(Character*, _character, MainCharacter);
		CC_SYNTHESIZE(MagicBook*, _weapon, Weapon);
		CC_SYNTHESIZE(DrawNode*, _rangeVisual, RangeVisual);
		CC_SYNTHESIZE(BaseStat*, _attackSpeed, AttackSpeed);
		float _elapsedTime;
		float _range;
	private:
		void update(float dt);
		void attack(Node* target);
		bool onCooldown();
		bool stateAbleAttack();
		Node* findTarget();
	};
}

#endif // !__CHARACTER_ATTACK_H__
