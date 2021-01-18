#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "cocos2d.h"
USING_NS_CC;

class Terrain : public cocos2d::Sprite {
public:
	
	static bool loadResources(); // resource loader, carried once
	
	CREATE_FUNC(Terrain);

	void initPhysicsBody();

	bool initSprite(std::string);

	//to add physicsBody to area
	void initAreaPhysicsBody(Point,Point );

private:

	std::string m_sType; // Terrain type

	bool init();
};

#endif