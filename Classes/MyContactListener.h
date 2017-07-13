#pragma once

#include "cocos2d.h"
#include <string.h>
#include "Box2D/Box2D.h"

class MyContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);

	int getnumFootContacts();

private:
	int numFootContacts = 0;
};