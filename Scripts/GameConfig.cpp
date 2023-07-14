#include "GameConfig.h"

GameConfig* GameConfig::_instance;

GameConfig::GameConfig()
{
	_font.fontFilePath = "fonts/Minecraft.ttf";
	_font.fontSize = 30;
	_font.glyphs = GlyphCollection::DYNAMIC;
	_font.outlineSize = 1;
	_font.customGlyphs = nullptr;
	_font.distanceFieldEnabled = false;

	// 
	Size frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	float displayWidth = (frameSize.height / 9.0f) * 18.0f;

	if (displayWidth < frameSize.width)
	{
		_fixedVisible.size = Size(displayWidth, frameSize.height);
		_fixedVisible.origin = Vec2((frameSize.width - displayWidth) / 2, 0);
	}
	else
	{
		_fixedVisible.size = Size(frameSize);
		_fixedVisible.origin = Vec2(0, 0);
	}
}

GameConfig* GameConfig::getIns()
{
	if (_instance == NULL)
	{
		_instance = new GameConfig();
	}
	return _instance;
}

TTFConfig GameConfig::getFont()
{
	return _font;
}

float GameConfig::getScaler()
{
	float h = Director::getInstance()->getOpenGLView()->getFrameSize().height;
	return defaultSize.height / h;
}
