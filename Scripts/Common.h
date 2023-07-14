#ifndef __COMMON_H__
#define __COMMON_H__

#define CONVERT_TO_PERCENT(val) val * 0.001f

#include "cocos2d.h"

using namespace std;

USING_NS_CC;

namespace MyGame
{
	class BaseStat;
	class Bonus;
	class Common
	{
	public:
		static std::vector<int> splitNumbers(const std::string& str);
		static vector<Size> getSizeFromNodes(vector<Node*> nodes);
		static std::string formatFloat(float val);
		static std::vector<cocos2d::Vec2> getPositionXCenter(const vector<Size>& sizeItems, float width, float distance);
		static std::vector<cocos2d::Vec2> getPositionYCenter(const std::vector<cocos2d::Size>& sizeItems, float height, float distance);
		static std::vector<cocos2d::Vec2> getPositionCenter(const std::vector<Size>& sizeItems, const Size& area, const Size& distance);
		static std::string convertValueBonus(Bonus* _bonus);
		static Label* getNodeWithBackground(std::string content, Color4F& bgColor);
		static Label* getLabelWithBackground(std::string content, Size bgSize, Color4F bgColor);
		static Size getFrameSize();
		static std::string justifyString(std::string str1, std::string str2, int maxW);
	};
}

#endif // !__COMMON_H__
