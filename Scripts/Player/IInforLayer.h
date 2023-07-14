#ifndef __I_INFOR_LAYER_H__
#define __I_INFOR_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

namespace MyGame
{
	class IInforLayer : public Layer
	{
	public:
		virtual bool init();
	protected:
		CC_SYNTHESIZE(Size, _sizeLayer, SizeLayer);
		CC_SYNTHESIZE(std::string, _iconPath, IconPath);
		CC_SYNTHESIZE(std::string, _nameLayer, NameLayer);
	};
}

#endif // !__I_INFOR_LAYER_H__
