#include "MainMenu.h"
#include "SceneManager.h"
#include "HelloWorldScene.h"

#define ACTION_PLAY 1
#define ACTION_LEVEL 2
#define ACTION_OPTION 3
#define ACTION_QUIT 4

USING_NS_CC;

using namespace ui;

Scene* MainMenu::createScene()
{
	auto scene = Scene::create();

	auto layer = MainMenu::create();

	scene->addChild(layer, 0, 999);

	return scene;
}

bool MainMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto map = CCTMXTiledMap::create("test2.tmx");

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	proPostProcess = GLProgram::createWithFilenames("Basic.vsh", "GreyScale.fsh");
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
	rendtexSprite->setAnchorPoint(Point::ZERO);
	rendtexSprite->setPosition(Point::ZERO);
	rendtexSprite->setFlippedY(true);
	rendtexSprite->setGLProgram(proPostProcess);
	this->addChild(rendtexSprite, 2);

	//this->addChild(map, 0);

	
	// Key Press & Key Release

	auto startButton = ui::Button::create("button_start-game.png", "button_start-game.png", "button_start-game.png");
	startButton->setActionTag(ACTION_PLAY);
	startButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));
	startButton->addTouchEventListener(CC_CALLBACK_1(MainMenu::onButtonPressed, this));
	this->addChild(startButton);

	auto levelSelect = Button::create("button_level-select.png", "button_level-select.png", "button_level-select.png");
	levelSelect->setActionTag(ACTION_LEVEL);
	levelSelect->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 100));
	levelSelect->addTouchEventListener(CC_CALLBACK_1(MainMenu::onButtonPressed, this));
	this->addChild(levelSelect);

	auto optionButton = Button::create("button_options.png", "button_options.png", "button_options.png");
	optionButton->setActionTag(ACTION_OPTION);
	optionButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 150));
	optionButton->addTouchEventListener(CC_CALLBACK_1(MainMenu::onButtonPressed, this));
	this->addChild(optionButton);

	auto quitButton = Button::create("button_quit-game.png", "button_quit-game.png", "button_quit-game.png");
	quitButton->setActionTag(ACTION_QUIT);
	quitButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 200));
	quitButton->addTouchEventListener(CC_CALLBACK_1(MainMenu::onButtonPressed, this));
	this->addChild(quitButton);

	this->scheduleUpdate();

	return true;
}

void MainMenu::onButtonPressed(Ref *pSender)
{
	if (((cocos2d::ui::Button*)pSender)->getActionTag() == ACTION_PLAY)
	{
		SceneManager::getInstance()->runSceneWithType(SceneType::GAME);
	}
	if (((cocos2d::ui::Button*)pSender)->getActionTag() == ACTION_LEVEL)
	{
		SceneManager::getInstance()->runSceneWithType(SceneType::GAME);
	}
	if (((cocos2d::ui::Button*)pSender)->getActionTag() == ACTION_OPTION)
	{
		SceneManager::getInstance()->runSceneWithType(SceneType::GAME);
	}
	if (((cocos2d::ui::Button*)pSender)->getActionTag() == ACTION_QUIT)
	{
		//SceneManager::getInstance()->runSceneWithType(SceneType::GAME);
		//exit(0);
		CCDirector::sharedDirector()->end();
	}
}

void MainMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	Input["Space"] = false;

	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE && !Input["Space"])
	{
		//Director::getInstance()->getTextureCache()->addImageAsync("Blue_Front1.png",CC_CALLBACK_1(HelloWorld::callback,this));
		//CCDirector::getInstance()->replaceScene(TransitionFade::create(2.0f, HelloWorld::createScene(), Color3B(0, 255, 255)));
		SceneManager::getInstance()->runSceneWithType(SceneType::GAME);
	}
}

void MainMenu::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE && Input["Space"])
	{
		Input["Space"] = false;
	}

}

void MainMenu::changeScene(cocos2d::Ref* sender)
{
	MenuItem *item = static_cast<MenuItem*>(sender);
	SceneManager::getInstance()->runSceneWithType(static_cast<SceneType>(item->getTag()));
}