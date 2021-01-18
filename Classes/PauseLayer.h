#ifndef	_PAUSELAYER__H_
#define _PAUSELAYER__H_

#include "CommonData.h"


class  PauseLayer: public cocos2d::LayerColor {
public:
	/*
    static PauseScene* create();

	static Scene* createScene(RenderTexture*);
	*/
	CREATE_FUNC(PauseLayer);
    bool init();
};

#endif