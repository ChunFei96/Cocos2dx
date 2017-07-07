#pragma once

#include "cocos2d.h"
#include "Constants.h"

class SceneManager
{
public:
	static SceneManager* getInstance();
	~SceneManager();
	void runSceneWithType(const SceneType sceneType);
	void returnToLastScene();
private:
	SceneType sceneTypeToReturn;
	SceneType currentSceneType;
	static SceneManager* instance;
	SceneManager();

};