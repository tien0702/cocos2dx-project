#include "SerpentScrew.h"
#include "Input/PlayerInput.h"
#include "Entity/BaseStat.h"
#include "Entity/Entity.h"

bool MyGame::SerpentScew::init()
{
	return false;
}

MyGame::SerpentScew::SerpentScew()
{
}

bool MyGame::SerpentScew::use()
{
	
	return false;
}

bool MyGame::SerpentScew::canUse()
{
	return false;
}

bool MyGame::SerpentScew::isReady()
{
	return false;
}

void MyGame::SerpentScew::update(float dt)
{
	_elapsedTime += dt;

	// Check input
	//bool input = PlayerInput::getIns()->getInput();
	//if (!input) return;

	//// Check cooldown
	//float cooldown = this->getStatByID(Stat::Cooldown)->getFinalValue() * 0.001f;
	//if (cooldown < _elapsedTime) return;

	//// Check tick frequency
	//float tickFrequency = this->getStatByID(Stat::TickFrequency)->getFinalValue() * 0.001f;
	//if (tickFrequency < _elapsedTime) return;

	//use();

	//_elapsedTime = 0.0f;
}
