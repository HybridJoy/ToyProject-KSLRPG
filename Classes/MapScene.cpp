#include "MapSwitcher.h"

#include "Hero.h"

#include "MapScene.h"
#include "Terrain.h"

USING_NS_CC;

bool MapScene::loadResources() {
	static bool done = false;
	if (done) return 0;
	// load resources here
	tSpriteFrameCache->addSpriteFramesWithFile("grass_1.png");
	tSpriteFrameCache->addSpriteFramesWithFile("brick_1.png");
	tSpriteFrameCache->addSpriteFramesWithFile("DarkMask.png");
	// tSpriteFrameCache->addSpriteFramesWithFile("asd.plist");

	done = true;
	return true;
}

void MapScene::addChildAndRecord(Node * node, int z, int tag) {
	this->addChild(node, z, tag);
	this->nodes.push_back(node);
}

void MapScene::clearNodes() {
	for (auto & n : this->nodes) {
		n->removeFromParentAndCleanup(false);
	}
	this->nodes.clear();
}

void MapScene::createMap(Point pos, int num, int type, std::string mapBlock)
{
	int x_varaition, y_varaition, vec;
	switch (type) {
	case 1:
		x_varaition = 25;
		y_varaition = 0;
		vec = -12.5;
		break;
	case 2:
		x_varaition = 25;
		y_varaition = 25;
		break;
	case 3:
		x_varaition = 25;
		y_varaition = -25;
		break;
	case 4:
		x_varaition = 0;
		y_varaition = 25;
		vec = 12.5;
		break;
	case 5:
		x_varaition = 0;
		y_varaition = -25;
		break;
	case 6:
		x_varaition = -25;
		y_varaition = 0;
		break;
	case 7:
		x_varaition = -25;
		y_varaition = 25;
		break;
	case 8:
		x_varaition = -25;
		y_varaition = -25;
		break;
	default:
		break;
	}
	switch (type)
	{
	case 2:
	case 3:
	case 7:
	case 8:
		for (int i = 0; i < num; i++) {
			auto ground = ::Terrain::create();
			ground->initSprite(mapBlock);
			float x = pos.x + x_varaition * i;
			float y = pos.y + y_varaition * i;
			ground->initAreaPhysicsBody(Point(x - 12.5, y + 12.5), Point(x + 12.5, y - 12.5));
			ground->setPosition(x, y);
			ground->setScaleX(0.5f);
			ground->setScaleY(0.5f);
			ground->getTexture()->setAliasTexParameters();
			this->addChild(ground, 1);
		}
		break;
	case 1:
	case 4:
	case 5:
	case 6:
		for (int i = 0; i < num; i++) {
			auto ground = Sprite::create(mapBlock);
			float x = pos.x + x_varaition * i;
			float y = pos.y + y_varaition * i;
			ground->setPosition(x, y);
			ground->setScaleX(0.5f);
			ground->setScaleY(0.5f);
			ground->getTexture()->setAliasTexParameters();
			this->addChild(ground, 1);
		}
		float x1, y1, x2, y2;
		auto t = ::Terrain::create();
		t->initSprite("transparent.png");
		if (type == 4 || type == 6) {
			x1 = pos.x + (num - 1) * x_varaition - 12.5;
			y1 = pos.y + (num - 1) * y_varaition + 12.5;
			x2 = pos.x + 12.5;
			y2 = pos.y - 12.5;
		}
		if (type == 1 || type == 5) {
			x1 = pos.x - 12.5;
			y1 = pos.y + 12.5;
			x2 = pos.x + (num - 1) * x_varaition + 12.5;
			y2 = pos.y + (num - 1) * y_varaition - 12.5;
		}
		t->setPosition((x1 + x2) / 2, (y1 + y2) / 2);
		t->initAreaPhysicsBody(Point(x1, y1), Point(x2, y2));
		this->addChild(t, 1);
		break;
	}
}

//void MapScene::setMask(float delta) {
//	Hero * hero = (Hero *)this->getChildByTag(16);
//	m_spMask->setPosition(hero->getPosition());
//}

/*
bool MapScene::isGoOtherMap() {
	if (!this->getChildByTag(16))	return false;
	auto heroPos = this->getChildByTag(16)->getPosition();
	if (heroPos.x > VISIBLE_SIZE.width || heroPos.x < 0)	return true;
	return false;
}

int MapScene::nextMap() {
	auto num = rand()%7+1;
	CCLOG("%d", num);
	return num;
}

const cocos2d::Point & MapScene::newPostion() {
	return Point(50, 350);
}
*/