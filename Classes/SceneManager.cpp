#include "SceneManager.h"
#include "MainMenu.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

// Singleton
SceneManager* SceneManager::instance = NULL;

SceneManager* SceneManager::getInstance()
{
	if (!instance) instance = new SceneManager();
	return instance;
}

SceneManager::SceneManager() :
	sceneTypeToReturn(SceneType::MAINMENU),
	currentSceneType(SceneType::MAINMENU)
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::runSceneWithType(const SceneType sceneType)
{
	Scene *sceneToRun = nullptr;

	switch (sceneType)
	{
	case SceneType::MAINMENU:
		sceneToRun = MainMenu::createScene();
		break;
		//case SceneType::LEVEL:
		//	sceneToRun = Level::createScene();
		//	break;
	case SceneType::GAME:
		sceneToRun = HelloWorld::createScene();
		break;
		//case SceneType::SETTINGS:
		//	sceneToRun = Settings::createScene();
		//	break;
		//case SceneType::ABOUT:
		//	sceneToRun = About::createScene();
		//	break;
	default:
		break;
	}

	SceneType oldScene = currentSceneType;
	currentSceneType = sceneType;
	sceneToRun->setTag(static_cast<int>(sceneType));

	if (sceneToRun == nullptr)
	{
		currentSceneType = oldScene;
		return;
	}

	sceneTypeToReturn = oldScene;

	if (CCDirector::getInstance()->getRunningScene() == nullptr) {
		CCDirector::getInstance()->runWithScene(sceneToRun);
	}
	else {
		CCDirector::getInstance()->replaceScene(sceneToRun);
	}
}

void SceneManager::returnToLastScene()
{
	this->runSceneWithType(sceneTypeToReturn);
}