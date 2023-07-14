#ifndef __CAMERA_FOLLOW_H__
#define __CAMERA_FOLLOW_H__

#include "cocos2d.h"

USING_NS_CC;

namespace MyGame
{
	class CameraFollow : public Node
	{
	public:
		CameraFollow(Camera* tagetCam, Node* target, Rect fieldOfView);
		virtual bool init();

		void setSmoothRate(float smooth) { this->_smoothRate = smooth; }
	protected:
		Camera* _camFollow;
		Node* _target;
		Rect _fieldOfView;
		float _smoothRate;

		Size _winSize;
		virtual void update(float dt);
	};
}

#endif // !__CAMERA_FOLLOW_H__
