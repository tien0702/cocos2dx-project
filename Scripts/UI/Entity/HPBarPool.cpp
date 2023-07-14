#include "HPBarPool.h"

MyGame::HPBarPool* MyGame::HPBarPool::_instance;

MyGame::HPBarPool* MyGame::HPBarPool::getIns()
{
	if (_instance == nullptr)
		_instance = new HPBarPool();
	return _instance;
}

MyGame::HPBarVisual* MyGame::HPBarPool::get()
{
	HPBarVisual* hpBar = nullptr;

	if (_hpBars.empty())
	{
		hpBar = new HPBarVisual();
		hpBar->init();
	}
	else
	{
		hpBar = _hpBars.front();
		_hpBars.pop();
	}

	return hpBar;
}

void MyGame::HPBarPool::add(HPBarVisual* val)
{
	_hpBars.push(val);
}
