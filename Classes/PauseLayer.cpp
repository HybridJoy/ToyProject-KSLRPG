#include "PauseLayer.h"
#include "GameOverScene.h"
#include "LoadingScene.h"

USING_NS_CC;

bool PauseLayer::init()
{
	if(!LayerColor::initWithColor(Color4B(0,0,0,128))) 
		return false;

	//continue game
	auto gameConti1 = Sprite::create("Continue_up.png");//createWithSpriteFrameName
	auto gameConti2 = Sprite::create("Continue_down.png");
	auto menuItemConti = MenuItemSprite::create(gameConti1, gameConti2, [this](Ref *){
		Director::getInstance()->resume();
		this->removeFromParentAndCleanup(false);
	});
	menuItemConti->setPosition(VISIBLE_SIZE.width/2,VISIBLE_SIZE.height/1.5-30);
	menuItemConti->setScale(2.0f);

	
	////restart  game 
	//auto gameRestar = Sprite::create("CloseNormal.png");
	//auto menuItemRestart= MenuItemSprite::create(gameRestar, gameRestar, [](Ref *){
	//	Director::getInstance()->setSendCleanupToScene(false);
	//	Director::getInstance()->replaceScene(LoadingScene::createScene());
	//	//Director::getInstance()->resume();
	//});
	//menuItemRestart->setPosition(VISIBLE_SIZE.width/2,VISIBLE_SIZE.height/1.5-75);
	//auto menu2 = Menu::create(menuItemRestart, NULL);
	//menu2->setPosition(Point::ZERO);
	//this->addChild(menu2,99,127);

	
	//setting
	auto gameSet = Sprite::create("CloseNormal.png");
	auto menuItemSet = MenuItemSprite::create(gameSet, gameSet, [](Ref *){
		//auto scene = Level1Scene::createScene();
		//Director::getInstance()->replaceScene(scene);
		//Director::getInstance()->resume();
	});
	menuItemSet->setPosition(VISIBLE_SIZE.width/2,VISIBLE_SIZE.height/1.5-120);
	menuItemSet->setScale(2.0f);
	
	//exit game
	auto gameExit1 = Sprite::create("Exit_up.png");
	auto gameExit2 = Sprite::create("Exit_up.png");
	auto menuItemExit = MenuItemSprite::create(gameExit1, gameExit2, [](Ref *){
		Director::getInstance()->end();
	});
	menuItemExit->setPosition(VISIBLE_SIZE.width/2,VISIBLE_SIZE.height/1.5-165);
	menuItemExit->setScale(2.0f);

	auto menu = Menu :: create();
	menu->setPosition(Point::ZERO);
	menu->addChild(menuItemConti,1);
	menu->addChild(menuItemSet,1);
	menu->addChild(menuItemExit,1);

	this->addChild(menu,1);
	return true;
}

