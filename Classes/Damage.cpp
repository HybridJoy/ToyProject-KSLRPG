#include "Damage.h"

#include "CommonData.h"

#include "Hero.h"

USING_NS_CC;

bool Damage::loadResources() {
	static bool done = false;
	if(done) return 0;
	// load resources here

	done = 1;
	return 1;
}

bool Damage::init(Hero * hero, int type) {
	if (!Sprite::init())	return false;

	this->hero = hero;
	this->group = hero->getGroup();

	this->dir = hero->getDirection();

	auto body = this->getPhysicsBody();
	auto heroPos = hero->getPosition();
	auto heroSize = hero->getContentSize();

	switch (type)
	{
	case(DAMAGE_HERO_1):
		this->initSprite("bullet.png");
		this->setScale(2.0);
		this->initPhysicsBody();
		this->m_fDamageValue = 5;
		this->setPosition(heroPos + (dir ? Point(heroSize.width/2, 0) : Point(-heroSize.width/2, 0)));
		this->runAction(Sequence::create(MoveBy::create(1.0f, Point(dir ? 320 : -320, 0)), RemoveSelf::create(), nullptr));
		break;
	case(DAMAGE_HERO_2):
		this->initSprite("bullet.png");
		this->initPhysicsBody();
		this->m_fDamageValue = 5;
		this->setPosition(heroPos + (dir ? Point(heroSize.width/2, 0) : Point(-heroSize.width/2, 0)));
		this->runAction(Sequence::create(DelayTime::create(1.0f), RemoveSelf::create(), nullptr));
		break;
	case(DAMAGE_HERO_3):
		this->initSprite("bullet.png");
		this->initPhysicsBody();
		this->m_fDamageValue = 5;
		this->setPosition(heroPos + (dir ? Point(heroSize.width/2, 0) : Point(-heroSize.width/2, 0)));
		this->runAction(Sequence::create(DelayTime::create(1.0f), RemoveSelf::create(), nullptr));
		break;
	case(DAMAGE_BOSS_1):
		this->initSprite("BigFire.png");
		this->initPhysicsBody();
		this->m_fDamageValue = 0.5;
		this->setPosition(heroPos + (dir ? Point(heroSize.width/2, 0) : Point(-heroSize.width/2, 0)));
		this->runAction(Sequence::create(DelayTime::create(1.0f), RemoveSelf::create(), nullptr));
		break;
	case(DAMAGE_BOSS_2):
		this->initSprite("BigFire.png");
		this->initPhysicsBody();
		this->m_fDamageValue = 0.5;
		this->setPosition(heroPos + (dir ? Point(heroSize.width/2, 0) : Point(-heroSize.width/2, 0)));
		this->runAction(Sequence::create(DelayTime::create(1.0f), RemoveSelf::create(), nullptr));
		break;
	case(DAMAGE_FIREYEYAN):
		this->initSprite("Fireyeyan_bullet.png");
		this->initPhysicsBody();
		this->m_fDamageValue = 0.5;
		this->runAction(Sequence::create(MoveBy::create(1.0f, Point(dir ? 260 : -300, 0)), RemoveSelf::create(), nullptr));
		break;
	case(DAMAGE_YANMO):
		// this->initSprite("BigFire.png");
		this->setContentSize(Size(3, 5));
		this->initPhysicsBody();
		this->m_fDamageValue = 0.5;
		this->setPosition(heroPos + ( dir ? Point(heroSize.width/4, -15) : Point(-heroSize.width/4, -15)));
		this->runAction(Sequence::create(MoveBy::create(0.2f, Point(dir ? 8 : -8, 0)), RemoveSelf::create(), nullptr));
		break;
	case(DAMAGE_YEYAN):
		this->initSprite("yeyan_bullet.png");
		this->initPhysicsBody();
		this->m_fDamageValue = 0.5;
		this->setPosition(heroPos + ( dir ? Point(heroSize.width/2, 5) : Point(-heroSize.width/2, 5)));
		this->runAction(Sequence::create(MoveBy::create(1.0f, Point(dir ? 260 : -300, 0)), RemoveSelf::create(), nullptr));
		break;
	default:
		break;
	}

	this->schedule(CC_SCHEDULE_SELECTOR(Damage::disCheck), 0.1f);

	return true;
}

bool Damage::initSprite(std::string name) {
	SpriteFrame* spFrame = nullptr;
	if( spFrame = tSpriteFrameCache->getSpriteFrameByName(name) ){
		this->initWithSpriteFrame(spFrame);
		this->setContentSize(this->getTextureRect().size);
		return 1;
	}
	CCLOG("SpriteFrameName Fail");
	//if( this->initWithFile(name) ){
	//	this->setContentSize(this->getTextureRect().size);
	//	return 1;
	//}
	return 0;
}

void Damage::initPhysicsBody() {
	auto body = PhysicsBody::createBox(this->getContentSize());
	/*body->getShape(0)->setRestitution(0.0f);
	body->getShape(0)->setFriction(100.0f);*/
	body->setRotationEnable(false);
	body->setGravityEnable(false);
	body->setCategoryBitmask(PhysicsMask::damage);
	body->setContactTestBitmask(PhysicsMask::hero);
	body->setCollisionBitmask(0);
	this->setPhysicsBody(body);
}

Damage * Damage::create(Hero * hero, int type) {
	auto damage = new Damage();
	if (damage && damage->init(hero, type)) {
		damage->autorelease();
		return damage;
	}
	CC_SAFE_DELETE(damage);
	return nullptr;
}

float Damage::getDamageValue() {
	return this->m_fDamageValue;
}

void Damage::disCheck(float delta) {
	auto func = [](PhysicsWorld& world, PhysicsShape& shape, void* userData)->bool
	{
		//Return true from the callback to continue rect queries
		auto a = shape.getBody();
		auto b = static_cast<Damage *>(userData)->getPhysicsBody();
		if(b->getCategoryBitmask()==PhysicsMask::damage 
			&& a->getCategoryBitmask()==PhysicsMask::hero)
			std::swap(a,b);
		if(a->getCategoryBitmask()==PhysicsMask::damage 
			&& b->getCategoryBitmask()==PhysicsMask::hero)
		{
			if (((Hero*)b->getNode())->getGroup() == ((Damage *)a->getNode())->getGroup())	return false;
			((Hero*)b->getNode())->causeDamage(static_cast<Damage *>(userData)->getDamageValue());
			// this->m_fDamageValue=0;
			static_cast<Damage *>(userData)->unscheduleAllCallbacks();
			static_cast<Damage *>(userData)->removeFromParentAndCleanup(true);
			return false;
		}

		return true;
	};

	Director::getInstance()->getRunningScene()->getPhysicsWorld()->queryRect(func, Rect(this->getPosition().x,this->getPosition().y, 25, 25), this);
}

int Damage::getGroup() {
	return this->group;
}