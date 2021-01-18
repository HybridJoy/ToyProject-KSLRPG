#include "SkillButton.h"
#include "MapSwitcher.h"

USING_NS_CC;

SkillButton::SkillButton() :
mItemSkill(NULL),
mMenuSkill(NULL),
mStencil(NULL),
mProgressTimer(NULL),
mCDTime(1.f)
{

}
SkillButton::~SkillButton()
{

}

SkillButton* SkillButton::createSkillButton(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name)
{
	SkillButton* skillButton = new SkillButton();
	if (skillButton && skillButton->init(cdTime, stencil_file_name, button_normal_name, button_click_name))
	{
		skillButton->autorelease();
		return skillButton;
	}
	else
	{
		delete skillButton;
		skillButton = NULL;
	}

	return NULL;
}

bool SkillButton::init(float cdTime, const char* stencil_file_name, const char* button_normal_name, const char* button_click_name)
{
	//Add skll button
	mItemSkill = MenuItemImage::create(button_normal_name, button_click_name, CC_CALLBACK_1(SkillButton::skillClickCallBack, this));
	mItemSkill->setPosition(Point::ZERO);
	mMenuSkill = Menu::create(mItemSkill, NULL);
	mMenuSkill->setPosition(Point::ZERO);
	addChild(mMenuSkill, -100);

	//Add shadow
	mStencil = Sprite::create(stencil_file_name);
		mStencil->setPosition(Point::ZERO);
	mStencil->setVisible(false);
	addChild(mStencil);

	//Add CD sprite
	Sprite* progressSprite = Sprite::create(button_normal_name);
	mProgressTimer = ProgressTimer::create(progressSprite);
	mProgressTimer->setPosition(Point::ZERO);
	mProgressTimer->setVisible(false);
	addChild(mProgressTimer, 100);

	mCDTime = cdTime;
	return true;
}

void SkillButton::skillClickCallBack(Ref* obj)
{
	//Use skill here
	switch (m_SkillType){
	case JUMP:
		hero->actJump();
		break;
	case ATTACK:
		hero->setAttacking(true, 1);
		MapSwitcher::getInstance()->getCurMap()->getChildByTag(13)->addChild(Damage::create(this->hero, 0));
		break;
	default:
		break;
	}
	//CD start
	mItemSkill->setEnabled(false);
	mStencil->setVisible(true);

	mProgressTimer->setVisible(true);
	mProgressTimer->setType(ProgressTimer::Type::RADIAL);

	//CD action
	ActionInterval* action_progress_to = ProgressTo::create(mCDTime, 100);
	CallFunc* action_callback = CallFuncN::create(CC_CALLBACK_1(SkillButton::skillCoolDownCallBack, this));
	mProgressTimer->runAction(Sequence::create(action_progress_to, action_callback, NULL));
}

void SkillButton::skillCoolDownCallBack(Node* node)
{
	//CD over
	mStencil->setVisible(false);

	mProgressTimer->setVisible(false);

	//Skill become enable
	mItemSkill->setEnabled(true);
}

void SkillButton::setHero(Hero* h){
	this->hero = h;
}
void SkillButton::setSkill(Skill_type type){
	m_SkillType = type;
}
