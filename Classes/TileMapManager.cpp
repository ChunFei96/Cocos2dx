
#include "TileMapManager.h"

void TileMap::init(const char* file)
{
	Tilemap = CCTMXTiledMap::create(file);

	auto checkHeight = Tilemap->getMapSize().height * Tilemap->getTileSize().height;
	auto checkWidth = Tilemap->getMapSize().width * Tilemap->getTileSize().width;
	MapSize = Size(checkWidth, checkHeight);
}

Size TileMap::GetSize()
{
	return MapSize;
}

Sprite* TileMap::getTile(const char* file, Vec2 coord)
{
	auto layer = Tilemap->layerNamed(file);
	auto tile = layer->tileAt(coord);
	return tile;
}

unsigned int TileMap::getTileGID(const char* file,Vec2 coord)
{
	auto layer = Tilemap->layerNamed(file);
	auto GID = layer->tileGIDAt(coord);
	return GID;
}

void TileMap::addTileGid(const char* file,unsigned int GID, Vec2 coord)
{
	auto layer = Tilemap->layerNamed(file);
	layer->setTileGID(GID, coord);
}

void TileMap::deleteTile(const char* file,Vec2 coord)
{
	auto layer = Tilemap->layerNamed(file);
	layer->removeTileAt(coord);
}

void TileMap::TestCode(const char* file)
{
	auto layer = Tilemap->layerNamed(file);
	Size s = layer->getLayerSize();
	for (int x = 0; x < s.width; ++x)
	{
		for (int y = 0; y < s.height; ++y)
		{
			//layer->setTileGID(GID, Vec2(x, y));
		}
	}

	
}

Vec2 TileMap::GetObjectPosition(const std::string& layer, const std::string& objectName)
{

	auto layer_object = Tilemap->objectGroupNamed(layer);
	cocos2d::ValueMap spawnPoint = layer_object->objectNamed(objectName);


	float x = spawnPoint.at("x").asFloat();
	float y = spawnPoint.at("y").asFloat();

	return Vec2(x, y);
}