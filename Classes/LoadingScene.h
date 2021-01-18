#ifndef __LOADING_SCREEN_H__
#define __LOADING_SCREEN_H__

#include "CommonData.h"
USING_NS_CC;

class LoadingScene : public Layer
{
public:
	static Scene * createScene();
	bool init();
	CREATE_FUNC(LoadingScene);

};
#endif