#include "BloodView.h"  

BloodView::BloodView() 
	: m_progressBackground(NULL)
	, m_progressForeground(NULL)
	, m_totalProgress(0.0f)
	, m_currentProgress(0.0f)
	, m_scale(1.0f)
{

}
void BloodView::setBackgroundTexture(const char *pName)
{
	m_progressBackground = Sprite::create(pName);
	this->addChild(m_progressBackground);
}

void BloodView::setForegroundTexture(const char *pName)
{
	m_progressForeground = CCSprite::create(pName);
	m_progressForeground->setAnchorPoint(ccp(0.0f, 0.5f));
	m_progressForeground->setPosition(ccp(-m_progressForeground->getContentSize().width * 0.5f, 0));
	this->addChild(m_progressForeground);
}

void BloodView::setTotalProgress(float total)
{
	if (m_progressForeground == NULL) { return; }
	m_scale = m_progressForeground->getContentSize().width / total;
	m_totalProgress = total;
}

void BloodView::setCurrentProgress(float progress)
{
	if (m_progressForeground == NULL) { return; }
	if (progress < 0.0f) { progress = 0.0f; }
	if (progress > m_totalProgress) { progress = m_totalProgress; }
	m_currentProgress = progress;
	float rectWidth = progress * m_scale;
	const CCPoint from = m_progressForeground->getTextureRect().origin;
	const CCRect rect = CCRectMake(from.x, from.y, rectWidth, m_progressForeground->getContentSize().height);
	setForegroundTextureRect(rect);
}

void BloodView::setForegroundTextureRect(const CCRect &rect)
{
	m_progressForeground->setTextureRect(rect);
}

float BloodView::getCurrentProgress() const
{
	return m_currentProgress;
}

float BloodView::getTotalProgress() const
{
	return m_totalProgress;
}
//设置英雄的血条  
//以下代码加入到场景的init中
//m_pBloodView = new BloodView();
//m_pBloodView->setPosition(ccp(150, 450));
//m_pBloodView->setScale(1.5f);
//m_pBloodView->setBackgroundTexture("bloodbg.png");
//m_pBloodView->setForegroundTexture("blood.png");
//m_pBloodView->setTotalProgress(100.0f);
//m_pBloodView->setCurrentProgress(100.0f);
//CCSprite *Bloodframe = CCSprite::create("bloodframe.png");
//Bloodframe->setScale(0.7f);
//Bloodframe->setPosition(ccp(m_pBloodView->getPositionX(), m_pBloodView->getPositionY()));
//this->addChild(Bloodframe, 2);
//this->addChild(m_pBloodView, 2);
//
//schedule(schedule_selector(TestMap::Bloodupdate), 0.1f);  //血条刷新函数，每隔0.1秒
//void TestMap::Bloodupdate(float delta){
//	m_pBloodView->setCurrentProgress(m_pBloodView->getCurrentProgress() - 1);
//}