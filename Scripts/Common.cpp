#include "Common.h"
#include "GameConfig.h"
#include "Entity/BaseStat.h"

std::vector<int> MyGame::Common::splitNumbers(const std::string& str)
{
	std::vector<int> numbers;
	std::stringstream ss(str);  
	std::string token; 

	while (std::getline(ss, token, ',')) { 
		int num = std::stoi(token); 
		numbers.push_back(num);
	}

	return numbers;
}

vector<Size> MyGame::Common::getSizeFromNodes(vector<cocos2d::Node*> nodes)
{
	vector<Size> sizes;
	for (Node* node : nodes)
	{
		sizes.push_back(node->getContentSize());
	}
	return sizes;
}

std::string MyGame::Common::formatFloat(float val)
{
	std::string formattedNumber = cocos2d::StringUtils::format("%.2f", val);
	if (formattedNumber.back() == '0') {
		formattedNumber.erase(formattedNumber.size() - 1, 1);
		if (formattedNumber.back() == '.') {
			formattedNumber.erase(formattedNumber.size() - 1, 1);
		}
	}

	return formattedNumber;
}

std::vector<cocos2d::Vec2> MyGame::Common::getPositionXCenter(const vector<Size>& sizeItems, float width, float distance)
{
	vector<Vec2> positions;
	int count = sizeItems.size();
	float totalWidth = count * (sizeItems[0].width + distance) - distance;
	float x = (width - totalWidth) / 2 + sizeItems[0].width / 2;
	for (int i = 0; i < count; i++) {
		positions.push_back(Vec2(x, sizeItems[i].height / 2));
		x += sizeItems[i].width + distance;
	}
	return positions;
}

std::vector<cocos2d::Vec2> MyGame::Common::getPositionYCenter(const std::vector<cocos2d::Size>& sizeItems, float height, float distance) {
	std::vector<cocos2d::Vec2> positions;
	float totalHeight = 0;
	for (const auto& size : sizeItems) {
		totalHeight += size.height + distance;
	}
	totalHeight -= distance;

	float yStart = height - totalHeight / 2;
	for (const auto& size : sizeItems) {
		float y = yStart + size.height / 2;
		positions.emplace_back(cocos2d::Vec2(height, y));
		yStart += size.height + distance;
	}
	return positions;
}

std::vector<cocos2d::Vec2> MyGame::Common::getPositionCenter(const std::vector<Size>& sizeItems, const Size& area, const Size& distance)
{
	std::vector<cocos2d::Vec2> positions, positionsX, positionsY;

	positionsX = Common::getPositionXCenter(sizeItems, area.width, distance.width);
	positionsY = Common::getPositionYCenter(sizeItems, area.height, distance.height);

	for (int i = 0; i < sizeItems.size(); ++i)
	{
		positions.push_back(Vec2(positionsX.at(i).x, positionsY.at(i).y));
	}

	return positions;
}

std::string MyGame::Common::convertValueBonus(Bonus* _bonus)
{

	std::string desc;

	ValueType type = _bonus->getStatBns().getStatValueType();
	switch (type)
	{
	case MyGame::ValueType::BothTypesNumbers:
	{
		switch (_bonus->getStatModifiType())
		{
		case StatModificationType::Percentage:
			desc += Common::formatFloat(CONVERT_TO_PERCENT(_bonus->getValueBns())) + "%";
			break;
		case StatModificationType::Numeric:
			desc += std::to_string(_bonus->getValueBns());
			break;
		case StatModificationType::Absolute:
			desc += std::to_string(_bonus->getValueBns());
			break;
		case StatModificationType::BaseValue:
			desc += std::to_string(_bonus->getValueBns());
			break;
		default:
			break;
		}
	}
	break;
	case MyGame::ValueType::OnlyPercent:
		desc += Common::formatFloat(CONVERT_TO_PERCENT(_bonus->getValueBns())) + " %";
		break;
	case MyGame::ValueType::OnlyNumber:
		desc += std::to_string(_bonus->getValueBns());
		break;
	default:
		break;
	}
	return desc;
}

Label* MyGame::Common::getNodeWithBackground(std::string content, Color4F& bgColor)
{
	auto label = cocos2d::Label::createWithTTF(content, "fonts/arial.ttf", 24);

	auto size = label->getContentSize();

	auto bg = cocos2d::DrawNode::create();
	bg->drawSolidRect(cocos2d::Vec2::ZERO, cocos2d::Vec2(size.width, size.height), bgColor);
	label->addChild(bg, -1);
	label->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	bg->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	bg->setPosition(size.width / 2, size.height / 2);
	return label;
}

Label* MyGame::Common::getLabelWithBackground(std::string content, Size bgSize, Color4F bgColor)
{
	auto font = GameConfig::getIns()->getFont();
	auto label = Label::createWithTTF(font, content);

	auto bg = DrawNode::create();
	bg->drawSolidRect(Vec2(0, 0), Vec2(bgSize.width, bgSize.height), bgColor);

	bg->setAnchorPoint(Vec2(0.5f, 0.5f));

	label->addChild(bg, -1);

	bg->setPosition(label->getContentSize() / 2.0f);

	return label;
}

Size MyGame::Common::getFrameSize()
{
	return Director::getInstance()->getOpenGLView()->getFrameSize();
}

std::string MyGame::Common::justifyString(std::string str1, std::string str2, int maxW)
{
	int spaceCount = maxW - str1.length() - str2.length();
	int leftSpaceCount = spaceCount / 2;
	int rightSpaceCount = spaceCount - leftSpaceCount;
	std::string spaces = "";
	for (int i = 0; i < leftSpaceCount; i++) {
		spaces += " ";
	}
	return str1 + spaces + str2;
}
