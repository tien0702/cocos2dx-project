#ifndef __REWARD_RENDERER_H__
#define __REWARD_RENDERER_H__

#include "cocos2d.h"
#include "GameReward/Reward.h"

USING_NS_CC;

namespace MyGame
{
	class RewardRenderer : public Layer
	{
	public:
		virtual bool init(Reward* reward);
		void showing();
	private:
		bool _isShowing = false;
		Reward* _reward;
	};
}

#endif // !__REWARD_RENDERER_H__
