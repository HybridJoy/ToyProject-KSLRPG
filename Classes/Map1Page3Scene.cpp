#include "Map1Page3Scene.h"
#include "Terrain.h"
#include "Hero.h"
#include "MapSwitcher.h"
#include "AIManager.h"

Scene * Map1Page3Scene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	scene->getPhysicsWorld()->setGravity(Vect(0, -600.0f));
	auto layer = Map1Page3Scene::create();
	scene->addChild(layer, -1, 13);
	return scene;
}

bool Map1Page3Scene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	//set background
	auto Map_Bg = Sprite::create("Evile.png");
	Map_Bg->setPosition(VISIBLE_SIZE.width/2, VISIBLE_SIZE.height/2);
	Map_Bg->setScaleX(2.4f);
	Map_Bg->setScaleY(3.09f);
	this->addChild(Map_Bg, 0);
	
	//create map block
	this->createMap(Point(12.5, 5), 15, 1, "stone.png");
	this->createMap(Point(627.5, 30.5), 9, 6, "stone.png");
	this->createMap(Point(627.5, 100), 6, 6, "stone.png");
	this->createMap(Point(627.5, 160), 2, 6, "stone.png");
	this->createMap(Point(627.5, 225), 4, 6, "stone.png");
	this->createMap(Point(327.5, 87.5), 7, 6, "stone.png");
	this->createMap(Point(152.5, 102.5), 2, 6, "stone.png");
	this->createMap(Point(52.5, 127.5), 3, 6, "stone.png");
	this->createMap(Point(152.5, 180), 14, 1, "stone.png");
	this->createMap(Point(327.5, 205), 7, 4, "stone.png");
	this->createMap(Point(12.5, 245), 7, 1, "stone.png");
	this->createMap(Point(87.5, 310), 6, 1, "stone.png");
	this->createMap(Point(277.5, 327.5), 2, 1, "stone.png");
	this->createMap(Point(377.5, 327.5), 8, 1, "stone.png");
	this->createMap(Point(425, 385), 4, 6, "stone.png");
	this->createMap(Point(502.5, 402.5), 7, 1, "stone.png");

	//Set the boundary

	//this->createMap(Point(-12.5, 127.5), 15, 4);
	this->createMap(Point(-12.5, -12.5), 20, 4, "stone.png");
	this->createMap(Point(12.5, 492.5), 26, 1, "stone.png");
	this->createMap(Point(652.5, 402.5), 20, 5, "stone.png");

	AIManager * aim = AIManager::create();
	aim->setMapLayer(this);
	aim->setHero(MapSwitcher::getInstance()->getHero());
	aim->stopEnemy();
	this->addChild(aim, 0, 256);

	aim->createEnemy(Hero::TYPE_YEYAN, Point(150, 350), 20);
	aim->createEnemy(Hero::TYPE_YEYAN, Point(250, 120), 10);
	aim->createEnemy(Hero::TYPE_YEYAN, Point(415, 215), 20);
	return true;
}

bool Map1Page3Scene::isGoOtherMap()
{
	auto hero = MapSwitcher :: getInstance()->getHero();
	if(hero->getPositionX() > VISIBLE_SIZE.width)
	{
		this->nextmap = 4;
		this->postion = Point(50,450);
		return true;
	}
	else if(hero->getPositionX() < 0)
	{
		this->nextmap = 2;
		this->postion = Point(590,460);
		return true;
	}
	return false;
}

int Map1Page3Scene::nextMap()
{
	return this->nextmap;
}

const cocos2d::Point Map1Page3Scene::newPostion()
{
	return this->postion;
}