#include "Power.h"

bool MyGame::Power::initWithStr(std::string valJson)
{
	std::string delimiter = ",";
	size_t pos = 0;
	std::string token;

	// Power Value
	if ((pos = valJson.find(delimiter)) != std::string::npos) {
		token = valJson.substr(0, pos);
		_powerValue = std::atof(token.c_str());
		valJson.erase(0, pos + delimiter.length());
	}

	// Power Value
	if ((pos = valJson.find(delimiter)) != std::string::npos) {
		token = valJson.substr(0, pos);
		_powerNumber = std::atoi(token.c_str());
		valJson.erase(0, pos + delimiter.length());
	}

	// Element Type
	if ((pos = valJson.find(delimiter)) != std::string::npos) {
		token = valJson.substr(0, pos);
		_elementType = (ElementType)std::atoi(token.c_str());
		valJson.erase(0, pos + delimiter.length());
	}

	// PowerBy
	_powerBy = (PowerBy)std::atoi(valJson.c_str());

	return true;
}

int MyGame::Power::convertIDBnsElement()
{
	switch (_elementType)
	{
	case MyGame::PhysicalType:
		return 13;
	case MyGame::PyroType:
		return 15;
	case MyGame::CryoType:
		return 17;
	case MyGame::LighningType:
		return 19;
	default:
		break;
	}
	return 0;
}

int MyGame::Power::convertIDResElement()
{
	switch (_elementType)
	{
	case MyGame::PhysicalType:
		return 14;
	case MyGame::PyroType:
		return 16;
	case MyGame::CryoType:
		return 18;
	case MyGame::LighningType:
		return 20;
	default:
		break;
	}
	return 0;
}

