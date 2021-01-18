#pragma once

#include "cocos2d.h"

class Hero;

class Damage : public cocos2d::Sprite {
public:
	static const int DAMAGE_HERO_1 = 0;
	static const int DAMAGE_HERO_2 = 1;
	static const int DAMAGE_HERO_3 = 2;
	static const int DAMAGE_BOSS_1 = 3;
	static const int DAMAGE_BOSS_2 = 4;
	static const int DAMAGE_FIREYEYAN = 5;
	static const int DAMAGE_YANMO = 6;
	static const int DAMAGE_YEYAN = 7;


	static bool loadResources(); // resource loader, carried once

	virtual bool init(Hero * hero, int type);
	bool initSprite(std::string name);
	void initPhysicsBody();
	
	static Damage * create(Hero * hero, int type);

	float getDamageValue();
	int getGroup();

private:
	Hero * hero;
	float m_fDamageValue;

	int dir;

	int group;

	void disCheck(float delta);
};
