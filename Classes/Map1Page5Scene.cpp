#include "Map1Page5Scene.h"
#include "Terrain.h"
#include "Hero.h"
#include "MapSwitcher.h"
#include "AIManager.h"

Scene * Map1Page5Scene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	scene->getPhysicsWorld()->setGravity(Vect(0, -600.0f));
	auto layer = Map1Page5Scene::create();
	scene->addChild(layer, -1, 13);
	return scene;
}

bool Map1Page5Scene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	//set background
	auto Map_Bg = Sprite::create("Moutains.png");
	Map_Bg->setPosition(VISIBLE_SIZE.width/2, VISIBLE_SIZE.height/2);
	Map_Bg->setScaleX(2.4f);
	Map_Bg->setScaleY(3.09f);
	this->addChild(Map_Bg, 0);

	//create map block
	this->createMap(Point(12.5, 0), 7, 1, "grass_1.png");
	this->createMap(Point(12.5, 75), 3, 1, "grass_1.png");
	this->createMap(Point(12.5, 190), 1, 1, "grass_1.png");
	this->createMap(Point(12.5, 320), 2, 1, "grass_1.png");
	this->createMap(Point(87.5, 137.5), 3, 1, "grass_1.png");
	this->createMap(Point(87.5, 255), 3, 1, "grass_1.png");
	this->createMap(Point(112.5, 375), 3, 1, "grass_1.png");

	this->createMap(Point(187.5, 0), 16, 4, "grass_1.png");
	this->createMap(Point(187.5, 175), 3, 1, "grass_1.png");

	this->createMap(Point(212.5, 0), 18, 1, "grass_1.png");

	this->createMap(Point(252.5, 235), 3, 1, "grass_1.png");
	this->createMap(Point(312.5, 375), 5, 4, "grass_1.png");

	this->createMap(Point(337.5, 295), 2, 1, "grass_1.png");
	this->createMap(Point(387.5, 295), 2, 2, "grass_1.png");
	this->createMap(Point(412.5, 185), 6, 1, "grass_1.png");
	this->createMap(Point(412.5, 345), 6, 1, "grass_1.png");

	this->createMap(Point(537.5, 405), 5, 1, "grass_1.png");

	this->createMap(Point(550, 260), 4, 1, "grass_1.png");
	this->createMap(Point(550, 235), 5, 5, "grass_1.png");
	this->createMap(Point(400, 110), 3, 5, "grass_1.png");
	this->createMap(Point(375, 60), 4, 6, "grass_1.png");

	//set the boundary

	//this->createMap(Point(-12.5, 60), 18, 4);
	this->createMap(Point(-12.5, -12.5), 20, 4,"grass_1.png");
	this->createMap(Point(12.5, 492.5), 26, 1, "grass_1.png");
	this->createMap(Point(652.5, 100), 17, 4, "grass_1.png");

	AIManager * aim = AIManager::create();
	aim->setMapLayer(this);
	aim->setHero(MapSwitcher::getInstance()->getHero());
	aim->stopEnemy();
	this->addChild(aim, 0, 256);

	aim->createEnemy(Hero::TYPE_YANMO, Point(110, 170), 10);
	aim->createEnemy(Hero::TYPE_YANMO, Point(110, 290), 10);
	aim->createEnemy(Hero::TYPE_YEYAN, Point(470, 395), 10);
	aim->createEnemy(Hero::TYPE_YEYAN, Point(475, 220), 10);
	aim->createEnemy(Hero::TYPE_YEYAN, Point(485, 35), 10);
	// aim->createEnemy(Hero::TYPE_YANMO, Point(485, 35), 10);
	return true;
}

bool Map1Page5Scene::isGoOtherMap()
{
	auto hero = MapSwitcher :: getInstance()->getHero();
	if(hero->getPositionX() > VISIBLE_SIZE.width)
	{
		this->nextmap = 6;
		this->postion = Point(50,50);
		return true;
	}
	else if(hero->getPositionX() < 0)
	{
		this->nextmap = 4;
		this->postion = Point(50,50);
		return true;
	}
	return false;
}

int Map1Page5Scene::nextMap()
{
	return this->nextmap;
}

const cocos2d::Point Map1Page5Scene::newPostion()
{
	return this->postion;
}