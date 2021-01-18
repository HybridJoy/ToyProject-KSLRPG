#include "Map1Page2Scene.h"
#include "Terrain.h"
#include "Hero.h"
#include "MapSwitcher.h"
#include "AIManager.h"

Scene * Map1Page2Scene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	scene->getPhysicsWorld()->setGravity(Vect(0,-600.0f));
	auto layer = Map1Page2Scene::create();
	scene->addChild(layer, -1, 13);
	return scene;
}

bool Map1Page2Scene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	
	//set the background
	auto Map_Bg = Sprite::create("Beach.png");
	Map_Bg->setPosition(VISIBLE_SIZE.width / 2,VISIBLE_SIZE.height / 2);
	Map_Bg->setScaleX(2.4f);
	Map_Bg->setScaleY(3.09f);
	this->addChild(Map_Bg,0);

	//create map block
	this->createMap(Point(12.5, 12.5), 26, 1,"sand.png");
	this->createMap(Point(12.5, 75), 4, 1, "sand.png");
	this->createMap(Point(12.5, 225), 5, 1, "sand.png");
	this->createMap(Point(12.5, 300), 5, 1, "sand.png");
	this->createMap(Point(137, 140), 5, 1,"sand.png");
	this->createMap(Point(262.5, 37.5), 8, 4, "stone.png");
	this->createMap(Point(287.5, 212.5), 10, 1, "sand.png");
	this->createMap(Point(287.5, 90), 8, 1, "sand.png");
	this->createMap(Point(287.5, 390), 8, 6, "sand.png");
	this->createMap(Point(502.5, 330), 10, 6, "sand.png");
	this->createMap(Point(627.5, 70), 4, 6, "sand.png");
	this->createMap(Point(627.5, 155.5), 3, 6,"sand.png");
	this->createMap(Point(627.5, 270), 4, 6,"sand.png");
	this->createMap(Point(627.5, 390), 11, 6,"sand.png");


	//Set the boundary
	//this->createMap(Point(-12.5, 75), 20, 4);
	this->createMap(Point(-12.5, -12.5), 20, 4, "sand.png");
	this->createMap(Point(12.5, 492.5), 26, 1, "sand.png");
	this->createMap(Point(652.5, 430), 20, 5, "sand.png");

	AIManager * aim = AIManager::create();
	aim->setMapLayer(this);
	aim->setHero(MapSwitcher::getInstance()->getHero());
	aim->stopEnemy();
	this->addChild(aim, 0, 256);

	aim->createEnemy(Hero::TYPE_YEYAN, Point(204, 430), 50);
	aim->createEnemy(Hero::TYPE_YEYAN, Point(312.5, 237.5), 10);
	aim->createEnemy(Hero::TYPE_YEYAN, Point(312.5, 162.5), 10);

	return true;
}

bool Map1Page2Scene::isGoOtherMap()
{
	auto hero = MapSwitcher :: getInstance()->getHero();
	if(hero->getPositionX() > VISIBLE_SIZE.width)
	{
		this->nextmap = 3;
		this->postion = Point(50,50);
		return true;
	}
	else if(hero->getPositionX() < 0)
	{
		this->nextmap = 1;
		this->postion = Point(590,50);
		return true;
		
	}
	return false;
}

int Map1Page2Scene::nextMap()
{
	return this->nextmap;
}

const cocos2d::Point Map1Page2Scene::newPostion()
{
	
	return this->postion;
}