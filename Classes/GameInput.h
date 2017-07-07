#pragma once

#include "cocos2d.h"
#include "Character.h"

using namespace cocos2d;

class GameInput : public cocos2d::Layer
{
private:

	std::unordered_map<const char*, bool> Input;
	GameChar *mainChar;

public:
	void initChar(GameChar *gamechar);

	// keyboard input
	EventListener* setupKeyboardInput(EventListenerKeyboard* listener);
	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);
	virtual void onKeyReleased(EventKeyboard::KeyCode, Event*);
	
};
