#pragma once
#include "cocos2d.h"

class Enemy_AI 
{
public:
	enum  ENMEY_TYPE
	{
		nope = 0,
		wolf,
		bee,

		Total_type
	};

	//Enemy_AI(int x, int y, const char* scoure, const char* name, ENMEY_TYPE type = nope);
	//virtual ~Enemy_AI() {}

	cocos2d::Sprite* getSprite(void)
	{
		return mainSprite;
	}

	ENMEY_TYPE GetType()
	{
		return EnemyType;
	}

	cocos2d::Vec2 SetPlayerPos(float x,float y)
	{
		PlayerPos.set(x, y);
	}

	cocos2d::Vec2 GetPlayrtPos()
	{
		return PlayerPos;
	}

private:
	cocos2d::Sprite* mainSprite;
	ENMEY_TYPE EnemyType;
	cocos2d::Vec2 PlayerPos;

};
