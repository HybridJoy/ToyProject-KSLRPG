#pragma once

#include "MapScene.h"

class Map1Page5Scene : public MapScene
{
public:
	static cocos2d::Scene * createScene();
	bool init();
	CREATE_FUNC(Map1Page5Scene);

	int nextMap();
	bool isGoOtherMap();
	virtual const cocos2d::Point newPostion();

private:
	int nextmap;
	cocos2d::Point postion;
};
