//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __REGION_SELECT_H__
#define __REGION_SELECT_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"
#include "cocos-ext.h"

class RegionSelect : public cocos2d::CCLayer
{
public:
    virtual ~RegionSelect();
    RegionSelect();
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
    void backButtonTapped(CCObject*object);
    void oneBananaButtonTapped(CCObject*object);
    void TutorialButtonTapped(CCObject*object);
    void TikiButtonTapped(CCObject*object);
    void CityButtonTapped(CCObject*object);
    void NightButtonTapped(CCObject*object);
    void SpaceButtonTapped(CCObject*object);
    void TwentyTwelveButtonTapped(CCObject*object);
    void BonusButtonTapped(CCObject*object);
    void ComingSoonButtonTapped(CCObject*object);
private:
    cocos2d::extension::CCScrollView *m_Scrollview;
    static float m_fScrollViewOffset;
    void addName(cocos2d::CCNode * node,const char *name);
    void addMedals(cocos2d::CCNode * node,int regionID);
    bool addLock(cocos2d::CCNode * node,int regionID);
};

#endif // __REGION_SELECT_H__
