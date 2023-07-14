#include "CameraFollow.h"

MyGame::CameraFollow::CameraFollow(Camera* tagetCam, Node* target, Rect fieldOfView)
{
	this->_camFollow = tagetCam;
	this->_target = target;
	this->_fieldOfView = fieldOfView;
}

bool MyGame::CameraFollow::init()
{
	if (!Node::init()) {
		log("init Camera Follow failed!");
		return false;
	}

	_winSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	_smoothRate = 0.05f;

	if (_fieldOfView.size.width < _winSize.width) { _fieldOfView.size.width = _winSize.width; }
	if (_fieldOfView.size.height < _winSize.height) { _fieldOfView.size.height = _winSize.height; }

	this->scheduleUpdate();
	return true;
}

void MyGame::CameraFollow::update(float dt)
{
	Vec2 posTarget = _target->getPosition();
	Vec2 posCam = _camFollow->getPosition();
	Size visible = _fieldOfView.size;
	float xNew, yNew;

	float offsetW = _winSize.width / 2.0f;
	float offsetH = _winSize.height / 2.0f;
	float right = posTarget.x + offsetW;
	float left = posTarget.x - offsetW;
	float top = posTarget.y + offsetH;
	float bot = posTarget.y - offsetH;

	if (left >= 0 && right <= visible.width) { xNew = posTarget.x; }
	else { (left < 0) ? (xNew = offsetW) : (xNew = visible.width - offsetW); }

	if (bot >= 0 && top <= visible.height) { yNew = posTarget.y; }
	else { (bot < 0) ? (yNew = offsetH) : (yNew = visible.height - offsetH); }

	_camFollow->setPositionX(MathUtil::lerp(posCam.x, xNew, _smoothRate));
	_camFollow->setPositionY(MathUtil::lerp(posCam.y, yNew, _smoothRate));
}
