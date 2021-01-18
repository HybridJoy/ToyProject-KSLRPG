#ifndef __JOYSTICK__H
#define __JOYSTICK__H
#include "Hero.h"
#include "cocos2d.h"

class JoyStick : public cocos2d::Layer
{
public:
	virtual bool init() override;

	CREATE_FUNC(JoyStick);

	virtual void onEnter() override;
	virtual void onExit() override;

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
	void setHero(Hero*);
	float center_x;				//ҡ����������
	float center_y;
	float radius;				//ң�а뾶
	bool touchsucceed;			//�Ƿ�ʼ����Ӣ��

private:
	cocos2d::EventListenerTouchOneByOne* listener;  
	cocos2d::Sprite* rocker;  
	cocos2d::Sprite* rocker_bg;
	Hero* hero;
};

#endif //__JOYSTICK__H

