#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Character/Character.h"
#include "Equipment/Weapon/MagicBook.h"
#include "GameReward/Coin.h"
namespace MyGame
{
	class Player
	{
	public:
		static Player* getIns();
		void releaseCharacter();
		Character* getCharacter();
		MagicBook* getWeaponEquiped();
		void addCoin(Coin* coin);
		Coin* getCoin(CoinType type);
	private:
		Player();
		static Player* _instance;
		Character* _character;
	};
}

#endif // !__PLAYER_H__
