#ifndef __LOCATION_INFO_H_BTN__
#define __LOCATION_INFO_H_BTN__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ChapterInfo.h"

USING_NS_CC;

namespace MyGame
{
	class LocationInfoBtn : public ui::Button
	{
	public:
		static LocationInfoBtn* create(ChapterInfo* chapterInfo);
	private:
		bool init(ChapterInfo* chapterInfo);
	private:
		ChapterInfo* _chapterInfo;
		std::string _pin, _pinCompleted, _pinUnopened;
	};
}

#endif // !__LOCATION_INFO_H_BTN__
