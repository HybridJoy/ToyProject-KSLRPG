#ifndef __START_LOADING_SCENE_H__
#define __START_LOADING_SCENE_H__

#include "CommonData.h"
USING_NS_CC;

class StartLoadingScene : public Layer
{
public:
	static Scene * createScene();
	bool init();
	CREATE_FUNC(StartLoadingScene);
};
#endif