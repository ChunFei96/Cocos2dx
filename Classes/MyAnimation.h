#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class MyAnimation
{
	
public:

	enum AllAnimation {
		Player_Moveright,
		Player_MoveLeft,
		Player_climbUp,
		Player_climbDown,
		Player_idle,

		Wolf_idle,
		Wolf_MoveRight,
		Wolf_MoveLeft,
	};

	 Animate* RunAnimation(AllAnimation);

};