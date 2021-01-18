#include "Map1Page7Scene.h"
#include "Terrain.h"
#include "Hero.h"
#include "MapSwitcher.h"
#include "AIManager.h"

Scene * Map1Page7Scene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	scene->getPhysicsWorld()->setGravity(Vect(0, -600.0f));
	auto layer = Map1Page7Scene::create();
	scene->addChild(layer, -1, 13);
	return scene;
}

bool Map1Page7Scene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//tSpriteFrameCache->addSpriteFramesWithFile("hero.plist");

	auto Map_Bg = Sprite::create("StarNight.png");
	Map_Bg->setPosition(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2);
	Map_Bg->setScaleX(640 / Map_Bg->getContentSize().width);
	Map_Bg->setScaleY(480 / Map_Bg->getContentSize().height);
	this->addChild(Map_Bg, 0);

	//create map block
	this->createMap(Point(12.5, 0), 5, 1,"grass_1.png");
	this->createMap(Point(12.5, 320), 2, 1, "brick_1.png");
	this->createMap(Point(25, 90), 2, 1, "brick_1.png");
	this->createMap(Point(12.5, 200), 1, 1, "brick_1.png");
	this->createMap(Point(87.5, 365), 5, 1, "stone.png");
	this->createMap(Point(87.5, 255), 3, 1, "brick_1.png");

	this->createMap(Point(125, 155), 2, 1, "brick_1.png");
	this->createMap(Point(137.5, 0), 3, 4, "stone.png");
	this->createMap(Point(262.5, 80), 3, 4, "stone.png");
	this->createMap(Point(262.5, 190), 2, 1, "brick_1.png");
	this->createMap(Point(262.5, 320), 8, 1, "stone.png");
	this->createMap(Point(287.5, 130), 12, 1, "stone.png");
	this->createMap(Point(362.5, 230), 2, 1, "brick_1.png");
	this->createMap(Point(450, 380), 3, 1, "brick_1.png");
	this->createMap(Point(475, 240), 3, 1, "brick_1.png");
	this->createMap(Point(500, 420), 3, 1, "brick_1.png");
	this->createMap(Point(587.5, 80), 3, 4, "stone.png");
	this->createMap(Point(600, 300), 2, 1, "brick_1.png");

	//set the boundary
	//this->createMap(Point(-12.5,100),17,4);
	this->createMap(Point(-12.5, -12.5), 17, 4, "grass_1.png");
	this->createMap(Point(12.5, 492.5), 26, 1, "grass_1.png");
	this->createMap(Point(652.5, 0), 20, 4, "grass_1.png");

	AIManager * aim = AIManager::create();
	aim->setMapLayer(this);
	aim->setHero(MapSwitcher::getInstance()->getHero());
	aim->stopEnemy();
	this->addChild(aim, 0, 256);

	/*
	auto hero = Hero::create("Hero");
	hero->initSprite("hero1.png");
	hero->setPosition(40,50);
	hero->initPhysicsBody();
	hero->setScale(0.25f);
	this->addChild(hero,1,3);

	typedef EventKeyboard::KeyCode KeyCode;
	auto kbListener = EventListenerKeyboard::create();
	kbListener->onKeyPressed = [=](KeyCode code, Event* event){
		switch (code) {
		case KeyCode::KEY_LEFT_ARROW:
			hero->setWalking(true, Hero::BTN_LEFT);
			break;
		case KeyCode::KEY_RIGHT_ARROW:
			hero->setWalking(true, Hero::BTN_RIGHT);
			break;
		case KeyCode::KEY_UP_ARROW:
			hero->actJump();
			break;
		default:
			break;
		}
	};

	kbListener->onKeyReleased = [=](KeyCode code, Event* event){
		switch (code) {
		case KeyCode::KEY_LEFT_ARROW:
			hero->setWalking(false, Hero::BTN_LEFT);
			break;
		case KeyCode::KEY_RIGHT_ARROW:
			hero->setWalking(false, Hero::BTN_RIGHT);
			break;
		default:
			break;
		}
	};

	tDirector->getEventDispatcher()->addEventListenerWithSceneGraphPriority(kbListener, this);
	*/

	return true;
}

bool Map1Page7Scene::isGoOtherMap()
{
	auto hero = MapSwitcher :: getInstance()->getHero();
	if(hero->getPositionX() > VISIBLE_SIZE.width)
	{
		this->nextmap = 1;
		this->postion = Point(50,50);
	}
	else if(hero->getPositionX() < 0)
	{
		this->nextmap = 6;
		this->postion = Point(590,50);
	}
	return false;
}

int Map1Page7Scene::nextMap()
{
	return this->nextmap;
}

const cocos2d::Point Map1Page7Scene::newPostion()
{
	return this->postion;
}