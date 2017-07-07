#ifndef __GAMECHARACTER_H__
#define __GAMECHARACTER_H__
#include "LightEffect.h"

#include "cocos2d.h"
#include "MyAnimation.h"

using namespace cocos2d ;

class GameChar
{

private:
	
	MyAnimation* myAnimation;
	MyAnimation::AllAnimation Player_animation;

	cocos2d::Sprite* mainSprite;
	float fSpeed;

	

	Size WorldSize;

	Vec2 mLoc;
	Vec2 mLocInc;

	cocos2d::GLProgram* shaderCharEffect;

public:
	void init(const char*, const char*, float, float,Size);

	void MoveChar(MyAnimation::AllAnimation);
	//void MoveCharByCoord(float, float);

	void Update(float);

	void updateMovement(float);

	

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
};

#endif