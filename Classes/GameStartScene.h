#ifndef __GAME_START_SCENE_H__
#define __GAME_START_SCENE_H__

#include "CommonData.h"
USING_NS_CC;

class GameStartScene : public Layer
{
public:
	static Scene * createScene();
	bool init();
	CREATE_FUNC(GameStartScene);
};
#endif