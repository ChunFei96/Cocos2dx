#ifndef __TILEMAP_MANAGER_H__
#define __TILEMAP_MANAGER_H__

#include "cocos2d.h"
#include <string.h>
#include "Box2D/Box2D.h"
#include "LevelObject.h"

using namespace cocos2d;

class GameChar;
class LevelObject;

class TileMap : public cocos2d::Layer
{
private:

	CCTMXTiledMap* Tilemap;

	CCTMXLayer* _meta;

	Size MapSize;

	Vec2 mLoc;
	Vec2 mLocInc;

	cocos2d::GLProgram* shaderCharEffect;

	b2World* world;

public:

	void init(const char*);

	//void Metainit(const std::string&);

	Sprite* getTile(const char*,Vec2);
	unsigned int getTileGID(const char*,Vec2);
	void addTileGid(const char*,unsigned int, Vec2);
	void deleteTile(const char*,Vec2);
	
	Vec2 GetObjectPosition(const std::string&, const std::string&);

	void TestCode(const char*);

	Size GetSize();

	CCTMXTiledMap* getMap(void)
	{
		return Tilemap;
	}

	CCTMXLayer* getMeta(void)
	{
		return _meta;
	}

	CCPoint tileCoordForPosition(CCPoint position);

	void prepareLayers();

	void createFixtures(CCTMXLayer* layer);

	void createRectangularFixture(TMXLayer* layer, int x, int y, float width, float height);

	void createPhysicalWorld();

	void addObjects();

	LevelObject* addObject(cocos2d::String className, ValueMap& properties);

	




};
#endif // __TILEMAP_MANAGER_H__