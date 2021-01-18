	#pragma once

#include "cocos2d.h"
USING_NS_CC;

class Hero;
class JoyStick;
class PauseLayer;

class MapSwitcher
{
public:
	static MapSwitcher * getInstance();
	~MapSwitcher();

	void init();

	void initMaps();

	void setHero(Hero *);
	Hero * getHero();

	//JoyStick * getRocker();
	cocos2d::Layer * getUILayer();

	void setSwitching(bool isSwitching);

	cocos2d::Scene * getCurMap();
	void setCurMap(int mapType);

	void update(float delta);
	
private:
	static MapSwitcher * instance;

	std::vector<cocos2d::Scene *> * maps;

	Hero * hero;

	bool isSwitching;
	cocos2d::Scene * curMap;
	int curMapNum;

	cocos2d::EventListenerKeyboard * KBListener;
	JoyStick * rocker;
	cocos2d::Layer * uiLayer;
	PauseLayer * pauseLayer;

	MapSwitcher();
	MapSwitcher(const MapSwitcher &) {};
};

