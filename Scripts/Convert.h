#ifndef __CONVERT_H__
#define __CONVERT_H__

#include "Entity/Stat.h"
#include "DamagerSystem/Power.h"

class Convert
{
public:
	static MyGame::ValueType stringToValueType(std::string str);
	static MyGame::ElementType stringToElementType(std::string str);
	static std::string ElementTypeToString(MyGame::ElementType type);
};

#endif // !__CONVERT_H__
