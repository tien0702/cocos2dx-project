#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class LoadingScene : public Scene
{
public:
	virtual bool init();

	virtual void startLoadingChapterMap(int mapID);

	void updateProgressBar(float progress);
	CREATE_FUNC(LoadingScene)
public:
	float _processValue = 0.0f;
	bool _completeProcess = false;
	Scene* _scene;
	std::string _bgFolderPath = "Background/BGLoading/1.jpg";
	std::string _trackPath = "Background/load-track.png";
	std::string _processbarPath = "Background/load-progress.png";
protected:

	TTFConfig _font;
	ui::Slider* _processBar;
	Label* _processValueLb;

	float _timeLoading = 2.5f;
	float _elapsedTime;

	bool loadProperties();
	virtual void update(float dt);

	void updateProcess();
	void updatePercent();
	void updateValueLabel();
	void completedLoading();
};

#endif // !__LOADING_SCENE_H__
