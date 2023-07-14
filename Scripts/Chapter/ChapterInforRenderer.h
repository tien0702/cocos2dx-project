#ifndef __CHAPTER_INFO_RENDERER_H__
#define __CHAPTER_INFO_RENDERER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Chapter/ChapterInfo.h"

USING_NS_CC;

namespace MyGame
{
	class ChapterInfoRenderer : public Layer
	{
	public:
		virtual bool init();
		void show(ChapterInfo* chapterInfo, Node* parent);
		void turnOff();

	protected:
		Label* _chapterName, * _chapterWave, *_chapterState;
		ChapterInfo* _chapterInfo;
		TTFConfig _font;
		Sprite* _boxInfo;
		LayerColor* _darkLayer;

		ui::Button* _hideBtn;
	protected:
		virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

		bool isTouchInsideEmptySpace(Touch* touch);
		bool loadComponent();
		bool loadProperies();
	};
}

#endif // !__CHAPTER_INFO_RENDERER_H__
