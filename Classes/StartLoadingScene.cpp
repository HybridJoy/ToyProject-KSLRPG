#include "StartLoadingScene.h"
#include "GameStartScene.h"
#include "Hero.h"

#define MM MapBuilder :: getInstance()

Scene * StartLoadingScene :: createScene()
{
	auto scene = Scene :: create();
	auto layer = StartLoadingScene :: create();
	scene->addChild(layer);
	return scene;
}

bool StartLoadingScene :: init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	Hero::loadResources();

	auto title = Sprite :: create("Title.png");
	title->setPosition(VISIBLE_SIZE.width / 2,VISIBLE_SIZE.height / 2 + title->getContentSize().height * 2);
	title->setScale(2.0f);
	this->addChild(title,0);

	auto icon = Sprite::createWithSpriteFrameName("YanMo.png");
	icon->setPosition(50,VISIBLE_SIZE.height / 2 - 60);
	this->addChild(icon,1);

	auto move1 = MoveTo :: create(0.5f,Point(150,VISIBLE_SIZE.height / 2));
	auto move2 = MoveTo :: create(0.5f,Point(250,VISIBLE_SIZE.height / 2 - 60));
	auto move3 = MoveTo :: create(0.5f,Point(350,VISIBLE_SIZE.height / 2));
	auto move4 = MoveTo :: create(0.5f,Point(450,VISIBLE_SIZE.height / 2 - 60));
	auto move5 = MoveTo :: create(0.5f,Point(550,VISIBLE_SIZE.height / 2));
	auto move6 = MoveTo :: create(0.5f,Point(650,VISIBLE_SIZE.height / 2 - 60));

	auto callFunc = CallFunc::create([=]()
	{
		tDirector->setSendCleanupToScene(true);
		tDirector->replaceScene(GameStartScene :: createScene());
	});

	icon->runAction(Sequence :: create(move1,move2,move3,move4,move5,move6,RemoveSelf :: create(),callFunc,nullptr));
	return true;
}