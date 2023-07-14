#ifndef __SERPENT_SCREW_H__
#define __SERPENT_SCREW_H__

#include "ActiveSkill.h"

namespace MyGame
{
	class SerpentScew : public ActiveSkill
	{
	public:
		virtual bool init();
		SerpentScew();
	public:
		virtual bool use();
		virtual bool canUse();
		virtual bool isReady();
	protected:
		virtual void update(float dt);
	};
}

#endif // !__SERPENT_SCREW_H__
