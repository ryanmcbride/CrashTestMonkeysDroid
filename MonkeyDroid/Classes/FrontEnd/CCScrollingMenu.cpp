//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "CCScrollingMenu.h"
#include "SimpleAudioEngine.h"
#include "MainMenu.h"
#include "cocos-ext.h"
#include "ScreenHelper.h"


using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;


CCScrollingMenu::CCScrollingMenu():
CCMenu()
{
}
CCScrollingMenu::~CCScrollingMenu()
{
}
CCScrollingMenu* CCScrollingMenu::create()
{
    CCScrollingMenu *pRet = new CCScrollingMenu();
    
    if (pRet && pRet->initWithArray(NULL))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}
bool CCScrollingMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    m_bMoved = false;
    m_TouchPoint = this->convertTouchToNodeSpace(touch);
    return CCMenu::ccTouchBegan(touch, event);
}
void CCScrollingMenu::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    CC_UNUSED_PARAM(event);
    CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchMoved] -- invalid state");
    
    CCPoint newPoint     = this->convertTouchToNodeSpace(touch);
    CCPoint moveDistance = ccpSub(newPoint, m_TouchPoint);
    if(ccpLength(moveDistance)>5)
    {
        m_pSelectedItem->unselected();
        m_bMoved = true;
    }
}
void CCScrollingMenu::ccTouchEnded(CCTouch *touch, CCEvent* event)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
    CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
    if (!m_bMoved && m_pSelectedItem)
    {
        m_bMoved = false;
        m_pSelectedItem->unselected();
        m_pSelectedItem->activate();
    }
    m_eState = kCCMenuStateWaiting;
}
void CCScrollingMenu::registerWithTouchDispatcher()
{
    CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    pDispatcher->addTargetedDelegate(this, 1, false);
}
