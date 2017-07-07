#include "Character.h"
#include "HelloWorldScene.h"

void GameChar::init(const char* chSource, const char* chName, float fX, float fY, Size size)
{
	mainSprite = Sprite::create(chSource);
	mainSprite->setAnchorPoint(Vec2(0, 0));
	mainSprite->setPosition(fX, fY);
	mainSprite->setName(chName);
	//intDir = 0;


	
	WorldSize = size;

	fSpeed = 500;

	mLoc.set(0.5f, 0.5f);
	mLocInc.set(0.005f, 0.01f);

	shaderCharEffect = new GLProgram();
	shaderCharEffect->initWithFilenames("Basic.vsh", "CharEffect.fsh");
	shaderCharEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	shaderCharEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	shaderCharEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);

	shaderCharEffect->link();
	shaderCharEffect->updateUniforms();

	//GLProgramState* state = GLProgramState::getOrCreateWithGLProgram(shaderCharEffect);
	//mainSprite->setGLProgram(shaderCharEffect);
	//mainSprite->setGLProgramState(state);
	//state->setUniformVec2("loc", mLoc);




	Stop();
}

//void GameChar::CharDash()
//{
//	mainSprite->stopAllActions();
//	auto moveEvent = MoveBy::create(0.2f, Vec2(100.0f,0.0f));
//	mainSprite->runAction(moveEvent);
//}

void GameChar::MoveChar(MyAnimation::AllAnimation Movement)
{
	Player_animation = Movement;
	mainSprite->stopAllActions();
	
	Animate* animate = myAnimation->RunAnimation(Player_animation);

	mainSprite->runAction(RepeatForever::create(animate));
}
//
//void GameChar::MoveCharByCoord(float fX, float fY)
//{
//	mainSprite->stopAllActions();
//	float diffX = fX - mainSprite->getPosition().x;
//	float diffY = fY - mainSprite->getPosition().y;
//	Vec2 vec = Vec2(diffX, diffY);
//	auto moveEvent = MoveBy::create(vec.length() * fSpeed, vec);
//
//	auto callbackStop = CallFunc::create([]()
//	{
//		auto scene = Director::getInstance()->getRunningScene();
//		auto layer = scene->getChildByTag(999);
//		HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
//		if (helloLayer != NULL)
//		{
//			helloLayer->getChar().Stop();
//		}
//	});
//	auto seq = Sequence::create(moveEvent, callbackStop, nullptr);
//
//	mainSprite->runAction(seq);
//
//	Vector<SpriteFrame*> animFrames;
//	animFrames.reserve(4);
//	animFrames.pushBack(SpriteFrame::create("Blue_Right2.png", Rect(0, 0, 45, 62)));
//	animFrames.pushBack(SpriteFrame::create("Blue_Right1.png", Rect(0, 0, 45, 62)));
//	animFrames.pushBack(SpriteFrame::create("Blue_Right3.png", Rect(0, 0, 45, 62)));
//	animFrames.pushBack(SpriteFrame::create("Blue_Right1.png", Rect(0, 0, 45, 62)));
//
//	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
//	Animate* animateRight = Animate::create(animation);
//
//
//	Vector<SpriteFrame*> animFrames2;
//	animFrames2.reserve(4);
//	animFrames2.pushBack(SpriteFrame::create("Blue_Left2.png", Rect(0, 0, 45, 62)));
//	animFrames2.pushBack(SpriteFrame::create("Blue_Left1.png", Rect(0, 0, 45, 62)));
//	animFrames2.pushBack(SpriteFrame::create("Blue_Left3.png", Rect(0, 0, 45, 62)));
//	animFrames2.pushBack(SpriteFrame::create("Blue_Left1.png", Rect(0, 0, 45, 62)));
//
//	Animation* animation2 = Animation::createWithSpriteFrames(animFrames2, 0.5f);
//	Animate* animateLeft = Animate::create(animation2);
//
//	Vector<SpriteFrame*> animFrames3;
//	animFrames3.reserve(4);
//	animFrames3.pushBack(SpriteFrame::create("Blue_Front2.png", Rect(0, 0, 50, 62)));
//	animFrames3.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 50, 62)));
//	animFrames3.pushBack(SpriteFrame::create("Blue_Front3.png", Rect(0, 0, 50, 62)));
//	animFrames3.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 50, 62)));
//
//	Animation* animation3 = Animation::createWithSpriteFrames(animFrames3, 0.5f);
//	Animate* animateUp = Animate::create(animation3);
//
//	Vector<SpriteFrame*> animFrames4;
//	animFrames4.reserve(4);
//	animFrames4.pushBack(SpriteFrame::create("Blue_Back2.png", Rect(0, 0, 50, 62)));
//	animFrames4.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 50, 62)));
//	animFrames4.pushBack(SpriteFrame::create("Blue_Back3.png", Rect(0, 0, 50, 62)));
//	animFrames4.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 50, 62)));
//
//	Animation* animation4 = Animation::createWithSpriteFrames(animFrames4, 0.5f);
//	Animate* animateDown = Animate::create(animation4);
//
//
//
//	if (diffX >= 0)
//	{
//		if (diffX <= diffY && diffY > 0)
//		{
//			mainSprite->runAction(RepeatForever::create(animateDown));
//		}
//		else if (diffX <= -diffY && diffY < 0)
//		{
//			mainSprite->runAction(RepeatForever::create(animateUp));
//		}
//		else
//		{
//			mainSprite->runAction(RepeatForever::create(animateRight));
//		}
//	}
//	else
//	{
//		if (-diffX <= diffY && diffY > 0)
//		{
//			mainSprite->runAction(RepeatForever::create(animateDown));
//		}
//		else if (-diffX <= -diffY && diffY < 0)
//		{
//			mainSprite->runAction(RepeatForever::create(animateUp));
//		}
//		else
//		{
//			mainSprite->runAction(RepeatForever::create(animateLeft));
//		}
//	}
//
//
//}

void GameChar::CheckBoundary()
{
	if (mainSprite->getPosition().x <= 0) 
	{
			if(Player_animation == myAnimation->Player_MoveLeft) Player_animation = myAnimation->Player_idle;
	}
	else if (mainSprite->getPosition().x >= WorldSize.width - mainSprite->getTextureRect().getMaxX())
	{
			if (Player_animation == myAnimation->Player_Moveright) Player_animation = myAnimation->Player_idle;
	}

	if (mainSprite->getPosition().y <= 0)
	{
		if (Player_animation == myAnimation->Player_climbDown) Player_animation = myAnimation->Player_idle;
	}
	else if (mainSprite->getPosition().y >= WorldSize.height - mainSprite->getTextureRect().getMaxY())
	{
		if (Player_animation == myAnimation->Player_climbUp) Player_animation = myAnimation->Player_idle;
	}
}


void GameChar::updateMovement(float delta)
{
	switch (Player_animation)
	{
	case MyAnimation::Player_Moveright:
	{
		auto moveEvent = MoveBy::create(0.0f, Vec2(1.0f, 0.0f) * fSpeed* delta);
		mainSprite->runAction(moveEvent);
	}
	break;
	case MyAnimation::Player_MoveLeft:
	{
		auto moveEvent = MoveBy::create(0.0f, Vec2(-1.0f, 0.0f) * fSpeed* delta);
		mainSprite->runAction(moveEvent);
	}
	break;
	case MyAnimation::Player_climbUp:
	{
		auto moveEvent = MoveBy::create(0.0f, Vec2(0.0f, 1.0f) * fSpeed* delta);
		mainSprite->runAction(moveEvent);
	}
	break;
	case MyAnimation::Player_climbDown:
	{
		auto moveEvent = MoveBy::create(0.0f, Vec2(0.0f, -1.0f) * fSpeed* delta);
		mainSprite->runAction(moveEvent);

	}
	break;
	case MyAnimation::Player_idle:
	{

		Stop();
	}

	break;
	}


}


void GameChar::Update(float delta)
{
	updateMovement(delta);
	CheckBoundary();


	//GLProgramState* state = GLProgramState::getOrCreateWithGLProgram(shaderCharEffect);
	//mainSprite->setGLProgram(shaderCharEffect);
	//mainSprite->setGLProgramState(state);
	//state->setUniformVec2("loc", mLoc);



}

void GameChar::Stop(void)
{
	Player_animation= myAnimation->Player_idle;

	mainSprite->stopAllActions();
	//now lets animate the sprite we moved
}