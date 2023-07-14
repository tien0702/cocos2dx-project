#include "StatRenderer.h"
#include "GameConfig.h"
#include "Common.h"

bool MyGame::StatRenderer::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    loadProperties();
    loadScrollView();
    
    DrawNode* drawNode = DrawNode::create();
    Size sizeOffset = Size(10, 20);
    drawNode->drawRect(Vec2::ZERO, _windowSize + sizeOffset, Color4F::WHITE);
    drawNode->drawSolidRect(Vec2::ZERO, _windowSize + sizeOffset, Color4F(0, 0, 0, 0.5));
    drawNode->setPosition((_windowSize + sizeOffset) / -2);
    addChild(drawNode);

    this->addChild(_windowScrollview);
	return true;
}

void MyGame::StatRenderer::renderer()
{
    loadScrollView();
}

bool MyGame::StatRenderer::loadProperties()
{
    _font = GameConfig::getIns()->getFont();
    return true;
}

bool MyGame::StatRenderer::loadScrollView()
{
    auto stats = Player::getIns()->getCharacter()->getStats();
    bool b = false;
    int maxWidth = _windowSize.width - 20;
    vector<Node*> nodes;
    for (std::list<BaseStat*>::iterator it = stats->begin(); it != stats->end(); ++it) {
        b = !b;
        auto node = getLabelState((*it)->getEStat().getStatName(), getStatValue((*it)), maxWidth, b);
        nodes.push_back(node);
    }

    _windowScrollview = createScrollView(_windowSize, nodes);
    return true;
}

Node* MyGame::StatRenderer::getLabelState(string statName, string statValue, int maxWidth, bool isEvenNumber)
{
    // color
    Color4F colorBG;
    if (isEvenNumber)
    {
        colorBG = Color4F(68, 70, 84, 70);
    }
    else
    {
        colorBG = Color4F(68, 70, 84, 255);
    }

    // label
    auto statNameLabel = Label::createWithTTF(_font, " " + statName);
    statNameLabel->setAnchorPoint(Vec2(0, 0.5));
    statNameLabel->setTextColor(Color4B::GRAY);

    auto statValueLabel = Label::createWithTTF(_font, statValue + " ");
    statValueLabel->setAnchorPoint(Vec2(1, 0.5));
    statValueLabel->setTextColor(Color4B::YELLOW);


    float offset = 10;
    auto container = Node::create();
    container->setContentSize(Size(maxWidth, statNameLabel->getContentSize().height + offset));

    statNameLabel->setPosition(Vec2(0, container->getContentSize().height / 2));
    container->addChild(statNameLabel);

    statValueLabel->setPosition(Vec2(container->getContentSize().width, container->getContentSize().height / 2));
    container->addChild(statValueLabel);

    // draw background
    cocos2d::DrawNode* drawNode = cocos2d::DrawNode::create();
    drawNode->drawSolidRect(cocos2d::Vec2::ZERO, container->getContentSize(), colorBG);
    //drawNode->setPosition(container->getContentSize() / 2);

    container->addChild(drawNode, -1);
    return container;
}

ui::ScrollView* MyGame::StatRenderer::createScrollView(Size size, std::vector<Node*> nodes)
{
    float containerHeight = 0;
    for (const auto& node : nodes) {
        containerHeight += node->getContentSize().height;
    }
    containerHeight += nodes.at(0)->getContentSize().height / 2;

    ui::ScrollView* scrollView = ui::ScrollView::create();
    scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
    scrollView->setContentSize(size);
    scrollView->setBounceEnabled(true);
    scrollView->setScrollBarOpacity(0);
    scrollView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    scrollView->setInnerContainerSize(Size(size.width, containerHeight));

    float y = containerHeight;
    for (const auto& node : nodes) {
        y -= node->getContentSize().height;
        node->setAnchorPoint(Vec2(0.5, 0.5));
        node->setPosition(Vec2(size.width / 2, y));
        scrollView->getInnerContainer()->addChild(node);
    }

    return scrollView;
}

std::string MyGame::StatRenderer::getStatValue(BaseStat* baseStat)
{
    std::string valueStr;
    ValueType type = baseStat->getEStat().getStatValueType();

    switch (type)
    {
    case MyGame::ValueType::BothTypesNumbers:
        valueStr = std::to_string(baseStat->getFinalValue()) + " [" + std::to_string(baseStat->getBaseValue()) + "]";
        break;
    case MyGame::ValueType::OnlyPercent:
        valueStr = Common::formatFloat(CONVERT_TO_PERCENT(baseStat->getFinalValue())) + " %";
        break;
    case MyGame::ValueType::OnlyNumber:
        valueStr = std::to_string(baseStat->getFinalValue());
        break;
    default:
        break;
    }

    return valueStr;
}
