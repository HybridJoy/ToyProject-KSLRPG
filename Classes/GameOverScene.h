#ifndef	_GAME_OVER_SCENE_H_
#define	_GAME_OVER_SCENE_H_


#include "CommonData.h"

//#include "SimpleAudioEngine.h"
//using namespace CocosDenshion;
using namespace cocos2d;

class GameOverScene : public Layer
{
public:
	GameOverScene();

	~GameOverScene();

	bool init(int);

	static GameOverScene* create(int);

	static Scene *createScene(int);

	void setScore(int);

	int getScore();

private:
	int score;
};

#endif