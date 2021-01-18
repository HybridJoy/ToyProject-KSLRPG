#include "Map1Page4Scene.h"
#include "Terrain.h"
#include "Hero.h"
#include "MapSwitcher.h"
#include "AIManager.h"

Scene * Map1Page4Scene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	scene->getPhysicsWorld()->setGravity(Vect(0, -600.0f));
	auto layer = Map1Page4Scene::create();
	scene->addChild(layer, -1, 13);
	return scene;
}

bool Map1Page4Scene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	//set background
	auto Map_Bg = Sprite::create("DarkCave.png");
	Map_Bg->setPosition(VISIBLE_SIZE.width/2, VISIBLE_SIZE.height/2);
	Map_Bg->setScaleX(2.4f);
	Map_Bg->setScaleY(3.09f);
	this->addChild(Map_Bg, 0);

	//create map block
	this->createMap(Point(12.5, 427.5), 3, 1, "clay.png");
	this->createMap(Point(37.5, 377.5), 3, 1, "clay.png");
	this->createMap(Point(162.5, 377.5), 3, 1, "clay.png");
	this->createMap(Point(262.5, 377.5), 6, 1, "clay.png");
	this->createMap(Point(462.5, 377.5), 4, 1, "clay.png");
	this->createMap(Point(512.5, 402.5), 2, 1, "clay.png");
	this->createMap(Point(587.5, 327.5), 2, 1, "clay.png");
	this->createMap(Point(587.5, 302.5), 3, 5, "clay.png");
	this->createMap(Point(562.5, 252.5), 4, 6, "clay.png");
	this->createMap(Point(437.5, 202.5), 3, 6, "clay.png");
	this->createMap(Point(337.5, 202.5), 3, 6, "clay.png");
	this->createMap(Point(237.5, 202.5), 7, 6, "clay.png");
	this->createMap(Point(12.5, 127.5), 4, 1, "clay.png");
	this->createMap(Point(162.5, 102.5), 5, 1, "clay.png");
	this->createMap(Point(262.5, 76), 3, 5, "clay.png");
	this->createMap(Point(262.5, 0), 17, 1, "clay.png");
	this->createMap(Point(330.5, 70), 5, 1, "clay.png");
	this->createMap(Point(475, 100), 5, 1, "clay.png");
	this->createMap(Point(580, 150), 4, 1, "clay.png");

	//set the boundary

	//this->createMap(Point(-12.5, 427.5), 18, 5);
	this->createMap(Point(-12.5, 492.5), 20, 5, "clay.png");
	this->createMap(Point(12.5, 492.5), 26, 1, "clay.png");
	this->createMap(Point(652.5, 150), 15, 4, "clay.png");

	AIManager * aim = AIManager::create();
	aim->setMapLayer(this);
	aim->setHero(MapSwitcher::getInstance()->getHero());
	aim->stopEnemy();
	this->addChild(aim, 0, 256);
	aim->createEnemy(Hero::TYPE_YEYAN, Point(170, 240), 20);
	aim->createEnemy(Hero::TYPE_YEYAN, Point(435, 25), 80);
	aim->createEnemy(Hero::TYPE_YEYAN, Point(355.5, 90), 10);
	aim->createEnemy(Hero::TYPE_YEYAN, Point(323, 415), 10);
	aim->createEnemy(Hero::TYPE_YEYAN, Point(470, 380), 20);


	return true;
}

bool Map1Page4Scene::isGoOtherMap()
{
	auto hero = MapSwitcher :: getInstance()->getHero();
	if(hero->getPositionX() > VISIBLE_SIZE.width)
	{
		
		this->nextmap = 5;
		this->postion = Point(50,25);
		return true;
	}
	else if(hero->getPositionX() < 0)
	{
		this->nextmap = 3;
		this->postion = Point(590,50);
		return true;
	}
	return false;
}

int Map1Page4Scene::nextMap()
{
	return this->nextmap;
}

const cocos2d::Point Map1Page4Scene::newPostion()
{
	return this->postion;
}