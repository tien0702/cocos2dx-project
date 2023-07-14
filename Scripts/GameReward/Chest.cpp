#include "Chest.h"

bool MyGame::Chest::initWithClosedImage(std::string closedImagePath, std::string openImagepath, Node* targetOpen, BonusRenderer* bounce)
{
	if (!Sprite::initWithFile(closedImagePath))
	{
		return false;
	}

	_openImagePath = openImagepath;
	_openImage = Sprite::create(_openImagePath);
	_bounce = bounce;
	_targetOpen = targetOpen;
	_isOpen = false;
	return true;
}

void MyGame::Chest::open()
{
	this->scheduleUpdate();
}

void MyGame::Chest::close()
{
}

bool MyGame::Chest::isOpened()
{
	return _isOpen;
}

void MyGame::Chest::update(float dt)
{
	if (_isOpen) return;
	if (this->getBoundingBox().containsPoint(_targetOpen->getPosition()))
	{
		_bounce->showing();
		_isOpen = true;
		log("open chest");
		this->unscheduleUpdate();
	}
}
