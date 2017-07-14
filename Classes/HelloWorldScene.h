#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Character.h"
#include "GameInput.h"
#include "Projectile.h"
#include "TileMapManager.h"
#include <unordered_map>

#include "AI_wolf.h"

class LightEffect;
class EffectSprite;
class SimpleAudioEngine;

using namespace cocos2d;

//static cocos2d::CCArray* Projectiles = CCArray::create();

class HelloWorld : public cocos2d::Layer
{
public:
	

	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	void reload() {};
	
	// audio init
	void audioInit();

	// light init
	void lightInit();

	// light update
	void lightUpdate(float);

	// moonlight init
	void moonlightInit();

	// moonlight update
	void moonlightUpdate(float);

	// lamp light update

	// init background
	void backgroundInit();

	// addbackground function
	EffectSprite *addBackground(const std::string &spriteFile,const std::string &normalsFile = std::string());

	cocos2d::Node* getSpriteNode()
	{
		return this;
	}


	virtual void update(float);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

	GameChar getChar()
	{
		return mainChar;
	}

private:
	GameChar mainChar;

	Wolf TestAI;

	GameInput mainInput;

	TileMap GameMap;

	cocos2d::Vec3 _lightPos;
	LightEffect *_effect;
	cocos2d::Sprite *_lightSprite;

	cocos2d::Vec3 _moonlightPos;
	LightEffect *_mooneffect;
	
	std::unordered_map<const char*, bool> Input;

	Size worldSize;

	GLProgram* proPostProcess;
	RenderTexture *rendtex;
	Sprite* rendtexSprite;
	bool changeScene = false;

	float brightness_;
	float timer;
};

#endif // __HELLOWORLD_SCENE_H__
