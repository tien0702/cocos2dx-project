#include "GameMap.h"
#include "ObjectTag.h"
#include "Entity/Entity.h"

const std::string MyGame::GameMap::MetaLayer = "Meta";
const std::string MyGame::GameMap::StaticObj = "ObjectStatic";
const std::string MyGame::GameMap::Collidable = "Collidable";
const std::string MyGame::GameMap::Gate = "Gate";
const std::string MyGame::GameMap::Chest = "Chest";
const std::string MyGame::GameMap::Teleport = "Teleport";
const std::string MyGame::GameMap::SpawnArea = "SpawnArea";

bool MyGame::GameMap::initWithTMXFile(const std::string& tmxFile)
{
	if (!TMXTiledMap::initWithTMXFile(tmxFile)) {
		log("init tile map failed!");
		return false;
	}

	// Spawn Areas
	auto area = this->getObjectGroup(GameMap::SpawnArea)->getObjects();
	for (int i = 0; i < area.size(); ++i)
	{
		ValueMap valMap = area.at(i).asValueMap();
		Rect rectVal;
		rectVal.origin.x = valMap["x"].asFloat();
		rectVal.origin.y = valMap["y"].asFloat();
		rectVal.size.width = valMap["width"].asFloat();
		rectVal.size.height = valMap["height"].asFloat();
		_spawnAreas.push_back(rectVal);
	}

	// Properties
	_meta = this->getLayer(GameMap::MetaLayer);
	_meta->setVisible(false);
	_tileSize.width = _contentSize.width / _mapSize.width;
	_tileSize.height = _contentSize.height / _mapSize.height;
	this->setTag(ObjectTag::Map);

	this->scheduleUpdate();
	return true;
}

int MyGame::GameMap::getMetaAtPos(const Vec2& position)
{
	Point posTile = convertPosTileMap(position);
	int result = MetaType::outside;
	int tileGid = _meta->getTileGIDAt(posTile);
	if (tileGid != 0)
	{
		Value temp = this->getPropertiesForGID(tileGid);
		if (!temp.isNull())
		{
			ValueMap properties = temp.asValueMap();
			auto properName = properties.find(GameMap::Collidable);
			auto properValue = properties.at(GameMap::Collidable).asInt();
			if (properName != properties.end() && properValue == MetaType::insideRed)
			{
				result = MetaType::insideRed;
			}
			else if (properName != properties.end() && properValue == MetaType::insideGreen)
			{
				result = MetaType::insideGreen;
			}
			else if (properName != properties.end() && properValue == MetaType::insideYellow)
			{
				result = MetaType::insideYellow;
			}
		}
	}

	return result;
}

void MyGame::GameMap::setBehindObj(Node* target)
{
	if (target->getParent() == this)
	{
		target->setLocalZOrder(this->getLayer("Wall")->getLocalZOrder() + 1);
	}
}

void MyGame::GameMap::setFrontObj(Node* target)
{
	return;
	if (target->getParent() == this)
	{
		target->setLocalZOrder(this->getLayer(GameMap::StaticObj)->getLocalZOrder() + 2);
	}
}

void MyGame::GameMap::handleZOrderObj(Node* obj1, Node* obj2)
{
	if (obj1->getParent() != this) return;
	if (obj2->getParent() != this) return;

	float y1 = obj1->getPosition().y - obj1->getContentSize().height * 0.5f;
	float y2 = obj2->getPosition().y - obj2->getContentSize().height * 0.5f;


	if (y1 < y2)
	{
		this->setFrontObj(obj2);
		this->setBehindObj(obj1);
	}
	else
	{
		this->setFrontObj(obj1);
		this->setBehindObj(obj2);
	}
}

void MyGame::GameMap::update(float dt)
{
	this->handleObjInMeta();
}

std::pair<Vec2, Rect> MyGame::GameMap::randomPos(int metaID)
{
	Rect area = _spawnAreas.at(RandomHelper::random_int(0, (int)(_spawnAreas.size() - 1)));
	Vec2 pos;
	int minX, minY, maxX, maxY;

	minX = (int)area.origin.x;
	maxX = (int)area.origin.x + area.size.width;
	minY = (int)area.origin.y;
	maxY = (int)area.origin.y + area.size.height;

	do
	{
		pos.x = RandomHelper::random_int(minX, maxX);
		pos.y = RandomHelper::random_int(minY, maxY);
	} while (this->getMetaAtPos(pos) != metaID);
	return std::pair<Vec2, Rect>(pos, area);
}

ValueVector MyGame::GameMap::getGates()
{
	auto objGr = this->getObjectGroup(GameMap::Gate);
	return objGr->getObjects();
}

ValueMap MyGame::GameMap::getObject(std::string nameGr, std::string nameObj)
{
	auto objGr = this->getObjectGroup(nameGr.c_str());
	ValueMap object = objGr->getObject(nameObj.c_str());
	return object;
}

ValueMap MyGame::GameMap::getObjectInPoint(std::string nameObj)
{
	auto objGr = this->getObjectGroup("Point");
	ValueMap object = objGr->getObject(nameObj.c_str());
	return object;
}

Point MyGame::GameMap::convertPosTileMap(Vec2 objectPos)
{
	int x = objectPos.x / _tileSize.width;
	int y = (this->getContentSize().height - objectPos.y) / _tileSize.height;
	return Point(x, y);
}


void MyGame::GameMap::handleObjInMeta()
{
	for (Node* node : _children)
	{
		int tag = node->getTag();
		if (!(tag == ObjectTag::Player ||
			tag == ObjectTag::Enemy ||
			tag == ObjectTag::Projectile))
		{
			continue;
		}

		if (this->getMetaAtPos(node->getPosition()) == MetaType::insideGreen)
		{
			this->setBehindObj(node);
		}
	}
}
