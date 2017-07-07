#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "LightEffect.h"
#include "EffectSprite.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

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

	
	audioInit();

	lightInit();

	moonlightInit();

	backgroundInit();

	GameMap.init("Level_Test.tmx");

	auto visibleSize = Director::getInstance()->getVisibleSize();

	worldSize = GameMap.GetSize();

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

	
	Vec2 SpawnPoint = GameMap.GetObjectPosition("Object", "SpawnPoint");
	this->addChild(GameMap.getMap(), 1);

	// Character
	mainChar.init("Idle__000.png", "spriteNode", SpawnPoint.x, SpawnPoint.y, worldSize);
	this->addChild(mainChar.getSprite(), 3);
	
	// camera
	//this->runAction(CCFollow::create(rendtexSprite, GameMap.getMap()->boundingBox()));
	this->runAction(CCFollow::create(mainChar.getSprite(), GameMap.getMap()->boundingBox()));

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

	
	//input
	mainInput.initChar(&mainChar);

	// Key Press & Key Release
	auto listener = EventListenerKeyboard::create();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mainInput.setupKeyboardInput(listener), this);

	
	this->scheduleUpdate();
	return true;
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

	lightUpdate(delta);

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
