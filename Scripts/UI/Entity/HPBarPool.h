#ifndef __HP_BAR_POOL_H__
#define __HP_BAR_POOL_H__

#include "UI/Entity/HPBarVisual.h"


namespace MyGame
{
	class HPBarPool
	{
	public:
		static HPBarPool* getIns();
		HPBarVisual* get();
		void add(HPBarVisual* val);
	private:
		static HPBarPool* _instance;
		std::queue<HPBarVisual*> _hpBars;
	};
}


#endif // !__HP_BAR_POOL_H__
