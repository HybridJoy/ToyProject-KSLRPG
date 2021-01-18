#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"

class Item : public cocos2d::Sprite {
public:
	
	static bool loadResources(); // resource loader, carried once

	bool init();

	void initPhysicsBody();

	bool initSprite(std::string);

	CREATE_FUNC(Item);

private:

	void update(float delta);

	std::string m_sType;
};

#endif