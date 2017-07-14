#include "MyAnimation.h"

Animate* MyAnimation::RunAnimation(AllAnimation n)
{
	Vector<SpriteFrame*> animFrames;
	

	switch (n)
	{
	case MyAnimation::Player_Moveright:
	{
		animFrames.reserve(10);
		animFrames.pushBack(SpriteFrame::create("RunRight__000.png", Rect(0, 0, 60, 76)));
		animFrames.pushBack(SpriteFrame::create("RunRight__001.png", Rect(0, 0, 60, 76)));
		animFrames.pushBack(SpriteFrame::create("RunRight__002.png", Rect(0, 0, 60, 76)));
		animFrames.pushBack(SpriteFrame::create("RunRight__003.png", Rect(0, 0, 60, 76)));
		animFrames.pushBack(SpriteFrame::create("RunRight__004.png", Rect(0, 0, 60, 76)));
		animFrames.pushBack(SpriteFrame::create("RunRight__005.png", Rect(0, 0, 60, 76)));
		animFrames.pushBack(SpriteFrame::create("RunRight__006.png", Rect(0, 0, 60, 76)));
		animFrames.pushBack(SpriteFrame::create("RunRight__007.png", Rect(0, 0, 60, 76)));
		animFrames.pushBack(SpriteFrame::create("RunRight__008.png", Rect(0, 0, 60, 76)));
		animFrames.pushBack(SpriteFrame::create("RunRight__009.png", Rect(0, 0, 60, 76)));
	}
		break;
	case MyAnimation::Player_MoveLeft:
	{
		animFrames.reserve(10);
		animFrames.pushBack(SpriteFrame::create("Run__000.png", Rect(0, 0, 60, 76)));
		animFrames.pushBack(SpriteFrame::create("Run__001.png", Rect(0, 0, 60, 76)));
		animFrames.pushBack(SpriteFrame::create("Run__002.png", Rect(0, 0, 60, 76)));
		animFrames.pushBack(SpriteFrame::create("Run__003.png", Rect(0, 0, 60, 76)));
		animFrames.pushBack(SpriteFrame::create("Run__004.png", Rect(0, 0, 60, 76)));
		animFrames.pushBack(SpriteFrame::create("Run__005.png", Rect(0, 0, 60, 76)));
		animFrames.pushBack(SpriteFrame::create("Run__006.png", Rect(0, 0, 60, 76)));
		animFrames.pushBack(SpriteFrame::create("Run__007.png", Rect(0, 0, 60, 76)));
		animFrames.pushBack(SpriteFrame::create("Run__008.png", Rect(0, 0, 60, 76)));
		animFrames.pushBack(SpriteFrame::create("Run__009.png", Rect(0, 0, 60, 76)));
	}
		break;
	case MyAnimation::Player_climbUp:
	{
		animFrames.reserve(10);
		animFrames.pushBack(SpriteFrame::create("Climb_000.png", Rect(0, 0, 46, 76)));
		animFrames.pushBack(SpriteFrame::create("Climb_001.png", Rect(0, 0, 46, 76)));
		animFrames.pushBack(SpriteFrame::create("Climb_002.png", Rect(0, 0, 46, 76)));
		animFrames.pushBack(SpriteFrame::create("Climb_003.png", Rect(0, 0, 46, 76)));
		animFrames.pushBack(SpriteFrame::create("Climb_004.png", Rect(0, 0, 46, 76)));
		animFrames.pushBack(SpriteFrame::create("Climb_005.png", Rect(0, 0, 46, 76)));
		animFrames.pushBack(SpriteFrame::create("Climb_006.png", Rect(0, 0, 46, 76)));
		animFrames.pushBack(SpriteFrame::create("Climb_007.png", Rect(0, 0, 46, 76)));
		animFrames.pushBack(SpriteFrame::create("Climb_008.png", Rect(0, 0, 46, 76)));
		animFrames.pushBack(SpriteFrame::create("Climb_009.png", Rect(0, 0, 46, 76)));
	}
		break;
	case MyAnimation::Player_climbDown:
	{
		animFrames.reserve(10);
		animFrames.pushBack(SpriteFrame::create("Climb_000.png", Rect(0, 0, 46, 76)));
		animFrames.pushBack(SpriteFrame::create("Climb_001.png", Rect(0, 0, 46, 76)));
		animFrames.pushBack(SpriteFrame::create("Climb_002.png", Rect(0, 0, 46, 76)));
		animFrames.pushBack(SpriteFrame::create("Climb_003.png", Rect(0, 0, 46, 76)));
		animFrames.pushBack(SpriteFrame::create("Climb_004.png", Rect(0, 0, 46, 76)));
		animFrames.pushBack(SpriteFrame::create("Climb_005.png", Rect(0, 0, 46, 76)));
		animFrames.pushBack(SpriteFrame::create("Climb_006.png", Rect(0, 0, 46, 76)));
		animFrames.pushBack(SpriteFrame::create("Climb_007.png", Rect(0, 0, 46, 76)));
		animFrames.pushBack(SpriteFrame::create("Climb_008.png", Rect(0, 0, 46, 76)));
		animFrames.pushBack(SpriteFrame::create("Climb_009.png", Rect(0, 0, 46, 76)));

	}
		break;
	case MyAnimation::Player_idle:
	{
		animFrames.reserve(10);
		animFrames.pushBack(SpriteFrame::create("Idle__000.png", Rect(0, 0, 40, 76)));
		animFrames.pushBack(SpriteFrame::create("Idle__001.png", Rect(0, 0, 40, 76)));
		animFrames.pushBack(SpriteFrame::create("Idle__002.png", Rect(0, 0, 40, 76)));
		animFrames.pushBack(SpriteFrame::create("Idle__003.png", Rect(0, 0, 40, 76)));
		animFrames.pushBack(SpriteFrame::create("Idle__004.png", Rect(0, 0, 40, 76)));
		animFrames.pushBack(SpriteFrame::create("Idle__005.png", Rect(0, 0, 40, 76)));
		animFrames.pushBack(SpriteFrame::create("Idle__006.png", Rect(0, 0, 40, 76)));
		animFrames.pushBack(SpriteFrame::create("Idle__007.png", Rect(0, 0, 40, 76)));
		animFrames.pushBack(SpriteFrame::create("Idle__008.png", Rect(0, 0, 40, 76)));
		animFrames.pushBack(SpriteFrame::create("Idle__009.png", Rect(0, 0, 40, 76)));
	}
	break;
	case MyAnimation::Wolf_idle:
	{
		animFrames.reserve(4);
		animFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 50, 62)));
		animFrames.pushBack(SpriteFrame::create("Blue_Front2.png", Rect(0, 0, 50, 62)));
		animFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 50, 62)));
		animFrames.pushBack(SpriteFrame::create("Blue_Front3.png", Rect(0, 0, 50, 62)));
	}
	break;

	case MyAnimation::Wolf_MoveRight:
	{
		animFrames.reserve(4);
		animFrames.pushBack(SpriteFrame::create("Blue_Right1.png", Rect(0, 0, 45, 62)));
		animFrames.pushBack(SpriteFrame::create("Blue_Right2.png", Rect(0, 0, 45, 62)));
		animFrames.pushBack(SpriteFrame::create("Blue_Right1.png", Rect(0, 0, 45, 62)));
		animFrames.pushBack(SpriteFrame::create("Blue_Right3.png", Rect(0, 0, 45, 62)));
	}
	break;

	case MyAnimation::Wolf_MoveLeft:
	{
		animFrames.reserve(4);
		animFrames.pushBack(SpriteFrame::create("Blue_Left1.png", Rect(0, 0, 45, 62)));
		animFrames.pushBack(SpriteFrame::create("Blue_Left2.png", Rect(0, 0, 45, 62)));
		animFrames.pushBack(SpriteFrame::create("Blue_Left1.png", Rect(0, 0, 45, 62)));
		animFrames.pushBack(SpriteFrame::create("Blue_Left3.png", Rect(0, 0, 45, 62)));
	}
	break;

	}

	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	Animate* animate = Animate::create(animation);
	
	return animate;
}