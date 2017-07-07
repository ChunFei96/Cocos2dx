#pragma once

#include "cocos2d.h"
#include <unordered_map>
#include "ui\CocosGUI.h"

using namespace cocos2d;
using namespace ui;

class MainMenu : public Layer
{
public:
	virtual bool init();
	static Scene* createScene();
	CREATE_FUNC(MainMenu);

protected:
	void changeScene(Ref* sender);
	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);
	virtual void onKeyReleased(EventKeyboard::KeyCode, Event*);
	virtual void onButtonPressed(Ref *pSender);

private:
	std::unordered_map<const char*, bool> Input;

	GLProgram* proPostProcess;
	RenderTexture *rendtex;
	Sprite* rendtexSprite;
};