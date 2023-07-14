#include "Convert.h"

MyGame::ValueType Convert::stringToValueType(std::string str)
{
	MyGame::ValueType type = MyGame::ValueType::BothTypesNumbers;
	if (str == "BothTypesNumbers")
	{
		type = MyGame::ValueType::BothTypesNumbers;
	}
	else if (str == "OnlyPercent")
	{
		type = MyGame::ValueType::OnlyPercent;
	}
	else if (str == "OnlyNumber")
	{
		type = MyGame::ValueType::OnlyNumber;
	}
	return type;
}

MyGame::ElementType Convert::stringToElementType(std::string str)
{
	MyGame::ElementType type;
	if (str == "Physical")
	{
		type = MyGame::ElementType::PhysicalType;
	}
	else if (str == "Pyro")
	{
		type = MyGame::ElementType::PyroType;
	}
	else if (str == "Cryo")
	{
		type = MyGame::ElementType::CryoType;
	}
	else if (str == "Lighning")
	{
		type = MyGame::ElementType::LighningType;
	}
	return type;
}

std::string Convert::ElementTypeToString(MyGame::ElementType type)
{
	std::string str = "";
	switch (type)
	{
	case MyGame::PhysicalType:
		str = "Physics";
		break;
	case MyGame::PyroType:
		str = "Pyro";
		break;
	case MyGame::CryoType:
		str = "Cryo";
		break;
	case MyGame::LighningType:
		str = "Lighning";
		break;
	default:
		break;
	}
	return str;
}
