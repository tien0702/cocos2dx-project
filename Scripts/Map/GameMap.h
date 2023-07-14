#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include "cocos2d.h"

USING_NS_CC;

namespace MyGame
{
	class Entity;
	class MetaType
	{
	public:
		static const int outside = 0;
		static const int insideRed = 1;
		static const int insideGreen = 2;
		static const int insideYellow = 3;
	};

	class MapLayer
	{
	public:
		static const int Default = 0;
		static const int Ground = 1;
		static const int Object = 5;
	};

	class GameMap : public TMXTiledMap
	{
	public:
		static const std::string MetaLayer;
		static const std::string StaticObj;
		static const std::string Collidable;
		static const std::string Gate;
		static const std::string Chest;
		static const std::string Teleport;
		static const std::string SpawnArea;
	public:
		virtual bool initWithTMXFile(const std::string& tmxFile);
		virtual int getMetaAtPos(const Vec2& position);
		virtual void setBehindObj(Node* target);
		virtual void setFrontObj(Node* target);
		virtual void handleZOrderObj(Node* obj1, Node* obj2);
		virtual void update(float dt);
		virtual std::pair<Vec2, Rect> randomPos(int metaID);

		virtual ValueVector getGates();
		ValueMap getObject(std::string nameGr, std::string nameObj);
		ValueMap getObjectInPoint(std::string nameObj);
		Point convertPosTileMap(Vec2 objectPos);
	protected:
		virtual void handleObjInMeta();

		TMXLayer* _meta;
		std::vector<Rect> _spawnAreas;
		Size _tileSize;
	};
}

#endif // !__GAME_MAP_H__
