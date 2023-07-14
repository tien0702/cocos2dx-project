#ifndef __CHARACTER_OBSERVER_H__
#define __CHARACTER_OBSERVER_H__

namespace MyGame
{
	class CharacterObserver
	{
		class ObserverType
		{
		public:
			static const int ChangeWeapon = 1;
			static const int UseUltimate = 2;
			static const int UseTalen = 3;
			static const int UseDash = 4;
			static const int UseNormalAttack = 5;
		};

	public:
		virtual void observerUpdateByID(int idType);
	public:
		virtual void onChangeWeapon() = 0;
		virtual void onUseUltimate() = 0;
		virtual void onUseTalen() = 0;
		virtual void onUseDash() = 0;
		virtual void onUseNormalAttack() = 0;
	};
}

#endif // !__CHARACTER_OBSERVER_H__
