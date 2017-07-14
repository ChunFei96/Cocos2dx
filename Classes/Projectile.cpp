#include "Projectile.h"
#include "HelloWorldScene.h"

void Projectile::init(int x, int y, const char* scoure, const char* name, cocos2d::Vec2 direction, int damage, float life_Length, IDStatus id)
{
	mainSprite = Sprite::create(scoure);
	mainSprite->setAnchorPoint(Vec2(0, 0));
	mainSprite->setPosition(x, y);
	mainSprite->setName(name);
	Direction = direction;
	ID = id;

	Damage = damage;
	lifeTime = life_Length;
}

void Projectile::update(float delta)
{
	lifeTime -= delta;
	Vec2 newPos = mainSprite->getPosition() + Direction * delta * 100.f;
	mainSprite->setPosition(newPos);
}

