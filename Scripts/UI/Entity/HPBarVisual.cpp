#include "HPBarVisual.h"
#include "UI/Entity/HPBarPool.h"

bool MyGame::HPBarVisual::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	if (!loadProperties())
	{
		return false;
	}

	this->addChild(_hpBarBG, 0);
	this->addChild(_hpBar, 1);
	return true;
}

void MyGame::HPBarVisual::active(Entity* owner)
{
	setOwner(owner);
	registration();
	setPosition(calculatePostion());
	updateHPBar();
	_owner->addChild(this);
}

void MyGame::HPBarVisual::disable()
{
	cancelRegistration();
	addToPool();
	removeFromParent();
}

bool MyGame::HPBarVisual::loadProperties()
{
	std::string path = "FHD/HealthBar/";
	_hpBar = ui::LoadingBar::create(path + "enemy-hp-bar.png");
	_hpBar->setDirection(ui::LoadingBar::Direction::LEFT);
	float percent = 100.0f;
	_hpBar->setPercent(percent);

	_hpBarBG = Sprite::create(path + "enemy-hp-bar-border.png");
	return true;
}

void MyGame::HPBarVisual::updateHPBar()
{
	_hpBar->setPercent(calculatePercent());
}

void MyGame::HPBarVisual::registration()
{
	if (_owner == nullptr)
	{
		log("Registration failed! Owner is null");
		return;
	}

	_owner->attach(EntityObserverType::OnTakeDame, this);
	_owner->attach(EntityObserverType::OnRebornHP, this);
	_owner->attach(EntityObserverType::OnRecoveryHP, this);
	_owner->attach(EntityObserverType::OnDie, this);
}

void MyGame::HPBarVisual::cancelRegistration()
{
	if (_owner == nullptr)
	{
		log("Cancel registration failed! Owner is null");
		return;
	}

	_owner->dettach(EntityObserverType::OnTakeDame, this);
	_owner->dettach(EntityObserverType::OnRebornHP, this);
	_owner->dettach(EntityObserverType::OnRecoveryHP, this);
	_owner->dettach(EntityObserverType::OnDie, this);
}

void MyGame::HPBarVisual::addToPool()
{
	HPBarPool::getIns()->add(this);
}

float MyGame::HPBarVisual::calculatePercent()
{
	float currentHP = _owner->getEntityStatByID(Stat::CurrentHP)->getBaseValue();
	float maxHp = _owner->getEntityStatByID(Stat::HP)->getFinalValue();

	float percent = currentHP / maxHp;
	percent *= 100.0f;

	return percent;
}

Vec2& MyGame::HPBarVisual::calculatePostion()
{
	Size ownerSize = _owner->getEntitySize();
	Size barSize = _hpBarBG->getContentSize();
	Vec2 position;
	position.x = 0;
	position.y = ownerSize.height / 2 + barSize.height / 2;

	return position;
}

void MyGame::HPBarVisual::onRecoveryHP()
{
	updateHPBar();
}

void MyGame::HPBarVisual::onRebornHp()
{
	updateHPBar();
}

void MyGame::HPBarVisual::onTakeDame()
{
	updateHPBar();
}

void MyGame::HPBarVisual::onDie()
{
	updateHPBar();
}
