#include "Item.h"
USING_NS_CC;

bool Item::loadResources() {
	static bool done = false;
	if(done) return 0;
	// load resources here

	done = 1;
	return 1;
}

bool Item::init() {
	Item::loadResources();

	this->scheduleUpdate();

	return true;
}

void Item::initPhysicsBody() {
	auto body = PhysicsBody::createBox(this->getContentSize());
	body->getShape(0)->setRestitution(0.0f);
	body->getShape(0)->setFriction(0.0f);
	body->setRotationEnable(false);
	this->setPhysicsBody(body);

	body->setCategoryBitmask(8);
	body->setCollisionBitmask(2);
	body->setContactTestBitmask(1);
	body->setGravityEnable(true);
}

bool Item::initSprite(std::string name) {
	return this->initWithFile(name);
}

void Item::update(float delta) {
	auto heroPos = this->getParent()->getChildByTag(16)->getPosition();
	auto itemPos = this->getPosition();
	auto disX = heroPos.x-itemPos.x, disY = heroPos.y-itemPos.y;
	if (sqrt(disX*disX+disY*disY) < 200) {
		float vx = disX > 0 ? 200.0f : -200.0f;
		float vy = abs(disX/vx)*300.0 + disY*2.0;
		this->getPhysicsBody()->setVelocity(Vect(vx, vy));
	}
	else if (sqrt(disX*disX + disY*disY) < 10) {
		this->runAction(RemoveSelf::create());
	}
	
	return;
}