
#include "TileMapManager.h"

void TileMap::init(const char* file)
{
	this->Tilemap = CCTMXTiledMap::create(file);

	auto checkHeight = Tilemap->getMapSize().height * Tilemap->getTileSize().height;
	auto checkWidth = Tilemap->getMapSize().width * Tilemap->getTileSize().width;
	MapSize = Size(checkWidth, checkHeight);
}

//void TileMap::Metainit(const std::string& metalayer)
//{
//	_meta = Tilemap->layerNamed(metalayer);
//	_meta->setVisible(true);
//}

//void TileMap::prepareLayers()
//{
//	for (auto& Object : this->Tilemap->getChildren())
//	{
//		auto layer = dynamic_cast<TMXLayer*>(Object);
//		if (layer != nullptr)
//			this->createFixtures(layer);
//	}
//}
////
//const float kPixelsPerMeter = 32.0f;
//const float kGravity = -kPixelsPerMeter / 0.7f; // adjust this to taste
//
//void TileMap::createPhysicalWorld()
//{
//	world = new b2World(b2Vec2(0.0f, kGravity));
//	world->SetAllowSleeping(true);
//	world->SetContinuousPhysics(true);
//	//world->SetContactListener(this);
//}
////
//void TileMap::addObjects()
//{
//	// loop over the object groups in this tmx file
//	auto objectGroups = Tilemap->getObjectGroups();
//	for (auto& objectGroup : objectGroups)
//	{
//		auto objects = objectGroup->getObjects();
//		for (auto& object : objects)
//		{
//			auto properties = object.asValueMap();
//			auto type = properties.at("type");
//			if (!type.isNull())
//			{
//				this->addObject(type.asString().c_str(), properties);
//			}
//		}
//	}
//}
////
//void TileMap::createFixtures(CCTMXLayer * layer)
//{
//	// create all the rectangular fixtures for each tile
//	Size layerSize = layer->getLayerSize();
//	for (int y = 0; y < layerSize.height; y++)
//	{
//		for (int x = 0; x < layerSize.width; x++)
//		{
//			// create a fixture if this tile has a sprite
//			auto tileSprite = layer->getTileAt(Point(x, y));
//			if (tileSprite)
//			{
//				this->createRectangularFixture(layer, x, y, 1.1f, 1.1f);
//			}
//			
//		}
//
//	}
//}
////
//void TileMap::createRectangularFixture(TMXLayer* layer, int x, int y, float width, float height)
//{
//	// get position & size
//	auto p = layer->getPositionAt(Point(x, y));
//	auto tileSize = this->Tilemap->getTileSize();
//	const float pixelsPerMeter = 32.0f;
//
//	// note: creating the 'world' member variable
//	// is discussed in the next chapter
//
//	// create the body
//	b2BodyDef bodyDef;
//	bodyDef.type = b2_staticBody;
//	bodyDef.position.Set(
//		(p.x + (tileSize.width / 2.0f)) / pixelsPerMeter,
//		(p.y + (tileSize.height / 2.0f)) / pixelsPerMeter
//	);
//	b2Body* body = world->CreateBody(&bodyDef);
//
//	// define the shape
//	b2PolygonShape shape;
//	shape.SetAsBox(
//		(tileSize.width / pixelsPerMeter) * 0.5f * width,
//		(tileSize.width / pixelsPerMeter) * 0.5f * height
//	);
//
//	// create the fixture
//	b2FixtureDef fixtureDef;
//	fixtureDef.shape = &shape;
//	fixtureDef.density = 1.0f;
//	fixtureDef.friction = 0.3f;
//	fixtureDef.restitution = 0.0f;
//	//fixtureDef.filter.categoryBits = kFilterCategoryLevel;
//	fixtureDef.filter.maskBits = 0xffff;
//	body->CreateFixture(&fixtureDef);
//}
//
//LevelObject* TileMap::addObject(cocos2d::String className, ValueMap& properties)
//{
//	// create the object
//	LevelObject* o = nullptr;
//	//if (className == "GameChar")
//		//o = new GameChar;
//	/*else if (className == "Monster")
//		o = new Monster;
//	else if (className == "MagicChest")
//		o = new MagicChest;*/
//
//	// process the new object
//	if (o != nullptr)
//	{
//		o->setProperties(properties);
//		//o->addSprite();
//		o->addBodyToWorld(this->world);
//		o->addFixturesToBody();
//		this->addChild(o);
//
//	}
//	return o;
//}

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
		//for (int y = 0; y < s.height; ++y)
		//{
		//	//layer->setTileGID(GID, Vec2(x, y));
		//}
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

CCPoint TileMap::tileCoordForPosition(CCPoint position)
{
	int x = position.x / Tilemap->getTileSize().width;
	int y = ((Tilemap->getMapSize().height * Tilemap->getTileSize().height) - position.y) / Tilemap->getTileSize().height;
	return ccp(x, y);
}