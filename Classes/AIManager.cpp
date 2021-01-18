#include "AIManager.h"

#include "CommonData.h"

#include "MapSwitcher.h"

#include "Hero.h"
#include "Damage.h"

USING_NS_CC;


AIManager::AIManager() {
}

AIManager::~AIManager() {
	delete meleeBusyEnemies, meleeBusyEnemies;
	delete rangedFreeEnemies, rangedBusyEnemies;
}

bool AIManager::init() {
	if (!Node::init())	return false;
	this->meleeFreeEnemies = new std::vector<std::pair<Hero *, float *> >;
	this->meleeBusyEnemies = new std::vector<std::pair<Hero *, float *> >;
	this->rangedFreeEnemies = new std::vector<std::pair<Hero *, float *> >;
	this->rangedBusyEnemies = new std::vector<std::pair<Hero *, float *> >;

	this->startEnemy();

	return true;
}

void AIManager::stopEnemy() {
	this->unscheduleAllSelectors();
}

void AIManager::startEnemy() {
	this->schedule(schedule_selector(AIManager::updateStatus), 0.1f);
	this->schedule(schedule_selector(AIManager::patrol), 0.2f);
	this->schedule(schedule_selector(AIManager::trackAndAttack), 0.5f);
}

void AIManager::setHero(Hero * hero) {
	this->hero = hero;
}

void AIManager::setMapLayer(Layer * mapLayer) {
	this->mapLayer = mapLayer;
}

void AIManager::createEnemy(int type, const Point & enePos, const float & range) {
	auto enemy = Hero::create(type);
	enemy->initPhysicsBody();
	enemy->setPosition(enePos);
	this->mapLayer->addChild(enemy);
	float * posInfo = new float[3];
	posInfo[0] = enePos.x, posInfo[1] = enePos.y, posInfo[2] = range;
	switch(type) {
	case(Hero::TYPE_YANMO): 
		this->meleeFreeEnemies->push_back(std::make_pair(enemy, posInfo));
		break;
	case(Hero::TYPE_YEYAN): 
		this->rangedFreeEnemies->push_back(std::make_pair(enemy, posInfo));
		break;
	case(Hero::TYPE_FIREYEYAN): 
		this->rangedFreeEnemies->push_back(std::make_pair(enemy, posInfo));
		break;
	case(Hero::TYPE_BOSS): 
		this->meleeFreeEnemies->push_back(std::make_pair(enemy, posInfo));
		break;
	}
	enemy->setWalking(true, rand()%2 ? Hero::BTN_LEFT : Hero::BTN_RIGHT);
}

void AIManager::createEnemy(int type, const float & enePosX, const float & enePosY, const float & range) {
	this->createEnemy(type, Point(enePosX, enePosY), range);
}

bool AIManager::calcDis(Hero * enemy) {
	auto ePos = enemy->getPosition();
	auto disX = abs( this->hero->getPosition().x - ePos.x );
	auto disY = abs( this->hero->getPosition().y - ePos.y );
	if (disY > 15.0) return false;
	else return disX < 300;
}

void AIManager::stopAct(Hero * enemy) {
	enemy->resetAction();
	enemy->setWalking(false, Hero::BTN_LEFT);
	enemy->setWalking(false, Hero::BTN_RIGHT);
	enemy->setAttacking(false, Hero::ATTACK);
}

void AIManager::updateStatus(float delta) {
	if (hero->isDead()) {
		auto endPic = Sprite::create("GameOver.png");
		endPic->setAnchorPoint(Point::ZERO);
		endPic->setScaleX(640 / endPic->getContentSize().width);
		endPic->setScaleY(480 / endPic->getContentSize().height);
		hero->kill();
		MapSwitcher::getInstance()->getCurMap()->getChildByTag(13)->addChild(endPic, 10000);
	}

	// CCLOG("test");
	// meleeEnemies status
	for (int i = 0; i < this->meleeFreeEnemies->size(); ++i) {
		if (meleeFreeEnemies->at(i).first->isDead()) {
			meleeFreeEnemies->at(i).first->kill();
			std::swap(meleeFreeEnemies->at(i), meleeFreeEnemies->at(meleeFreeEnemies->size()-1));
			this->meleeFreeEnemies->pop_back();
		}
		else {
			auto dis = this->calcDis(this->meleeFreeEnemies->at(i).first);
			if (dis) {
				this->meleeBusyEnemies->push_back(this->meleeFreeEnemies->at(i));
				this->meleeFreeEnemies->erase(meleeFreeEnemies->begin()+i);
			}
		}
	}
	for (int i = 0; i < meleeBusyEnemies->size(); ++i) {
		if (meleeBusyEnemies->at(i).first->isDead()) {
			meleeBusyEnemies->at(i).first->kill();
			std::swap(meleeBusyEnemies->at(i), meleeBusyEnemies->at(meleeBusyEnemies->size()-1));
			this->meleeBusyEnemies->pop_back();
		}
		else {
			auto dis = this->calcDis(this->meleeBusyEnemies->at(i).first);
			if (!dis) {
				this->meleeFreeEnemies->push_back(this->meleeBusyEnemies->at(i));
				this->meleeBusyEnemies->erase(meleeBusyEnemies->begin()+i);
			}
		}
	}

	// rangedEnemies status
	for (int i = 0; i < this->rangedFreeEnemies->size(); ++i) {
		if (rangedFreeEnemies->at(i).first->isDead()) {
			rangedFreeEnemies->at(i).first->kill();
			std::swap(rangedFreeEnemies->at(i), rangedFreeEnemies->at(rangedFreeEnemies->size()-1));
			this->rangedFreeEnemies->pop_back();
		}
		else {
			auto dis = this->calcDis(this->rangedFreeEnemies->at(i).first);
			if (dis) {
				this->rangedBusyEnemies->push_back(this->rangedFreeEnemies->at(i));
				this->rangedFreeEnemies->erase(rangedFreeEnemies->begin()+i);
			}
		}
	}
	for (int i = 0; i < rangedBusyEnemies->size(); ++i) {
		if (rangedBusyEnemies->at(i).first->isDead()) {
			rangedBusyEnemies->at(i).first->kill();
			std::swap(rangedBusyEnemies->at(i), rangedBusyEnemies->at(rangedBusyEnemies->size()-1));
			this->rangedBusyEnemies->pop_back();
		}
		else {
			auto dis = this->calcDis(this->rangedBusyEnemies->at(i).first);
			if (!dis) {
				this->rangedFreeEnemies->push_back(this->rangedBusyEnemies->at(i));
				this->rangedBusyEnemies->erase(rangedBusyEnemies->begin()+i);
			}
		}
	}
}

void AIManager::patrol(float delta) {
	for (auto & e : *(this->meleeFreeEnemies)) {
		// CCLOG("%f", e.first->getPositionX() - e.second[0]);
		if (e.first->getPositionX() - e.second[0] > e.second[2]) {
			// out right range
			this->stopAct(e.first);
			e.first->setWalking(true, Hero::BTN_LEFT);
		}
		else if (e.second[0] - e.first->getPositionX() > e.second[2]) {
			// out left range
			this->stopAct(e.first);
			e.first->setWalking(true, Hero::BTN_RIGHT);
		}
	}
	for (auto & e : *(this->rangedFreeEnemies)) {
		// CCLOG("%f", e.first->getPositionX() - e.second[0]);
		if (e.first->getPositionX() - e.second[0] > e.second[2]) {
			// out right range
			this->stopAct(e.first);
			e.first->setWalking(true, Hero::BTN_LEFT);
		}
		else if (e.second[0] - e.first->getPositionX() > e.second[2]) {
			// out left range
			this->stopAct(e.first);
			e.first->setWalking(true, Hero::BTN_RIGHT);
		}
	}
}

void AIManager::trackAndAttack(float delta) {
	/*auto detectCallBack = [](PhysicsWorld& world, PhysicsShape& shape, void* userData) -> bool {
		auto nodeA = shape.getBody()->getNode();
		if (nodeA) {
			if (nodeA->getTag() == 16) {
				auto hero =  static_cast<Hero *>(userData);
				auto dis = nodeA->getPosition().x - hero->getPosition().x;
				hero->setWalking(true, dis < 0 ? Hero::BTN_LEFT : Hero::BTN_RIGHT);
				Director::getInstance()->getScheduler()->schedule(
					[dis, hero](float delta) {
						hero->setWalking(false, dis < 0 ? Hero::BTN_LEFT : Hero::BTN_RIGHT);
					},
					hero->getParent(), 1.0f, 1, 0.5, false, "stopRunning"
				);
				return false;
			}
		}
		return true;
	};*/
	for (auto & e : *(this->meleeBusyEnemies)) {
		this->stopAct(e.first);
		auto ePos = e.first->getPosition();
		auto disX = hero->getPosition().x - ePos.x;
			e.first->setWalking(true, disX < 0 ? Hero::BTN_LEFT : Hero::BTN_RIGHT);
		if (abs(disX) < 120) {
			e.first->stopAllActions();
			e.first->setWalking(false, disX < 0 ? Hero::BTN_LEFT : Hero::BTN_RIGHT);
			e.first->setAttacking(true, Hero::ATTACK);
			switch(e.first->getType()) {
			case(Hero::TYPE_YANMO):
				mapLayer->addChild(Damage::create(e.first, Damage::DAMAGE_YANMO));
				break;
			case(Hero::TYPE_YEYAN):
				mapLayer->addChild(Damage::create(e.first, Damage::DAMAGE_YEYAN));
				break;
			case(Hero::TYPE_FIREYEYAN):
				mapLayer->addChild(Damage::create(e.first, Damage::DAMAGE_FIREYEYAN));
				break;
			case(Hero::TYPE_BOSS):
				mapLayer->addChild(Damage::create(e.first, Damage::DAMAGE_BOSS_1));
				break;
			}
		}
		if (disX >= 200)	e.first->setAttacking(false, Hero::ATTACK);

	}

	for (auto & e : *(this->rangedBusyEnemies)) {
		this->stopAct(e.first);
		auto ePos = e.first->getPosition();
		auto disX = hero->getPosition().x - ePos.x;
			e.first->setWalking(true, disX < 0 ? Hero::BTN_LEFT : Hero::BTN_RIGHT);
		if (abs(disX) < 250) {
			e.first->stopAllActions();
			e.first->setWalking(false, disX < 0 ? Hero::BTN_LEFT : Hero::BTN_RIGHT);
			e.first->setAttacking(true, Hero::ATTACK);

			switch(e.first->getType()) {
			case(Hero::TYPE_YANMO):
				mapLayer->addChild(Damage::create(e.first, Damage::DAMAGE_YANMO));
				break;
			case(Hero::TYPE_YEYAN):
				mapLayer->addChild(Damage::create(e.first, Damage::DAMAGE_YEYAN));
				break;
			case(Hero::TYPE_FIREYEYAN):
				mapLayer->addChild(Damage::create(e.first, Damage::DAMAGE_FIREYEYAN));
				break;
			case(Hero::TYPE_BOSS):
				mapLayer->addChild(Damage::create(e.first, Damage::DAMAGE_BOSS_1));
				break;
			}
		}
		if (disX >= 320)	e.first->setAttacking(false, Hero::ATTACK);
	}
}
