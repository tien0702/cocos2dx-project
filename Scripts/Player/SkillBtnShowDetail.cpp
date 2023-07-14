#include "SkillBtnShowDetail.h"
#include "UI/BounceLayer.h"
#include "GameConfig.h"

bool MyGame::SkillBtnShowDetail::init()
{
	if (!ui::Button::init()) 
	{
		return false;
	}
	_font = GameConfig::getIns()->getFont();
	loadTextureNormal("FHD/Icon/" + _skillTarget->getInfo()->getIconName() + ".png");
	setZoomScale(0.1);
	addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::ENDED:
			{
				Sprite* boxDetail = getDescription();
				auto bounceLayer = BounceLayer::create(boxDetail, Color4B(0, 0, 0, 30));
				bounceLayer->bounce(boxDetail);
			}
			break;
			default:
				break;
			}
		});
	return true;
}

Sprite* MyGame::SkillBtnShowDetail::getDescription()
{
	Size size(800, 600);
	Sprite* box = Sprite::create();
	box->setContentSize(size);

	DrawNode* drawNode = DrawNode::create();
	drawNode->drawRect(Vec2::ZERO, size, Color4F::WHITE);
	drawNode->drawSolidRect(Vec2::ZERO, size, Color4F(1, 0.6, 0, 0.7));

	Label* skillName = Label::createWithTTF(_font, _skillTarget->getInfo()->getSkillName());
	Size skillNameSize = skillName->getContentSize();
	skillName->setPosition(Vec2(size.width / 2, 
		size.height - skillNameSize.height / 2));
	
	box->addChild(drawNode);
	box->addChild(skillName);
	return box;
}
