#pragma once

#include "CommonData.h"

#include "cocos2d.h"

class MapScene : public cocos2d::Layer
{
public:
	static bool loadResources(); 

	virtual bool init() = 0;
	// virtual bool initAim(Hero * hero);

	void createMap(cocos2d::Point pos, int num, int type, std::string mapBlock = "brick.png");

	
	virtual bool isGoOtherMap() = 0;	// = 0
	virtual int nextMap() = 0;	// = 0
	virtual const cocos2d::Point newPostion() = 0;	// = 0

	virtual void addChildAndRecord(cocos2d::Node * node, int z, int tag);
	virtual void clearNodes();

	void setMask(float delta);

protected:
	std::vector<cocos2d::Node *> nodes;

	cocos2d::Sprite * m_spMask;
};