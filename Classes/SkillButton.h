#ifndef _SKILLBUTTON_H_
#define _SKILLBUTTON_H_
#include <cocos2d.h>
#include "Hero.h"

typedef enum
{
	JUMP,
	ATTACK
}Skill_type;

class SkillButton : public cocos2d::CCNode
{
public:
	SkillButton();
	virtual ~SkillButton();
	//Create skill button
	static SkillButton* createSkillButton(float cdTime,
		const char* stencil_file_name,
		const char* button_normal_name,
		const char* button_click_name);

	void setCDTime(float time) { mCDTime = time; }
	float getCDTime() const { return mCDTime; }

	void skillClickCallBack(cocos2d::CCObject* obj);

	void skillCoolDownCallBack(cocos2d::CCNode* node);

	void setSkill(Skill_type type);
	void setHero(Hero*);						

private:
	bool init(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name);

private:
	cocos2d::CCMenuItemImage*   mItemSkill;    
	cocos2d::CCMenu*            mMenuSkill;     
	cocos2d::CCSprite*          mStencil;       
	cocos2d::CCProgressTimer*   mProgressTimer; 
	float                       mCDTime;    
	Skill_type m_SkillType;
	Hero* hero;									
};
#endif