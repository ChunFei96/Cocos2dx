#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "LightEffect.h"
#include "EffectSprite.h"

#define COCOS2D_DEBUG 1
#define PTM_RATIO 50.0
USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();
	// add layer as a child to scene
	scene->addChild(layer, 0, 999);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//audioInit();


	lightInit();

	moonlightInit();

	backgroundInit();

	GameMap = new TileMap();

	GameMap->init("Level_Test.tmx");

	visibleSize = Director::getInstance()->getVisibleSize();

	worldSize = GameMap->GetSize();

	Vec2 SpawnPoint = GameMap->GetObjectPosition("Object", "SpawnPoint");
	this->addChild(GameMap->getMap(), 1);

	// Character
	mainChar.init("Idle__000.png", "spriteNode", SpawnPoint.x, SpawnPoint.y, worldSize);
	//mainChar.setPlayerPosition(mainChar.getPos(), GameMap, GameMap->getMeta(), GameMap->getMap());
	this->addChild(mainChar.getSprite(), 3);
	//this->setViewPointCenter(mainChar.getPos());

	//// box2d init
	//// Create a world
	//b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
	//_world = new b2World(gravity);

	//// Create edges around the entire screen
	//b2BodyDef groundBodyDef;
	//groundBodyDef.position.Set(0, 0);
	//_groundBody = _world->CreateBody(&groundBodyDef);

	//b2EdgeShape groundBox;
	//b2FixtureDef groundBoxDef;
	//groundBoxDef.shape = &groundBox;

	//groundBox.Set(b2Vec2(0, 0), b2Vec2(visibleSize.width / PTM_RATIO, 0));
	//_bottomFixture = _groundBody->CreateFixture(&groundBoxDef);

	//groundBox.Set(b2Vec2(0, 0), b2Vec2(0, visibleSize.height / PTM_RATIO));
	//_groundBody->CreateFixture(&groundBoxDef);

	//groundBox.Set(b2Vec2(0, visibleSize.height / PTM_RATIO), b2Vec2(visibleSize.width / PTM_RATIO,
	//	visibleSize.height / PTM_RATIO));
	//_groundBody->CreateFixture(&groundBoxDef);

	//groundBox.Set(b2Vec2(visibleSize.width / PTM_RATIO, visibleSize.height / PTM_RATIO),
	//	b2Vec2(visibleSize.width / PTM_RATIO, 0));
	//_groundBody->CreateFixture(&groundBoxDef);

	//// Create sprite and add it to the layer
	//CCSprite *ball = Sprite::create("ball.png");
	//ball->setPosition(100, 100);
	//ball->setTag(1);

	//// Create ball body 
	//b2BodyDef ballBodyDef;
	//ballBodyDef.type = b2_dynamicBody;
	//ballBodyDef.position.Set(100 / PTM_RATIO, 100 / PTM_RATIO);
	//ballBodyDef.userData = ball;
	//b2Body * ballBody = _world->CreateBody(&ballBodyDef);

	//// Create circle shape
	//b2CircleShape circle;
	//circle.m_radius = 26.0 / PTM_RATIO;

	//// Create shape definition and add to body
	//b2FixtureDef ballShapeDef;
	//ballShapeDef.shape = &circle;
	//ballShapeDef.density = 1.0f;
	//ballShapeDef.friction = 0.f;
	//ballShapeDef.restitution = 1.0f;
	//_ballFixture = ballBody->CreateFixture(&ballShapeDef);

	//b2Vec2 force = b2Vec2(10, 10);
	//ballBody->ApplyLinearImpulse(force, ballBodyDef.position,true);

	//this->addChild(ball);
	//// box2d init

	//GameMap->Metainit("Meta");

	// Define the gravity vector.
	b2Vec2 gravity;
	gravity.Set(0.0f, -9.8f);//No gravity

	bool doSleep = true; // Do we want to let bodies sleep?

	// create a world object, which will hold and simulate the rigid bodies.
	_world = new b2World(gravity);
	_world->SetAllowSleeping(false);
	_world->SetContactListener(&contactlistner);

	b2CircleShape circle;
	circle.m_radius = 26.0 / PTM_RATIO;

	b2PolygonShape rect;
	rect.SetAsBox(60 / PTM_RATIO / 2,
		76 / PTM_RATIO / 2);


	// Create sprite and add it to the layer
	//CCSprite *ball = Sprite::create("ball.png");
	//ball->setPosition(mainChar.getPos().x, mainChar.getPos().y);
	//ball->setTag(1);
	//this->addChild(ball,5);

	// Create body definition 
	b2BodyDef playerBodyDef;
	playerBodyDef.type = b2_dynamicBody;
	playerBodyDef.position.Set(mainChar.getPos().x/ PTM_RATIO, mainChar.getPos().y / PTM_RATIO);
	playerBodyDef.userData = mainChar.getSprite();
	playerBodyDef.fixedRotation = true;
	playerBody = _world->CreateBody(&playerBodyDef);

	// Create shape definition and add to body
	b2FixtureDef playerFixtureDef;
	playerFixtureDef.shape = &circle;
	playerFixtureDef.density = 10.0f;
	playerFixtureDef.friction = 0.2f;
	playerFixtureDef.restitution = 0.0f;

	_playerFixture = playerBody->CreateFixture(&playerFixtureDef);

	// add foot sensor fixture
	//rect.SetAsBox(0.3, 0.3, b2Vec2(0, -2), 0);
	//circle.m_radius = 13.0;
	playerFixtureDef.isSensor = true;
	b2Fixture* footSensorFixture = playerBody->CreateFixture(&playerFixtureDef);
	footSensorFixture->SetUserData((void*)3);

	/*b2PolygonShape paddleShape;
	paddleShape.SetAsBox(
		mainChar.getSprite()->getContentSize().width * this->getScale(),
		mainChar.getSprite()->getContentSize().height * this->getScale()
	);*/

	

	
	
	/*b2Vec2 force = b2Vec2(10, 0);
	_paddleBody->ApplyLinearImpulse(force, paddleBodyDef2.position,true);*/

	// boundary
	// Create edges around the entire screen
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	b2Body *groundBody = _world->CreateBody(&groundBodyDef);
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	//wall definitions
	/*groundEdge.Set(b2Vec2(0, 0), b2Vec2(visibleSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);*/

	// left wall
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, visibleSize.height / PTM_RATIO ));
	groundBody->CreateFixture(&boxShapeDef);

	// //top wall
	//groundEdge.Set(b2Vec2(0, 1000 / PTM_RATIO),
	//	b2Vec2(visibleSize.width / PTM_RATIO, 1000 / PTM_RATIO));
	//groundBody->CreateFixture(&boxShapeDef);

	/*groundEdge.Set(b2Vec2(visibleSize.width / PTM_RATIO, visibleSize.height / PTM_RATIO),
		b2Vec2(visibleSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);*/

	//b2Body *_paddleBody2;
	prepareLayers(GameMap);

	

	//// Create paddle and add it to the layer
	//CCSprite *paddle = CCSprite::create("Blue_Front1.png");
	//paddle->setPosition(mainChar.getPos().x, 100);
	//this->addChild(paddle,4);

	//// Create paddle body
	//b2BodyDef paddleBodyDef;
	//paddleBodyDef.type = b2_staticBody;
	//paddleBodyDef.position.Set(paddle->getPosition().x / PTM_RATIO, paddle->getPosition().y / PTM_RATIO);
	//paddleBodyDef.userData = paddle;
	//_paddleBody = _world->CreateBody(&paddleBodyDef);

	//// Create paddle shape
	//b2PolygonShape paddleShape;
	//paddleShape.SetAsBox(paddle->getContentSize().width / PTM_RATIO / 2,
	//	paddle->getContentSize().height / PTM_RATIO / 2);

	//// Create shape definition and add to body
	//b2FixtureDef paddleShapeDef2;
	//paddleShapeDef2.shape = &paddleShape;
	//paddleShapeDef2.density = 10.0f;
	//paddleShapeDef2.friction = 0.4f;
	//paddleShapeDef2.restitution = 0.1f;
	//_paddleFixture2 = _paddleBody->CreateFixture(&paddleShapeDef2);



	// Mr Wee shader code
	proPostProcess = GLProgram::createWithFilenames("Basic.vsh", "CharEffect.fsh");
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_POSITION);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_COLOR);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD1, GLProgram::VERTEX_ATTRIB_TEX_COORD1);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD2, GLProgram::VERTEX_ATTRIB_TEX_COORD2);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD3, GLProgram::VERTEX_ATTRIB_TEX_COORD3);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_NORMAL, GLProgram::VERTEX_ATTRIB_NORMAL);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_WEIGHT, GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_INDEX, GLProgram::VERTEX_ATTRIB_BLEND_INDEX);
	
	proPostProcess->link();
	proPostProcess->updateUniforms();

	rendtex = RenderTexture::create(visibleSize.width, visibleSize.height);
	rendtex->retain();

	rendtexSprite = Sprite::createWithTexture(rendtex->getSprite()->getTexture());
	rendtexSprite->setTextureRect(Rect(0, 0, rendtexSprite->getTexture()->getContentSize().width, rendtexSprite->getTexture()->getContentSize().height));
	//rendtexSprite->setAnchorPoint(Point::ZERO);
	rendtexSprite->setPosition(Point::ZERO);
	rendtexSprite->setFlippedY(true);
	rendtexSprite->setGLProgram(proPostProcess);
	this->addChild(rendtexSprite, 2);

	

	//// create player physics body
	//auto physicsBody = PhysicsBody::createBox(Size(mainChar.getSprite()->getContentSize().width, 
	//	mainChar.getSprite()->getContentSize().height), PhysicsMaterial(0.1f, 0.5f,0.0f));
	//physicsBody->setDynamic(true);
	//mainChar.getSprite()->addComponent(physicsBody);

	/*Sprite* mytest = Sprite::create("Blue_Front1.png");
	mytest->setPosition(mainChar.getPos() - Vec2(0,100));
	this->addChild(mytest);

	auto physicsBody2 = PhysicsBody::createBox(Size(mytest->getContentSize().width,
		mytest->getContentSize().height), PhysicsMaterial(0.1f, 0.5f, 0.0f));
	physicsBody2->setDynamic(false);
	mytest->addComponent(physicsBody2);*/
	
	// camera
	//this->runAction(CCFollow::create(rendtexSprite, GameMap->getMap()->boundingBox()));
	this->runAction(CCFollow::create(mainChar.getSprite(), GameMap->getMap()->boundingBox()));

	//AI

	Vec2 AI_SpawnPoint = GameMap->GetObjectPosition("Object", "AI_1");
	Vec2 AI_WayPoints[2];
	AI_WayPoints[0] = GameMap->GetObjectPosition("Object", "1_0");
	AI_WayPoints[1] = GameMap->GetObjectPosition("Object", "1_1");


	TestAI.SetWayPoint(AI_WayPoints);

	TestAI.init(AI_SpawnPoint.x, AI_SpawnPoint.y,"Blue_Front1.png", "Test");
	this->addChild(TestAI.getSprite(), 4);

	//// 
	//for (int i = 0; ; i++)
	//{
	//auto background = EffectSprite::create("background001.png");


	//background->setAnchorPoint(Vec2::ZERO);
	//background->setPosition(0 + background->getContentSize().width * i, 0);
	//background->setEffect(_effect, "background001_n.png");

	//this->addChild(background);


	//if (worldSize.width < background->getContentSize().width * (i + 1))
	//{
	//break;
	//}
	//}

	//playerMove = true;
	
	//input
	mainInput.initChar(&mainChar);

	// Key Press & Key Release
	auto listener = EventListenerKeyboard::create();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mainInput.setupKeyboardInput(listener), this);

	this->scheduleUpdate();
	return true;
}

//void HelloWorld::setPlayerPosition(Vec2 playerpos, double delta)
//{
//	CCPoint tileCoord = GameMap->tileCoordForPosition(playerpos);
//	int tileGid = GameMap->getMeta()->tileGIDAt(tileCoord);
//	if (tileGid) {
//
//		ValueMap properties = GameMap->getMap()->propertiesForGID(tileGid).asValueMap();
//		if (properties.size() > 0) {
//			
//			Sprite* testing = Sprite::create("Blue_Front1.png");
//			testing->setPosition(Vec2(100, 100));
//			this->addChild(testing);
//			//mainChar.updateMovement(delta);
//			//playerMove = false;
//		}
//		else
//		{
//			Sprite* testing2 = Sprite::create("Blue_Back1.png");
//			testing2->setPosition(Vec2(100, 100));
//			this->addChild(testing2);
//			
//		}
//			//mainChar.updateMovement(delta);
//
//	}
//	//mainChar.updateMovement(delta);
//	mainChar.getSprite()->setPosition(playerpos);
//
//}


void HelloWorld::setViewPointCenter(CCPoint position) {

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (GameMap->getMap()->getMapSize().width * this->GameMap->getMap()->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (GameMap->getMap()->getMapSize().height * GameMap->getMap()->getTileSize().height) - winSize.height / 2);
	CCPoint actualPosition = ccp(x, y);

	CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
	this->setPosition(viewPoint);
}

void HelloWorld::lightInit()
{
	brightness_ = 1.5f;
	_effect = LightEffect::create();
	_effect->retain();
	_effect->setLightCutoffRadius(200);
	_effect->setBrightness(brightness_);
	//_effect->setLightColor(cocos2d::Color3B::BLUE);

}
void HelloWorld::moonlightInit()
{
	//_moonlightPos = Vec3(worldSize.width - 200, worldSize.height - 200, 100);
	_moonlightPos = Vec3(100,100, 100);
	_mooneffect = LightEffect::create();
	_mooneffect->retain();
	_mooneffect->setLightPos(_moonlightPos);
	_mooneffect->setLightColor(cocos2d::Color3B::RED);
	_mooneffect->setLightCutoffRadius(200);
	_mooneffect->setBrightness(5);
}

void HelloWorld::audioInit()
{
	auto backgroundAudio = CocosDenshion::SimpleAudioEngine::getInstance();

	backgroundAudio->preloadBackgroundMusic("Fantasy-Forest-Battle.mp3");
	backgroundAudio->playBackgroundMusic("Fantasy-Forest-Battle.mp3", true);

}

void HelloWorld::backgroundInit()
{
	addBackground("background001.png", "background001_n.png");
	addBackground("background001_moon.png");
}

EffectSprite *HelloWorld::addBackground(const std::string &spriteFile, const std::string &normalsFile)
{
	auto background = EffectSprite::create(spriteFile);

	background->setAnchorPoint(Vec2(0, 0));

	if (!normalsFile.empty())
	{
		background->setEffect(_effect, normalsFile);
	}
	else
	{
		//background->setColor(_effect->getAmbientLightColor());
	}

	this->addChild(background);

	return background;

}

void HelloWorld::lightUpdate(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	if (mainChar.getPos().x <= visibleSize.width/2)
	{
		if (mainChar.getPos().y <= visibleSize.height/2)
		{
			_lightPos = Vec3(mainChar.getPos().x, mainChar.getPos().y, 100);
			
		}
		else if (mainChar.getPos().y >= worldSize.height - visibleSize.height / 2)
		{
			_lightPos = Vec3(mainChar.getPos().x, mainChar.getPos().y - (worldSize.height - visibleSize.height), 100);
		}
		else
		{
			_lightPos = Vec3(mainChar.getPos().x, visibleSize.height / 2, 100);
		}
	}
	else if (mainChar.getPos().x >= worldSize.width - visibleSize.width / 2)
	{
		if (mainChar.getPos().y <= visibleSize.height / 2)
		{
			_lightPos = Vec3(mainChar.getPos().x - (worldSize.width - visibleSize.width), mainChar.getPos().y, 100);

		}
		else if (mainChar.getPos().y >= worldSize.height - visibleSize.height / 2)
		{
			_lightPos = Vec3(mainChar.getPos().x - (worldSize.width - visibleSize.width), mainChar.getPos().y - (worldSize.height - visibleSize.height), 100);
		}
		else
		{
			_lightPos = Vec3(mainChar.getPos().x - (worldSize.width - visibleSize.width), visibleSize.height / 2, 100);
		}
	}
	else
	{
		if (mainChar.getPos().y <= visibleSize.height / 2)
		{
			_lightPos = Vec3(visibleSize.width / 2, mainChar.getPos().y, 100);

		}
		else if (mainChar.getPos().y >= worldSize.height - visibleSize.height / 2)
		{
			_lightPos = Vec3(visibleSize.width / 2, mainChar.getPos().y - (worldSize.height - visibleSize.height), 100);
		}
		else
		{
			_lightPos = Vec3(visibleSize.width / 2, visibleSize.height / 2, 100);
		}
	}

	_effect->setLightPos(_lightPos);

	if (brightness_ >= 5.0f)
	{
		brightness_ = 0.0f;
	}
	else
		brightness_ += 2*dt;

	_effect->setBrightness(brightness_);
	
}

void HelloWorld::update(float delta)
{

	mainChar.Update(delta);
	//setPlayerPosition(mainChar.getPos(),delta);
	lightUpdate(delta);
	//mainChar.setPlayerPosition(mainChar.getPos(), GameMap, delta);
	//mainChar.UpdateJumpUpwards(mainChar.getPos(), GameMap, delta);
	//mainChar.UpdateFreeFall(mainChar.getPos(), GameMap, delta);
	mainChar.updateMovement(delta, GameMap,playerBody, _playerFixture,contactlistner);

	int velocityIterations = 8;
	int positionIterations = 1;


	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.
	_world->Step(delta, velocityIterations, positionIterations);

	bool blockFound = false;

	// Iterate over the bodies in the physics world
	for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL) {
			// Synchronize the AtlasSprites position and rotation with the corresponding body
			CCSprite* myActor = (CCSprite*)b->GetUserData();
			myActor->setPosition(CCPointMake(b->GetPosition().x * PTM_RATIO  , b->GetPosition().y * PTM_RATIO));
			//myActor->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));

			if (myActor->getTag() == 1)
			{
				static int maxSpeed = 10;

				b2Vec2 velocity = b->GetLinearVelocity();
				float32 speed = velocity.Length();

				if (speed > maxSpeed) {
					b->SetLinearDamping(0.5);
				}
				else if (speed < maxSpeed) {
					b->SetLinearDamping(0.0);
				}

			}

			if (myActor->getTag() == 2) {
				blockFound = true;
			}

		}
	}

	TestAI.SetPlayerPos(mainChar.getPos().x, mainChar.getPos().y);
	TestAI.update(delta);

	//std::stringstream ss;
	//ss << TestAI.Projectiles.size();
	//CCLOG(ss.str().c_str());
	

	for (std::vector<Projectile*>::iterator iter = TestAI.Projectiles.begin(); iter != TestAI.Projectiles.end();)
	{
		Projectile *spriteTemp = dynamic_cast<Projectile*>(*iter);

		if (spriteTemp->getID() == Projectile::IDStatus::AI)
		{

		/*	std::stringstream ss;
			ss << "this Angle : ";
			CCLOG(ss.str().c_str());*/

			spriteTemp->update(delta);

			if (spriteTemp->getLifeTime() < 0.f)
			{
				this->removeChild(spriteTemp->getSprite(), true);
				delete *iter;
				iter = TestAI.Projectiles.erase(iter);
			}
			else
			{
				++iter;
			}
		}
		//this->addChild(spriteTemp->getSprite(), 5);

	}




	//CCObject* it = NULL;

	//if (Projectiles->data != nullptr && Projectiles != nullptr)
	//{
	//	CCARRAY_FOREACH(Projectiles, it)
	//	{
	//		Projectile *Project = dynamic_cast<Projectile*>(it);

	//		Project->update(delta);


	//		std::stringstream ss;
	//		ss << "this Angle : ";
	//		CCLOG(ss.str().c_str());


	//		if (Project->getLifeTime() < 0.f)
	//		{
	//			Project->getSprite()->removeFromParentAndCleanup(true);
	//		}

	//	}
	//}

	/*rendtex->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
	
	this->visit();
	
	
	rendtex->end();
	
	rendtexSprite->setTexture(rendtex->getSprite()->getTexture());

	rendtexSprite->setGLProgram(proPostProcess);
	

	
	rendtex->setPosition(mainChar.getPos().x, mainChar.getPos().y);

	rendtexSprite->setPosition(mainChar.getPos().x, mainChar.getPos().y);*/
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

enum
{
	kFilterCategoryLevel = 0x01,
	kFilterCategorySolidObject = 0x02,
	kFilterCategoryNonSolidObject = 0x04
};

void HelloWorld::prepareLayers(TileMap* GameMap)
{
	for (auto& Object : GameMap->getMap()->getChildren())
	{
		auto layer = dynamic_cast<TMXLayer*>(Object);
		if (layer != nullptr)
			this->createFixtures(layer, GameMap);
	}
}
//
const float kPixelsPerMeter = 50.0f;
const float kGravity = -kPixelsPerMeter / 0.7f; // adjust this to taste
//void HelloWorld::createPhysicalWorld()
//{
//	world = new b2World(b2Vec2(0.0f, kGravity));
//	world->SetAllowSleeping(true);
//	world->SetContinuousPhysics(true);
//	//world->SetContactListener(this);
//}

//
//void HelloWorld::addObjects(TileMap* GameMap)
//{
//	// loop over the object groups in this tmx file
//	auto objectGroups = GameMap->getMap()->getObjectGroups();
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
//
void HelloWorld::createFixtures(CCTMXLayer * layer, TileMap* GameMap)
{
	Vec2 scaleFactor = Vec2( 1920.0f / 1024.0f, 1080.0f / 648.0f );
	// create all the rectangular fixtures for each tile
	Size layerSize = layer->getLayerSize();
	for (int y = 0; y < layerSize.height; y++)
	{
		for (int x = 0; x < layerSize.width; x++)
		{
			// create a fixture if this tile has a sprite
			auto tileSprite = layer->getTileAt(Point(x, y));
			if (tileSprite)
			{
				//this->setScale(scaleFactor.x, scaleFactor.y);
				this->createRectangularFixture(layer, x, y, 1.1f, 1.1f, GameMap);
			}

		}

	}
}
//
void HelloWorld::createRectangularFixture(TMXLayer* layer, int x, int y, float width, float height,TileMap* GameMap)
{
	// get position & size
	auto p = (layer->getPositionAt(Point(x, y))) - Vec2(25,40);
	auto tileSize = GameMap->getMap()->getTileSize();
	const float pixelsPerMeter = 50.0f;

	// note: creating the 'world' member variable
	// is discussed in the next chapter

	// create the body
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(
		(p.x + (tileSize.width / 2.0f)) / pixelsPerMeter,
		(p.y + (tileSize.height / 2.0f)) / pixelsPerMeter
	);
	b2Body* body = _world->CreateBody(&bodyDef);

	// define the shape
	b2PolygonShape shape;
	shape.SetAsBox(
		(tileSize.width / pixelsPerMeter) * 1.f * width,
		(tileSize.height / pixelsPerMeter) * 1.5f * height
	);

	// create the fixture
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;
	fixtureDef.filter.categoryBits = kFilterCategoryLevel;
	fixtureDef.filter.maskBits = 0xffff;
	body->CreateFixture(&fixtureDef);
}



//void HelloWorld::addBodyToWorld(b2World* world)
//{
//	// add a dynamic body to world
//	// (subclasses can use other body types by overriding
//	// this method and calling body->SetType())
//	b2BodyDef bodyDef;
//	bodyDef.type = b2_dynamicBody;
//	//bodyDef.position.Set(
//	//	//this->getPositionX() / kPixelsPerMeter,
//	//	//this->getPositionY() / kPixelsPerMeter
//	//);
//	bodyDef.userData = this;
//	bodyDef.fixedRotation = true;
//	this->body = world->CreateBody(&bodyDef);
//}
//
//
//void HelloWorld::createFixture(b2Shape* shape)
//{
//	// note that friction, etc. can be modified later by looping
//	// over the body's fixtures and calling fixture->SetFriction()
//	b2FixtureDef fixtureDef;
//	fixtureDef.shape = shape;
//	fixtureDef.density = 1.0f;
//	fixtureDef.friction = 0.7f;
//	fixtureDef.restitution = 0.1f;
//	fixtureDef.filter.categoryBits = kFilterCategorySolidObject;
//	fixtureDef.filter.maskBits = 0xffff;
//	this->body->CreateFixture(&fixtureDef);
//}
//
//void HelloWorld::addCircularFixtureToBody(float radius)
//{
//	b2CircleShape shape;
//	shape.m_radius = radius * this->getScale();
//	this->createFixture(&shape);
//}
//
//void HelloWorld::addRectangularFixtureToBody(float width, float height)
//{
//	b2PolygonShape shape;
//	shape.SetAsBox(
//		width * this->getScale(),
//		height * this->getScale()
//	);
//	this->createFixture(&shape);
//}
//
//void HelloWorld::setProperties(ValueMap& properties)
//{
//	this->setPosition(Point(
//		properties["x"].asFloat(),
//		properties["y"].asFloat()
//	));
//}

