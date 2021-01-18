#include "Terrain.h"

bool ::Terrain::loadResources() {
	static bool done = false;
	if(done) return 0;
	// load resources here

	done = 1;
	return 1;
}

bool ::Terrain::init() {
	//Terrain::loadResources();
	loadResources();
	return 1;
}

void ::Terrain::initPhysicsBody() {
	auto body = PhysicsBody::createBox(this->getContentSize());
	body->setGravityEnable(false); // Terrain cant afforded by gravity
	body->setDynamic(false);
	body->getShape(0)->setRestitution(0.0f);
	body->setCategoryBitmask(1);
	body->setCollisionBitmask(15);
	body->setContactTestBitmask(0);
	this->setPhysicsBody(body);
}

bool ::Terrain::initSprite(std::string name) {
	return this->initWithFile(name);
}

void ::Terrain :: initAreaPhysicsBody(Point left_top,Point right_bottom)
{
	auto body = PhysicsBody :: createEdgeBox(Size(right_bottom.x - left_top.x,right_bottom.y - left_top.y));
	body->setGravityEnable(false); // Terrain cant afforded by gravity
	body->setDynamic(false);
	body->getShape(0)->setRestitution(0.0f);
	this->setPhysicsBody(body);
}