//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __CC_SCROLLING_MENU_H__
#define __CC_SCROLLING_MENU_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"
#include "cocos-ext.h"

class CCScrollingMenu : public cocos2d::CCMenu
{
public:
    CCScrollingMenu();
    virtual ~CCScrollingMenu();
    static CCScrollingMenu* create();
    virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent* event);
    virtual void registerWithTouchDispatcher();
protected:
    bool m_bMoved;
    cocos2d::CCPoint m_TouchPoint;
};

#endif // __CC_SCROLLING_MENU_H__
