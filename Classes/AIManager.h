#pragma once

#include "cocos2d.h"

class Hero;

class AIManager : public cocos2d::Node
{
public:
	AIManager();
	~AIManager();
	
	bool init();
	CREATE_FUNC(AIManager);

	void stopEnemy();
	void startEnemy();

	void setHero(Hero * hero);
	void setMapLayer(cocos2d::Layer * mapLayer);

	void createEnemy(int type, const cocos2d::Point & enePos, const float & range);
	void createEnemy(int type, const float & enePosX, const float & enePosY, const float & range);

private:
	bool calcDis(Hero * enemy);

	void stopAct(Hero * enemy);

	void updateStatus(float delta);

	void patrol(float delta);

	void trackAndAttack(float delta);

	Hero * hero;
	cocos2d::Layer * mapLayer;

	std::vector<std::pair<Hero *, float *> > * meleeFreeEnemies;
	std::vector<std::pair<Hero *, float *> > * meleeBusyEnemies;

	std::vector<std::pair<Hero *, float *> > * rangedFreeEnemies;
	std::vector<std::pair<Hero *, float *> > * rangedBusyEnemies;
};

