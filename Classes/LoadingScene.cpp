#include "LoadingScene.h"
#include "MapSwitcher.h"
#include "MapScene.h"
#include "Hero.h"
#include "AIManager.h"

Scene * LoadingScene :: createScene()
{
	auto scene = Scene :: create();
	auto layer = LoadingScene :: create();
	scene->addChild(layer);
	return scene;
}

bool LoadingScene :: init ()
{
	if ( !Layer::init() )
	{
		return false;
	}

	srand((unsigned int)time(0));
	int bg_type = rand() % 9;
	std :: string scene_bg;
	switch(bg_type)
	{
		case 0: scene_bg = "Beach.png";break;
		case 1: scene_bg = "BloodyCave.png";break;
		case 2: scene_bg = "DarkCave.png";break;
		case 3: scene_bg = "Evile.png";break;
		case 4: scene_bg = "FireCave.png";break;
		case 5: scene_bg = "Heaven.png";break;
		case 6: scene_bg = "Moutains.png";break;
		case 7: scene_bg = "StarNight.png";break;
		case 8: scene_bg = "WaterCave.png";break;
	}
	auto Loading_Bg = Sprite :: create(scene_bg);
	Loading_Bg->setPosition(VISIBLE_SIZE.width / 2,VISIBLE_SIZE.height / 2);
	Loading_Bg->setScaleX(640 / Loading_Bg->getContentSize().width);
	Loading_Bg->setScaleY(480 / Loading_Bg->getContentSize().height);
	this->addChild(Loading_Bg,0);

	
	auto icon = Sprite::createWithSpriteFrameName("YanMo.png");
	icon->setPosition(VISIBLE_SIZE.width - 80,80);
	this->addChild(icon,1);

	auto animation = Animation :: create();
	animation->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("YanMo.png"));
	animation->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("YanMo_hit1.png"));
	animation->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("YanMo_hit2.png"));
	animation->setDelayPerUnit(0.5f);
	animation->setLoops(2);
	
	auto ms =  MapSwitcher::getInstance();
	ms->initMaps();
	ms->setCurMap(1);
	auto map = ms->getCurMap();
	auto layer = dynamic_cast<MapScene *>(map->getChildByTag(13));
	auto hero = ms->getHero();
	hero->setPosition(50, 300);
	layer->addChildAndRecord(hero, 0, 16);
	layer->addChildAndRecord(ms->getUILayer(), 1, 123);
	dynamic_cast<AIManager *>(map->getChildByTag(13)->getChildByTag(256))->startEnemy();

	icon->runAction(Sequence::create(Animate :: create(animation),
		RemoveSelf::create(),
		CallFunc::create([=]() {
			tDirector->setSendCleanupToScene(true);
			CCLOG("%d\n", map==nullptr);
			tDirector->replaceScene(map);
	}),
		CallFunc::create([](){ MapSwitcher::getInstance()->setSwitching(false); }),
		nullptr
	));
	return true;
	/*
	if(Type == 0)
	{
		icon->setSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("hero1.png"));
		icon->setPosition(visiblesize.width - 30,40);
		this->addChild(icon,1);
		animation->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("hero1.png"));
		animation->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("hero2.png"));
		animation->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("hero_run.png"));
		animation->setLoops(4);
		icon->runAction(Animate::create(animation));
	}
	*/
}