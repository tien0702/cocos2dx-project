#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class TestScene : public Scene
{
public:
	static Scene* createTestScene();
	virtual bool init();
	CREATE_FUNC(TestScene);

public:
	PhysicsWorld* _world;
	void SetPhysicsWorld(PhysicsWorld* world) { this->_world = world; }

private:
};

#endif // !__TEST_SCENE_H__
