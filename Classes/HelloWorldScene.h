#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Character.h"
#include "GameInput.h"
#include "TileMapManager.h"
#include <unordered_map>
#include "Box2D\Box2D.h"
#include "Box2dDebugDraw.h"
#include "MyContactListener.h"

class LightEffect;
class EffectSprite;
class SimpleAudioEngine;
class Node;

using namespace cocos2d;

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



	virtual void update(float);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

	/*GameChar getChar()
	{
		return mainChar;
	}*/

	void setViewPointCenter(CCPoint position);

	void setPlayerPosition(Vec2 playerpos, double delta);

	// box2d
	void addBodyToWorld(b2World* world);
	void addCircularFixtureToBody(float radius);
	void addRectangularFixtureToBody(float width, float height);
	void createFixture(b2Shape* shape);
	void setProperties(ValueMap& properties);

	void prepareLayers(TileMap* GameMap);

	void createFixtures(CCTMXLayer * layer, TileMap* GameMap);

	void createRectangularFixture(TMXLayer* layer, int x, int y, float width, float height, TileMap* GameMap);

	void createPhysicalWorld();

	void addObjects(TileMap* GameMap);

	//virtual void draw(Renderer *renderer, const kmMat4& transform, bool transformUpdated);

	void onDrawPrimitives(const kmMat4 &transform, bool transformUpdated);



private:
	GameChar mainChar;

	GameInput mainInput;

	TileMap* GameMap;

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

	bool playerMove;

	Vec2 Gravity;

	// box2d

	b2World *_world;
	b2Body *_groundBody;
	b2Body *playerBody;
	b2Fixture *_bottomFixture;
	b2Fixture *_ballFixture;

	b2Fixture *_playerFixture;

	CustomCommand m_drawCommand;

	MyContactListener contactlistner;

	
	
};

#endif // __HELLOWORLD_SCENE_H__
