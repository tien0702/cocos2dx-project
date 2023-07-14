#include "IInforLayer.h"

bool MyGame::IInforLayer::init()
{
	if (!Layer::init()) {
		log("Init Infor layer failed!");
		return false;
	}

	return true;
}
