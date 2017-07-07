#pragma once

#include "cocos2d.h"
#include <string.h>

using namespace cocos2d;

class TileMap
{
private:

	CCTMXTiledMap* Tilemap;

	Size MapSize;

	Vec2 mLoc;
	Vec2 mLocInc;

	cocos2d::GLProgram* shaderCharEffect;

public:
	void init(const char*);

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
};
