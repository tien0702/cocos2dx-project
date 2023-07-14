#ifndef __OPTION_LAYERR_H__
#define __OPTION_LAYERR_H__

#include "Player/IInforLayer.h"

namespace MyGame
{
	class OptionLayer : public IInforLayer
	{
	public:
		virtual bool init();
	private:
		CC_SYNTHESIZE(short, _BGMusic, BGMusic);	
		CC_SYNTHESIZE(short, _SFX, SFX);
		CC_SYNTHESIZE(bool, _isFixedJoystick, FixedJoystick);

		CC_SYNTHESIZE(std::string, _switchOffPath, SwitchOffPath);
		CC_SYNTHESIZE(std::string, _switchOnPath, SwitchOnPath);
		CC_SYNTHESIZE(std::string, _thumbPath, ThumbPath);
		CC_SYNTHESIZE(std::string, _trackPath, SlidePath);
		CC_SYNTHESIZE(std::string, _progressBarPath, ProgressBarPath);
		
		TTFConfig _font;
	private:
		bool loadDefaultProperties();

		Sprite* createLine(Node* left, Node* right);
	};
}

#endif // !__OPTION_LAYERR_H__
