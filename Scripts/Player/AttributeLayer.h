#ifndef __ATTRIBUTE_LAYER_H__
#define __ATTRIBUTE_LAYER_H__

#include "Player/IInforLayer.h"
#include "Character/Character.h"

namespace MyGame
{
	class AttributeLayer : public IInforLayer
	{
	public:
		virtual bool init();
		CREATE_FUNC(AttributeLayer);
	protected:
	};
}

#endif // !__ATTRIBUTE_LAYER_H__
