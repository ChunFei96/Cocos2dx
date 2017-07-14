#include "AI_wolf.h"
#include "HelloWorldScene.h"
#include "Projectile.h"


#define _USE_MATH_DEFINES

#include <math.h>

void Wolf::init(int x, int y, const char* scoure, const char* name)
{
	mainSprite = Sprite::create(scoure);
	mainSprite->setAnchorPoint(Vec2(0, 0));
	mainSprite->setPosition(x, y);
	mainSprite->setName(name);

	//Enemy_AI(x, y, scoure, name, type);
	WayPointIndex = 1;
	CurrentState = IDLE;

	waitTime = 0.f;
	direction.set(0, 0);

	SpottedPlayer = false;
	AlertTime = 5.f;
	AttackTime = 0.2f;
	RangeAttackTime = 0.5f;
	ReachBound = false;

}
//Wolf::~Wolf()
//{
//	/*if (this->theState != nullptr)
//	{
//		delete this->theState;
//	}*/
//}

void Wolf::checkState()
{
	switch (CurrentState)
	{
	case Wolf::IDLE:
	{
		if (waitTime < 0.f)
		{
			waitTime = 3.f;

			WayPointIndex++;
			if (WayPointIndex == 2) WayPointIndex = 0;

			direction = WayPoints[WayPointIndex] - mainSprite->getPosition();
			direction.normalize();

			if (direction.x > 0)
			{
				WolfAnimation = myAnimation->Wolf_MoveRight;

			}
			else if (direction.x  < 0)
			{
				WolfAnimation = myAnimation->Wolf_MoveLeft;
			}

			mainSprite->stopAllActions();
			Animate* animate = myAnimation->RunAnimation(WolfAnimation);
			mainSprite->runAction(RepeatForever::create(animate));

			CurrentState = PATROL;
		}


		CheckPlayerInFront();
		break;
	}

	case Wolf::PATROL:
	{
		float WayPointDistanceSQ = mainSprite->getPosition().distance(WayPoints[WayPointIndex]);
		if (WayPointDistanceSQ < 10)
		{
			CurrentState = IDLE;
		}
		CheckPlayerInFront();
		break;
	}

	case Wolf::CHASE:
	{
		if (CheckinRange(300.f) /*&& rayCast*/ )
		{
			CheckDirection();
			SpottedPlayer = true;
			AlertTime = 5.f;
		}
		else
		{
			SpottedPlayer = false;
		}

		if (AlertTime < 0.f)
		{
			AlertTime = 5.f;
			waitTime = 1.f;
			CurrentState = IDLE;
		}

		if (SpottedPlayer)
		{
			if (!ChaseBoundary(WayPoints[0].x, WayPoints[1].x, WayPoints[0].y, WayPoints[1].y) && CheckinRange(60.f) /*&& rayCast*/)
			{
				Stop();
				SpottedPlayer = false;
				CurrentState = ATTACK;
			}
			else if (ReachBound && CheckinRange(200.f) /*&& rayCast*/ )
			{
				Stop();
				CurrentState = RANGE_ATTACK;
			}
		}



		break;
	}
	case Wolf::ATTACK:
	{
		if (AttackTime < 0.f)
		{
			//attack
			Director::getInstance()->getRunningScene();
			auto scene = Director::getInstance()->getRunningScene();
			auto layer = scene->getChildByTag(999);
			HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);

			Node* SpriteNode = helloLayer->getSpriteNode();

			cocos2d::Vec2 PlayerDirection = PlayerPos - mainSprite->getPosition();
			PlayerDirection.normalize();

			Projectile *newProj = new Projectile();
			newProj->init(mainSprite->getPosition().x + PlayerDirection.x * 50, mainSprite->getPosition().y, "CloseNormal.png", "Projectile", cocos2d::Vec2(0,0) , 1, 0.1f, Projectile::IDStatus::AI);

			/*std::stringstream ss;
			ss << "that Angle : ";
			CCLOG(ss.str().c_str());*/

			//this->addChild(newProj->getSprite(), 5);
			SpriteNode->addChild(newProj->getSprite(), 5);

			Projectiles.push_back(newProj);


			AttackTime = 0.8f;
			CurrentState = CHASE;
		}
		else
		{
			if (!CheckinRange(60.f) /*&& rayCast*/)
			{
				AttackTime = 0.8f;
				CurrentState = CHASE;
			}
		}
		break;
	}
	case Wolf::RANGE_ATTACK:
	{
		if (RangeAttackTime < 0.f)
		{
			//rangeAttack
			Director::getInstance()->getRunningScene();
			auto scene = Director::getInstance()->getRunningScene();
			auto layer = scene->getChildByTag(999);
			HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);

			Node* SpriteNode = helloLayer->getSpriteNode();

			cocos2d::Vec2 PlayerDirection = PlayerPos - mainSprite->getPosition();
			PlayerDirection.normalize();

			Projectile *newProj = new Projectile();
			newProj->init(mainSprite->getPosition().x, mainSprite->getPosition().y,"CloseNormal.png", "Projectile", PlayerDirection,1,5.f,Projectile::IDStatus::AI);

			/*std::stringstream ss;
			ss << "that Angle : ";
			CCLOG(ss.str().c_str());*/

			//this->addChild(newProj->getSprite(), 5);
			SpriteNode->addChild(newProj->getSprite(), 5);

			Projectiles.push_back(newProj);

			RangeAttackTime = 1.0f;
			CurrentState = CHASE;
		}
		else 
		{
			if (!CheckinRange(200.f) /*&& rayCast*/)
			{
				RangeAttackTime = 1.0f;
				CurrentState = CHASE;
			}
		}
		break;
	}
	case Wolf::DEAD:
	{

		break;
	}
	}
}
void Wolf::setData()
{
	switch (CurrentState)
	{
	case Wolf::IDLE:
	{

		break;
	}

	case Wolf::PATROL:
	{

		break;
	}

	case Wolf::CHASE:
	{

		break;
	}

	case Wolf::DEAD:
	{

		break;
	}
	}
}
//void Wolf::setState(FSM *NewtheState)
//{
//
//	if (this->theState != nullptr)
//	{
//		delete this->theState;
//		this->theState = nullptr;
//	}
//
//	this->theState = NewtheState;
//}
void Wolf::getData()
{
	switch (CurrentState)
	{
	case Wolf::IDLE:
	{

		break;
	}

	case Wolf::PATROL:
	{

		break;
	}

	case Wolf::CHASE:
	{

		break;
	}

	case Wolf::DEAD:
	{

		break;
	}
	}
}

void Wolf::update(float delta)
{
	checkState();
	//setData();
	updateState(delta);
	//theState->Update();
	//getData();


	/*std::stringstream ss;
	ss << CurrentState;
	CCLOG(ss.str().c_str());*/

}

void Wolf::updateState(float delta)
{
	switch (CurrentState)
	{
	case Wolf::IDLE:
	{
		waitTime -= delta;
		Stop();
		break;
	}

	case Wolf::PATROL:
	{
		
		Vec2 newPos = mainSprite->getPosition() + direction * delta * PatrolSpeed;
		mainSprite->setPosition(newPos);

		break;
	}

	case Wolf::CHASE:
	{
		if (SpottedPlayer && !ChaseBoundary(WayPoints[0].x, WayPoints[1].x, WayPoints[0].y, WayPoints[1].y))
		{
			CheckDirection();
			Vec2 newPos = mainSprite->getPosition() + direction * delta * ChaseSpeed;
			mainSprite->setPosition(newPos);
		}	
		if (ChaseBoundary(WayPoints[0].x, WayPoints[1].x, WayPoints[0].y, WayPoints[1].y))
		{
			Stop();
			ReachBound = true;
		}
		else
		{
			ReachBound = false;
		}
		if (SpottedPlayer == false)
		{
			Stop();
			AlertTime -= delta;
		}

		break;
	}
	case Wolf::ATTACK:
	{
		AttackTime -= delta;
		break;
	}
	case Wolf::RANGE_ATTACK:
	{
		RangeAttackTime -= delta;
		break;
	}
	case Wolf::DEAD:
	{

		break;
	}
	}
}

void Wolf::Stop(void)
{
	WolfAnimation = myAnimation->Wolf_idle;

	mainSprite->stopAllActions();
	//now lets animate the sprite we moved
}

void Wolf::CheckPlayerInFront()
{
	float playerDistanceSQ = mainSprite->getPosition().distance(PlayerPos);
	
	cocos2d::Vec2 PlayerDirection = PlayerPos - mainSprite->getPosition();
	PlayerDirection.normalize();

	if (playerDistanceSQ < SearchRange)
	{
		float hi = direction.getAngle(PlayerDirection) * 180 / M_PI;
		if (hi < 0) hi = -hi;

		if (hi  < 45)
		{
			std::stringstream ss;
			ss << "this Angle : " << hi;
			CCLOG(ss.str().c_str());
			


			direction = PlayerPos - mainSprite->getPosition();
			direction.normalize();

			if (direction.x > 0)
			{
				direction.set(1, 0);
				WolfAnimation = myAnimation->Wolf_MoveRight;

			}
			else if (direction.x  < 0)
			{
				direction.set(-1, 0);
				WolfAnimation = myAnimation->Wolf_MoveLeft;
			}

			mainSprite->stopAllActions();
			Animate* animate = myAnimation->RunAnimation(WolfAnimation);
			mainSprite->runAction(RepeatForever::create(animate));

			CurrentState = CHASE;
			SpottedPlayer = true;
		}
	}
}

bool Wolf::CheckinRange(float Range)
{
	float playerDistanceSQ = mainSprite->getPosition().distance(PlayerPos);

	cocos2d::Vec2 PlayerDirection = PlayerPos - mainSprite->getPosition();
	PlayerDirection.normalize();

	if (playerDistanceSQ < Range)
	{
		return true;
	}
	else
	{
		return false;
	}
}



bool Wolf::ChaseBoundary(float x1,float x2, float y1, float y2)
{
	if (mainSprite->getPosition().x < x1)
	{
		mainSprite->setPosition(Vec2(x1, mainSprite->getPosition().y));
		return true;
	}
	if (mainSprite->getPosition().x > x2) 
	{
		mainSprite->setPosition(Vec2(x2, mainSprite->getPosition().y));
		return true;
	}
	if (mainSprite->getPosition().y < y1) 
	{
		mainSprite->setPosition(Vec2(mainSprite->getPosition().x, y1));
		return true;
	}
	if (mainSprite->getPosition().y > y2) 
	{
		mainSprite->setPosition(Vec2(mainSprite->getPosition().x, y2));
		return true;
	}

	return false;
}

void Wolf::CheckDirection()
{
	cocos2d::Vec2 PlayerDirection = PlayerPos - mainSprite->getPosition();
	PlayerDirection.normalize();

	direction = (mainSprite->getPosition() + direction) - mainSprite->getPosition();
	direction.normalize();

	if (SpottedPlayer)
	{
		if (direction.x > 0 && PlayerDirection.x < 0)
		{
			direction.set(-1, 0);
			WolfAnimation = myAnimation->Wolf_MoveLeft;
			mainSprite->stopAllActions();
			Animate* animate = myAnimation->RunAnimation(WolfAnimation);
			mainSprite->runAction(RepeatForever::create(animate));
		}
		else if (direction.x < 0 && PlayerDirection.x > 0)
		{
			direction.set(1, 0);
			WolfAnimation = myAnimation->Wolf_MoveRight;
			mainSprite->stopAllActions();
			Animate* animate = myAnimation->RunAnimation(WolfAnimation);
			mainSprite->runAction(RepeatForever::create(animate));
		}
	}
	else
	{
		if (PlayerDirection.x < 0)
		{
			direction.set(-1, 0);
			WolfAnimation = myAnimation->Wolf_MoveLeft;
			mainSprite->stopAllActions();
			Animate* animate = myAnimation->RunAnimation(WolfAnimation);
			mainSprite->runAction(RepeatForever::create(animate));
		}
		else if (PlayerDirection.x > 0)
		{
			direction.set(1, 0);
			WolfAnimation = myAnimation->Wolf_MoveRight;
			mainSprite->stopAllActions();
			Animate* animate = myAnimation->RunAnimation(WolfAnimation);
			mainSprite->runAction(RepeatForever::create(animate));
		}
	}
	

}