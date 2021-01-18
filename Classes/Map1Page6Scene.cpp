#include "Map1Page6Scene.h"
#include "Terrain.h"
#include "Hero.h"
#include "MapSwitcher.h"
#include "AIManager.h"
#include "Item.h"

Scene * Map1Page6Scene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	scene->getPhysicsWorld()->setGravity(Vect(0,-600.0f));
	auto layer = Map1Page6Scene::create();
	scene->addChild(layer, -1, 13);
	return scene;
}

bool Map1Page6Scene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	
	//set background
	auto Map_Bg = Sprite::create("WaterCave.png");
	Map_Bg->setPosition(VISIBLE_SIZE.width / 2,VISIBLE_SIZE.height / 2);
	Map_Bg->setScaleX(640 / Map_Bg->getContentSize().width);
	Map_Bg->setScaleY(480 / Map_Bg->getContentSize().height);
	this->addChild(Map_Bg,0);

	//create map block
	this->createMap(Point(12.5,12.5),15,1,"grass_1.png");
	this->createMap(Point(162.5,37.5),2,4,"grass_1.png");
	this->createMap(Point(187.5,37.5),2,4,"grass_1.png");
	this->createMap(Point(212.5,37.5),2,4,"grass_1.png");
	this->createMap(Point(237.5,37.5),2,4,"grass_1.png");
	this->createMap(Point(275,125),3,1,"grass_1.png");
	this->createMap(Point(400,162.5),7,1,"grass_1.png");
	this->createMap(Point(412.5,62.5),3,1,"grass_1.png");
	this->createMap(Point(488,37.5),7,1,"grass_1.png");
	this->createMap(Point(575,162.5),3,4,"grass_1.png");
	this->createMap(Point(600,162.5),3,4,"grass_1.png");

	this->createMap(Point(487.5,262.5),4,6,"grass_1.png");

	this->createMap(Point(375,287.5),1,6,"grass_1.png");
	this->createMap(Point(300,287.5),4,6,"grass_1.png");
	this->createMap(Point(150,287.5),3,6,"grass_1.png");
	this->createMap(Point(50,337.5),2,6,"grass_1.png");
	
	//set the boundary
	//this->createMap(Point(-12.5,100),17,4,"grass_1.png");
	this->createMap(Point(-12.5,-12.5),20,4,"grass_1.png");
	this->createMap(Point(12.5,492.5),26,1,"grass_1.png");
	this->createMap(Point(692.5,262.5),10,4,"grass_1.png");

	AIManager * aim = AIManager::create();
	aim->setMapLayer(this);
	aim->setHero(MapSwitcher::getInstance()->getHero());
	aim->stopEnemy();
	this->addChild(aim, 0, 256);

	aim->createEnemy(Hero::TYPE_YEYAN, Point(112.5, 385), 10);
	aim->createEnemy(Hero::TYPE_YEYAN, Point(475, 196), 10);

	/*
	auto item = Item::create();
	item->initSprite("potion_hp.png");
	item->initPhysicsBody();
	item->setPosition(40, 370);
	this->addChild(item);
	*/

	return true;
}

bool Map1Page6Scene::isGoOtherMap()
{
	auto hero = MapSwitcher :: getInstance()->getHero();
	if(hero->getPositionX() > VISIBLE_SIZE.width)
	{
		this->nextmap = 7;
		this->postion = Point(50,50);
		return true;
	}
	else if(hero->getPositionX() < 0)
	{
		this->nextmap = 5;
		this->postion = Point(590,50);
		return true;
	}
	return false;
}

int Map1Page6Scene::nextMap()
{
	return this->nextmap;
}

const cocos2d::Point Map1Page6Scene::newPostion()
{
	return this->postion;
}