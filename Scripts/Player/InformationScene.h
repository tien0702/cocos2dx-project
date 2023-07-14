#ifndef __INFORMATION_SCENE_H__
#define __INFORMATION_SCENE_H__

#include "cocos2d.h"
#include "Player/AttributeLayer.h"
#include "Player/OptionLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

namespace MyGame
{
	enum class LayerName
	{
		AttributeLayer,
		Option_Layer,
		AllLayer
	};

	class InformationScene : public Scene
	{
	public:
		virtual bool init();
		CREATE_FUNC(InformationScene);
	protected:
		static const int MarginSide = 10;
		static const int LayerTag = 1;
		Size _sizeOfInforLayer;
		Vec2 _posOfInforLayer;

		std::string _backgroundPath;
		std::string _backgroundButtonPath;
		std::string _homeIconPath;

		IInforLayer* _layers[(int)LayerName::AllLayer];
		ui::Button* _buttons[(int)LayerName::AllLayer];
		LayerName _currentIndex = LayerName::AttributeLayer;
		TTFConfig _font;
	private:
		bool initLayerInfor(IInforLayer* layer, LayerName indexLayer);
		bool createButtons();
		void changeLayer(LayerName indexLayer);
		void backToMainScene();
	};
}

#endif // !__INFORMATION_SCENE_H__
