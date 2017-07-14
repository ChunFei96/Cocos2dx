#pragma once
#include "Enemy_AI.h"
#include "cocos2d.h"
#include "MyAnimation.h"
#include "Projectile.h"

class Wolf : public cocos2d::Layer
{
public: 

	std::vector<Projectile *>Projectiles;

	enum WolfState
	{
		IDLE,
		PATROL,
		CHASE,
		ATTACK,
		RANGE_ATTACK,
		DEAD,

		Total
	};

	void init(int x, int y, const char* scoure, const char* name);
	~Wolf()
	{
		std::vector<Projectile*>::iterator deleteIterator = Projectiles.begin();
		while (deleteIterator != Projectiles.end()) {
			deleteIterator = Projectiles.erase(deleteIterator);
		}
	}

	void update(float);

	void checkState();
	void setData();
	//void setState(FSM *NewtheState);
	void getData();
	void updateState(float);

	void CheckPlayerInFront();

	bool ChaseBoundary(float,float,float,float);
	bool CheckinRange(float);
	void CheckDirection();

	void Stop(void);

	void SetWayPoint(cocos2d::Vec2 points[])
	{
		for (int i = 0; i < 2; i++)
		{
			WayPoints[i] = points[i];
		}
	}

	cocos2d::Sprite* getSprite(void)
	{
		return mainSprite;
	}

	void SetPlayerPos(float x, float y)
	{
		PlayerPos.set(x, y);
	}

	cocos2d::Vec2 GetPlayrtPos()
	{
		return PlayerPos;
	}


private:

	MyAnimation* myAnimation;
	MyAnimation::AllAnimation WolfAnimation;
	cocos2d::Sprite* mainSprite;
	cocos2d::Vec2 PlayerPos;

	float waitTime;

	float SearchRange = 250.f;

	bool SpottedPlayer;
	float AlertTime;

	float AttackTime;
	float RangeAttackTime;

	float PatrolSpeed = 50.f;
	float ChaseSpeed = 100.f;

	bool ReachBound;

	cocos2d::Vec2 direction;

	WolfState CurrentState;
	//WolfState PreState;

	//FSM *theState;
	int WayPointIndex;
	cocos2d::Vec2 WayPoints[2];
};
