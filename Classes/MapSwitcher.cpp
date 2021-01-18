#include "MapSwitcher.h"

#include "Hero.h"
#include "JoyStick.h"
#include "Damage.h"
#include "AIManager.h"
#include "PauseLayer.h"
#include "BloodView.h"
#include "SkillButton.h"

#include "Map1Page1Scene.h"
#include "Map1Page2Scene.h"
#include "Map1Page3Scene.h"
#include "Map1Page4Scene.h"
#include "Map1Page5Scene.h"
#include "Map1Page6Scene.h"
#include "Map1Page7Scene.h"

USING_NS_CC;

MapSwitcher * MapSwitcher::instance = nullptr;

MapSwitcher * MapSwitcher::getInstance() {
	if (!MapSwitcher::instance)	MapSwitcher::instance = new MapSwitcher();
	return MapSwitcher::instance;
}

MapSwitcher::~MapSwitcher() {
	this->hero->release();
	this->rocker->release();
	for (auto & m : *(this->maps))
		m->release();
	this->maps->clear();
}

void MapSwitcher::init() {
	srand(time(0));

	this->isSwitching = true;

	this->hero = Hero::create(Hero::TYPE_HERO);
	// hero->setScale(1.0);
	this->hero->initPhysicsBody();
	this->hero->retain();

	// this->initMaps();
	
	// °´¼ü¼àÌý
	typedef EventKeyboard::KeyCode KeyCode;
	KBListener = EventListenerKeyboard::create();
	KBListener->onKeyPressed = [&](KeyCode code, Event* event){
		switch (code) {
		case KeyCode::KEY_LEFT_ARROW:
			this->hero->setWalking(true, Hero::BTN_LEFT);
			break;
		case KeyCode::KEY_RIGHT_ARROW:
			this->hero->setWalking(true, Hero::BTN_RIGHT);
			break;
		case KeyCode::KEY_UP_ARROW:
			this->hero->actJump();
			break;
		case KeyCode::KEY_DOWN_ARROW:
			this->hero->setAttacking(true, 1);
			this->curMap->getChildByTag(13)->addChild(Damage::create(this->hero, 0));
			break;
		default:
			break;
		}
	};
	KBListener->onKeyReleased = [&](KeyCode code, Event* event){
		switch (code) {
		case KeyCode::KEY_LEFT_ARROW:
			this->hero->setWalking(false, Hero::BTN_LEFT);
			break;
		case KeyCode::KEY_RIGHT_ARROW:
			this->hero->setWalking(false, Hero::BTN_RIGHT);
			break;
		case KeyCode::KEY_DOWN_ARROW:
			this->hero->setAttacking(false, 1);
			break;
		default:
			break;
		}
	};
	tDirector->getEventDispatcher()->addEventListenerWithFixedPriority(KBListener, -1000000);

	//Ìí¼ÓÒ¡¸Ë
	this->rocker = JoyStick::create();
	this->rocker->setPosition(Point::ZERO);
	this->rocker->setHero(this->hero);
	//this->rocker->retain();

	//add the pause Layer
	this->pauseLayer = PauseLayer::create();
	this->pauseLayer->retain();

	//add the UI
	this->uiLayer = Layer::create();
	this->uiLayer->retain();

	//add the skill button
	auto jumpButton = SkillButton::createSkillButton(2, "Gray_bg.png", "jump.png", "jump.png");
	jumpButton->setHero(this->hero);
	jumpButton->setSkill(JUMP);
	jumpButton->setPosition(550, 100);
	uiLayer->addChild(jumpButton, 1);

	auto attackButton = SkillButton::createSkillButton(0.5, "Gray_bg.png", "skill1.png", "skill1.png");
	attackButton->setHero(this->hero);
	attackButton->setSkill(ATTACK);
	attackButton->setPosition(490, 75);
	uiLayer->addChild(attackButton, 1);

	//Pause button
	auto pauseButton = Sprite::create("pause.png");
	auto menuItemPause = MenuItemSprite::create(pauseButton, pauseButton, [=](Ref *){
		dynamic_cast<MapScene *>(this->curMap->getChildByTag(13))->addChildAndRecord(this->pauseLayer, 5, 14);
		Director::getInstance()->pause();
	});
	menuItemPause->setPosition(VISIBLE_SIZE.width - pauseButton->getContentSize().width / 2,VISIBLE_SIZE.height - pauseButton->getContentSize().height / 2);
	auto menu = Menu::create(menuItemPause, NULL);
	menu->setPosition(Point::ZERO);
	uiLayer->addChild(menu, 1, 108);

	auto m_pBloodView = new BloodView();
	m_pBloodView->setPosition(ccp(150, 450));
	m_pBloodView->setScale(1.5f);
	m_pBloodView->setBackgroundTexture("hp1.png");
	m_pBloodView->setForegroundTexture("hp2.png");
	m_pBloodView->setTotalProgress(100.0f);
	m_pBloodView->setCurrentProgress(100.0f);
	m_pBloodView->setVisible(false);
	uiLayer->addChild(m_pBloodView, 2);

	uiLayer->addChild(rocker, 5, 110);

	Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
}

void MapSwitcher::setHero(Hero * hero) {
	this->hero = hero;
}

Hero * MapSwitcher::getHero() {
	return this->hero;
}

Layer * MapSwitcher::getUILayer() {
	return this->uiLayer;
}

/*
JoyStick * MapSwitcher::getRocker() {
	return this->rocker;
}
*/

void MapSwitcher::setSwitching(bool isSwitching) {
	this->isSwitching = isSwitching;
}


Scene * MapSwitcher::getCurMap() {
	return this->curMap;
}

void MapSwitcher::setCurMap(int mapType) {
	this->curMapNum = curMapNum;
	this->curMap = maps->at(mapType-1);
}

void MapSwitcher::update(float delta) {
	if (isSwitching)	return;
	auto preMap = dynamic_cast<MapScene *>(curMap->getChildByTag(13));
	bool isOut = preMap->isGoOtherMap();

	// CCLOG("%d", isOut);
	if (isOut) {
		this->isSwitching = true;
		dynamic_cast<AIManager *>(curMap->getChildByTag(13)->getChildByTag(256))->stopEnemy();
		this->setCurMap(preMap->nextMap());
		auto newPos = preMap->newPostion();
		preMap->clearNodes();

		this->hero->resetAction();
		this->hero->setWalking(false, Hero::BTN_LEFT);
		this->hero->setWalking(false, Hero::BTN_RIGHT);

		// CCLOG("test");
		this->hero->setPosition(newPos);
		dynamic_cast<MapScene *>(curMap->getChildByTag(13))->addChildAndRecord(hero, 1, 16);
		dynamic_cast<MapScene *>(curMap->getChildByTag(13))->addChildAndRecord(uiLayer, 2, 999);
		
		tDirector->setSendCleanupToScene(false);
		tDirector->replaceScene(curMap);

		dynamic_cast<AIManager *>(curMap->getChildByTag(13)->getChildByTag(256))->startEnemy();

		this->isSwitching = false;
	}
}

MapSwitcher::MapSwitcher() {
	this->init();
}

void MapSwitcher::initMaps() {
	MapScene::loadResources();

	this->maps = new std::vector<Scene *>();

	auto map11 = Map1Page1Scene::createScene();
	map11->retain();
	this->maps->push_back(map11);

	auto map12 = Map1Page2Scene::createScene();
	map12->retain();
	this->maps->push_back(map12);

	auto map13 = Map1Page3Scene::createScene();
	map13->retain();
	this->maps->push_back(map13);

	auto map14 = Map1Page4Scene::createScene();
	map14->retain();
	this->maps->push_back(map14);

	auto map15 = Map1Page5Scene::createScene();
	map15->retain();
	this->maps->push_back(map15);

	auto map16 = Map1Page6Scene::createScene();
	map16->retain();
	this->maps->push_back(map16);

	auto map17 = Map1Page7Scene::createScene();
	map17->retain();
	this->maps->push_back(map17);

	CCLOG("Map loaded");
}