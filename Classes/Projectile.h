#pragma once
#include "cocos2d.h"


class Projectile 
{
public:
	enum IDStatus
	{
		None,
		AI,
		Player,

		total_Status
	};

	void init(int x, int y, const char* scoure, const char* name,cocos2d::Vec2 direction, int damage, float life_Length, IDStatus id = None);

	void update(float);

	cocos2d::Sprite* getSprite(void)
	{
		return mainSprite;
	}

	int getID()
	{
		return ID;
	}

	int getDamage()
	{
		return Damage;
	}

	float getLifeTime()
	{
		return lifeTime;
	}

private:
	int ID;
	cocos2d::Sprite* mainSprite;
	cocos2d::Vec2 Direction;

	float Speed = 150.f;
	float lifeTime;
	int Damage;
};