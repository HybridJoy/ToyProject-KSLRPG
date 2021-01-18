#ifndef _SKILLBUTTON_H_
#define _SKILLBUTTON_H_
#include <cocos2d.h>
#include "Hero.h"
using namespace cocos2d;
typedef enum
{
	JUMP,
	ATTACK
}Skill_type;

class SkillButton : public Node
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

	void skillClickCallBack(Ref* obj);

	void skillCoolDownCallBack(Node* node);

	void setSkill(Skill_type type);
	void setHero(Hero*);						

private:
	bool init(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name);

private:
	MenuItemImage*   mItemSkill;    
	Menu*            mMenuSkill;     
	Sprite*          mStencil;       
	ProgressTimer*   mProgressTimer; 
	float                       mCDTime;    
	Skill_type m_SkillType;
	Hero* hero;									
};
#endif