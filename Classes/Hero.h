#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"
#include "Damage.h"
typedef unsigned int uint;

class Hero : public cocos2d::Sprite {

public:
	
	static bool loadResources(); // resource loader, carried once

	// hero type
	static const int TYPE_HERO = 0;	
	static const int TYPE_YANMO = 1;
	static const int TYPE_YEYAN = 2;
	static const int TYPE_FIREYEYAN = 3;
	static const int TYPE_BOSS = 4;

	// m_iDirection parm
	static const int BTN_LEFT = 1;
	static const int BTN_RIGHT = 2;
	static const bool DIREC_LEFT = 0;
	static const bool DIREC_RIGHT = 1;

	// m_iActionStat parm, in order of priority
	static const uint DEATH = -2;
	static const uint BUSY = -1;
	static const uint NORMAL = 0; // normal
	static const uint WALK = 1; // walking
	static const uint ATTACK = 2; // attacking

	// group
	static const uint ALLY = 0;
	static const uint ENEMY = 1;

	// cool duration tag
	static const uint ACT_ATTACK = 0;

	static Hero* create(int);
	
	void initPhysicsBody(); // load a physics body

	bool initSprite(std::string);

	//group (assit damage judging)
	int getGroup();
	void setGroup(int);

	bool getDirection();
	int getType();
	
	// damage helper
	void causeDamage(float);
	bool isDead();
	void kill();

	// set button continous pressed stat
	void setWalking(bool,int);
	int isWalking();
	void setAttacking(bool,int);
	int isAttacking();

	// cool duration judge
	bool isCool(int);
	void setCool(float);
	float getCool(int);
	
	// set actual movement
	void resetAction();
	void actJump();
	void actWalk(bool, int);
	void actAttack(int);

	// update only action func
	void updateAction();

private:
	
	int m_sType; // character type
	
	std::string m_sName; // name displayed

	int m_iGroup;
	
	float m_fHpt; // health point
	
	float m_fAtk; // attack point
	
	// cool duration timer
	float m_fCool[10]; 
	float m_fTimer[10];
	cocos2d::Vect m_vcDamageOffset[10];

	int m_iActionStat; // current action
	bool m_bOnGround; // is onGround
	int m_iWalkSpeed; // walking speed
	int m_iAttacking; // attack button pressed
	int m_iWalking; // attack button pressed
	bool m_bDirection; // facing direction
	
	bool init(int); // init function                              
	
	void update(float); // update func (frame)
};

#endif