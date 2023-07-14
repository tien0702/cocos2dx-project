#ifndef __STAT_RENDERER_H__
#define __STAT_RENDERER_H__

#include "Player/Player.h"

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

namespace MyGame
{
	class StatRenderer : public Sprite
	{
	public:
		bool init();
		void renderer();
	private:
		bool loadProperties();
		bool loadScrollView();

		Node* getLabelState(string statName, string statValue, int maxWidth, bool isEvenNumber);
		ui::ScrollView* createScrollView(Size size, std::vector<Node*> nodes);
		std::string getStatValue(BaseStat* baseStat);
	private:
		CC_SYNTHESIZE(Size, _windowSize, WindowSize);
		ui::ScrollView* _windowScrollview;
		TTFConfig _font;
	};
}

#endif // !__STAT_RENDERER_H__
