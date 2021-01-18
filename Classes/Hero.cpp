#include "Hero.h"
#include "Damage.h"
#include "CommonData.h"
USING_NS_CC;

Hero* Hero::create(int type) {
	auto hero = new Hero();
	if(hero && hero->init(type)) {
		hero->autorelease();
		return hero;
	}
	CC_SAFE_DELETE(hero);
	return nullptr;
}

void Hero::initPhysicsBody() {
	
	// set body with Texture size at scale
	auto size = this->getContentSize();
	size.width *= this->getScaleX();
	size.height *= this->getScaleY();
	auto body = PhysicsBody::createBox(size);
	//auto body = PhysicsBody::createBox(Size(40, 40));
	body->getShape(0)->setRestitution(0.0f);
	body->getShape(0)->setFriction(0.0f);
	body->setCategoryBitmask(2);
	body->setContactTestBitmask(1);
	body->setCollisionBitmask(1);
	body->setRotationEnable(false);

	this->setPhysicsBody(body);

	/*EventListenerPhysicsContact* evListener = EventListenerPhysicsContact::create();
	evListener->onContactBegin = [this] (PhysicsContact& contact) { return true; };
	evListener->onContactPostSolve = [this] (PhysicsContact& contact, const PhysicsContactPostSolve& postsolve) {
		CCLOG("Post Solve\n");
		this->getPhysicsBody()->resetForces();
	};
	evListener->onContactSeperate = [this](PhysicsContact& contact){
		CCLOG("Seperate\n");
		Vect v = this->getPhysicsBody()->getVelocity();
		v.x = 0;
		this->getPhysicsBody()->setVelocity(v);
		this->actWalk(true, this->m_iWalking);
	};
	tDirector->getEventDispatcher()->addEventListenerWithSceneGraphPriority(evListener, this);*/
}

bool Hero::initSprite(std::string name) {
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

void Hero::setWalking(bool stat, int btn) {

	if(stat) while(!(m_iWalking&btn)) m_iWalking ^= btn;
	if(!stat) while(m_iWalking&btn) m_iWalking ^= btn;
	//CCLOG("stat:%d btn:%d iWalk:%d\n", stat, btn, m_iWalking);
	
	if(m_iWalking&Hero::BTN_LEFT) m_bDirection = Hero::DIREC_LEFT;
	if(m_iWalking&Hero::BTN_RIGHT) m_bDirection = Hero::DIREC_RIGHT;
	if((m_iWalking&Hero::BTN_LEFT) && (m_iWalking&Hero::BTN_RIGHT))
		m_bDirection = btn==Hero::BTN_LEFT ?  Hero::DIREC_LEFT : Hero::DIREC_RIGHT;
	this->setFlippedX(!m_bDirection);
	
	if (!stat && m_sType==Hero::TYPE_HERO) {
		CCLOG("%.2f %.2f \n", this->getPositionX(), this->getPositionY());
	}
}

int Hero::isWalking() {
	// have speed in x-direction
	return this->m_iWalking;
}

void Hero::setAttacking(bool stat, int btn) {
	//if(stat) while(!(this->m_iAttacking&btn)) this->m_iAttacking ^= btn;
	//if(!stat) while(this->m_iAttacking&btn) this->m_iAttacking ^= btn;
	if(stat) this->m_iAttacking = 1;
	else this->m_iAttacking = 0;
}

int Hero::isAttacking() { return this->m_iAttacking; }

bool Hero::isCool(int atk) { return this->m_fTimer[atk] < 0.01f;}

void Hero::setCool(float delt) { 
	for(int i=0; i<10 && this->m_fCool[i]>0.0f; i++) {
		if(this->m_fTimer[i] > 0.01f) {
			this->m_fTimer[i] -= delt;
			if(this->m_fTimer[i] < 0.01f) 
				this->m_fTimer[i] = 0.0f;
		}
	}
}

float Hero::getCool(int atk) { return this->m_fTimer[atk]; }

void Hero::resetAction() {
	this->m_iActionStat = Hero::NORMAL;
}

void Hero::actJump() {
	if(!this->m_bOnGround) return;
	Vect v = this->getPhysicsBody()->getVelocity() + Vect(0, 300);
	this->getPhysicsBody()->setVelocity(v);
}

void Hero::actWalk(bool b, int walkMask) {
	Vect v = getPhysicsBody()->getVelocity();
	m_iWalkSpeed = 0;
	if(b) {
		if(walkMask & Hero::BTN_LEFT) m_iWalkSpeed += -100;
		if(walkMask & Hero::BTN_RIGHT) m_iWalkSpeed += 100;
	}
	v.x = m_iWalkSpeed;
	this->getPhysicsBody()->setVelocity(v);
}

void Hero::actAttack(int atk){
	//auto damage = Damage::create(this, atk);
	// pos damage here
	this->m_fTimer[atk] = this->m_fCool[atk];
}

int Hero::getGroup() { return this->m_iGroup; }

void Hero::setGroup(int group) { this->m_iGroup = group; }

bool Hero::getDirection() {
	return this->m_bDirection;
}

int Hero::getType() {
	return this->m_sType;
}

void Hero::causeDamage(float d) {
	this->m_fHpt -= d;
	if(this->isDead()) {
		this->kill();
	}
}

bool Hero::isDead() { return this->m_fHpt < 0.1f; }

void Hero::kill() {
	this->m_iActionStat = Hero::DEATH;
	this->stopAllActions();
	this->actWalk(false, m_iWalking);
	auto callFun = CallFunc::create([=]{
		// death 
		// get into gameover scene
		this->removeFromParentAndCleanup(true);
	});
	auto action = Animate::create(
		tAnimationCache->getAnimation(
			StringUtils::format("Death_%d", this->m_sType)
		)
	);
	this->runAction( Sequence::create( action, callFun, nullptr));
}

void Hero::updateAction() {
	this->stopAllActions();
	Animation* anim = nullptr;
	auto setToNormal = CallFunc::create([this](){
		this->m_iActionStat = Hero::NORMAL;
		this->updateAction();
	});
	switch (this->m_iActionStat)
	{
	case Hero::NORMAL:
		//CCLOG("updateAction Normal\n");
		if(this->m_bOnGround){
			anim = tAnimationCache->getAnimation(StringUtils::format("Normal_%d", m_sType));
			this->runAction( Animate::create(anim) );
		} else { 
			//hero on air normal
			anim = tAnimationCache->getAnimation(StringUtils::format("Jump_%d", m_sType));
			this->runAction( Animate::create(anim) );
		}
		break;
	case Hero::WALK:
		//CCLOG("updateAction Walk\n");
		if(this->m_bOnGround) {
			// play walking
			anim = tAnimationCache->getAnimation(StringUtils::format("Walk_%d", m_sType));
			this->runAction( Animate::create(anim) );
		}
		else {
			// play normal(on air)
			anim = tAnimationCache->getAnimation(StringUtils::format("Jump_%d", m_sType));
			this->runAction( Animate::create(anim) );
		}
		break;
	case Hero::ATTACK:
		//CCLOG("updateAction Attack\n");
		// play attack (cant move)
		this->m_iActionStat = Hero::BUSY; // wont be interupt
		anim = tAnimationCache->getAnimation(StringUtils::format("Attack_%d", m_sType));
		this->runAction( Sequence::create(Animate::create(anim), setToNormal, nullptr) );
		break;
	default:
		break;
	}

	return;
}

void Hero::update(float delta) {
	//CCLOG("Refresh Frames\n");
	bool actionShiftFlag = false;

	//check on ground stat
	bool oldOnGround = m_bOnGround;
	if(abs(this->getPhysicsBody()->getVelocity().y)>0.01f)
		this->m_bOnGround = false;
	else
		this->m_bOnGround = true;
	actionShiftFlag |= (oldOnGround!= m_bOnGround);
		// on ground shift -> updateAction

	if(m_iActionStat == Hero::DEATH) return;

	// execute in action priority
	if(m_iActionStat != Hero::BUSY)
	{
		int oldStat = m_iActionStat;
		m_iActionStat = Hero::NORMAL; // reset Action every frame
		if(m_iWalking) m_iActionStat = Hero::WALK;
		if(m_iAttacking && isCool(Hero::ACT_ATTACK)){
			this->actAttack(Hero::ACT_ATTACK);
			m_iActionStat = Hero::ATTACK;
		}
		actionShiftFlag |= (oldStat!=m_iActionStat);
		// action update
		if(actionShiftFlag) {
			updateAction();
		}
		// control actual moving
		if(m_iWalking) {
			if(!m_bOnGround) actWalk(true, m_iWalking);
			else actWalk(m_iActionStat == Hero::WALK, m_iWalking);
		}
		else actWalk(false, m_iWalking);
	}

}

bool Hero::init(int type) {
	Hero::loadResources();

	// data init
	this->m_iActionStat = Hero::NORMAL;
	this->m_iAttacking = 0;
	this->m_iWalking = 0;
	this->m_bDirection = Hero::DIREC_LEFT;
	this->m_iWalkSpeed = 0;
	for(int i=0; i<10; i++) this->m_fTimer[i] = this->m_fCool[i] = 0.0f;
	for(int i=0; i<10; i++) this->m_vcDamageOffset[i] = Vect(0,0);
	
	// data load
	/*this->m_sType = type;
	this->m_fHpt = 10.0f;
	this->m_fAtk = 10.0f;
	this->m_fCool[Hero::ACT_ATTACK] = 0.2f;
	this->m_iGroup = Hero::ALLY;*/

	this->m_sType = type;
	switch (type)
	{
	case TYPE_HERO:
		this->m_fHpt = 10.0f;
		this->m_fAtk = 10.0f;
		this->m_fCool[Hero::ACT_ATTACK] = 0.6f;
		this->m_iGroup = Hero::ALLY;
		this->initSprite("hero1.png");
		this->setTag(16);
		break;
	case TYPE_YANMO:
		this->m_fHpt = 10.0f;
		this->m_fAtk = 10.0f;
		this->m_fCool[Hero::ACT_ATTACK] = 0.6f;
		this->initSprite("YanMo.png");
		this->setScale(0.5f);
		this->m_iGroup = Hero::ENEMY;
		break;
	case TYPE_YEYAN:
		this->m_fHpt = 10.0f;
		this->m_fAtk = 10.0f;
		this->m_fCool[Hero::ACT_ATTACK] = 0.6f;
		this->initSprite("yeyan.png");
		this->m_iGroup = Hero::ENEMY;
		break;
	case TYPE_FIREYEYAN:
		this->m_fHpt = 10.0f;
		this->m_fAtk = 10.0f;
		this->m_fCool[Hero::ACT_ATTACK] = 0.2f;
		this->m_iGroup = Hero::ENEMY;
		break;
	case TYPE_BOSS:
		this->m_fHpt = 10.0f;
		this->m_fAtk = 10.0f;
		this->m_fCool[Hero::ACT_ATTACK] = 0.2f;
		this->initSprite("boss_come2.png");
		this->m_iGroup = Hero::ENEMY;
		break;
	default:
		return 1;
		break;
	}

	schedule(CC_SCHEDULE_SELECTOR(Hero::setCool), 0.1f);
	this->updateAction();
	//schedule(schedule_selector(setCool), 0.1f);
	this->scheduleUpdate();
	return 1;
}

bool Hero::loadResources() {
	static bool done = false;
	if(done) return 0;
	// load resources here

	tSpriteFrameCache->addSpriteFramesWithFile("hero.plist");
	tSpriteFrameCache->addSpriteFramesWithFile("YanMo.plist");
	tSpriteFrameCache->addSpriteFramesWithFile("YeYan.plist");
	tSpriteFrameCache->addSpriteFramesWithFile("Boss.plist");

	// animation init
	Animation* anim = nullptr;
	int curType = -1;

	// hero anim
	curType = Hero::TYPE_HERO;

	anim = Animation::create();
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("hero1.png"));
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("hero2.png"));
	anim->setDelayPerUnit(1.0f);
	anim->setLoops(-1);
	tAnimationCache->addAnimation(anim, StringUtils::format("Normal_%d", curType));
	
	anim = Animation::create();
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("hero_jump.png"));
	anim->setDelayPerUnit(1.0f);
	anim->setLoops(-1);
	tAnimationCache->addAnimation(anim, StringUtils::format("Jump_%d", curType));
	
	anim = Animation::create();
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("hero_run.png"));
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("hero1.png"));
	anim->setDelayPerUnit(AnimDelay::walk);
	anim->setLoops(-1);
	tAnimationCache->addAnimation(anim, StringUtils::format("Walk_%d", curType));
	
	anim = Animation::create();
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("hero_shoot.png"));
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("hero_shoot1.png"));
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("hero_shoot2.png"));
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("hero1.png"));
	anim->setDelayPerUnit(AnimDelay::attack);
	anim->setLoops(1);
	tAnimationCache->addAnimation(anim, StringUtils::format("Attack_%d", curType));

	anim = Animation::create();
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("hero_down.png"));
	for(int i=2; i<4; i++)
		anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName(
			StringUtils::format("hero_down%d.png", i)
		));
	anim->setDelayPerUnit(0.2f);
	anim->setLoops(1);
	tAnimationCache->addAnimation(anim, StringUtils::format("Death_%d", curType));

	// YanMo anim
	curType = Hero::TYPE_YANMO;

	anim = Animation::create();
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("YanMo.png"));
	anim->setDelayPerUnit(1.0f);
	anim->setLoops(-1);
	tAnimationCache->addAnimation(anim, StringUtils::format("Normal_%d", curType));
	
	anim = Animation::create();
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("YanMo.png"));
	anim->setDelayPerUnit(1.0f);
	anim->setLoops(-1);
	tAnimationCache->addAnimation(anim, StringUtils::format("Jump_%d", curType));
	
	anim = Animation::create();
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("YanMo_DieandRun.png"));
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("YanMo.png"));
	anim->setDelayPerUnit(AnimDelay::walk);
	anim->setLoops(-1);
	tAnimationCache->addAnimation(anim, StringUtils::format("Walk_%d", curType));
	
	anim = Animation::create();
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("YanMo_hit1.png"));
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("YanMo_hit2.png"));
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("YanMo.png"));
	anim->setDelayPerUnit(AnimDelay::attack);
	anim->setLoops(1);
	tAnimationCache->addAnimation(anim, StringUtils::format("Attack_%d", curType));

	anim = Animation::create();
	for(int i=0; i<4; i++)
		anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName(
			StringUtils::format("YanMo_Die%d.png", i)
		));
	anim->setDelayPerUnit(0.1f);
	anim->setLoops(1);
	tAnimationCache->addAnimation(anim, StringUtils::format("Death_%d", curType));

	// YeYan
	curType = Hero::TYPE_YEYAN;

	anim = Animation::create();
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("yeyan.png"));
	anim->setDelayPerUnit(1.0f);
	anim->setLoops(-1);
	tAnimationCache->addAnimation(anim, StringUtils::format("Normal_%d", curType));
	
	anim = Animation::create();
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("yeyan.png"));
	anim->setDelayPerUnit(1.0f);
	anim->setLoops(-1);
	tAnimationCache->addAnimation(anim, StringUtils::format("Jump_%d", curType));
	
	anim = Animation::create();
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("yeyan_run.png"));
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("yeyan.png"));
	anim->setDelayPerUnit(AnimDelay::walk);
	anim->setLoops(-1);
	tAnimationCache->addAnimation(anim, StringUtils::format("Walk_%d", curType));
	
	anim = Animation::create();
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("yeyan_hit.png"));
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("yeyan_hit.png"));
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("yeyan.png"));
	anim->setDelayPerUnit(AnimDelay::attack);
	anim->setLoops(1);
	tAnimationCache->addAnimation(anim, StringUtils::format("Attack_%d", curType));

	anim = Animation::create();
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("yeyan.png"));
	for(int i=1; i<3; i++)
		anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName(
			StringUtils::format("yeyan_down%d.png", i)
		));
	anim->setDelayPerUnit(0.2f);
	anim->setLoops(1);
	tAnimationCache->addAnimation(anim, StringUtils::format("Death_%d", curType));

	// Boss
	curType = Hero::TYPE_BOSS;

	anim = Animation::create();
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("boss2.png"));
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("boss1.png"));
	anim->setDelayPerUnit(1.0f);
	anim->setLoops(-1);
	tAnimationCache->addAnimation(anim, StringUtils::format("Normal_%d", curType));
	
	anim = Animation::create();
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("boss_jump.png"));
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("boss1.png"));
	anim->setDelayPerUnit(1.0f);
	anim->setLoops(-1);
	tAnimationCache->addAnimation(anim, StringUtils::format("Jump_%d", curType));
	
	anim = Animation::create();
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("boss3.png"));
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("boss1.png"));
	anim->setDelayPerUnit(AnimDelay::walk);
	anim->setLoops(-1);
	tAnimationCache->addAnimation(anim, StringUtils::format("Walk_%d", curType));

	anim = Animation::create();
	for(int i=1; i<4; i++)
		anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName(
			StringUtils::format("boss_fire%d.png",i)
		));
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("boss_fire3.png"));
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("boss1.png"));
	anim->setDelayPerUnit(AnimDelay::attack);
	anim->setLoops(1);
	tAnimationCache->addAnimation(anim, StringUtils::format("Attack_%d", curType));
	
	anim = Animation::create();
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("boss_wind1.png"));
	for(int i=0; i<5; i++)
		anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("boss_wind2.png"));
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("boss1.png"));
	anim->setDelayPerUnit(AnimDelay::attack);
	anim->setLoops(1);
	tAnimationCache->addAnimation(anim, StringUtils::format("Attack1_%d", curType));

	anim = Animation::create();
	anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName("boss1.png"));
	for(int i=1; i<4; i++)
		anim->addSpriteFrame(tSpriteFrameCache->getSpriteFrameByName(
			StringUtils::format("boss_down%d.png", i)
		));
	anim->setDelayPerUnit(0.2f);
	anim->setLoops(1);
	tAnimationCache->addAnimation(anim, StringUtils::format("Death_%d", curType));

	CCLOG("Hero::loadResources done\n");
	done = 1;
	return 1;
}