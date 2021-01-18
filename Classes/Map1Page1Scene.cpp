#include "Map1Page1Scene.h"
#include "Terrain.h"
#include "Hero.h"
#include "MapSwitcher.h"
#include "AIManager.h"
USING_NS_CC;

Scene * Map1Page1Scene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	scene->getPhysicsWorld()->setGravity(Vect(0,-600.0f));
	auto layer = Map1Page1Scene::create();
	scene->addChild(layer, -1, 13);
	return scene;
}

bool Map1Page1Scene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	auto Map_Bg = Sprite::create("Heaven.png");
	Map_Bg->setPosition(VISIBLE_SIZE.width / 2,VISIBLE_SIZE.height / 2);
	Map_Bg->setScaleX(2.4f);
	Map_Bg->setScaleY(3.09f);
	this->addChild(Map_Bg,0);

	this->createMap(Point(12.5, 12.5), 26, 4,"brick_1.png");
	this->createMap(Point(37.5, 12.5), 7, 1,"grass_1.png");
	this->createMap(Point(302.5, 12.5), 14, 1,"grass_1.png");
	this->createMap(Point(162.5, 75), 7, 1,"grass_1.png");

	AIManager * aim = AIManager::create();
	aim->setMapLayer(this);
	aim->setHero(MapSwitcher::getInstance()->getHero());
	aim->stopEnemy();
	this->addChild(aim, 0, 256);
	aim->createEnemy(Hero::TYPE_YEYAN, Point(240, 130), 30);
	aim->createEnemy(Hero::TYPE_YEYAN, Point(500, 75), 50);

	//m_spMask = Sprite::create("DarkMask.png");
	//CC_ASSERT(m_spMask!=nullptr);
	//m_spMask->setScale(20);
	//this->addChild(m_spMask, 3);
	//this->schedule(schedule_selector(MapScene::setMask), 0.015f);

	return true;
}

bool Map1Page1Scene::isGoOtherMap()
{
	auto hero = MapSwitcher :: getInstance()->getHero();
	if(hero->getPositionX() > VISIBLE_SIZE.width)
	{
		this->nextmap = 2;
		this->postion = Point(50,50);
		return true;
	}
	return false;
}

int Map1Page1Scene::nextMap()
{
	return this->nextmap;
}

const cocos2d::Point Map1Page1Scene::newPostion()
{

	return this->postion;
}