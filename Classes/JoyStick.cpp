#include "JoyStick.h"
#include "Hero.h"
#include "CommonData.h"
USING_NS_CC;

bool JoyStick::init()
{

	if (!Layer::init()) {
		return false;
	}

	this->rocker_bg = Sprite::create("yaogan.png");
	rocker_bg->setPosition(Point(150, 150));
	addChild(rocker_bg,99,10);
	this->setVisible(false);

	this->rocker = Sprite::create("yaoganqiu.png");
	rocker->setPosition(Point(150, 150));
	addChild(rocker,99,11);
	this->setVisible(false);
	touchsucceed = false;

	return true;
}

void JoyStick::onEnter()
{
	Layer::onEnter();

	listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(JoyStick::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(JoyStick::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(JoyStick::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}

void JoyStick::onExit()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);

	Layer::onExit();
}

bool JoyStick::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	if (touch->getLocation().x < VISIBLE_SIZE.width / 2){
		this->setVisible(true);
		Point touch_pos = touch->getLocation();
		Point center = touch_pos;
		center_x = touch_pos.x;
		center_y = touch_pos.y;
		radius = rocker_bg->getContentSize().width / 2;
		rocker->setPosition(touch_pos);
		this->getChildByTag(11)->setPosition(center);
		this->getChildByTag(10)->setPosition(center);
		touchsucceed = true;
		return true;
	}
	return false;
}
void JoyStick::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	if (touchsucceed){
		Point touch_pos = touch->getLocation();
		float dis = sqrt(pow((touch->getLocation().x - center_x), 2) + pow((touch->getLocation().y - center_y), 2));
		float angle = acos((touch_pos.x - center_x) / dis);

		if (dis <= radius) {
			rocker->setPosition(Point(touch_pos));
		}
		else {
			if (touch_pos.y >  center_y) {
				rocker->setPosition(Point(center_x + radius*cos(angle), center_y + radius*sin(angle)));
			}
			else {
				rocker->setPosition(Point(center_x + radius*cos(angle), center_y - radius*sin(angle)));
			}
		}
		if (touch_pos.x > center_x){
			hero->setWalking(false, Hero::BTN_LEFT);
			hero->setWalking(true, Hero::BTN_RIGHT);
		}
		else{
			hero->setWalking(false, Hero::BTN_RIGHT);
			hero->setWalking(true, Hero::BTN_LEFT);

		}
	}

}

void JoyStick::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	this->setVisible(false);
	touchsucceed = false;
	hero->setWalking(false, Hero::BTN_RIGHT);
	hero->setWalking(false, Hero::BTN_LEFT);
}

void JoyStick::setHero(Hero* h){
	this->hero = h;
}
