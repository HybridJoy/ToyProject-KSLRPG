#include "GameStartScene.h"
#include "MenuSelect.h"
#include "LoadingScene.h"

Scene * GameStartScene :: createScene()
{
	auto scene = Scene :: create();
	auto layer = GameStartScene :: create();
	scene->addChild(layer);
	return scene;
}

bool GameStartScene :: init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	auto  scene_bg = Sprite :: create("GSbackground.png");
	scene_bg->setPosition(VISIBLE_SIZE.width / 2,VISIBLE_SIZE.height / 2);
	this->addChild(scene_bg,0);

	auto helpButton1 = Sprite :: create("Help_up.png");
	auto helpButton2 = Sprite :: create("Help_down.png");
	auto menuItemHelp = MenuItemSprite::create(helpButton1, helpButton2, [=](Ref *){
		auto scene = MenuSelect::createScene(HELP);
		Director::getInstance()->replaceScene(scene);
	});
	menuItemHelp->setPosition(170,275);
	menuItemHelp->setScale(3.0f);

	auto aboutButton1 = Sprite :: create("About_up.png");
	auto aboutButton2 = Sprite :: create("About_down.png");
	auto menuItemAbout = MenuItemSprite::create(aboutButton1, aboutButton2, [=](Ref *){
		auto scene = MenuSelect::createScene(ABOUT);
		Director::getInstance()->replaceScene(scene);
	});
	menuItemAbout->setPosition(170,210);
	menuItemAbout->setScale(3.0f);

	auto monsterButton1 = Sprite :: create("Monster_up.png");
	auto monsterButton2 = Sprite :: create("Monster_down.png");
	auto menuItemMonster = MenuItemSprite::create(monsterButton1, monsterButton1, [=](Ref *){
		auto scene = MenuSelect::createScene(MONSTER);
		Director::getInstance()->replaceScene(scene);
	});
	menuItemMonster->setPosition(170,145);
	menuItemMonster->setScale(3.0f);

	auto exitButton1 = Sprite :: create("Exit_up.png");
	auto exitButton2 = Sprite :: create("Exit_down.png");
	auto menuItemExit = MenuItemSprite::create(exitButton1, exitButton2, [=](Ref *){
		auto scene = MenuSelect::createScene(EXIT);
		Director::getInstance()->replaceScene(scene);
	});
	menuItemExit->setPosition(170,80);
	menuItemExit->setScale(3.0f);

	auto playButton1 = Sprite :: create("Play_up.png");
	auto playButton2 = Sprite::create("Play_down.png");
	auto menuItemPlay = MenuItemSprite::create(playButton1, playButton2, [=](Ref *){
		auto scene = LoadingScene :: createScene();
		Director::getInstance()->replaceScene(scene);
	});
	menuItemPlay->setPosition(465,75);
	menuItemPlay->setScale(2.0f);

	auto menu = Menu::create();
	menu->addChild(menuItemHelp);
	menu->addChild(menuItemAbout);
	menu->addChild(menuItemMonster);
	menu->addChild(menuItemExit);
	menu->addChild(menuItemPlay);	
	menu->setPosition(Point::ZERO);
	this->addChild(menu,99,147);

	return true;
}