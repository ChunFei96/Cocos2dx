#include "GameInput.h"
#include "HelloWorldScene.h"
#include "SceneManager.h"
#include "MyAnimation.h"

void GameInput::initChar(GameChar *gamechar)
{
	this->mainChar = gamechar;
}

EventListener* GameInput::setupKeyboardInput(EventListenerKeyboard* listener)
{
	listener->onKeyPressed = CC_CALLBACK_2(GameInput::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(GameInput::onKeyReleased, this);
	return listener;
}

void GameInput::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	Input["Right"] = false;
	Input["Left"] = false;
	Input["Up"] = false;
	Input["Down"] = false;
	Input["Jump"] = false;
	Input["Menu"] = false;

	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW && !Input["Right"])
	{
		mainChar->MoveChar(MyAnimation::Player_Moveright);
		for (auto it = Input.begin(); it != Input.end(); ++it)
		{
			it->second = false;
		}
		Input["Right"] = true;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW && !Input["Left"])
	{
		mainChar->MoveChar(MyAnimation::Player_MoveLeft);
		for (auto it = Input.begin(); it != Input.end(); ++it)
		{
			it->second = false;
		}
		Input["Left"] = true;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW && !Input["Up"])
	{
		mainChar->MoveChar(MyAnimation::Player_climbUp);
		for (auto it = Input.begin(); it != Input.end(); ++it)
		{
			it->second = false;
		}
		Input["Up"] = true;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW && !Input["Down"])
	{
		mainChar->MoveChar(MyAnimation::Player_climbDown);
		for (auto it = Input.begin(); it != Input.end(); ++it)
		{
			it->second = false;
		}
		Input["Down"] = true;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE && !Input["Jump"])
	{
		mainChar->MoveChar(MyAnimation::Player_Jump);
		for (auto it = Input.begin(); it != Input.end(); ++it)
		{
			it->second = false;
		}
		Input["Jump"] = true;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE && !Input["Menu"])
	{
		//CCDirector::getInstance()->replaceScene(TransitionFade::create(2.0f, Test::createScene(), Color3B(0, 255, 255)));
		SceneManager::getInstance()->runSceneWithType(SceneType::MAINMENU);
		Input["Menu"] = false;
	}
}

void GameInput::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW && Input["Right"])
	{
		mainChar->MoveChar(MyAnimation::Player_idle);
		Input["Right"] = false;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW && Input["Left"])
	{
		mainChar->MoveChar(MyAnimation::Player_idle);
		Input["Left"] = false;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW && Input["Up"])
	{
		mainChar->MoveChar(MyAnimation::Player_idle);
		Input["Up"] = false;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW && Input["Down"])
	{
		mainChar->MoveChar(MyAnimation::Player_idle);
		Input["Down"] = false;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE && Input["Jump"])
	{
		mainChar->MoveChar(MyAnimation::Player_idle);
		Input["Jump"] = false;
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE && Input["Menu"])
	{
		Input["Menu"] = false;
	}
}

