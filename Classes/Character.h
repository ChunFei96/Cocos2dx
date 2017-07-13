#ifndef __GAMECHARACTER_H__
#define __GAMECHARACTER_H__
#include "LightEffect.h"

#include "cocos2d.h"
#include "MyAnimation.h"
#include "TileMapManager.h"
#include "Box2D\Box2D.h"
#include "MyContactListener.h"

using namespace cocos2d ;

class GameChar 
{

private:
	
	MyAnimation* myAnimation;
	MyAnimation::AllAnimation Player_animation;

	cocos2d::Sprite* mainSprite;
	float fSpeed;

	//TileMap* TileMap_;

	Size WorldSize;

	Vec2 mLoc;
	Vec2 mLocInc;

	cocos2d::GLProgram* shaderCharEffect;

	//jump
	int jumpspeed;
	bool hero_inMidAir_Up;
	bool hero_inMidAir_Down;

	int remainingJumpSteps;

	int m_jumpTimeout;

public:
	void init(const char*, const char*, float, float,Size);

	void MoveChar(MyAnimation::AllAnimation);
	//void MoveCharByCoord(float, float);

	void Update(float);

	void updateMovement(float delta, TileMap* Tilemap, b2Body* body, b2Fixture* paddleShapeDef, MyContactListener contactlistner);

	void CheckBoundary();

	void Stop(void);

	cocos2d::Sprite* getSprite(void)
	{
		return mainSprite;
	}
	

	cocos2d::Vec2 getPos(void)
	{
		return mainSprite->getPosition();
	}

	void setPlayerPosition(Vec2 playerpos, TileMap *TileMap_, double delta);


	//jump

	// Returns true if the player is on ground
	bool isOnGround(void);
	// Returns true if the player is jumping upwards
	bool isJumpUpwards(void);
	// Returns true if the player is on freefall
	bool isFreeFall(void);
	// Set the player's status to free fall mode
	void SetOnFreeFall(bool isOnFreeFall);
	// Set the player to jumping upwards
	void SetToJumpUpwards(bool isOnJumpUpwards, b2Body* body,b2Vec2 vel);
	// Stop the player's movement
	void SetToStop(void);
	// Set Jumpspeed of the player
	void SetJumpspeed(int jumpspeed);
	// Get Jumpspeed of the player
	int GetJumpspeed();

	// Update Jump Upwards
	void UpdateJumpUpwards(Vec2 playerpos, TileMap *TileMap_, double delta);
	// Update FreeFall
	void UpdateFreeFall(Vec2 playerpos, TileMap *TileMap_, double delta);

	void addBodyToWorld(b2World* world);
	void addFixturesToBody();


	
};

#endif