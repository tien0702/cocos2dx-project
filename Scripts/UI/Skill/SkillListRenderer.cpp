#include "SkillListRenderer.h"
#include "GameConfig.h"
#include "AudioManager/AudioManager.h"

MyGame::SkillListRenderer* MyGame::SkillListRenderer::create(std::vector<Skill*>* skills, SkillDetailRenderer* detailRenderer, SkillEquipRenderer* equipRender)
{
    SkillListRenderer* renderer = new (std::nothrow) SkillListRenderer();
    if (renderer && renderer->init(skills, detailRenderer, equipRender))
    {
        renderer->autorelease();
        return renderer;
    }
	return nullptr;
}

bool MyGame::SkillListRenderer::init(std::vector<Skill*>* skills, SkillDetailRenderer* detailRenderer, SkillEquipRenderer* equipRender)
{
    _skills = skills;
    _detailRenderer = detailRenderer;
    _equipRender = equipRender;
	if (!Layer::init())
	{
		return false;
	}
    _selectedSprite = Sprite::create("FHD/Button/skill-selected.png");
    _selectedSprite->retain();

    auto buttons = getButtons(skills);
    float w = buttons->at(0)->getContentSize().width;
    w += w * 0.2f;
    float h = 400;
    auto scrollView = createScrollView(buttons, 10, Size(w, h));

    this->addChild(scrollView, 0);
    _detailRenderer->render(_skills->at(0), _equipRender);

    auto nameLb = Label::createWithTTF(GameConfig::getIns()->getFont(), "Skill List");
    nameLb->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    nameLb->setAlignment(TextHAlignment::CENTER);
    nameLb->setPosition(w / 2.0f, h + 30 + nameLb->getContentSize().height / 2);
    this->addChild(nameLb);

	return true;
}

ui::ScrollView* MyGame::SkillListRenderer::createScrollView(std::vector<ui::Button*>* buttons, float distance, Size size) {
    auto scrollView = ui::ScrollView::create();
    scrollView->setContentSize(size + Size(0, 30));
    scrollView->setBounceEnabled(true);
    scrollView->setScrollBarOpacity(0);

    // create background
    auto background = DrawNode::create();
    scrollView->addChild(background);

    // calculate InnerContainerSize
    Size innerContainerSize = Size(size.width, (distance + buttons->at(0)->getContentSize().height) * buttons->size());
    scrollView->setInnerContainerSize(innerContainerSize);

    // add buttons to scrollview
    float yPosition = innerContainerSize.height - distance / 2 - buttons->at(0)->getContentSize().height / 2;
    for (int i = 0; i < buttons->size(); i++) {
        auto button = buttons->at(i);
        button->setPosition(Vec2(size.width / 2, yPosition));
        scrollView->addChild(button);
        yPosition -= distance + button->getContentSize().height;
    }

    background->drawSolidRect(Vec2::ZERO, innerContainerSize + Size(0, 30), Color4F(0, 0, 0, 0.7f));

    return scrollView;
}

void MyGame::SkillListRenderer::selected(Node* target)
{
    _selectedSprite->removeFromParent();
    _selectedSprite->setPosition(target->getContentSize() / 2);
    target->addChild(_selectedSprite, INT_MAX);
}

std::vector<ui::Button*>* MyGame::SkillListRenderer::getButtons(std::vector<Skill*>* skills)
{
    if (skills == nullptr) return nullptr;
    std::vector<ui::Button*>* buttons = new std::vector<ui::Button*>();

    for (int i = 0; i < skills->size(); ++i)
    {
        auto button = ui::Button::create();
        std::string path = "FHD/Icon/" + skills->at(i)->getInfo()->getIconName() + ".png";
        button->loadTextureNormal(path);
        button->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
            switch (type)
            {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                AudioManager::getIns()->playeButtonEffect();
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
            {
                selected(button);
                _detailRenderer->render(_skills->at(i), _equipRender);
            }
            break;
            default:
                break;
            }
            });

        buttons->push_back(button);
    }

    selected(buttons->at(0));
    return buttons;
}

void MyGame::SkillListRenderer::setupdButtons(std::vector<ui::Button*> buttons)
{
}
