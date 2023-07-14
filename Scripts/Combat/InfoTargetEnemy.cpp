#include "InfoTargetEnemy.h"
#include "Enemy/Enemy.h"
#include "UI/HUDLayer.h"
#include "GameConfig.h"

MyGame::InfoTargetEnemy* MyGame::InfoTargetEnemy::_instance;

MyGame::InfoTargetEnemy* MyGame::InfoTargetEnemy::getIns()
{
	if (_instance == nullptr)
	{
		_instance = new InfoTargetEnemy();
		_instance->init();
	}
	return _instance;
}

MyGame::InfoTargetEnemy::InfoTargetEnemy()
{
}

void MyGame::InfoTargetEnemy::changeTarget(Enemy* enemy)
{
	if (enemy == nullptr)
	{
		_targetIcon->removeFromParent();
		_targetEnemy = nullptr;
		this->setVisible(false);
		return;
	}

	// Cancel registration 
	if (_targetEnemy != nullptr)
	{
		_targetEnemy->dettach(EntityObserverType::OnTakeDame, this);
		_targetEnemy->dettach(EntityObserverType::OnDie, this);
	}

	// Register
	this->_targetEnemy = enemy;
	_targetEnemy->attach(EntityObserverType::OnTakeDame, this);
	_targetEnemy->attach(EntityObserverType::OnDie, this);

	// Update
	this->updateInfo();
	this->setVisible(true);
}

void MyGame::InfoTargetEnemy::onDead()
{
	changeTarget(nullptr);
}

void MyGame::InfoTargetEnemy::onDie()
{
	changeTarget(nullptr);
}

void MyGame::InfoTargetEnemy::onTakingDamage()
{
	this->updateInfo();
}

void MyGame::InfoTargetEnemy::onTakeDame()
{
	this->updateInfo();
}

bool MyGame::InfoTargetEnemy::init()
{
	if (!Layer::init()) {
		log("Init InfoTargetEnemy failed!");
		return false;
	}
	// Load Properties
	_hublayer = HUDlayer::getIns();
	_font = GameConfig::getIns()->getFont();
	_font.fontSize = 20;
	_targetEnemy = nullptr;
	_targetIcon = Sprite::create("FHD/Icon/target.png");

	// Health Bar
	_bgHealthBar = Sprite::create("FHD/HealthBar/Border2.png");
	_healthBar = ui::LoadingBar::create("FHD/HealthBar/Bar2.png");
	_healthBar->setDirection(ui::LoadingBar::Direction::LEFT);

	// Info
	_targetInfo = Label::createWithTTF(_font, "");
	_infoHp = Label::createWithTTF(_font, "");

	_targetInfo->setAlignment(TextHAlignment::RIGHT);
	_targetInfo->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);


	_infoHp->setAlignment(TextHAlignment::LEFT);
	_infoHp->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);

	// Postion
	float margin = 10;
	Vec2 posHPBar, posInfo, posInfoHP;
	Rect fixedVisible = GameConfig::getIns()->getFixedVisible();
	Size frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();

	posHPBar.x = frameSize.width / 2 ;
	posHPBar.y = frameSize.height - _bgHealthBar->getContentSize().height / 2 - margin;

	posInfo.x = posHPBar.x + _bgHealthBar->getContentSize().width / 2;
	posInfo.y = posHPBar.y - _bgHealthBar->getContentSize().height / 2 - _targetInfo->getContentSize().height / 2 - margin;

	posInfoHP.x = posHPBar.x - _bgHealthBar->getContentSize().width / 2 + 5;
	posInfoHP.y = posHPBar.y;

	_bgHealthBar->setPosition(posHPBar);
	_healthBar->setPosition(posHPBar);
	_targetInfo->setPosition(posInfo);
	_infoHp->setPosition(posInfoHP);

	this->setVisible(false);

	// Retain
	_bgHealthBar->retain();
	_healthBar->retain();
	_infoHp->retain();
	_targetInfo->retain();
	_targetIcon->retain();

	// addChild
	this->addChild(_bgHealthBar, 0);
	this->addChild(_healthBar, 1);
	this->addChild(_targetInfo, 1);
	this->addChild(_infoHp, 2);
	return true;
}

void MyGame::InfoTargetEnemy::updateInfo()
{
	int maxHp = 0;
	int curHp = 0;

	if (_targetEnemy != nullptr)
	{
		maxHp = _targetEnemy->getHealth()->getMaxHp()->getFinalValue();
		curHp = _targetEnemy->getHealth()->getHp()->getFinalValue();
	}

	// Update target icon
	_targetIcon->removeFromParent();
	_targetIcon->setPosition(Vec2(0, _targetEnemy->getSprite()->getContentSize().height / 2 + 20));
	_targetEnemy->addChild(_targetIcon, 3);

	// Update percent
	float percent = (float)(curHp) / (float)(maxHp);
	percent *= 100.0f;
	_healthBar->setPercent(percent);

	// update info
	std::string infoHp = std::to_string(curHp) + " / " + std::to_string(maxHp);
	std::string targetInfo = "Lv. " + std::to_string(_targetEnemy->getLevel()) + " - " + _targetEnemy->getEntityName();
	_infoHp->setString(infoHp);
	_targetInfo->setString(targetInfo);
}
